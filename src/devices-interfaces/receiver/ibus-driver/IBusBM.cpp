/*
 * Interface to the RC IBus protocol
 * 
 * Based on original work from: https://gitlab.com/timwilkinson/FlySkyIBus
 * Extended to also handle sensors/telemetry data to be sent back to the transmitter,
 * interrupts driven and other features.
 *
 * This lib requires a hardware UART for communication
 * Another version using software serial is here https://github.com/Hrastovc/iBUStelemetry
 * 
 * Explaination of sensor/ telemetry prtocol here: 
 * https://github.com/betaflight/betaflight/wiki/Single-wire-FlySky-(IBus)-telemetry
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public 
 * License as published by the Free Software Foundation; either  
 * version 2.1 of the License, or (at your option) any later version.
 *   
 * Created 12 March 2019 Bart Mellink
 * Updated 4 April 2019 to support ESP32
 * updated 13 jun 2019 to support STM32 (pauluzs)
 * Updated 21 Jul 2020 to support MBED (David Peverley) 
 */

#include "IBusBM.h"
#include "../../../utils/utils.h"

// pointer to the first class instance to be used to call the loop() method from timer interrupt
// will be initiated by class constructor, then daisy channed to other class instances if we have more than one
IBusBM* IBusBMfirst = NULL;


// Interrupt on timer0 - called every 1 ms
// we call the IBusSensor.loop() here, so we are certain we respond to sensor requests in a timely matter
#ifdef ARDUINO_ARCH_AVR
SIGNAL(TIMER0_COMPA_vect) {
  if (IBusBMfirst) IBusBMfirst->loop();  // gets new servo values if available and process any sensor data
}
#elif defined _VARIANT_ARDUINO_STM32_
void  onTimer(stimer_t *htim) {
  if (IBusBMfirst) IBusBMfirst->loop();  // gets new servo values if available and process any sensor data
}
#else
void  onTimer() {
  if (IBusBMfirst) IBusBMfirst->loop();  // gets new servo values if available and process any sensor data
}
#endif


#if defined(ARDUINO_ARCH_MBED)
extern "C" {
  void TIMER4_IRQHandler_v() {
    if (NRF_TIMER4->EVENTS_COMPARE[0] == 1) {   
        onTimer();
        NRF_TIMER4->EVENTS_COMPARE[0] = 0;
    }
  }
}
#endif


/*
 *  supports max 14 channels in this lib (with messagelength of 0x20 there is room for 14 channels)

  Example set of bytes coming over the iBUS line for setting servos: 
    20 40 DB 5 DC 5 54 5 DC 5 E8 3 D0 7 D2 5 E8 3 DC 5 DC 5 DC 5 DC 5 DC 5 DC 5 DA F3
  Explanation
    Protocol length: 20
    Command code: 40 
    Channel 0: DB 5  -> value 0x5DB
    Channel 1: DC 5  -> value 0x5Dc
    Channel 2: 54 5  -> value 0x554
    Channel 3: DC 5  -> value 0x5DC
    Channel 4: E8 3  -> value 0x3E8
    Channel 5: D0 7  -> value 0x7D0
    Channel 6: D2 5  -> value 0x5D2
    Channel 7: E8 3  -> value 0x3E8
    Channel 8: DC 5  -> value 0x5DC
    Channel 9: DC 5  -> value 0x5DC
    Channel 10: DC 5 -> value 0x5DC
    Channel 11: DC 5 -> value 0x5DC
    Channel 12: DC 5 -> value 0x5DC
    Channel 13: DC 5 -> value 0x5DC
    Checksum: DA F3 -> calculated by adding up all previous bytes, total must be FFFF
 */

void IBusBM::begin(int8_t timerid, int8_t rxPin, int8_t txPin) {
  this->state = DISCARD;
  this->last = get_ms_count();
  this->ptr = 0;
  this->len = 0;
  this->chksum = 0;
  this->lchksum = 0;

  // we need to process the iBUS sensor protocol handler frequently enough (at least once each ms) to ensure the response data
  // from the sensor is sent on time to the receiver
  // if timerid==IBUSBM_NOTIMER the user is responsible for calling the loop function
  this->IBusBMnext = IBusBMfirst;

  IBusBMfirst = this; 
}

// called from timer interrupt or mannually by user (if IBUSBM_NOTIMER set in begin())
void IBusBM::loop(void) {

  // if we have multiple instances of IBusBM, we (recursively) call the other instances loop() function
  if (IBusBMnext) IBusBMnext->loop(); 

  // only process data already in our UART receive buffer 
  while (stream->numBytesAvailable() == true) {
    // only consider a new data package if we have not heard anything for >3ms
    uint32_t now = get_ms_count();
    if (now - last >= PROTOCOL_TIMEGAP){
      state = GET_LENGTH;
    }
    last = now;
    
    uint8_t v = 0;
    v = stream->readByte();

    switch (state) {
      case GET_LENGTH:
        if (v <= PROTOCOL_LENGTH && v > PROTOCOL_OVERHEAD) {
          ptr = 0;
          len = v - PROTOCOL_OVERHEAD;
          chksum = 0xFFFF - v;
          state = GET_DATA;
        } else {
          state = DISCARD;
        }
        break;

      case GET_DATA:
        buffer[ptr++] = v;
        chksum -= v;
        if (ptr == len) {
          state = GET_CHKSUML;
        }
        break;
        
      case GET_CHKSUML:
        lchksum = v;
        state = GET_CHKSUMH;
        break;

      case GET_CHKSUMH:
        // Validate checksum
        if (chksum == (v << 8) + lchksum) {
          // Checksum is all fine Execute command - 
          uint8_t adr = buffer[0] & 0x0f;
          if (buffer[0]==PROTOCOL_COMMAND40) {
            // Valid servo command received - extract channel data
            for (uint8_t i = 1; i < PROTOCOL_CHANNELS * 2 + 1; i += 2) {
              channel[i / 2] = buffer[i] | (buffer[i + 1] << 8);
            }
            cnt_rec++;
          } 
        }
        state = DISCARD;
        break;

      case DISCARD:
      default:
        break;
    }
  }
}

uint16_t IBusBM::readChannel(uint8_t channelNr) {
  if (channelNr < PROTOCOL_CHANNELS) {
    return channel[channelNr];
  } else {
    return 0;
  }
}

uint8_t IBusBM::addSensor(uint8_t type, uint8_t len) {
  // add a sensor, return sensor number
  if (len!=2 && len!=4) len = 2;
  if (NumberSensors < SENSORMAX) {
    sensorinfo *s = &sensors[NumberSensors];
    s->sensorType = type;
    s->sensorLength = len;
    s->sensorValue = 0;
    NumberSensors++;
  }
  return NumberSensors;
}

void IBusBM::setSensorMeasurement(uint8_t adr, int32_t value) {
   if (adr<=NumberSensors && adr>0)
     sensors[adr-1].sensorValue = value;
}

int8_t IBusBM::init() {
    begin();
    return 0;
}

int8_t IBusBM::deinit() {
    return 0;
}

size_t IBusBM::update() {
    this->loop();
    return 0;
}

IBusBM::IBusBM(UartDevice &serial) {
    this->stream = &serial;
}

IBusBM::~IBusBM() {
    deinit();
}
