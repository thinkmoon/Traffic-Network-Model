#pragma once

#include "stdafx.h"
#include "Point.h"
#include "Vehicle.h"
#include "TrafficLight.h"
#include "BitMatrix.h"

#define R 6378  //�����ƽ���뾶
#define PI 3.14
#define LANNE_AMOUNT 3  //ÿ����·�ĳ������� 
#define MIN_VEHICLE 10  //��ʼ״̬ÿ����·�����ٳ���
#define VEHICLE_SIZE 70 

class Vehicle;
class TrafficLight;

class Road
{
public:
	Road(double longitude1, double latitude1, double longitude2, double latitude2) : point1(longitude1, latitude1), point2(longitude2, latitude2)
	{
		length = R * 2 * asin(sqrt(pow(sin((latitude1/180*PI-latitude2/180*PI)/2), 2) + cos(latitude1/180*PI)*cos(latitude2/180*PI)*pow(sin((longitude1/180*PI-longitude2/180*PI)/2), 2))); //�����·����
	}

	bool operator==(Road& road);      //�����ж�������·�Ƿ�����
	double countVehicleDensity(void); //�����г��ܶȣ� �г��ܶ� = ������ / (��·����(km) * ��������
	double countCrowdExtent(void);    //�����·ӵ����
	double returnLength(void);        //���ص�·����
	bool enterVehicle(void);          //��ǰ��·�Ƿ��ܽ���
	void updateVehicle(vector<Road>& road); //���µ�ǰ��·�ĳ���
	void creatVehicle(int roadSize, int totalRoadSize, BitMatrix& roadBitMatrix, vector<Road>& road);//Ϊ�õ�·���ɳ���
	void enterVehicle(Vehicle& vehicle); //���복��
	void updateTrafficLight(void);    //���µ�ǰ��·�Ľ�ͨ��





	/*
	����ӵ���ȵĹ�ʽ:
	crowdExtent = 0.15 * exp(-0.0322 * vehicleDensity) - 0.15 (vehicleDensity <= 45.5)
	crowdExtent = 0.111 * vehicleDensity - 0.0152 (vehicleDensity > 45.5)
	*/

	
	
	
	vector<int> adjoin;   //�洢�����ĵ�·���   �Ƿ�ĳ�private?

private:
	Point point1, point2; //��·�������˵�ľ�γ��
	double length, vehicleDensity, crowdExtent; //lengthΪ��·�ĳ���,vehicleDensityΪ�г��ܶ�,crowdExtentΪ��·ӵ����
	list<Vehicle> vehicle;//��ǰ��·�ĳ�����
	TrafficLight trafficLight;//��ͨ�����ڿ��Ƴ�������õ�·
	int vehicleSize;     //��ǰ��·������
};