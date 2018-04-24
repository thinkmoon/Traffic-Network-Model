//
// Created by chauncey on 18-2-8.
//

#ifndef TRAFFIC_NETWORK_MODEL_POINT_H
#define TRAFFIC_NETWORK_MODEL_POINT_H

class Point {
public:
    Point(double lon, double lat) : m_fLon(lon), m_fLat(lat), m_nID(-1) {};

    bool operator==(Point &point);

public:
    int m_nID;
    float m_fLon, m_fLat;//经纬度的定义
};

#endif //TRAFFIC_NETWORK_MODEL_POINT_H
