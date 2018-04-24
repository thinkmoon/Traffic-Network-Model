//
// Created by chauncey on 18-3-6.
//
#include "stdafx.h"
#include "Point.h"

bool Point::operator==(Point &point) {
    return fabs(m_fLon - point.m_fLon) <= 0.000001 && fabs(m_fLat - point.m_fLat) <= 0.000001;
}


