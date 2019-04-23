//
// Created by chauncey on 18-4-24.
//
#include "Utility/tinyxml2/tinyxml2.h"
#include "Utility/tinyxml2/tinyxml2.cpp"
#include "func.h"

void addRoad(Graph &Map_Graph, CrossRoad A, CrossRoad B, double length) {
    // 初始化A，B路口的索引位置为-1
    int CrossRoadSiteB = -1, CrossRoadSiteA = -1;
    auto CrossRoadNum = Map_Graph.m_CrossRoad_v.size(), RoadNum = Map_Graph.m_Road_v.size();
    //循环判断是否有重合点
    for (int i = 0; i < CrossRoadNum; i++) {
        if (Map_Graph.m_CrossRoad_v[i] == A) {
            CrossRoadSiteA = i;
        }
        if (Map_Graph.m_CrossRoad_v[i] == B) {
            CrossRoadSiteB = i;
        }
    }
    //如果不存在与A点重合的路口,添加路口，保存路口索引
    if (CrossRoadSiteA == -1) {
        Map_Graph.m_CrossRoad_v.push_back(A);
        CrossRoadSiteA = CrossRoadNum++;
        Map_Graph.m_CrossRoad_v[CrossRoadSiteA].m_nID = CrossRoadSiteA;
    }
    if (CrossRoadSiteB == -1) {
        Map_Graph.m_CrossRoad_v.push_back(B);
        CrossRoadSiteB = CrossRoadNum++;
        Map_Graph.m_CrossRoad_v[CrossRoadSiteB].m_nID = CrossRoadSiteB;
    }
    int RoadSiteA = RoadNum, RoadSiteB = RoadNum + 1;
    // 确定A，B路的site，加入模型图
    Road roadA(RoadSiteA, CrossRoadSiteA, CrossRoadSiteB, length);
    Map_Graph.m_Road_v.push_back(roadA);
    Road roadB(RoadSiteB, CrossRoadSiteB, CrossRoadSiteA, length);
    Map_Graph.m_Road_v.push_back(roadB);
    // 对接A，B路口节点数据
    Map_Graph.m_CrossRoad_v[CrossRoadSiteA].addNode(RoadSiteA, RoadSiteB,
                                                    atan2((B.m_fLat - A.m_fLat), (B.m_fLon - A.m_fLon)));
    Map_Graph.m_CrossRoad_v[CrossRoadSiteB].addNode(RoadSiteB, RoadSiteA,atan2((A.m_fLat - B.m_fLat), (A.m_fLon - B.m_fLon)));
}

void RoutePathAddInt(RoutePath &routePath, int i) {
    stringstream stream;
    stream << i << " ";
    routePath.strPath = routePath.strPath + stream.str();
    routePath.num++;
}

void calcShortestPath(Graph *G) {
    int currentPointSite,nextPointSite;
    ofstream PointPathFile(DIR_RES"PointPath.txt"),RoadPathFile(DIR_RES"RoadPath.txt");
    //对点进行的一级遍历
    for (int V_begin = 0; V_begin < G->m_CrossRoad_v.size(); V_begin++) {
        // =================== 迪杰斯特拉算法开始 ===============================
        vector<bool> S(G->m_CrossRoad_v.size(), false); //判断是否选中
        vector<double> dist(G->m_CrossRoad_v.size(), DBL_MAX/2);// dist
        vector<double> compare_dist(G->m_CrossRoad_v.size(), DBL_MAX/2);// 辅助dist用来取最短距离点
        vector<int> path(G->m_CrossRoad_v.size(),-2); // path
        S[V_begin] = true;
        path[V_begin] = -1;
        for(auto crossroad : G->m_CrossRoad_v[V_begin].JunctionRoad){
            nextPointSite = G->m_Road_v[crossroad.outRoadID].m_CrossRoadToSite;
            dist[nextPointSite] = G->m_Road_v[crossroad.outRoadID].m_dLength;
            compare_dist[nextPointSite] = dist[nextPointSite];
        }
        auto min = min_element(compare_dist.begin(), compare_dist.end());
        int min_element_index = distance(compare_dist.begin(), min);
        compare_dist[min_element_index] = DBL_MAX/2;
        // 循环size-1次
        for(int i = 0; i < G->m_CrossRoad_v.size()-1; i++){
            for(auto crossroad : G->m_CrossRoad_v[min_element_index].JunctionRoad){
                currentPointSite = min_element_index;
                nextPointSite = G->m_Road_v[crossroad.outRoadID].m_CrossRoadToSite;
                if(S[nextPointSite]){
                    continue;
                }
                if(dist[nextPointSite] > dist[currentPointSite] + G->m_Road_v[crossroad.outRoadID].m_dLength) {
                    dist[nextPointSite] = dist[currentPointSite] + G->m_Road_v[crossroad.outRoadID].m_dLength;
                    compare_dist[nextPointSite] = dist[nextPointSite];
                    path[nextPointSite] = currentPointSite;
                }
            }
            min = min_element(compare_dist.begin(), compare_dist.end());
            min_element_index = distance(compare_dist.begin(), min);
            S[min_element_index] = true;
            compare_dist[min_element_index] = DBL_MAX/2;
        }
        for(int i = 0;i<path.size();i++){
            int j = i;
            bool flag = false;
            while( path[j] >= 0) {
                flag = true;
                PointPathFile << path[j] << " ";
                for(auto node:G->m_CrossRoad_v[j].JunctionRoad){
                    if(G->m_Road_v[node.outRoadID].m_CrossRoadToSite == path[j]){
                        RoadPathFile << node.outRoadID << " ";
                    }
                }
                j = path[j];
            }
            if(flag){RoadPathFile << endl;PointPathFile << endl ;}
        }
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
            //一次解析一条路
            auto road_length = elm_Road->FirstAttribute()->Next()->Value();
            auto elm_from = elm_Road->FirstChildElement("from");
            auto elm_to = elm_Road->FirstChildElement("to");
            auto from_attribute = elm_from->FirstAttribute();
            const XMLAttribute *to_attribute = elm_to->FirstAttribute();
            //道路点A，B
            CrossRoad A(strtod(from_attribute->Value(), nullptr), strtod(from_attribute->Next()->Value(), nullptr));
            CrossRoad B(strtod(to_attribute->Value(), nullptr), strtod(to_attribute->Next()->Value(), nullptr));
            //添加A，B点至图中
            addRoad(Map_Graph, A, B, strtod(road_length, nullptr));
            elm_Road = elm_Road->NextSiblingElement("road");
        }
    } else {
        cout << RED << MapFileName << " The map file loading failed" << endl;
        exit(1);
    }
}
