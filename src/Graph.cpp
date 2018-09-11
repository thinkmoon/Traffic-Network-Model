//
// Created by chauncey on 18-3-6.
//
#include "Graph.h"
void Graph::showPoint() {
    cout << "show point:";
    cout << endl << "------------+ Point +-------------" << endl;
    for (auto item: point) {
        cout << "point[" << item.m_nID << "],";
        cout << "longitude=" << item.m_fLon << ",latitude=" << item.m_fLat << endl;
    }
    cout << endl << "-----------------------------------" << endl;
}

void Graph::showRoadTable(int num) {
    int count = 0;
    cout << endl << "-------------+ RoadTable +------------" << endl;
    for (auto item:RoadTable) {
            cout << "Point[" << item.junctionID << "]," << "num:" << item.length;
            RoadNode *p = item.link;
            cout << " link:";
            while (p != nullptr) {
                cout << " -> road[" << p->roadID << "] " << "TO:" << p->junctionID << "(" << p->length << ")";
                p = p->link;
            }
            cout << endl;
            count++;
    }
    cout << endl << "-----------------------------------" << endl;
    cout << "there are " << count << " point" << endl;
}

void Graph::showRoad() {
    cout << endl << "-------------+ road +------------" << endl;
    for (int k = 0; k < road.size(); ++k) {
        cout << "road[" << k << "]=" << road[k].m_dLength << endl;
    }
    cout << endl << "---------------------------------" << endl;
}

void Graph::show() {
    showPoint();
    showRoad();
    showRoadTable(2);
}

int Graph::getRoadID(int PointFromID,int PointToID) {
    int n_RoadID=-1;
    auto p = RoadTable[PointFromID].link;
    while(p != nullptr){
        if(p->junctionID == PointToID){
            n_RoadID = p->roadID;
        }
        p = p->link;
    }
    return n_RoadID;
}

void RoadNode::addNode(int m_ID, double m_length, int roadID, int ParallelRoadID) {
    auto node = new RoadNode(m_ID, m_length, roadID, ParallelRoadID);
    if (link == nullptr) {
        link = node;
    } else {
        RoadNode *q = link, *p = link->link;
        while (p != nullptr) {
            q = p;
            p = p->link;
        }
        q->link = node;
    }
    length++;
}

