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
			(*it).updateRemainDistance();       //���¸ó���ʣ�����

			if ((*it).enterNextPosition(road[(*it).returnNextPossition()].enterVehicle())) //�жϸó��Ƿ��ܽ�����һ��λ��
			{
				--vehicleSize;  //�õ�·�ĳ�������һ
				road[(*it).returnNextPossition()].enterVehicle(*it);  //���ó����뵽��һ��λ��
				vehicle.erase(it); //���ó��Ӹõ�·ɾ��
			}
			else
			{
				countVehicleDensity();
				(*it).updateSpeed(countCrowdExtent()); //���¸ó����ٶ�
			}
		}
		else
		{
			//�ڴ�����ѵ���Ŀ�ĵصĳ�����ִ��
		}

	}
}

void Road::creatVehicle(int roadSize, int totalRoadSize, BitMatrix& roadBitMatrix, vector<Road>& road)
{
	Vehicle *pVehicle;

	vehicleSize = rand() % VEHICLE_SIZE + MIN_VEHICLE;  //��ʼ���õ�·�ĳ�����
	countVehicleDensity();

	for (int i=1; i <= vehicleSize; i++) //���ɳ���
	{
		pVehicle = new Vehicle(roadSize, totalRoadSize, length, countCrowdExtent(), roadBitMatrix, road);
		vehicle.push_back(*pVehicle);
		free(pVehicle);
	}
}

void Road::enterVehicle(Vehicle& vehicle)
{
	++vehicleSize;  //�õ�·��������һ
	vehicle.updatePosition();  //���¸ó���λ��

	//���¸ó����ٶ�
	countVehicleDensity();
	vehicle.updateSpeed(countCrowdExtent());

	vehicle.setReaminDistance(length); //���ĸó���ʣ�����
	this->vehicle.push_back(vehicle);  //���ó��ӵ��õ�·�ĳ�������
}

void Road::updateTrafficLight(void)
{
	trafficLight.updateNowLight();
}

