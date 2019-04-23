//
// Created by chauncey on 18-3-1.
//
#include "Road.h"

int Road::get_Congestion() {
    m_nCongestion = 50 * m_queVehicle.size() / m_dLength;
    if(m_nCongestion >= 100) {
        m_nCongestion = 99;
    }
    return m_nCongestion;
}
