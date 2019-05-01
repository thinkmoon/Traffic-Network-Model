//
// Created by chauncey on 18-9-11.
//

#ifndef TRAFFIC_NETWORK_MODEL_CROSSROAD_H
#define TRAFFIC_NETWORK_MODEL_CROSSROAD_H

#include "stdafx.h"
#include "TrafficLight.h"

//一条方向道路节点
class Node{
public:
    Node(int outRoad,int inRoad) : outRoadID(outRoad),inRoadID(inRoad){};
    int outRoadID;
    int inRoadID;
};
/**
*  路口类，记录着该路口的点坐标，以及其相连的方向道路节点组
 *               |           |
 *               |     |     |
 *               |  1     2  |
 *               |     |     |
 *        --------           --------
 *           3                  5
 *        - - - -            - - - -
 *           4                  6
 *        --------           --------
 *               |     |     |
 *               |  7     8  |
 *               |     |     |
 *               |           |
 *    如上图(1,2), (3,4), (5,6), (7,8)在同一个方向,我将其称为四组方向道路节点Node.
 *    其中,Node.inRoadID=1, Node.outRoadID=2;
 *         Node.inRoadID=4, Node.outRoadID=3;
 *         ...
 *         根据车辆靠右行原则以此类推.
*/
class CrossRoad {
public:
    CrossRoad(double fLon,double fLat) : m_fLat(fLat),m_fLon(fLon){};
    /**
     * 重载运算符 （==） 判断两个路口是否为同一个
     */
    bool operator==(CrossRoad &crossRoad);
    /**
     * 添加方向道路节点组
     * @param outRoadID 出度道路ID,对应注释图中的2号路
     * @param inRoadID 入度道路ID,对应注释图中的1号路
     */
    void addNode(int outRoadID,int inRoadID);
public:
    //唯一标示符
    int m_nID;
    //经纬度的定义
    double m_fLon, m_fLat;
    // 与该路口相连的道路
    vector<Node> JunctionRoad;
    //该路口的交通灯
    TrafficLight m_CTrafficLight_Light;
    int row=0,col=0;
};



#endif //TRAFFIC_NETWORK_MODEL_CROSSROAD_H
