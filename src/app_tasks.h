#ifndef AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_TASKS_H
#define AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_TASKS_H

void receiverTask(void *args);
void sensorsTask(void *args);
void navigationTask(void *args);
void commanderTask(void *args);
void controllerTask(void *args);
void motorsTask(void *args);
void telemetryTask(void *args);

#endif