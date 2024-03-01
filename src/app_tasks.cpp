#include "app_tasks.h"
#include "modules/attitude/AttitudeModule.h"
#include "modules/motors/MotorsModule.h"
#include "modules/navigation/NavigationModule.h"
#include "modules/receiver/ReceiverModule.h"
#include "modules/telemetry/TelemetryModule.h"
#include "modules/commander/CommanderModule.h"
#include "modules/controller/ControllerModule.h"
#include "modules/altitude/AltitudeModule.h"

void receiverTask(void *args) {
    ReceiverModule module;
    module.init();
    while(true) {
        module.run();
    }
}

void attitudeTask(void *args) {
    AttitudeModule module;
    module.init();
    while(true) {
        module.run();
    }
}

void altitudeTask(void *args) {
    AltitudeModule module;
    module.init();
    while(true) {
        module.run();
    }
}

void navigationTask(void *args) {
    NavigationModule module;
    module.init();
    while(true) {
        module.run();
    }
}

void commanderTask(void *args) {
    CommanderModule module;
    while(true) {
        module.run();
    }
}

void controllerTask(void *args) {
    ControllerModule module;
    module.init();
    while(true) {
        module.run();
    }
}

void motorsTask(void *args) {
    MotorsModule module;
    module.init();
    while(true) {
        module.run();
    }
}

void telemetryTask(void *args) {
    TelemetryModule module;
    module.init();
    while(true) {
        module.run();
    }
}