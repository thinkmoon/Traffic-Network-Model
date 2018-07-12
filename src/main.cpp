#include "stdafx.h"
#include "func.h"

long long int SYSTEM_TIME = 0;

vector<queue<int>> v_Route;

/**
 * load route from route file
 * @param Map_graph
 */
void loadRoute(Graph &Map_graph) {
    string str_Path;
    ifstream fin_Route(DIR_RES"route.txt");
    while (getline(fin_Route, str_Path)) {
        stringstream ss_Temp(str_Path);
        queue<int> q_Path_Temp;
        int n_Temp;
        while (ss_Temp >> n_Temp) {
            q_Path_Temp.push(n_Temp);
        }
        v_Route.push_back(q_Path_Temp);
    }
}

/**
 * then generate Vehicle
 * @param G
 */
void generateVehicle(Graph &G) {
    std::random_device rd;
    std::mt19937 mt(rd());
    for (int n_VehicleNum = 0; n_VehicleNum < 1; ++n_VehicleNum) {
        //auto route = v_Route[mt() % v_Route.size()];
        auto route = v_Route[3];
        Vehicle car(n_VehicleNum, route, 0, 0, route.front());
        G.road[route.front()].m_queVehicle.push_back(car);
        this_thread::sleep_for(chrono::milliseconds(1));
    }
}

/**
 * And then run the simulation
 * @param G
 */
void runSimulation(Graph &G) {
    double dist;
    //每一条路的遍历
    for (auto &road:G.road) {
        auto src = road.m_queVehicle;
        decltype(road.m_queVehicle) obj;
        //路内车的遍历
        while (!src.empty()) {
            //弹出一辆车
            auto it = src.front();
            src.pop_front();
            // 当车的时间戳小于实际时间时，才模拟运行
            if (it.time < SYSTEM_TIME) {
                it.fSpec = (100 - road.get_Congestion() - 20) / 3.6;
                dist = it.dDistance + it.fSpec * 10;
                it.time++;

                it.showself();
                //如果车十秒后不在此路
                if (dist >= road.m_dLength) {
                    //路径擦除
                    auto route = it.queRoute;
                    route.pop();
                    //如果抵达终点
                    if (route.empty()) {
                        cout << "it is be shutdown" << endl;
                        exit(0);
                        // 否侧没有抵达终点
                    } else {
                        //获取所在路和下一条路的ID
                        int next = route.front();
                        int RoadTabletSite = G.road[it.m_nSiteRoadID].m_nTrafficLightSite;
                        //判断红绿灯情况
                        G.RoadTable[RoadTabletSite].m_CTrafficLight_Light.clock(SYSTEM_TIME);
                        //如果可以同行
                        if (G.RoadTable[RoadTabletSite].m_CTrafficLight_Light.getStatus(it.m_nSiteRoadID, next)) {
                            it.queRoute = route;
                            it.dDistance = 0;
                            it.m_nSiteRoadID = next;
                            auto *site_road = &G.road[next].m_queVehicle;
                            site_road->push_back(it);
                            //如果不能通行
                        } else {
                            //将距离置为道路长度，表示正在等候红灯
                            it.dDistance = G.road[it.m_nSiteRoadID].m_dLength;
                            cout << " 等待红灯";
                            //车辆塞回去
                            obj.push_back(it);
                        }
                    }
                    //否则，当车十秒后还在此路时
                } else {
                    it.dDistance = dist;
                    obj.push_back(it);
                }
                //否则直接填入
            } else {
                obj.push_back(it);
            }
        }
        road.m_queVehicle = obj;
    }
}

class PointPositon {
public:
    int RoadID, site;
    float tan;
    Point P;

    bool operator<(PointPositon m) const {
        if (site != m.site) {
            return site < m.site;
        } else {
            return tan < m.tan;
        }
    }

};

int computeSite(Point origin, Point aim, float &tan) {
    int site;
    float x = aim.m_fLat - origin.m_fLat;
    float y = aim.m_fLon - origin.m_fLon;
    //计算坐标系
    if (x >= 0 && y >= 0) {
        site = 0;
    } else if (x <= 0 && y >= 0) {
        site = 1;
    } else if (x >= 0 && y <= 0) {
        site = 2;
    } else if (x <= 0 && y <= 0) {
        site = 3;
    }
    //计算sinx的值
    if (y == 0.0) {
//
        tan = FLT_MAX;
    } else {
        tan = x / y;
    }

}

vector<int> computePosition(Graph &G, Point origin, RoadNode *res) {
    vector<int> RoadPosition;
    vector<PointPositon> PP;
    while (res) {
        PointPositon temp;
        temp.P = G.point[res->junctionID];
        temp.RoadID = res->roadID;
        temp.site = computeSite(origin, temp.P, temp.tan);
        PP.push_back(temp);
        res = res->link;
    }
    sort(PP.begin(), PP.end());
    for (auto x: PP) {
        RoadPosition.push_back(x.RoadID);
    }
    return RoadPosition;
}

void initTraffic_Light(Graph &G) {
    int outRoadID, RoadTableNum = 0;
    for (auto it = G.RoadTable.begin(); it != G.RoadTable.end(); it++) {
        RoadTableNum++;
        it->m_CTrafficLight_Light.setType(it->length);
        vector<int> RoadPosition;
        Point origin = G.point[it->junctionID];
        {
            RoadPosition = computePosition(G, origin, it->link);
            switch (RoadPosition.size()) {
                case 2:
                    it->m_CTrafficLight_Light.roadID[4] = RoadPosition[0];
                    outRoadID = G.road[RoadPosition[0]].ParallelRoadID;
                    G.road[outRoadID].m_nTrafficLightSite = RoadTableNum;
                    it->m_CTrafficLight_Light.roadID[5] = outRoadID;

                    it->m_CTrafficLight_Light.roadID[0] = RoadPosition[1];
                    outRoadID = G.road[RoadPosition[1]].ParallelRoadID;
                    it->m_CTrafficLight_Light.roadID[1] = outRoadID;
                    G.road[outRoadID].m_nTrafficLightSite = RoadTableNum;

                    break;
                case 3:
                    it->m_CTrafficLight_Light.roadID[4] = RoadPosition[0];
                    it->m_CTrafficLight_Light.roadID[5] = outRoadID = G.road[RoadPosition[0]].ParallelRoadID;
                    G.road[outRoadID].m_nTrafficLightSite = RoadTableNum;

                    it->m_CTrafficLight_Light.roadID[0] = RoadPosition[1];
                    it->m_CTrafficLight_Light.roadID[1] = outRoadID = G.road[RoadPosition[1]].ParallelRoadID;
                    G.road[outRoadID].m_nTrafficLightSite = RoadTableNum;

                    it->m_CTrafficLight_Light.roadID[2] = RoadPosition[2];
                    outRoadID = it->m_CTrafficLight_Light.roadID[3] = G.road[RoadPosition[2]].ParallelRoadID;
                    G.road[outRoadID].m_nTrafficLightSite = RoadTableNum;
                    break;
                case 4:
                    it->m_CTrafficLight_Light.roadID[4] = RoadPosition[0];
                    it->m_CTrafficLight_Light.roadID[5] = outRoadID = G.road[RoadPosition[0]].ParallelRoadID;
                    G.road[outRoadID].m_nTrafficLightSite = RoadTableNum;

                    it->m_CTrafficLight_Light.roadID[6] = RoadPosition[1];
                    it->m_CTrafficLight_Light.roadID[7] = outRoadID = G.road[RoadPosition[1]].ParallelRoadID;
                    G.road[outRoadID].m_nTrafficLightSite = RoadTableNum;

                    it->m_CTrafficLight_Light.roadID[0] = RoadPosition[2];
                    it->m_CTrafficLight_Light.roadID[1] = outRoadID = G.road[RoadPosition[2]].ParallelRoadID;
                    G.road[outRoadID].m_nTrafficLightSite = RoadTableNum;

                    it->m_CTrafficLight_Light.roadID[2] = RoadPosition[3];
                    it->m_CTrafficLight_Light.roadID[3] = outRoadID = G.road[RoadPosition[3]].ParallelRoadID;
                    G.road[outRoadID].m_nTrafficLightSite = RoadTableNum;
                    break;
            }
        }

    }
}

int main() {
    Graph Map_Graph;
    parseMap(Map_Graph, DIR_RES"map.xml");
//    generateTestGraph(&Map_Graph);
    //Map_Graph.show();
    cout << "Parse succeed" << endl;
    initTraffic_Light(Map_Graph);
    loadRoute(Map_Graph);
    generateVehicle(Map_Graph);
    cout << Map_Graph.road[0].m_nTrafficLightSite;
    for (int i = 0; i < 8; i++) {
        cout << " " << Map_Graph.RoadTable[2].m_CTrafficLight_Light.roadID[i];
    }
    //calcShortestPath(&Map_Graph);
    int time = 0;
//    while (true) {
//        cout << "现在是" << SYSTEM_TIME++ << "0s " << endl;
//        runSimulation(Map_Graph);
//    }
    cout << endl << "end" << endl;
    return 0;
}







