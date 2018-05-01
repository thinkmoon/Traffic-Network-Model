//
// Created by chauncey on 18-3-1.
//

#ifndef TRAFFIC_NETWORK_MODEL_ROAD_H
#define TRAFFIC_NETWORK_MODEL_ROAD_H

#include "stdafx.h"
#include "Point.h"
#include "Vehicle.h"

/**
 * 节点道路类
 */
class Road {
public:
    Road(Point CPoint_from, Point CPoint_to, double dLength) : m_CPoint_from(CPoint_from), m_CPoint_to(CPoint_from),
                                                               m_dLength(dLength) {};

    void showqueVehicle() {
        cout << " pos Vehicle" << endl;
        cout << this->m_queVehicle_pos.size();
        cout << " neg Vehicle" << endl;
        cout << this->m_queVehicle_neg.size();
    }
public:
    double m_dLength;
    Point m_CPoint_from, m_CPoint_to;
    int m_nCongestion_pos, m_nCongestion_neg; //(50 * car / length),[0,100]
    deque<Vehicle> m_queVehicle_pos, m_queVehicle_neg;
};


#endif //TRAFFIC_NETWORK_MODEL_ROAD_H
