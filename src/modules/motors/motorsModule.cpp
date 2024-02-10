//
// Created by lenny on 28/01/24.
//

#include "motorsModule.h"
#include "../../devices-interfaces/motors/Motors.h"
#include "../../devices-interfaces/low-level/AdcDevice.h"
#include "../../resources/nodes.h"
#include "../../utils/utils.h"
#include "../../config.h"

void motorsTask(void *args) {
    Motors motors;
    AdcDevice vBatPin;
    struct pidOutput pidValues;
    struct commanderState state;
    struct motorsSetpoint setpoint;
    struct receiverData receiverValues;
    struct motorsData values;
    uint64_t timestamp = 0;

    if(motors.init() != 0)
        while(1) { delay_milis(100); }
        
    vBatPin.init();
    vBatPin.initPin(VBAT_PIN);

    while(1) {
        timestamp = get_ms_count();

        pidOutputNode.get(pidValues);
        commanderStateNode.get(state);
        receiverNode.get(receiverValues);

        values.vBat = vBatPin.getValue(VBAT_PIN) * (3.1f / 4095);

#if NUMBER_OF_MOTORS == 4
        setpoint.mot[0] = receiverValues.chan[THROTTLE_CHAN] + pidValues.out_roll - pidValues.out_pitch - pidValues.out_yaw + pidValues.out_alt;
        setpoint.mot[1] = receiverValues.chan[THROTTLE_CHAN] - pidValues.out_roll - pidValues.out_pitch + pidValues.out_yaw + pidValues.out_alt;
        setpoint.mot[2] = receiverValues.chan[THROTTLE_CHAN] + pidValues.out_roll + pidValues.out_pitch + pidValues.out_yaw + pidValues.out_alt;
        setpoint.mot[3] = receiverValues.chan[THROTTLE_CHAN] - pidValues.out_roll + pidValues.out_pitch - pidValues.out_yaw + pidValues.out_alt;
#else //NUMBER_OF_MOTORS == 6
        setpoint.mot[0] = receiverValues.chan[THROTTLE_CHAN] + int16_t(pidValues.out_roll != 0 ? pidValues.out_roll * COEFF_ROLL_LEFT_RIGHT : 0)                                                                                    + int16_t(pidValues.out_yaw != 0 ? pidValues.out_yaw * C_YAW : 0) + pidValues.out_alt;
        setpoint.mot[1] = receiverValues.chan[THROTTLE_CHAN] + int16_t(pidValues.out_roll != 0 ? pidValues.out_roll * COEFF_ROLL_FRONT_REAR : 0) - int16_t(pidValues.out_pitch != 0 ? pidValues.out_pitch * C_PITCH_FRONT_REAR : 0) - int16_t(pidValues.out_yaw != 0 ? pidValues.out_yaw * C_YAW : 0) + pidValues.out_alt;
        setpoint.mot[2] = receiverValues.chan[THROTTLE_CHAN] - int16_t(pidValues.out_roll != 0 ? pidValues.out_roll * COEFF_ROLL_FRONT_REAR : 0) - int16_t(pidValues.out_pitch != 0 ? pidValues.out_pitch * C_PITCH_FRONT_REAR : 0) + int16_t(pidValues.out_yaw != 0 ? pidValues.out_yaw * C_YAW : 0) + pidValues.out_alt;
        setpoint.mot[3] = receiverValues.chan[THROTTLE_CHAN] - int16_t(pidValues.out_roll != 0 ? pidValues.out_roll * COEFF_ROLL_LEFT_RIGHT : 0)                                                                                    - int16_t(pidValues.out_yaw != 0 ? pidValues.out_yaw * C_YAW : 0) + pidValues.out_alt;
        setpoint.mot[4] = receiverValues.chan[THROTTLE_CHAN] - int16_t(pidValues.out_roll != 0 ? pidValues.out_roll * COEFF_ROLL_FRONT_REAR : 0) + int16_t(pidValues.out_pitch != 0 ? pidValues.out_pitch * C_PITCH_FRONT_REAR : 0) + int16_t(pidValues.out_yaw != 0 ? pidValues.out_yaw * C_YAW : 0) + pidValues.out_alt;
        setpoint.mot[5] = receiverValues.chan[THROTTLE_CHAN] + int16_t(pidValues.out_roll != 0 ? pidValues.out_roll * COEFF_ROLL_FRONT_REAR : 0) + int16_t(pidValues.out_pitch != 0 ? pidValues.out_pitch * C_PITCH_FRONT_REAR : 0) - int16_t(pidValues.out_yaw != 0 ? pidValues.out_yaw * C_YAW : 0) + pidValues.out_alt;
#endif

        if(state.state == MANU) {
            motorsConfigNode.get(setpoint);
        } else if(state.state == DISARMED) {
            for (int i = 0; i < NUMBER_OF_MOTORS; i++)
                setpoint.mot[i] = MIN_THROTTLE_VALUE;
        }

        motors.setMotors(setpoint);

        for (int i = 0; i < NUMBER_OF_MOTORS; i++)
            values.mot[i] = setpoint.mot[i];

        motorsNode.set(values);

        values.loopPeriod = get_ms_count() - timestamp;
        wait(values.loopPeriod, MOTORS_LOOP_FREQ);
    }
}