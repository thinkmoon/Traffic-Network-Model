#include "stdafx.h"
#include "Point.h"

Point::Point(double longitude, double latitdue)
{
	this->longitude = longitude;
	this->latitude = latitdue;
}

bool Point::operator==(Point& point)
{
	if (fabs(longitude-point.longitude)<=0.000001 && fabs(latitude-point.latitude)<=0.000001)
	{
		return true;
	}
	return false;
}