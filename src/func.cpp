//
// Created by chauncey on 18-4-24.
//
#include "Utility/tinyxml2/tinyxml2.h"
#include "Utility/tinyxml2/tinyxml2.cpp"
#include "func.h"

void addRoad(Graph &Map_Graph, Point A, Point B, double length) {
    auto site_B = -1;
    auto site_A = -1;
    auto point_num = Map_Graph.point.size();
    auto roadID = Map_Graph.road.size();
    Road m_road(A, B, length);
    Map_Graph.road.push_back(m_road);
    for (int i = 0; i < point_num; i++) {
        if (Map_Graph.point[i] == A) {
            site_A = i;
        }
        if (Map_Graph.point[i] == B) {
            site_B = i;
        }
    }
    if (site_A == -1) {
        Map_Graph.point.push_back(A);
        site_A = point_num++;
        Map_Graph.point[site_A].m_nID = site_A;
        RoadNode node(site_A, 0, roadID);
        Map_Graph.RoadTable.push_back(node);
        Map_Graph.RoadTable[site_A].junctionID = site_A;
    }
    if (site_B == -1) {
        Map_Graph.point.push_back(B);
        site_B = point_num;
        Map_Graph.point[site_B].m_nID = site_B;
        RoadNode node(site_B, 0, roadID);
        Map_Graph.RoadTable.push_back(node);
        Map_Graph.RoadTable[site_B].junctionID = site_B;
    }
    Map_Graph.RoadTable[site_A].addNode(site_B, length, roadID);
    Map_Graph.RoadTable[site_B].addNode(site_A, -length, roadID);
}

void StringAddInt(string &str, int i) {
    stringstream stream;
    stream << i << " ";
    str = str + stream.str();
}

void generateTestGraph(Graph &G) {
    Point v1(1, 3), v2(1, 2), v3(2, 1), v4(3, 2), v5(3, 3), v6(2, 4);
    addRoad(G, v2, v3, 5);
    addRoad(G, v1, v3, 10);
    addRoad(G, v4, v6, 10);
    addRoad(G, v4, v5, 20);
    addRoad(G, v1, v5, 30);
    addRoad(G, v4, v3, 50);
    addRoad(G, v5, v6, 60);
    addRoad(G, v1, v6, 100);
}

void calcShortestPath(Graph *G) {
    ofstream out("../res/route.txt");
    for (int V_begin = 0; V_begin < G->point.size(); V_begin++) {
        vector<bool> S(G->point.size(), false);
        vector<double> Determined_dist(G->point.size(), 0.0);
        vector<double> Estimated_dist(G->point.size(), DBL_MAX);
        vector<string> path(G->point.size());
        Determined_dist[V_begin] = 0;
        StringAddInt(path[V_begin], V_begin);
        int V_node = V_begin; //Ｖ_node作为正在进行出度遍历点的节点索引
        int count = 0;
        while (++count <= G->point.size()) {
            auto p = G->RoadTable[V_node].link;
            while (p != nullptr) {
                if (S[p->junctionID] == false &&
                    (fabs(p->length) + Determined_dist[V_node]) < Estimated_dist[p->junctionID]) {
                    Estimated_dist[p->junctionID] = fabs(p->length) + Determined_dist[V_node];
                    path[p->junctionID] = path[V_node];
                }
                p = p->link;
            }
            S[V_node] = true;
            auto min = min_element(Estimated_dist.begin(), Estimated_dist.end());
            unsigned int min_element_index = distance(Estimated_dist.begin(), min);
            Determined_dist[min_element_index] = Estimated_dist[min_element_index];
            Estimated_dist[min_element_index] = DBL_MAX;
            StringAddInt(path[min_element_index], min_element_index);
            V_node = min_element_index;
//        for(auto item:Determined_dist){cout << item << " ";}cout<<endl;
//        for(auto item:Estimated_dist){cout << item << " ";}cout<<endl;
//        cout << V_node << endl;
        }
        string str;
        for (const auto item:path) { if (item.empty() && item.size() < G->point.size()) str += item + "\n"; }
        out << str;
    }
}

void parseMap(Graph &Map_Graph, const char *MapFileName) {
    using namespace tinyxml2;
    XMLDocument docXml;
    XMLError errXml = docXml.LoadFile(MapFileName);
    if (XML_SUCCESS == errXml) {
        XMLElement *elm_Root = docXml.RootElement();
        XMLElement *elm_Road = elm_Root->FirstChildElement("road");
        while (elm_Road != nullptr) {
            auto road_length = elm_Road->FirstAttribute()->Next()->Value();
            auto elm_from = elm_Road->FirstChildElement("from");
            auto elm_to = elm_Road->FirstChildElement("to");
            auto from_attribute = elm_from->FirstAttribute();
            const XMLAttribute *to_attribute = elm_to->FirstAttribute();
            Point A(strtod(from_attribute->Value(), nullptr), strtod(from_attribute->Next()->Value(), nullptr));
            Point B(strtod(to_attribute->Value(), nullptr), strtod(to_attribute->Next()->Value(), nullptr));
            addRoad(Map_Graph, A, B, strtod(road_length, nullptr));
            elm_Road = elm_Road->NextSiblingElement("road");
        }
    } else {
        cout << "The map file loading failed" << endl;
        exit(1);
    }
}
