//
// Created by chauncey on 18-9-11.
//

#include "CrossRoad.h"
bool CrossRoad::operator==(CrossRoad &crossRoad) {
    return fabs(m_fLon - crossRoad.m_fLon) <= 0.000001 && fabs(m_fLat - crossRoad.m_fLat) <= 0.000001;
}
void CrossRoad::addNode(int outRoadID, int inRoadID) {
    Node node(outRoadID,inRoadID);
    JunctionRoad.push_back(node);
}