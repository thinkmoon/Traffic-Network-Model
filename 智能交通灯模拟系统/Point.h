#pragma once


class Point
{
public:
	Point(double longitude, double latitdue);
	bool operator==(Point& point);

private:
	double longitude;  //����
	double latitude;   //γ��
};