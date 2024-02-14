#include "commanderModule.h"
#include "../../resources/nodes.h"
#include "../../utils/utils.h"

void commanderTask(void *args) {
    struct commanderState state;
    struct commanderState stateFromTelemetry;
    struct receiverData receiverValues;

    uint64_t timestamp(0), loopPeriod(0);

    state.state = DISARMED;

    while (1)
    {
        timestamp = get_ms_count();

        commanderStateConfNode.get(stateFromTelemetry);
        receiverNode.get(receiverValues);

        if(stateFromTelemetry.state == MANU) {
            state.state = MANU;
        } else if(receiverValues.chan[THROTTLE_CHAN] < MIN_THROTTLE_THRESOLD || receiverValues.chan[DISARMED_CHAN] >= MAX_CHANNEL_VALUE || stateFromTelemetry.state == DISARMED) {
            state.state = DISARMED;
        } else if(
            receiverValues.chan[ROLL_CHAN] > MAX_CHANNEL_THRESOLD || receiverValues.chan[ROLL_CHAN] < MIN_CHANNEL_THRESOLD
            || receiverValues.chan[PITCH_CHAN] > MAX_CHANNEL_THRESOLD || receiverValues.chan[PITCH_CHAN] < MIN_CHANNEL_THRESOLD
        ) {
            state.state = LEVEL;
        } else if(receiverValues.chan[NAVIGATION_CHAN] >= MAX_CHANNEL_VALUE) {
            state.state = POS_HOLD; //TODO Test purpose
        } else {
            state.state = LEVEL; //TODO Test purpose
        }

        commanderStateNode.set(state);

        loopPeriod = get_ms_count() - timestamp;
        wait(loopPeriod, COMMANDER_LOOP_FREQ);
    }
}