#include "stdafx.h"
#include "func.h"

long long int SYSTEM_TIME = 0;
int VehicleNum = 500000, endVehicleNum = 0;
vector<queue<int>> v_Route;

int AllTime = 0;
int areaID[10][5] = {0};
int areaRoadNum[10][5] = {0};
int areaCongestion[10][5] = {0};
int congestion = 0;
clock_t start, finish;

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
    string str;
    int rand[500000] = {0};
    int i = 0;
    ifstream fin_Route(DIR_DATA"rand.txt");
    while (getline(fin_Route, str)) {
        stringstream ss_Temp(str);
        int n_Temp;
        while (ss_Temp >> n_Temp) {
            rand[i++] = n_Temp;
        }
    }
    for (int n_VehicleNum = 0; n_VehicleNum < VehicleNum; ++n_VehicleNum) {
        auto route = v_Route[rand[n_VehicleNum]];
        Vehicle car(n_VehicleNum, route, 0, 0, route.front());
        G.m_Road_v[route.front()].m_queVehicle.push_back(car);
    }
//    for (int n_VehicleNum = 0; n_VehicleNum < v_Route.size(); ++n_VehicleNum) {
//        auto route = v_Route[n_VehicleNum];
//        Vehicle car(n_VehicleNum, route, 0, 0, route.front());
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
    if (endVehicleNum == VehicleNum) {
        finish = clock();
        cout << BLUE << "程序模拟结束, 耗时:" << finish - start << "ms" << endl;
        cout << BLUE << "初始平均拥挤度:" << congestion << endl;
        cout << BLUE << "所有车辆到达终点总消耗时间:" << SYSTEM_TIME << "个单位" << endl;
        cout << BLUE << "所有车辆到达终点平均消耗时间:" << AllTime / VehicleNum << "个单位" << endl;
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
//                if (it.weight != 100) {
//                    cout << "weight:" << it.weight << endl;
//                }
                it.fSpec = (100 - road.get_Congestion()) / 3.6;
                if (it.fSpec < 0) {
                    cout << RED << "在道路：" << road.m_nID << "上,发现一辆异常车辆" << it.m_nID << "车速" << it.fSpec << "当前道路拥挤度"
                         << road.m_nCongestion << endl;
                    it.showself();
                    exit(1);
                }
                dist = it.dDistance + it.fSpec;
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
                        AllTime+=SYSTEM_TIME;
//                        cout << YELLOW << endVehicleNum << "号车抵达终点" << endl;
                        // 否侧没有抵达终点
                    } else {
                        //下一条路的ID
                        int next = route.front();
                        // 即将通行的路口
                        int next_CrossRoadID = G.m_Road_v[site].m_CrossRoadToSite;
                        //判断红绿灯情况
                        G.m_CrossRoad_v[next_CrossRoadID].m_CTrafficLight_Light.clock(SYSTEM_TIME);
                        //如果可以通行
                        if (G.m_CrossRoad_v[next_CrossRoadID].m_CTrafficLight_Light.getStatus(it.m_nSiteRoadID, next)) {
                            if (it.dDistance == G.m_Road_v[it.m_nSiteRoadID].m_dLength) {
                                G.m_CrossRoad_v[next_CrossRoadID].m_CTrafficLight_Light.subWait(it.m_nSiteRoadID, next,
                                                                                                it.weight, it.value);
                                it.value = 0;
                            }
                            it.queRoute = route;
                            it.dDistance = 0;
                            it.m_nSiteRoadID = next;
                            auto *site_road = &G.m_Road_v[next].m_queVehicle;
                            site_road->push_back(it);
                            //如果不能通行
                        } else {
                            G.m_CrossRoad_v[next_CrossRoadID].m_CTrafficLight_Light.addWait(it.m_nSiteRoadID, next,
                                                                                            it.weight);
                            it.value++;
                            //将距离置为道路长度，表示正在等候红灯
                            it.dDistance = G.m_Road_v[it.m_nSiteRoadID].m_dLength;
                            //车辆塞回去
                            queVehicleObj.push_back(it);
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
    if (flag) {
        cout << GREEN << "路已被肃清" << endl;
        finish = clock();
        cout << BLUE << "程序模拟结束, 耗时:" << finish - start << "ms" << endl;
        exit(1);
    }
}

void initTraffic_Light(Graph &G) {
    for (auto it = G.m_CrossRoad_v.begin(); it != G.m_CrossRoad_v.end(); it++) {
        it->m_CTrafficLight_Light.setType(it->JunctionRoad.size());
        it->m_CTrafficLight_Light.setID(it->m_nID);
        {
            switch (it->JunctionRoad.size()) {
                case 4:
                    it->m_CTrafficLight_Light.roadID[2] = it->JunctionRoad[3].inRoadID;
                    it->m_CTrafficLight_Light.roadID[3] = it->JunctionRoad[3].outRoadID;
                    it->m_CTrafficLight_Light.mp[it->JunctionRoad[3].inRoadID] = 2;
                    it->m_CTrafficLight_Light.mp[it->JunctionRoad[3].outRoadID] = 3;
                case 3:
                    it->m_CTrafficLight_Light.roadID[6] = it->JunctionRoad[2].inRoadID;
                    it->m_CTrafficLight_Light.roadID[7] = it->JunctionRoad[2].outRoadID;
                    it->m_CTrafficLight_Light.mp[it->JunctionRoad[2].inRoadID] = 6;
                    it->m_CTrafficLight_Light.mp[it->JunctionRoad[2].outRoadID] = 7;
                case 2:
                    it->m_CTrafficLight_Light.roadID[0] = it->JunctionRoad[1].inRoadID;
                    it->m_CTrafficLight_Light.roadID[1] = it->JunctionRoad[1].outRoadID;
                    it->m_CTrafficLight_Light.mp[it->JunctionRoad[1].inRoadID] = 0;
                    it->m_CTrafficLight_Light.mp[it->JunctionRoad[1].outRoadID] = 1;
                case 1:
                    it->m_CTrafficLight_Light.roadID[5] = it->JunctionRoad[0].outRoadID;
                    it->m_CTrafficLight_Light.roadID[4] = it->JunctionRoad[0].inRoadID;
                    it->m_CTrafficLight_Light.mp[it->JunctionRoad[0].inRoadID] = 4;
                    it->m_CTrafficLight_Light.mp[it->JunctionRoad[0].outRoadID] = 5;
            }
        }
    }
}

// 创造固定车辆数的随机数
void createRand() {
    ofstream randFile(DIR_DATA"rand.txt");
    std::random_device rd;
    std::mt19937 mt(rd());
    for (int i = 0; i < VehicleNum; i++) {
        randFile << mt() % v_Route.size() << " ";
    }
    randFile << endl;
}

// 计算图边界
void calcBorder(Graph &G) {
    double min_longtitude = G.m_CrossRoad_v[0].m_fLon, max_longtitude = G.m_CrossRoad_v[0].m_fLon, min_latitude = G.m_CrossRoad_v[0].m_fLat, max_latitude = G.m_CrossRoad_v[0].m_fLat;
    for (auto item: G.m_CrossRoad_v) {
        if (item.m_fLat < min_latitude) {
            min_latitude = item.m_fLat;
        }
        if (item.m_fLat > max_latitude) {
            max_latitude = item.m_fLat;
        }
        if (item.m_fLon < min_longtitude) {
            min_longtitude = item.m_fLon;
        }
        if (item.m_fLon > max_longtitude) {
            max_longtitude = item.m_fLon;
        }
    }
    cout << "经度差" << max_longtitude << " - " << min_longtitude << " = " << max_longtitude - min_longtitude << ",经度单位值:"
         << (max_longtitude - min_longtitude) / 10 << endl;
    cout << "纬度差" << max_latitude << " - " << min_latitude << " = " << max_latitude - min_latitude << ", 纬度单位值:"
         << (max_latitude - min_latitude) / 5 << endl;
}

// 切割图
void cutGraph(Graph &G) {

    double min_longtitude = G.m_CrossRoad_v[0].m_fLon, max_longtitude = G.m_CrossRoad_v[0].m_fLon, min_latitude = G.m_CrossRoad_v[0].m_fLat, max_latitude = G.m_CrossRoad_v[0].m_fLat;
    for (auto item: G.m_CrossRoad_v) {
        if (item.m_fLat < min_latitude) {
            min_latitude = item.m_fLat;
        }
        if (item.m_fLat > max_latitude) {
            max_latitude = item.m_fLat;
        }
        if (item.m_fLon < min_longtitude) {
            min_longtitude = item.m_fLon;
        }
        if (item.m_fLon > max_longtitude) {
            max_longtitude = item.m_fLon;
        }
    }
    cout << "经度差" << max_longtitude << " - " << min_longtitude << " = " << max_longtitude - min_longtitude << ",经度单位值:"
         << (max_longtitude - min_longtitude) / 10 << endl;
    cout << "纬度差" << max_latitude << " - " << min_latitude << " = " << max_latitude - min_latitude << ", 纬度单位值:"
         << (max_latitude - min_latitude) / 5 << endl;
    double unit_Lon = (max_longtitude - min_longtitude) / 10, unit_lat = (max_latitude - min_latitude) / 5;
    cout << endl;
    for (auto it = G.m_CrossRoad_v.begin(); it < G.m_CrossRoad_v.end(); it++) {
        it->row = (it->m_fLon - min_longtitude) / unit_Lon;
        it->col = (it->m_fLat - min_latitude) / unit_lat;
        if (it->row == 10) {
//            cout << it->m_fLon << " " << it->m_fLat << endl;
            it->row--;
        }
        if (it->col == 5) {
//            cout << it->m_fLon << " " << it->m_fLat << endl;
            it->col--;
        }
//        if(it->m_fLon == max_longtitude || it->m_fLat == max_latitude) {
//            cout << it->row << " " << it->col << endl;
//        }
    }
    for (auto item:G.m_CrossRoad_v) {
        areaID[item.row][item.col]++;
    }
    cout << "----区域路口表---" << endl;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 5; ++j) {
            cout << areaID[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// 计算区域道路数
void calcAreaNum(Graph &G) {
    for (auto item:G.m_Road_v) {
        int row = G.m_CrossRoad_v[item.m_CrossRoadFromSite].row;
        int col = G.m_CrossRoad_v[item.m_CrossRoadFromSite].col;
        areaRoadNum[row][col]++;
    }
    cout << "----区域道路表---" << endl;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 5; ++j) {
            cout << areaRoadNum[i][j] << " ";
        }
        cout << endl;
    }
}

// 计算区域拥挤度
void calcAreaCongestion(Graph &G) {
    for (auto item:G.m_Road_v) {
        int row = G.m_CrossRoad_v[item.m_CrossRoadFromSite].row;
        int col = G.m_CrossRoad_v[item.m_CrossRoadFromSite].col;
        areaCongestion[row][col] += item.m_nCongestion;
    }
//    cout << "----区域总拥挤度表---" << endl;
//    for (int i = 0; i < 10; ++i) {
//        for (int j = 0; j < 5; ++j) {
//            cout << areaCongestion[i][j] << " ";
//        }
//        cout << endl;
//    }
    cout << "----区域加权拥挤度表---" << endl;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (areaRoadNum[i][j] != 0) {
                areaID[i][j] = areaCongestion[i][j] / areaRoadNum[i][j];
            }
            cout << areaID[i][j] << " ";
        }
        cout << endl;
    }
}

// 计算未来十分钟会到达的区域ID
void calcFutureTo(Graph &G) {
    for (auto &road:G.m_Road_v) {
        auto queVehicleSrc = road.m_queVehicle;
        decltype(road.m_queVehicle) queVehicleObj;
        while (!queVehicleSrc.empty()) {
            auto it = queVehicleSrc.front();
            queVehicleSrc.pop_front();
            if (!it.queRoute.empty()) {
                it.siteArea[0] = G.m_CrossRoad_v[road.m_CrossRoadFromSite].row;
                it.siteArea[1] = G.m_CrossRoad_v[road.m_CrossRoadFromSite].col;
                // 预测100个单位时间
                float dist = it.fSpec * 10;
                auto route = it.queRoute;
                dist -= road.m_dLength - it.dDistance;
                if (dist < 0 || route.empty()) {
                    it.futureArea[0] = it.siteArea[0];
                    it.futureArea[1] = it.siteArea[1];
                } else {
                    int futureID = route.front();
                    while (!route.empty() && dist > 0) {
                        futureID = route.front();
                        dist -= G.m_Road_v[futureID].m_dLength;
                        route.pop();
                    }
                    it.futureArea[0] = G.m_CrossRoad_v[G.m_Road_v[futureID].m_CrossRoadFromSite].row;
                    it.futureArea[1] = G.m_CrossRoad_v[G.m_Road_v[futureID].m_CrossRoadFromSite].col;
                }
            }
            queVehicleObj.push_back(it);
        }
        road.m_queVehicle = queVehicleObj;
    }
}

// 调整车俩权值
void adjustWeight(Graph &G) {
    for (auto &road:G.m_Road_v) {
        auto queVehicleSrc = road.m_queVehicle;
        decltype(road.m_queVehicle) queVehicleObj;
        while (!queVehicleSrc.empty()) {
            auto it = queVehicleSrc.front();
            queVehicleSrc.pop_front();
            if (!it.queRoute.empty()) {
                int diff = areaID[it.siteArea[0]][it.siteArea[1]] - areaID[it.futureArea[0]][it.futureArea[1]];
                if (diff == 0 || it.dDistance == G.m_Road_v[it.m_nSiteRoadID].m_dLength) {
                    it.weight == 100;
                } else {
                    it.weight += diff;
                }
                if(it.weight < 0) it.weight = 0;
            }
            queVehicleObj.push_back(it);
        }
        road.m_queVehicle = queVehicleObj;
    }
}



int main() {
    Graph Map_Graph;
    parseMap(Map_Graph, DIR_RES"map.xml");
    Map_Graph.output();
    cout << BLACK << "Parse succeed" << endl;
//    calcShortestPath(&Map_Graph);
    initTraffic_Light(Map_Graph);
    loadRoute(Map_Graph);
    createRand();
//    calcBorder(Map_Graph);
    cutGraph(Map_Graph);
    calcAreaNum(Map_Graph);
    generateVehicle(Map_Graph);
    start = clock();
    cout << BLUE << "程序模拟开始" << endl;
    while (true) {
        SYSTEM_TIME++;
        runSimulation(Map_Graph);
        calcAreaCongestion(Map_Graph);
        calcFutureTo(Map_Graph);
        adjustWeight(Map_Graph);
        if(SYSTEM_TIME == 1){
            int n = 0;
            for(int i = 0; i < 10; ++i){
                for(int j = 0; j < 5; ++j){
                    if(areaID[i][j] != 0) {
                        congestion+=areaID[i][j];
                        n++;
                    }
                }
            }
            congestion = congestion / n;
            cout << congestion << endl;
        }
        exit(0);
    }
    return 0;
}







