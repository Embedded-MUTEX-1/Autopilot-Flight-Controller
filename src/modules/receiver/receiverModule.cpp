//
// Created by lenny on 14/01/24.
//

#include "receiverModule.h"
#include "../../devices-interfaces/low-level/UartDevice.h"
#include "../../devices-interfaces/receiver/Receiver.h"
#include "../../resources/nodes.h"
#include "../../utils/utils.h"

void receiverTask(void *args) {
    UartDevice uart;
    Receiver receiver(uart);
    struct receiverData values;
    struct pidSetpoint setpoint;
    struct commanderState state;
    uint64_t timestamp = 0;

    uart.init(RECEIVER_UART_PORT, RECEIVER_UART_TX, RECEIVER_UART_RX, RECEIVER_UART_BAUD);
    if(receiver.init() != 0)
        while(1) { delay_milis(100); }

    while(1) {
        timestamp = get_ms_count();

        commanderStateNode.get(state);
        receiver.updateAndGetData(values);

        setpoint.roll = computeAngleFromChannel(values.chan[ROLL_CHAN]);
        setpoint.pitch = computeAngleFromChannel(values.chan[PITCH_CHAN]);
        setpoint.yawRate = computeYawRateFromChannel(values.chan[YAW_CHAN]);

        receiverNode.set(values);

        if(state.state == LEVEL)
            pidSetpointNode.set(setpoint);

        values.loopPeriod = get_ms_count() - timestamp;
        wait(values.loopPeriod, RECEIVER_LOOP_FREQ);
    }
}

float computeAngleFromChannel(uint16_t channel) {
    return map_((float)channel,  MIN_CHANNEL_VALUE, MAX_CHANNEL_VALUE, -MAX_ANGLE, MAX_ANGLE); // deg
}

float computeYawRateFromChannel(uint16_t channel) {
    return map_((float)channel,   MIN_CHANNEL_VALUE, MAX_CHANNEL_VALUE,   -MAX_ANGLE_RATE, MAX_ANGLE_RATE);   // deg/sec
}