//
// Created by lenny on 14/01/24.
//

#include "ReceiverModule.h"

float computeAngleFromChannel(uint16_t channel) {
    return map_((float)channel,  MIN_CHANNEL_VALUE, MAX_CHANNEL_VALUE, -MAX_ANGLE, MAX_ANGLE); // deg
}

float computeYawRateFromChannel(uint16_t channel) {
    return map_((float)channel,   MIN_CHANNEL_VALUE, MAX_CHANNEL_VALUE,   -MAX_ANGLE_RATE, MAX_ANGLE_RATE);   // deg/sec
}

ReceiverModule::ReceiverModule() {

}

int8_t ReceiverModule::init()
{
    return receiver.init();
}

void ReceiverModule::run()
{
    timestamp = get_ms_count();

    getDataFromNodesAndReceiver();

    setpoint.roll = computeAngleFromChannel(values.chan[ROLL_CHAN]);
    setpoint.pitch = computeAngleFromChannel(values.chan[PITCH_CHAN]);
    setpoint.yawRate = computeYawRateFromChannel(values.chan[YAW_CHAN]);

    setDataToNodes();

    values.loopPeriod = get_ms_count() - timestamp;
    wait(values.loopPeriod, RECEIVER_LOOP_FREQ);
}

void ReceiverModule::getDataFromNodesAndReceiver()
{
    commanderStateNode.get(state);
    receiver.updateAndGetData(values);
}

float ReceiverModule::computeAngleFromChannel(uint16_t channel)
{
    return map_((float)channel,  MIN_CHANNEL_VALUE, MAX_CHANNEL_VALUE, -MAX_ANGLE, MAX_ANGLE); // deg
}

float ReceiverModule::computeYawRateFromChannel(uint16_t channel)
{
    return map_((float)channel,   MIN_CHANNEL_VALUE, MAX_CHANNEL_VALUE,   -MAX_ANGLE_RATE, MAX_ANGLE_RATE);   // deg/sec
}

void ReceiverModule::setDataToNodes()
{
    receiverNode.set(values);
    if(state.state == LEVEL)
        pidSetpointNode.set(setpoint);
}


