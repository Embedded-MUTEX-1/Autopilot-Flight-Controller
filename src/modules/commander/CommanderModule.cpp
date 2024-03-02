#include "CommanderModule.h"

CommanderModule::CommanderModule() {

}

void CommanderModule::run() {
    timestamp = get_ms_count();

    getDataFromNodes();
    processState();

    commanderStateNode.set(state);

    loopPeriod = get_ms_count() - timestamp;
    wait(loopPeriod, COMMANDER_LOOP_FREQ);
}

void CommanderModule::getDataFromNodes() {
    commanderStateConfNode.get(stateFromTelemetry);
    receiverNode.get(receiverValues);
}

void CommanderModule::processState() {
    if(receiverValues.chan[THROTTLE_CHAN] < MIN_THROTTLE_THRESOLD || receiverValues.chan[DISARMED_CHAN] >= MAX_CHANNEL_VALUE || stateFromTelemetry.state == DISARMED) {
        state.state = DISARMED;
    } else if(stateFromTelemetry.state == MANU) {
        state.state = MANU;
    } else if(
            receiverValues.chan[ROLL_CHAN] > MAX_CHANNEL_THRESOLD || receiverValues.chan[ROLL_CHAN] < MIN_CHANNEL_THRESOLD
            || receiverValues.chan[PITCH_CHAN] > MAX_CHANNEL_THRESOLD || receiverValues.chan[PITCH_CHAN] < MIN_CHANNEL_THRESOLD
            ) {
        state.state = LEVEL;
    } else if(receiverValues.chan[MODE_SELECTION_CHAN] == POS_HOLD_CHAN_5_VALUE) {
        state.state = POS_HOLD; //TODO Test purpose
    } else {
        state.state = LEVEL; //TODO Test purpose
    }
}
