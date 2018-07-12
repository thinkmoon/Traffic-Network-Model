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
    Road(Point CPoint_from, Point CPoint_to, double dLength, int roadID, int ParallelRoadID) : m_CPoint_from(
            CPoint_from), m_CPoint_to(CPoint_from),
                                                                                               m_dLength(dLength),
                                                                                               roadID(roadID),
                                                                                               ParallelRoadID(
                                                                                                       ParallelRoadID) {};

    /**
     * 获取拥挤度
     * @return 返回拥挤值
     */
    int get_Congestion();
public:
    int roadID, ParallelRoadID, m_nTrafficLightSite;
    double m_dLength;
    Point m_CPoint_from, m_CPoint_to;
    int m_nCongestion; //(50 * car / length),[0,100] 拥挤度
    deque<Vehicle> m_queVehicle;
};


#endif //TRAFFIC_NETWORK_MODEL_ROAD_H
