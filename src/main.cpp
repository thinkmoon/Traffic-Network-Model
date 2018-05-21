#include "stdafx.h"
#include "func.h"

vector<queue<int>> Route; //路径容器
/**
 * load route from route file
 * @param Map_graph
 */
void loadRoute(Graph &Map_graph) {
    string str_Path; //字符串的路径
    ifstream fin_Route(DIR_RES"route.txt");//路径文件
    // 循环加载路径
    while (getline(fin_Route, str_Path)) {
        stringstream ss_Temp(str_Path);
        queue<int> q_Path_Temp;
        int n_Temp;
        while (ss_Temp >> n_Temp) { q_Path_Temp.push(n_Temp); }
        Route.push_back(q_Path_Temp);
    }
}

/**
 * then generate Vehicle
 * @param G
 */
void generateVehicle(Graph &G) {
    std::random_device rd;
    std::mt19937 mt(rd());
    for (int n_VehicleNum = 0; n_VehicleNum < 100; ++n_VehicleNum) {
        auto route = Route[mt() % Route.size()];
        Vehicle car(route, 0, 0);
        cout << route.front() << endl;
        G.road[route.front()].m_queVehicle.push_back(car);
    }
    cout << "size:" << G.road.size() << endl;
//    for (auto temp:G.road){
//        temp.showqueVehicle();
//    }
}

/**
 * And then run the simulation
 * @param G
 */
void runSimulation(Graph &G) {
    auto begin = std::chrono::steady_clock::now();
    double dist;
    for (auto &road:G.road) {
        auto src = road.m_queVehicle;
        decltype(road.m_queVehicle) obj;
        while (!src.empty()) {
            auto it = src.front();
            src.pop_front();
            it.showself();
            dist = it.dDistance + it.fSpec * 5;
            if (dist >= road.m_dLength) {
                if (it.queRoute.empty()) {
                    cout << "----------------------" << endl;
                } else {
                    it.dDistance = 0;
                    int next = it.queRoute.front();
                    it.queRoute.pop();
                    auto *site_road = &G.road[next].m_queVehicle;
                    auto test = G.road[192];
                    site_road->push_back(it);
                }
            } else {
                it.dDistance = dist;
                obj.push_back(it);
            }
        }
        road.m_queVehicle = obj;
//        for(auto i=road.m_queVehicle_pos.begin();i<road.m_queVehicle_pos.end();++i){
//            i->showself();
//            exit(0);
//        }

//        for(auto it = item.m_queVehicle_pos.end(); it != item.m_queVehicle_pos.begin(); it--){
//            dist=it->dDistance + it->fSpec * 5;
//            if(dist > item.m_dLength){
//                Vehicle temp = item.m_queVehicle_pos.back();
//                item.m_queVehicle_pos.pop_back();
//                if(temp.queRoute.empty()){
//                    cout << "---------------------------------" << endl;
//                }else{
//                    auto next = temp.queRoute.front();
//                    temp.queRoute.pop();
//                    G.road[next].m_queVehicle_pos.push_back(temp);
//                }
//            }else{


//                it->dDistance = dist;
//            }
//        }
    }
    int flag = 0;
    for (auto road:G.road) {
        flag += road.m_queVehicle.size();
    }
    if (flag == 0) exit(0);
    auto end = std::chrono::steady_clock::now();
    auto diff = (end - begin).count();//end-begin得到一个duration类型
    //std::cout<<std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()<<std::endl;
}
int main() {
    Graph Map_Graph;
    parseMap(Map_Graph, DIR_RES"map.xml");
//    //generateTestGraph(&Map_Graph);
//    Map_Graph.show();
//    cout << "Parse succeed" << endl;
    loadRoute(Map_Graph);
    generateVehicle(Map_Graph);
    //calcShortestPath(&Map_Graph);
//    while (1) {
//        runSimulation(Map_Graph);
//    }
    cout << "end" << endl;
    return 0;
}







