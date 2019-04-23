//
// Created by chauncey on 18-2-7.
//
#ifndef TRAFFIC_NETWORK_MODEL_GRAPH_H
#define TRAFFIC_NETWORK_MODEL_GRAPH_H

#include "stdafx.h"
#include "TrafficLight.h"
#include "Road.h"

/**
 * the traffic Graph
 */
class Graph {
public:
    void output();
public:
    // 道路容器
    vector<Road> m_Road_v;
    // 路口容器
    vector<CrossRoad> m_CrossRoad_v;

//    int getRoadID(int PointFromID, int PointToID);
};

#endif //TRAFFIC_NETWORK_MODEL_GRAPH_H
