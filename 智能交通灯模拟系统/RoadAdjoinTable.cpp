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
	Road *pRoad;  //用于构建临时对象
	char str[LINESIZE];
	int num = 0;  //记录道路的编号
	double longitude1, latitude1, longitude2, latitude2;
	
	while (file.getline(str, LINESIZE))
	{
		sscanf(str, "%d %lf %lf %lf %lf", &num, &longitude1, &latitude1, &longitude2, &latitude2);
		pRoad = new Road(longitude1, latitude1, longitude2, latitude2);
		cout << pRoad->returnLength();
		road.push_back(*pRoad);  //将读取的新道路存到容器中
		addRoadToAdjion(*pRoad); //将该道路加到相连道路的邻接表中
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
	for (unsigned int i=0; i < road.size(); i++)//道路条数
	{
		for (unsigned int j=0; j < road[i].adjoin.size(); j++)//
		{
			roadBitMatrix.SetOne(i, j);
		}
		road[i].adjoin.clear(); //清空邻接表
	}

}

void RoadAdjoinTable::creatRoadVehicle(BitMatrix& roadBitMatrix)
{
	for (int i=0; i < road.size(); i++)//循环为每一条道路创造汽车
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