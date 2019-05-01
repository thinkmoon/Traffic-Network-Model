//
// Created by chauncey on 18-6-11.
//
#include "stdafx.h"
#ifndef TRAFFIC_NETWORK_MODEL_TRAFFIC_LIGHT_H
#define TRAFFIC_NETWORK_MODEL_TRAFFIC_LIGHT_H

/**
 * 交通灯类
 */
class TrafficLight {
public:
    TrafficLight();

    void changeStatus();

    void clock(int time);

    void setAllRed();

    void setAllGreen();

    void addWait(int from, int to, int weight);
    void subWait(int from, int to, int weight, int value);

    bool getStatus(int from, int to);
    /**
     * 设置灯的类型, 是T字路口还是+字路口
     * @param type
     */
    void setType(int type);
    //路口标号
    int roadID[8];
    map<int, int> mp;
    //路口是否能走通
    int status[8][8] = {0};
    int wait[8][8] = {0};
    int type;
    //表示可通过的方向（目标方向）
    //AllRED = 0,LeftGreen = 1,DownGreen = 2,RightGreen = 3,UpGreen = 4,UpDownGreen = 5,LeftRightGreen = 6,cross1 = 7,cross2 = 8
    int emStatus = 0;
    long long int time = 0;
};


#endif //TRAFFIC_NETWORK_MODEL_TRAFFIC_LIGHT_H
