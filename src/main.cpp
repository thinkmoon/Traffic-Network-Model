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
        auto route = v_Route[mt() % v_Route.size()];
        Vehicle car(n_VehicleNum, route, 0, 0);
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
    for (auto &road:G.road) {
        auto src = road.m_queVehicle;
        decltype(road.m_queVehicle) obj;
        while (!src.empty()) {
            auto it = src.front();
            src.pop_front();
            // 当车的时间戳小于实际时间时，才模拟运行
            if (it.time < SYSTEM_TIME) {
                it.fSpec = (100 - road.get_Congestion() - 20) / 3.6;
                dist = it.dDistance + it.fSpec * 10;
                it.time++;
                it.showself();
                if (dist >= road.m_dLength) {
                    it.queRoute.pop();
                    if (it.queRoute.empty()) {
                        cout << "it is be shutdown" << endl;
                        exit(0);
                    } else {
                        it.dDistance = 0;

                        int next = it.queRoute.front();

                        auto *site_road = &G.road[next].m_queVehicle;
                        site_road->push_back(it);
                    }
                } else {
                    it.dDistance = dist;
                    obj.push_back(it);
                }
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
    for (auto it = G.RoadTable.begin(); it != G.RoadTable.end(); it++) {
        it->m_CTrafficLight_Light.setType(it->length);
        vector<int> RoadPosition;
        Point origin = G.point[it->junctionID];
        {
            RoadPosition = computePosition(G, origin, it->link);
            switch (RoadPosition.size()) {
                case 2:
                    it->m_CTrafficLight_Light.roadID[0] = RoadPosition[0];
                    it->m_CTrafficLight_Light.roadID[4] = RoadPosition[1];
            }
        }

    }
}

int main() {
    Graph Map_Graph;
    parseMap(Map_Graph, DIR_RES"map.xml");
//    generateTestGraph(&Map_Graph);
    Map_Graph.show();
    cout << "Parse succeed" << endl;
    initTraffic_Light(Map_Graph);
    loadRoute(Map_Graph);
    generateVehicle(Map_Graph);
    //calcShortestPath(&Map_Graph);
    int time = 0;
//    while (true) {
//        cout << "现在是" << SYSTEM_TIME++ << "0s " << endl;
//        runSimulation(Map_Graph);
//    }
    cout << "end" << endl;
    return 0;
}







