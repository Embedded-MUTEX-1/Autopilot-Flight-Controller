//
// Created by lenny on 14/01/24.
//

#include "nodes.h"

PropertyNode<struct attitudeData> attitudeNode;
PropertyNode<struct attitudeConfig> attitudeConfigNode;

PropertyNode<struct positionData> positionNode;

PropertyNode<struct imuSetpoint> imuSetpointNode;
PropertyNode<struct pidOutput> pidOutputNode;

PropertyNode<struct pidConfig> pidConfigNode;
PropertyNode<struct pidNavigationConfig> pidNavConfigNode;
PropertyNode<struct pidAltitudeConfig> pidAltConfigNode;
PropertyNode<struct motorsConfig> motorsConfigNode;

PropertyNode<struct motorsData> motorsNode;
PropertyNode<struct commanderState> stateNode;
