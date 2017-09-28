#pragma once

#include "stdafx.h"
#include "RoadAdjoinTable.h"
#include "BitMatrix.h"

#define INFINITY 65535  //�����

class Road;

class Vehicle
{
public:
	Vehicle(int roadSize, int totalRoadSize, double length, double crowdExten, BitMatrix& roadBitMatrix, vector<Road>& road);       //���������ʼ�غ�Ŀ�ĵ�,λ��

	void updateSpeed(double crowdExten);//���µ�ǰ����
	void updateRemainDistance(void);    //���µ�ǰ��ʣ�����
	bool enterNextPosition(bool enterVehicle); //�жϸó��Ƿ��ܽ�����һ��λ��
	int returnNowPosition(void);    //���ص�ǰλ��
	int returnNextPossition(void);  //������һ��λ��
	void updatePosition(void);//���µ�ǰλ�ú���һ��λ��
	void setReaminDistance(double newRemainDistance); //���ĸó���ʣ�����
	void countShortestWay(BitMatrix& roadBitMatrix, vector<Road>& road);        //�������ʼ�ص�Ŀ�ĵص����·��

private:
	int origin, destination, nowPosition, nextPosition; //originΪ��ʼ�أ�destinationΪĿ�ĵأ�nowPositionΪ��ǰ���ڵ�·���,nextPositionΪ�ó�����һ��λ��,Ϊ-1ʱ��ʾ����Ŀ�ĵ�
	double remainDistance, nowSpeed;          //remainDistanceΪ��ǰ��·��ʣ��·�̣�nowSpeedΪ��ǰ�ĳ��٣���λkm/h
	static vector<vector<vector<int> > > way; //�����������ʼ�ص�Ŀ�ĵص����·��
	clock_t start, finish;                    //���ڼ�¼�ó������ϴθ��µ�ʱ��
};