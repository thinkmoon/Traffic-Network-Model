#include "stdafx.h"
#include "Road.h"

bool Road::operator==(Road& road)
{
	if (point1==road.point1 || point1==road.point2 || point2==road.point1 || point2==road.point2)
	{
		return true;
	}
	else
	{
		return false;
	}
}

double Road::countVehicleDensity(void)
{
	return vehicleDensity = vehicleSize / (length * LANNE_AMOUNT);
}

double Road::countCrowdExtent(void)
{
	if (vehicleDensity <= 45.5)
	{
		return crowdExtent = 0.15 * exp(-0.0322 * vehicleDensity) - 0.15;
	}
	else
	{
		return crowdExtent = 0.111 * vehicleDensity - 0.0152;
	}
}

double Road::returnLength(void)
{
	return length;
}

bool Road::enterVehicle(void)
{
	if (trafficLight.passVehicle())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Road::updateVehicle(vector<Road>& road)
{
	for (auto it = vehicle.begin(); it != vehicle.end(); it++)
	{
		if ((*it).returnNextPossition() != -1)
		{
			(*it).updateRemainDistance();       //更新该车的剩余距离

			if ((*it).enterNextPosition(road[(*it).returnNextPossition()].enterVehicle())) //判断该车是否能进入下一个位置
			{
				--vehicleSize;  //该道路的车辆数减一
				road[(*it).returnNextPossition()].enterVehicle(*it);  //将该车送入到下一个位置
				vehicle.erase(it); //将该车从该道路删除
			}
			else
			{
				countVehicleDensity();
				(*it).updateSpeed(countCrowdExtent()); //更新该车的速度
			}
		}
		else
		{
			//在此添加已到达目的地的车辆的执行
		}

	}
}

void Road::creatVehicle(int roadSize, int totalRoadSize, BitMatrix& roadBitMatrix, vector<Road>& road)
{
	Vehicle *pVehicle;

	vehicleSize = rand() % VEHICLE_SIZE + MIN_VEHICLE;  //初始化该道路的车辆数
	countVehicleDensity();

	for (int i=1; i <= vehicleSize; i++) //生成车辆
	{
		pVehicle = new Vehicle(roadSize, totalRoadSize, length, countCrowdExtent(), roadBitMatrix, road);
		vehicle.push_back(*pVehicle);
		free(pVehicle);
	}
}

void Road::enterVehicle(Vehicle& vehicle)
{
	++vehicleSize;  //该道路车辆数加一
	vehicle.updatePosition();  //更新该车的位置

	//更新该车的速度
	countVehicleDensity();
	vehicle.updateSpeed(countCrowdExtent());

	vehicle.setReaminDistance(length); //更改该车的剩余距离
	this->vehicle.push_back(vehicle);  //将该车加到该道路的车辆表中
}

void Road::updateTrafficLight(void)
{
	trafficLight.updateNowLight();
}

