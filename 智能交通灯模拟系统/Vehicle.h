#pragma once

#include "stdafx.h"
#include "RoadAdjoinTable.h"
#include "BitMatrix.h"

#define INFINITY 65535  //无穷大

class Road;

class Vehicle
{
public:
	Vehicle(int roadSize, int totalRoadSize, double length, double crowdExten, BitMatrix& roadBitMatrix, vector<Road>& road);       //随机生成起始地和目的地,位置

	void updateSpeed(double crowdExten);//更新当前车速
	void updateRemainDistance(void);    //更新当前的剩余距离
	bool enterNextPosition(bool enterVehicle); //判断该车是否能进入下一个位置
	int returnNowPosition(void);    //返回当前位置
	int returnNextPossition(void);  //返回下一个位置
	void updatePosition(void);//更新当前位置和下一个位置
	void setReaminDistance(double newRemainDistance); //更改该车的剩余距离
	void countShortestWay(BitMatrix& roadBitMatrix, vector<Road>& road);        //计算从起始地到目的地的最短路径

private:
	int origin, destination, nowPosition, nextPosition; //origin为起始地，destination为目的地，nowPosition为当前所在道路编号,nextPosition为该车的下一个位置,为-1时表示到达目的地
	double remainDistance, nowSpeed;          //remainDistance为当前道路的剩余路程，nowSpeed为当前的车速，单位km/h
	static vector<vector<vector<int> > > way; //保存从任意起始地到目的地的最短路径
	clock_t start, finish;                    //用于记录该车距离上次更新的时间
};