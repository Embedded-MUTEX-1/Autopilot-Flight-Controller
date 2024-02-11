#include "controllerModule.h"
#include "../../resources/nodes.h"
#include "../../utils/utils.h"
#include "../../../lib/QuickPID/src/QuickPID.h"

void controllerTask(void *args) {
    struct pidOutput values;
    struct commanderState state;
    struct attitudeData attitudeValues;
    struct altitudeData altitudeValues;
    struct pidSetpoint anglesSetpoint;
    struct receiverData receiverValues;
    
    QuickPID rateRollPid;
    QuickPID ratePitchPid;
    QuickPID rateYawPid;

    uint64_t timestamp = 0;
    float offsetYaw = 0;
    float yawRateSetpoint, rollRateSetpoint, pitchRateSetpoint;

    rateRollPid.SetSampleTimeUs((1 / PID_LOOP_FREQ) * 1000);
    ratePitchPid.SetSampleTimeUs((1 / PID_LOOP_FREQ) * 1000);
    rateYawPid.SetSampleTimeUs((1 / PID_LOOP_FREQ) * 1000);

    rateRollPid.SetOutputLimits(-MAX_ANGLE_RATE, MAX_ANGLE_RATE);
    ratePitchPid.SetOutputLimits(-MAX_ANGLE_RATE, MAX_ANGLE_RATE);
    rateYawPid.SetOutputLimits(-MAX_ANGLE_RATE, MAX_ANGLE_RATE);

    while (1)
    {
        timestamp = get_ms_count();

        pidSetpointNode.get(anglesSetpoint);
        commanderStateNode.get(state);
        attitudeNode.get(attitudeValues);
        altitudeNode.get(altitudeValues);
        receiverNode.get(receiverValues);

        rollRateSetpoint = (anglesSetpoint.roll  - attitudeValues.roll)  * 5.0f;
        pitchRateSetpoint = (anglesSetpoint.pitch - attitudeValues.pitch) * 5.0f;

        if(state.state == LEVEL) {
            if(receiverValues.chan[YAW_CHAN] < MAX_YAW_CHAN_THRESHOLD && receiverValues.chan[YAW_CHAN] > MIN_YAW_CHAN_THRESHOLD) {
                attitudeValues.yaw -= offsetYaw;
                yawRateSetpoint = (0 - attitudeValues.yaw) * 5.0f;
            } else {
                offsetYaw = attitudeValues.yaw;
                yawRateSetpoint = anglesSetpoint.yawRate;
            }
        } else if(state.state == NAVIGATION || state.state == POS_HOLD) {
            yawRateSetpoint = (0 - attitudeValues.yaw) * 5.0f;
        } else if(state.state == DISARMED) {
            rateRollPid.Reset();
            ratePitchPid.Reset();
            rateYawPid.Reset();
        }

        values.out_roll  = rateRollPid.Compute(rollRateSetpoint, attitudeValues.gyroRateRoll);
        values.out_pitch = ratePitchPid.Compute(pitchRateSetpoint, attitudeValues.gyroRatePitch);
        values.out_yaw   = rateYawPid.Compute(yawRateSetpoint, attitudeValues.gyroRateYaw);

        pidOutputNode.set(values);

        values.loopPeriod = get_ms_count() - timestamp;
        wait(values.loopPeriod, PID_LOOP_FREQ);
    }
    
}