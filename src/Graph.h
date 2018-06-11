//
// Created by chauncey on 18-2-7.
//
#ifndef TRAFFIC_NETWORK_MODEL_GRAPH_H
#define TRAFFIC_NETWORK_MODEL_GRAPH_H

#include "stdafx.h"
#include "Road.h"
#include "Point.h"
#include "TrafficLight.h"

/**
 *  The road node
 */
class RoadNode {
public:
    RoadNode(int junctionID, double length, int roadID) : junctionID(junctionID), length(length), roadID(roadID),
                                                          link(nullptr) {};
    void addNode(int m_ID, double m_length, int roadID);
public:
    int junctionID, roadID;
    double length;
    RoadNode *link;
    TrafficLight m_CTrafficLight_Light;
};

/**
 * the traffic Graph
 */
class Graph {
public:
    vector<Road> road;
    vector<Point> point;
    vector<RoadNode> RoadTable;

    void show();
    void showPoint();
    void showRoad();
    /**
     * show the traffic network table
     * @param num  Out of degree's num
     */
    void showRoadTable(int num);
    int getRoadID(int PointFromID, int PointToID);
};

#endif //TRAFFIC_NETWORK_MODEL_GRAPH_H
