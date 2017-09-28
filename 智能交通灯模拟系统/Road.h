#pragma once

#include "stdafx.h"
#include "Point.h"
#include "Vehicle.h"
#include "TrafficLight.h"
#include "BitMatrix.h"

#define R 6378  //地球的平均半径
#define PI 3.14
#define LANNE_AMOUNT 3  //每条道路的车道数量 
#define MIN_VEHICLE 10  //初始状态每条道路的最少车辆
#define VEHICLE_SIZE 70 

class Vehicle;
class TrafficLight;

class Road
{
public:
	Road(double longitude1, double latitude1, double longitude2, double latitude2) : point1(longitude1, latitude1), point2(longitude2, latitude2)
	{
		length = R * 2 * asin(sqrt(pow(sin((latitude1/180*PI-latitude2/180*PI)/2), 2) + cos(latitude1/180*PI)*cos(latitude2/180*PI)*pow(sin((longitude1/180*PI-longitude2/180*PI)/2), 2))); //计算道路长度
	}

	bool operator==(Road& road);      //用于判断两条道路是否相连
	double countVehicleDensity(void); //计算行车密度， 行车密度 = 车辆数 / (道路长度(km) * 车道数）
	double countCrowdExtent(void);    //计算道路拥挤度
	double returnLength(void);        //返回道路长度
	bool enterVehicle(void);          //当前道路是否能进车
	void updateVehicle(vector<Road>& road); //更新当前道路的车辆
	void creatVehicle(int roadSize, int totalRoadSize, BitMatrix& roadBitMatrix, vector<Road>& road);//为该道路生成车辆
	void enterVehicle(Vehicle& vehicle); //进入车辆
	void updateTrafficLight(void);    //更新当前道路的交通灯





	/*
	计算拥挤度的公式:
	crowdExtent = 0.15 * exp(-0.0322 * vehicleDensity) - 0.15 (vehicleDensity <= 45.5)
	crowdExtent = 0.111 * vehicleDensity - 0.0152 (vehicleDensity > 45.5)
	*/

	
	
	
	vector<int> adjoin;   //存储相连的道路编号   是否改成private?

private:
	Point point1, point2; //道路的两个端点的经纬度
	double length, vehicleDensity, crowdExtent; //length为道路的长度,vehicleDensity为行车密度,crowdExtent为道路拥挤度
	list<Vehicle> vehicle;//当前道路的车辆表
	TrafficLight trafficLight;//交通灯用于控制车辆进入该道路
	int vehicleSize;     //当前道路车辆数
};