#pragma once

#include "stdafx.h"

#define RED_TIME 60     //红灯时间
#define GREEN_TIME 20   //绿灯时间
#define YELLOW_TIME 10  //黄灯时间

class TrafficLight
{
public:
	TrafficLight(int redLightTime = RED_TIME, int greenLightTime = GREEN_TIME, int yellowLightTime = YELLOW_TIME);
	
	void updateNowLight(void); //更新当前灯的状态
	void updateLightTime(void);//智能改变各灯的持续时间
	bool passVehicle(void);    //当前是否能通车

private:
	enum {redLight, greenLight, yellowLight} nowLight; //当前灯的状态
	int redLightTime, greenLightTime, yellowLightTime; //红绿黄各灯的持续时间
	clock_t start, finish; //记录当前状态已持续的时间
};