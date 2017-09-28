#pragma once

#include "stdafx.h"

#define RED_TIME 60     //���ʱ��
#define GREEN_TIME 20   //�̵�ʱ��
#define YELLOW_TIME 10  //�Ƶ�ʱ��

class TrafficLight
{
public:
	TrafficLight(int redLightTime = RED_TIME, int greenLightTime = GREEN_TIME, int yellowLightTime = YELLOW_TIME);
	
	void updateNowLight(void); //���µ�ǰ�Ƶ�״̬
	void updateLightTime(void);//���ܸı���Ƶĳ���ʱ��
	bool passVehicle(void);    //��ǰ�Ƿ���ͨ��

private:
	enum {redLight, greenLight, yellowLight} nowLight; //��ǰ�Ƶ�״̬
	int redLightTime, greenLightTime, yellowLightTime; //���̻Ƹ��Ƶĳ���ʱ��
	clock_t start, finish; //��¼��ǰ״̬�ѳ�����ʱ��
};