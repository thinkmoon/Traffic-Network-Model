#pragma once

#include "stdafx.h"
#include "Road.h"
#include "BitMatrix.h"

#define MAXSIZE 43000
#define LINESIZE 100    //文件每行的最大数

class Road;

//构建道路邻接表类
class RoadAdjoinTable
{
public:
	RoadAdjoinTable(void);
	void creatTable(string& fileName, RoadAdjoinTable& roadAdjoinTable);  //构建邻接表
	void addRoadToAdjion(Road& road);   //将该道路加到相连道路的邻接表中
	void creatRoadBitMatrix(BitMatrix& roadBitMatrix); //构建道路比特矩阵
	void creatRoadVehicle(BitMatrix& roadBitMatrix); //让道路生成车辆
	void updateRoad(void);       //更新道路信息

	vector<Road> road;
};