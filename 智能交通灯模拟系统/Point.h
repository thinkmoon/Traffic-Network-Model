#pragma once


class Point
{
public:
	Point(double longitude, double latitdue);
	bool operator==(Point& point);

private:
	double longitude;  //¾­¶È
	double latitude;   //Î³¶È
};