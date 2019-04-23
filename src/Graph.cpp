//
// Created by chauncey on 18-3-6.
//
#include "Graph.h"

void Graph::output() {
    ofstream RoadTableFile(DIR_DATA"RoadTable.txt");
    RoadTableFile << endl << "-------------+ RoadTable +------------" << endl;
    for (auto crossroad:m_CrossRoad_v) {
        RoadTableFile << "CrossRoad["<< crossroad.m_nID << "]" << endl;
        if(crossroad.JunctionRoad.size() == 1){
            RoadTableFile << endl<< "           ----------------" << endl;
            RoadTableFile << "               <-(" << crossroad.JunctionRoad[0].outRoadID <<")"<< endl;
            RoadTableFile << "           - - - - - - - -   {" << crossroad.m_nID << "} " << endl;
            RoadTableFile << "              (" << crossroad.JunctionRoad[0].inRoadID << ")->" << endl;
            RoadTableFile << "           ----------------" << endl << endl;
        }else if(crossroad.JunctionRoad.size() == 2){
            RoadTableFile << endl<< "           ----------------" << "         " << "---------------" << endl;
            RoadTableFile << "              <-(" << crossroad.JunctionRoad[0].outRoadID << ")                      <-(" << crossroad.JunctionRoad[1].inRoadID <<") "<< endl;
            RoadTableFile << "           - - - - - - - -   {" << crossroad.m_nID << "} " << endl;
            RoadTableFile << "              (" << crossroad.JunctionRoad[0].inRoadID << ")->                       (" << crossroad.JunctionRoad[1].outRoadID << ")->" << endl;
            RoadTableFile << "           ----------------" << "         " << "---------------"<< endl << endl;
        }else if(crossroad.JunctionRoad.size() == 3){
            RoadTableFile << "                          |" << "           " << "|" << endl;
            RoadTableFile << "                          |" << "     |     " << "|" << endl;
            RoadTableFile << "                          |" << "("<<crossroad.JunctionRoad[2].inRoadID<<")   ↑  " << "|" << endl;
            RoadTableFile << "                          |" << " ↓ | ("<<crossroad.JunctionRoad[2].outRoadID<<")" << "|" << endl;
            RoadTableFile << "                          |" << "           " << "|";
            RoadTableFile << endl<< "           ----------------" << "         " << "---------------" << endl;
            RoadTableFile << "              <-(" << crossroad.JunctionRoad[0].outRoadID << ")                      <-(" << crossroad.JunctionRoad[1].inRoadID <<") "<< endl;
            RoadTableFile << "           - - - - - - - -   {" << crossroad.m_nID << "} " << endl;
            RoadTableFile << "              (" << crossroad.JunctionRoad[0].inRoadID << ")->                       (" << crossroad.JunctionRoad[1].outRoadID << ")->" << endl;
            RoadTableFile << "           ----------------" << "         " << "---------------"<< endl << endl;
        }else if(crossroad.JunctionRoad.size() == 4){
            RoadTableFile << "                          |" << "           " << "|" << endl;
            RoadTableFile << "                          |" << "     |     " << "|" << endl;
            RoadTableFile << "                          |" << "("<<crossroad.JunctionRoad[2].inRoadID<<")   ↑  " << "|" << endl;
            RoadTableFile << "                          |" << " ↓ | ("<<crossroad.JunctionRoad[2].outRoadID<<")" << "|" << endl;
            RoadTableFile << "                          |" << "           " << "|";
            RoadTableFile << endl<< "           ----------------" << "         " << "---------------" << endl;
            RoadTableFile << "              <-(" << crossroad.JunctionRoad[0].outRoadID << ")                      <-(" << crossroad.JunctionRoad[1].inRoadID <<") "<< endl;
            RoadTableFile << "           - - - - - - - -   {" << crossroad.m_nID << "} " << endl;
            RoadTableFile << "              (" << crossroad.JunctionRoad[0].inRoadID << ")->                       (" << crossroad.JunctionRoad[1].outRoadID << ")->" << endl;
            RoadTableFile << "           ----------------" << "         " << "---------------"<< endl ;
            RoadTableFile << "                          |" << "           " << "|" << endl;
            RoadTableFile << "                          |" << "     |     " << "|" << endl;
            RoadTableFile << "                          |" << " ("<<crossroad.JunctionRoad[3].outRoadID<<")   ↑  " << "|" << endl;
            RoadTableFile << "                          |" << "   ↓ | ("<<crossroad.JunctionRoad[3].inRoadID<<")" << "|" << endl;
            RoadTableFile << "                          |" << "           " << "|" << endl;
        }else {
            RoadTableFile << " 遇到一个特殊路口,连接道路数为：" << crossroad.JunctionRoad.size() << endl;
        }
    }
    RoadTableFile << endl << "---------------+ RoadTable END +--------------------" << endl;
    RoadTableFile.close();
    ofstream RoadFile(DIR_DATA"Road.txt");
    RoadFile << endl << "-------------+ Road +------------" << endl;
    int i = 0;
    for(auto road:m_Road_v){
        RoadFile << "Road[" << i++ << "] ( [" << road.m_CrossRoadFromSite << "] |=======> [" << road.m_CrossRoadToSite << "] )" << endl;
    }
    RoadFile << endl << "---------------+ Road END +--------------------" << endl;
    RoadFile.close();
}
//
//int Graph::getRoadID(int PointFromID,int PointToID) {
//    int n_RoadID=-1;
//    auto p = RoadTable[PointFromID].link;
//    while(p != nullptr){
//        if(p->m_ID == PointToID){
//            n_RoadID = p->roadID;
//        }
//        p = p->link;
//    }
//    return n_RoadID;
//}
//
//void RoadNode::addNode(int m_ID, double m_length, int roadID, int ParallelRoadID) {
//    auto node = new RoadNode(m_ID, m_length, roadID, ParallelRoadID);
//    if (link == nullptr) {
//        link = node;
//    } else {
//        RoadNode *q = link, *p = link->link;
//        while (p != nullptr) {
//            q = p;
//            p = p->link;
//        }
//        q->link = node;
//    }
//    length++;
//}

