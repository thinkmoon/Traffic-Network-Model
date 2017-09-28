#include "stdafx.h"
#include "Vehicle.h"
#include "RoadAdjoinTable.h"

vector<vector<vector<int> > > Vehicle::way;

Vehicle::Vehicle(int roadSize, int totalRoadSize, double length, double crowdExten, BitMatrix& roadBitMatrix, vector<Road>& road)
{
	if (!way.size())  //初始化way的大小
	{
		way.resize(road.size());
		for (int i=0; i < way.size(); i++)
		{
			way[i].resize(road.size());
		}
	}

	start = clock(); //开始计时

	nowPosition = origin = roadSize;
	destination = rand() % totalRoadSize;
	while (destination == origin)
	{
		destination = rand() % totalRoadSize;
	}

	remainDistance = (double)(rand() % ((int)length + 1)); //随机获得车辆位置, 加1是为了避免出现和0取余的情况
	updateSpeed(crowdExten);   //获得初始速度

	if (!way[origin][destination].size())  //如果该起始地到目的地在最短路径表里为空
	{
		countShortestWay(roadBitMatrix, road);
	}

	nextPosition = (way[origin][destination].size() > 1) ? 1 : -1; //初始化下一个位置
}

void Vehicle::updateSpeed(double crowdExten)
{
	if (crowdExten >= 0 && crowdExten <= 0.17)
	{
		nowSpeed = rand() % 6 + 55;
	}
	else if (crowdExten >= 0.17 && crowdExten <= 0.33)
	{
		nowSpeed = rand() % 12 + 44;
	}
	else if (crowdExten >= 0.33 && crowdExten <= 0.50)
	{
		nowSpeed = rand() % 8 + 37;
	}
	else if (crowdExten >= 0.50 && crowdExten <= 0.67)
	{
		nowSpeed = rand() % 13 + 25;
	}
	else if (crowdExten >=0.67 && crowdExten <= 0.83)
	{
		nowSpeed = rand() % 14 + 12;
	}
	else
	{
		nowSpeed = rand() % 13;
	}
}

void Vehicle::updateRemainDistance(void)
{
	double duration;

	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	if ((remainDistance -= nowSpeed * duration / 3600) < 0)
	{
		remainDistance = 0;
	}
	start = clock();
}

bool Vehicle::enterNextPosition(bool enterVehicle)
{
	if (fabs(remainDistance) <= 0.000001 && enterVehicle)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Vehicle::returnNowPosition(void)
{
	return nowPosition;
}

int Vehicle::returnNextPossition(void)
{
	return nextPosition;
}

void Vehicle::updatePosition(void)
{
	for (int i=0; i < way[origin][destination].size(); i++)
	{
		if (nextPosition == way[origin][destination][i])
		{
			nowPosition = nextPosition;
			nextPosition = (++i == way[origin][destination].size()) ? -1 : i;
			break;
		}
	}
}

void Vehicle::setReaminDistance(double newRemainDistance)
{
	remainDistance = newRemainDistance;
}

void Vehicle::countShortestWay(BitMatrix& roadBitMatrix, vector<Road>& road)
{
	vector<int> find(road.size()), minRoute(road.size());
	vector<double> minLength(road.size());
	stack<int> route;
	double min;
	int k;

	//用Dijkstra算法求origin到其他各点的最短路径
	for (int i=0; i < road.size(); i++)
	{
		minRoute[i] = origin;

		if (roadBitMatrix.CheckPosition(origin, i))
		{
			minLength[i] = road[origin].returnLength();
		}
		else
		{
			minLength[i] =  INFINITY;
		}

	}

	find[origin] = 1;
	for (int i=0; i < road.size() - 1; i++)
	{
		min = INFINITY;
		for (int j=0; j < road.size(); j++)
		{
			if (!find[j] && minLength[j] < min)
			{
				min = minLength[j];
				k = j;
			}
		}
		find[k] = 1;

		for (int j=0; j < road.size(); j++)
		{
			if (!find[j] && roadBitMatrix.CheckPosition(k, j) && min+road[k].returnLength() < minLength[j])
			{
				minLength[j] = min + road[k].returnLength();
				minRoute[j] = k;
			}
		}
	}

	//将所有的origin到i的最短路径的路线存到表中
	for (int i=0; i < road.size(); i++)
	{
		if (i != origin)
		{
			for (int j=minRoute[i]; j != origin; j=minRoute[j])
			{
				route.push(j);
			}

			way[origin][i].push_back(origin);
			while (!route.empty())
			{
				way[origin][i].push_back(route.top());
				route.pop();
			}
		}
	}
}