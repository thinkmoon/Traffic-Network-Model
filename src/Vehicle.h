//
// Created by chauncey on 18-3-1.
//

#ifndef TRAFFIC_NETWORK_MODEL_VEHICLE_H
#define TRAFFIC_NETWORK_MODEL_VEHICLE_H

#include "stdafx.h"

class Vehicle {
public:
    int nSiteRoad, nDirectionRoad;
    double dDistance;
    float fSpec;
    queue<int> queRoute;
};


#endif //TRAFFIC_NETWORK_MODEL_VEHICLE_H
