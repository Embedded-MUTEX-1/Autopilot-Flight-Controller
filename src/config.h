//
// Created by lenny on 05/01/24.
//

#ifndef AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_CONFIG_H
#define AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_CONFIG_H

#define NUMBER_OF_MOTORS 4 // 4 or 6
#define NUMBER_OF_CHANNELS 14
#define ENABLE_MAG_CALIBRATION 1

#define THROTTLE_CHAN         2
#define ROLL_CHAN             0
#define PITCH_CHAN            1
#define YAW_CHAN              3

#define UDP_PORT 5000
#define WIFI_CONNECTING_TIMEOUT 10000 // 10 sec
#define WIFI_AP_SSID   "Autopilot Drone"
#define WIFI_AP_PASSWD "12345678"

#define SCL_PIN 22
#define SDA_PIN 21

#define ATTITUDE_LOOP_FREQ   250 // Hz
#define PID_LOOP_FREQ        250 // Hz
#define MOTORS_LOOP_FREQ     250 // Hz
#define ALTITUDE_LOOP_FREQ   100 // Hz
#define POSITION_LOOP_FREQ    10 // Hz
#define COMMANDER_LOOP_FREQ   50 // Hz
#define RECEIVER_LOOP_FREQ   100 // Hz
#define TELEMETRY_LOOP_FREQ   25 // Hz

#define MAGNETIC_DECLINATION  1 // deg

#endif //AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_CONFIG_H
