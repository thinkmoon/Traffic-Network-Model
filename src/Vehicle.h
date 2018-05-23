//
// Created by chauncey on 18-3-1.
//

#ifndef TRAFFIC_NETWORK_MODEL_VEHICLE_H
#define TRAFFIC_NETWORK_MODEL_VEHICLE_H

#include "stdafx.h"

class Vehicle {
public:
    Vehicle(int nID,queue<int> route, float spec, double distance) : m_nID(nID),fSpec(spec), dDistance(distance) {
        this->queRoute = route;
    };

    void showself() {
        //ofstream out(DIR_RES"vehicle.txt");
        if (queRoute.empty()) {
            cout << "it[" << m_nID << "] is return" ;
            cout << "distance have " << dDistance << "m" << endl;
        } else {
            cout << "it[" << m_nID << "] is a Vehicle :";
            cout << " spec:" << fSpec;
            cout << " it's destination is ";
            auto r = this->queRoute;
            if (r.empty())
                return;
            cout << " To :" << r.back() ;
            cout << " it's site is :" << queRoute.front() << " distance:" << dDistance;
            cout <<  " route:";
            while (!r.empty()) {
                cout << r.front() << " ";
                r.pop();
            }
            cout << endl;
        }
    }

public:
    long long int time=0;
    int m_nID;
    double dDistance;
    float fSpec; //spec = ( 100 - congestion ) + ( 10 - rand(0,20))
    queue<int> queRoute;
};


#endif //TRAFFIC_NETWORK_MODEL_VEHICLE_H
