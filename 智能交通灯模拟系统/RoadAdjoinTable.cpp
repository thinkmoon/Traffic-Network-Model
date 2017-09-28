#include "stdafx.h"
#include "Road.h"
#include "RoadAdjoinTable.h"

RoadAdjoinTable::RoadAdjoinTable(void)
{
	road.reserve(MAXSIZE);
}

void RoadAdjoinTable::creatTable(string& fileName, RoadAdjoinTable& roadAdjoinTable)
{
	ifstream file(fileName.c_str());
	Road *pRoad;  //���ڹ�����ʱ����
	char str[LINESIZE];
	int num = 0;  //��¼��·�ı��
	double longitude1, latitude1, longitude2, latitude2;
	
	while (file.getline(str, LINESIZE))
	{
		sscanf(str, "%d %lf %lf %lf %lf", &num, &longitude1, &latitude1, &longitude2, &latitude2);
		pRoad = new Road(longitude1, latitude1, longitude2, latitude2);
		cout << pRoad->returnLength();
		road.push_back(*pRoad);  //����ȡ���µ�·�浽������
		addRoadToAdjion(*pRoad); //���õ�·�ӵ�������·���ڽӱ���
		delete pRoad;
	}

	file.close();
	return;
}

void RoadAdjoinTable::addRoadToAdjion(Road& road)
{
	int num = this->road.size();

	for (int i=0; i < num; i++)
	{
		if (this->road[i] == road)
		{
			this->road[i].adjoin.push_back(num-1);
			this->road[num-1].adjoin.push_back(i);
		}
	}

	return;
}

void RoadAdjoinTable::creatRoadBitMatrix(BitMatrix& roadBitMatrix)
{
	for (unsigned int i=0; i < road.size(); i++)//��·����
	{
		for (unsigned int j=0; j < road[i].adjoin.size(); j++)//
		{
			roadBitMatrix.SetOne(i, j);
		}
		road[i].adjoin.clear(); //����ڽӱ�
	}

}

void RoadAdjoinTable::creatRoadVehicle(BitMatrix& roadBitMatrix)
{
	for (int i=0; i < road.size(); i++)//ѭ��Ϊÿһ����·��������
	{
		road[i].creatVehicle(i, road.size(), roadBitMatrix, road);
	}
}

void RoadAdjoinTable::updateRoad(void)
{
	for (int i=0; i < road.size(); i++)
	{
		road[i].updateVehicle(road);
		road[i].updateTrafficLight();
	}
}