//
// Created by chauncey on 18-3-1.
//

#ifndef TRAFFIC_NETWORK_MODEL_VEHICLE_H
#define TRAFFIC_NETWORK_MODEL_VEHICLE_H

#include "stdafx.h"

class Vehicle {
public:
    Vehicle(queue<int> route, float spec, double distance) : fSpec(spec), dDistance(distance) {
        this->queRoute = route;
    };

    void showself() {
        ofstream out(DIR_RES"vehicle.txt");
        if (queRoute.empty()) {
            out << "it is return" << endl;
        } else {
            out << " This is a Vehicle :";
            out << " it's site is :" << queRoute.front() << endl << " distance:" << dDistance << endl;
            out << " spec:" << fSpec << endl;
            out << " it's destination is ";
            auto r = this->queRoute;
            if (r.empty())
                return;
            out << " To :" << r.back() << endl << " route:";
            while (!r.empty()) {
                out << r.front() << " ";
                r.pop();
            }
            out << endl;
        }
    }

public:

    double dDistance;
    float fSpec; //spec = ( 100 - congestion ) + ( 10 - rand(0,20))
    queue<int> queRoute;
};


#endif //TRAFFIC_NETWORK_MODEL_VEHICLE_H
