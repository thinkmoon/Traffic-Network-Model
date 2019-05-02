//
// Created by chauncey on 18-3-1.
//

#ifndef TRAFFIC_NETWORK_MODEL_VEHICLE_H
#define TRAFFIC_NETWORK_MODEL_VEHICLE_H

#include "stdafx.h"

class Vehicle {
public:
    Vehicle(int nID, queue<int> route, float spec, double distance, int SiteRoadID) : m_nID(nID), fSpec(spec),
                                                                                      dDistance(distance),
                                                                                      m_nSiteRoadID(SiteRoadID) {
        this->queRoute = route;
    };

    void showself() {
        //ofstream out(DIR_RES"vehicle.txt");
        cout << BLACK;
        if (queRoute.empty()) {
            cout << "it[" << m_nID << "] is return";
            cout << "distance have " << dDistance << "m" << endl;
        } else {
            cout << "it[" << m_nID << "] is a Vehicle :";
            cout << " spec:" << fSpec;
            cout << " it's destination is ";
            auto r = this->queRoute;
            if (r.empty())
                return;
            cout << " To :" << r.back();
            cout << " it's site is :" << m_nSiteRoadID << " distance:" << dDistance;
            cout << " route:";
            while (!r.empty()) {
                cout << r.front() << " ";
                r.pop();
            }
            cout << endl;
        }
    }

public:
    long long int time = 0;
    // 表示该车能影响交通的权重和权值
    int weight = 100,value = 0;
    int m_nID, m_nSiteRoadID;
    double dDistance;
    float fSpec; //spec = ( 100 - congestion ) + ( 10 - rand(0,20))
    queue<int> queRoute;
    int siteArea[2],futureArea[2];
};


#endif //TRAFFIC_NETWORK_MODEL_VEHICLE_H
