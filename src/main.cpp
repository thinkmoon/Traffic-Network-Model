#include "stdafx.h"
#include "func.h"

long long int  SYSTEM_TIME = 0;
struct Route{
    queue<int> que_Path;
    int n_RoadID;
    Route(int n_RoadID,queue<int> que_Path):n_RoadID(n_RoadID),que_Path(que_Path){};
};
vector<Route> v_Route;
/**
 * load route from route file
 * @param Map_graph
 */
void loadRoute(Graph &Map_graph) {
    int numVehicle =0 ;
    string str_Path; //字符串的路径
    ifstream fin_Route(DIR_RES"route.txt");//路径文件
    // 循环加载路径
    while (getline(fin_Route, str_Path)) {
        int n_Begin=-1,n_Last=-1,n_Falg=0,n_RoadID=-1;
        stringstream ss_Temp(str_Path);
        queue<int> q_Path_Temp;
        int n_Temp;
        while (ss_Temp >> n_Temp) {
            ++n_Falg;
            q_Path_Temp.push(n_Temp);
            if(n_Falg == 1){n_Begin = n_Temp;}
            else if(n_Falg == 2){n_Last = n_Temp;}
        }
        if(n_Begin != -1 && n_Last != -1){
            n_RoadID = Map_graph.getRoadID(n_Begin,n_Last);
            if(n_RoadID != -1){
                Route route(n_RoadID,q_Path_Temp);
                v_Route.push_back(route);
                numVehicle++;
            }
        }
    }
    if(numVehicle <= 0){
        cout << " no vehicle" << endl;
        exit(0);
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
        Vehicle car(n_VehicleNum,route.que_Path, 0, 0);
        G.road[route.n_RoadID].m_queVehicle.push_back(car);
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
            if(it.time < SYSTEM_TIME){
                it.fSpec =  ( 100 - road.get_Congeestion() - 20) / 3.6;
                dist = it.dDistance + it.fSpec * 10;
                it.time++;
                it.showself();
                if (dist >= road.m_dLength) {
                    if (it.queRoute.empty()) {
                        cout << "it is be shutdown" << endl;
                        exit(0);
                    } else {
                        it.dDistance = 0;
                        int next = it.queRoute.front();
                        it.queRoute.pop();
                        auto *site_road = &G.road[next].m_queVehicle;
                        site_road->push_back(it);
                    }
                } else {
                    it.dDistance = dist;
                    obj.push_back(it);
                }
            }else{
                obj.push_back(it);
            }
        }
        road.m_queVehicle = obj;
    }
}
int main() {
    Graph Map_Graph;
    parseMap(Map_Graph, DIR_RES"map.xml");
//    //generateTestGraph(&Map_Graph);
    Map_Graph.show();
//    cout << "Parse succeed" << endl;
    loadRoute(Map_Graph);
    generateVehicle(Map_Graph);
    //calcShortestPath(&Map_Graph);
    int time=0;
    while (true){
        cout << "现在是" << SYSTEM_TIME++ << "0s " << endl;
        runSimulation(Map_Graph);
    }
    cout << "end" << endl;
    return 0;
}







