#include "stdafx.h"
#include "func.h"

long long int SYSTEM_TIME = 0;
int VehicleNum = 1000;
int endVehicleNum = 0;
vector<queue<int>> v_Route;

/**
 * load route from route file
 * @param Map_graph
 */
void loadRoute(Graph &Map_graph) {
    string str_Path;
    ifstream fin_Route(DIR_RES"RoadPath.txt");
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
    for (int n_VehicleNum = 0; n_VehicleNum < VehicleNum; ++n_VehicleNum) {
        auto route = v_Route[mt() % v_Route.size()];
        Vehicle car(n_VehicleNum, route, 0, 0, route.front());
        G.m_Road_v[route.front()].m_queVehicle.push_back(car);
        this_thread::sleep_for(chrono::milliseconds(1));
    }
//    for (int i = 0; i < v_Route.size(); ++i) {
//        auto route = v_Route[i];
//        Vehicle car(i,route,0,0,route.front());
//        G.m_Road_v[route.front()].m_queVehicle.push_back(car);
//    }
}

/**
 * And then run the simulation
 * @param G
 */
void runSimulation(Graph &G) {
    double dist;
    //每一条路的遍历
    if(endVehicleNum == VehicleNum) {
        cout << "程序运行结束" << endl;
        exit(0);
    }
    bool flag = true;
    for (auto &road:G.m_Road_v) {
        auto queVehicleSrc = road.m_queVehicle;
        decltype(road.m_queVehicle) queVehicleObj;
        //路内车的遍历
        while (!queVehicleSrc.empty()) {
            flag = false;
            //弹出一辆车
            auto it = queVehicleSrc.front();
            queVehicleSrc.pop_front();
            // 当车的时间戳小于实际时间时，才模拟运行
            if (it.time < SYSTEM_TIME) {
                it.fSpec = (100 - road.get_Congestion() ) / 3.6;
                if(it.fSpec < 0) {
                    cout << RED << "在道路："<< road.m_nID << "上,发现一辆异常车辆" << it.m_nID << "车速" << it.fSpec << "当前道路拥挤度" << road.m_nCongestion << endl;
                    it.showself();
                    exit(1);
                }
                dist = it.dDistance + it.fSpec * 10;
                it.time++;

//                it.showself();
                //如果车十秒后不在此路
                if (dist >= road.m_dLength) {
                    //路径擦除
                    auto route = it.queRoute;
                    int site = it.m_nSiteRoadID;
                    route.pop();
                    //如果抵达终点
                    if (route.empty()) {
                        endVehicleNum++;
                        cout << GREEN << "endVehicleNum:" << endVehicleNum << endl;
                        // 否侧没有抵达终点
                    } else {
                        //下一条路的ID
                        int next = route.front();
                        //判断红绿灯情况
                        G.m_CrossRoad_v[G.m_Road_v[site].m_CrossRoadToSite].m_CTrafficLight_Light.clock(SYSTEM_TIME);
                        //如果可以通行
                        printf(BLUE"路口ID:%d,打算从%d号路转至%d,路口数%d\n",G.m_Road_v[site].m_CrossRoadToSite,it.m_nSiteRoadID,next,G.m_CrossRoad_v[G.m_Road_v[site].m_CrossRoadToSite].JunctionRoad.size());
                        try {
                            if (G.m_CrossRoad_v[G.m_Road_v[site].m_CrossRoadToSite].m_CTrafficLight_Light.getStatus(
                                    it.m_nSiteRoadID, next)) {
                                if(it.dDistance == G.m_Road_v[it.m_nSiteRoadID].m_dLength){
                                    G.m_CrossRoad_v[G.m_Road_v[site].m_CrossRoadToSite].m_CTrafficLight_Light.subWait(it.m_nSiteRoadID,next);
                                }
                                it.queRoute = route;
                                it.dDistance = 0;
                                it.m_nSiteRoadID = next;
                                auto *site_road = &G.m_Road_v[next].m_queVehicle;
                                site_road->push_back(it);
                                //如果不能通行
                            } else {
                                G.m_CrossRoad_v[G.m_Road_v[site].m_CrossRoadToSite].m_CTrafficLight_Light.addWait(it.m_nSiteRoadID,next);
                                //将距离置为道路长度，表示正在等候红灯
                                it.dDistance = G.m_Road_v[it.m_nSiteRoadID].m_dLength;
                                //车辆塞回去
                                queVehicleObj.push_back(it);
                            }
                        } catch(const char* msg) {
                            printf(RED"路口ID:%d,打算从%d号路转至%d\n",G.m_CrossRoad_v[G.m_Road_v[site].m_CrossRoadToSite].m_nID,it.m_nSiteRoadID,next);
                        }
                    }
                    //否则，当车十秒后还在此路时
                } else {
                    it.dDistance = dist;
                    queVehicleObj.push_back(it);
                }
                //否则直接填入
            } else {
                queVehicleObj.push_back(it);
            }
        }
        road.m_queVehicle = queVehicleObj;
    }
    if(flag){
        cout << GREEN << "路已被肃清" << endl;
        exit(1);
    }
    }

void initTraffic_Light(Graph &G) {
    for (auto it = G.m_CrossRoad_v.begin(); it != G.m_CrossRoad_v.end(); it++) {
        it->m_CTrafficLight_Light.setType(it->JunctionRoad.size());
        {
            if(it->JunctionRoad.size() == 1){
                it->m_CTrafficLight_Light.roadID[5] = it->JunctionRoad[0].outRoadID;
                it->m_CTrafficLight_Light.roadID[4] = it->JunctionRoad[0].inRoadID;
            }else if(it->JunctionRoad.size() == 2){
                it->m_CTrafficLight_Light.roadID[5] = it->JunctionRoad[0].outRoadID;
                it->m_CTrafficLight_Light.roadID[4] = it->JunctionRoad[0].inRoadID;

                it->m_CTrafficLight_Light.roadID[0] = it->JunctionRoad[1].inRoadID;
                it->m_CTrafficLight_Light.roadID[1] = it->JunctionRoad[1].outRoadID;
            }else if(it->JunctionRoad.size() == 3){
                it->m_CTrafficLight_Light.roadID[5] = it->JunctionRoad[0].outRoadID;
                it->m_CTrafficLight_Light.roadID[4] = it->JunctionRoad[0].inRoadID;

                it->m_CTrafficLight_Light.roadID[0] = it->JunctionRoad[1].inRoadID;
                it->m_CTrafficLight_Light.roadID[1] = it->JunctionRoad[1].outRoadID;

                it->m_CTrafficLight_Light.roadID[6] = it->JunctionRoad[2].inRoadID;
                it->m_CTrafficLight_Light.roadID[7] = it->JunctionRoad[2].outRoadID;
            }else if(it->JunctionRoad.size() == 4){
                it->m_CTrafficLight_Light.roadID[5] = it->JunctionRoad[0].outRoadID;
                it->m_CTrafficLight_Light.roadID[4] = it->JunctionRoad[0].inRoadID;

                it->m_CTrafficLight_Light.roadID[0] = it->JunctionRoad[1].inRoadID;
                it->m_CTrafficLight_Light.roadID[1] = it->JunctionRoad[1].outRoadID;

                it->m_CTrafficLight_Light.roadID[6] = it->JunctionRoad[2].inRoadID;
                it->m_CTrafficLight_Light.roadID[7] = it->JunctionRoad[2].outRoadID;

                it->m_CTrafficLight_Light.roadID[2] = it->JunctionRoad[3].inRoadID;
                it->m_CTrafficLight_Light.roadID[3] = it->JunctionRoad[3].outRoadID;
            }
        }

    }
}

int main() {
    Graph Map_Graph;
    parseMap(Map_Graph, DIR_RES"map.xml");
    // Map_Graph.output();
    cout << BLACK << "Parse succeed" << endl;
    // calcShortestPath(&Map_Graph);
    initTraffic_Light(Map_Graph);
    loadRoute(Map_Graph);
    generateVehicle(Map_Graph);
    auto time_now = chrono::system_clock::now();
    auto duration_in_ms = chrono::duration_cast<chrono::milliseconds>(time_now.time_since_epoch());
    cout << duration_in_ms.count();
    while (true) {
        SYSTEM_TIME++;
        runSimulation(Map_Graph);
    }
    return 0;
}







