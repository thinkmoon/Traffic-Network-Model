#pragma once

#include "stdafx.h"
#include "Road.h"
#include "BitMatrix.h"

#define MAXSIZE 43000
#define LINESIZE 100    //�ļ�ÿ�е������

class Road;

//������·�ڽӱ���
class RoadAdjoinTable
{
public:
	RoadAdjoinTable(void);
	void creatTable(string& fileName, RoadAdjoinTable& roadAdjoinTable);  //�����ڽӱ�
	void addRoadToAdjion(Road& road);   //���õ�·�ӵ�������·���ڽӱ���
	void creatRoadBitMatrix(BitMatrix& roadBitMatrix); //������·���ؾ���
	void creatRoadVehicle(BitMatrix& roadBitMatrix); //�õ�·���ɳ���
	void updateRoad(void);       //���µ�·��Ϣ

	vector<Road> road;
};