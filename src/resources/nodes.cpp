//
// Created by lenny on 14/01/24.
//

#include "nodes.h"

PropertyNode<struct attitudeData> attitudeNode;
PropertyNode<struct attitudeConfig> attitudeConfigNode;

PropertyNode<struct positionData> positionNode;
PropertyNode<struct altitudeData> altitudeNode;

PropertyNode<struct receiverData> receiverNode;

PropertyNode<struct pidSetpoint> pidSetpointNode;
PropertyNode<struct pidOutput> pidOutputNode;

PropertyNode<struct pidConfig> pidConfigNode;
PropertyNode<struct pidNavigationConfig> pidNavConfigNode;
PropertyNode<struct pidAltitudeConfig> pidAltConfigNode;
PropertyNode<struct motorsSetpoint> motorsConfigNode;
PropertyNode<struct navigationSetpoint> navigationSetpointNode;

PropertyNode<struct motorsData> motorsNode;
PropertyNode<struct commanderState> commanderStateNode;
PropertyNode<struct commanderState> commanderStateConfNode;
