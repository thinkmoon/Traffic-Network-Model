//
// Created by chauncey on 18-3-1.
//
#include "Road.h"

int Road::get_Congeestion() {
    m_nCongestion = 50 * m_queVehicle.size() / m_dLength;
    return m_nCongestion;
}
