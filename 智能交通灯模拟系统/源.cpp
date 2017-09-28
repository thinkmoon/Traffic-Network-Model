#include "stdafx.h"
#include "RoadAdjoinTable.h"

#define SLEEP_TIME 1000

void inputFileName(string& fileName);

int main(void)
{
	string fileName("E:/tim/桌面/新建文本文档.txt");
	RoadAdjoinTable roadAdjoinTable;

	srand(time(NULL));  
	//inputFileName(fileName);
	roadAdjoinTable.creatTable(fileName, roadAdjoinTable);  //构建道路邻接表
	BitMatrix roadBitMatrix(roadAdjoinTable.road.size()); //构建道路的比特矩阵
	roadBitMatrix.FillOnes();  //置1;
	roadBitMatrix.Not();       //置0
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
	cout << "请将道路文件拖到窗口:";
	cin >> fileName;
}