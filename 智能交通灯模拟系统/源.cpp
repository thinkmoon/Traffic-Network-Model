#include "stdafx.h"
#include "RoadAdjoinTable.h"

#define SLEEP_TIME 1000

void inputFileName(string& fileName);

int main(void)
{
	string fileName("E:/tim/����/�½��ı��ĵ�.txt");
	RoadAdjoinTable roadAdjoinTable;

	srand(time(NULL));  
	//inputFileName(fileName);
	roadAdjoinTable.creatTable(fileName, roadAdjoinTable);  //������·�ڽӱ�
	BitMatrix roadBitMatrix(roadAdjoinTable.road.size()); //������·�ı��ؾ���
	roadBitMatrix.FillOnes();  //��1;
	roadBitMatrix.Not();       //��0
	roadAdjoinTable.creatRoadBitMatrix(roadBitMatrix);

	roadAdjoinTable.creatRoadVehicle(roadBitMatrix);
	while (1)
	{
		roadAdjoinTable.updateRoad();
		Sleep(SLEEP_TIME);
	}

	return 0;
}

void inputFileName(string& fileName)
{
	cout << "�뽫��·�ļ��ϵ�����:";
	cin >> fileName;
}