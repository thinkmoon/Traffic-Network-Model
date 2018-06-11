//
// Created by chauncey on 18-6-11.
//

#ifndef TRAFFIC_NETWORK_MODEL_TRAFFIC_LIGHT_H
#define TRAFFIC_NETWORK_MODEL_TRAFFIC_LIGHT_H


class TrafficLight {
public:
    void changeStatus();

    void setType(int type) { this->type = type; };
    //路口标号
    // nLeftIn,nLeftOut,nDownIn,nDownOut,nRightIn,nRightOut,nUpIn,nUpOut;
    int roadID[8];
    //路口是否能走通
    bool status[4][4] = {false};
    int type;
    //表示可通过的方向（目标方向）
    enum {
        AllRED = 0,
        LeftGreen = 1,
        DownGreen = 2,
        RightGreen = 3,
        UpGreen = 4,
        UpDownGreen = 5,
        LeftRightGreen = 6,
        cross1 = 7,
        cross2 = 8
    } emStatus;

};


#endif //TRAFFIC_NETWORK_MODEL_TRAFFIC_LIGHT_H
