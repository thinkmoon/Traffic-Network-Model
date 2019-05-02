//
// Created by chauncey on 18-3-1.
//

#ifndef TRAFFIC_NETWORK_MODEL_ROAD_H
#define TRAFFIC_NETWORK_MODEL_ROAD_H

#include "stdafx.h"
#include "Vehicle.h"
#include "CrossRoad.h"
/**
 * 节点道路类
 */
class Road {
public:
    /**
     * 构造函数，初始化下列参数
     * @param nID
     * @param CrossRoadFromSite
     * @param CrossRoadToSite
     * @param dLength
     */
    Road(int nID, int CrossRoadFromSite, int CrossRoadToSite, double dLength):m_nID(nID),m_CrossRoadFromSite(CrossRoadFromSite),m_CrossRoadToSite(CrossRoadToSite),m_dLength(dLength){};
    /**
     * 获取拥挤度
     * @return 返回拥挤值
     */
    int get_Congestion();
public:
    int m_nID;
    int m_CrossRoadFromSite, m_CrossRoadToSite;
    double m_dLength;
    int m_nCongestion = 0; //(50 * car / length),[0,100] 拥挤度
    deque<Vehicle> m_queVehicle;
};


#endif //TRAFFIC_NETWORK_MODEL_ROAD_H
