#include "stdafx.h"
#include "TrafficLight.h"

TrafficLight::TrafficLight(int redLightTime, int greenLightTime, int yellowLightTime)
{
	int i = rand() % 3;

	start = clock();

	this->redLightTime = redLightTime;
	this->greenLightTime = greenLightTime;
	this->yellowLightTime = yellowLightTime;

	if (i == 0)
	{
		nowLight = redLight;
	}
	else if (i == 1)
	{
		nowLight = greenLight;
	}
	else
	{
		nowLight = yellowLight;
	}
}

void TrafficLight::updateNowLight(void)
{
	int duration;

	finish = clock();
	duration = (int)((double)(finish - start) / CLOCKS_PER_SEC);

	if (nowLight == redLight)
	{
		if (duration >= redLightTime)
		{
			nowLight = greenLight;
			start = clock();
		}
	}
	else if (nowLight == greenLight)
	{
		if (duration >= greenLightTime)
		{
			nowLight = yellowLight;
			start = clock();
		}
	}
	else
	{
		if (duration >= yellowLightTime)
		{
			nowLight = redLight;
			start = clock();
		}
	}
}

void TrafficLight::updateLightTime(void)
{
	return;
}

bool TrafficLight::passVehicle(void)
{
	if (nowLight == redLight)
	{
		return false;
	}
	else
	{
		return true;
	}
}