//
// Created by lenny on 14/01/24.
//

#ifndef AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_NODES_H
#define AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_NODES_H

#include "PropertyNode.h"
#include "../structs.h"

extern PropertyNode<struct attitudeData> attitudeNode;
extern PropertyNode<struct attitudeConfig> attitudeConfigNode;

extern PropertyNode<struct altitudeData> altitudeNode;

extern PropertyNode<struct positionData> positionNode;
extern PropertyNode<struct receiverData> receiverNode;

extern PropertyNode<struct pidSetpoint> pidSetpointNode;
extern PropertyNode<struct pidOutput> pidOutputNode;

extern PropertyNode<struct pidConfig> pidConfigNode;
extern PropertyNode<struct pidNavigationConfig> pidNavConfigNode;
extern PropertyNode<struct pidAltitudeConfig> pidAltConfigNode;
extern PropertyNode<struct motorsSetpoint> motorsConfigNode;
extern PropertyNode<struct navigationSetpoint> navigationSetpointNode;

extern PropertyNode<struct motorsData> motorsNode;
extern PropertyNode<struct commanderState> commanderStateNode;
extern PropertyNode<struct commanderState> commanderStateConfNode;

#endif //AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_NODES_H
