#include "stdafx.h"

#include "func.h"

struct route_node {
    int outset;
    vector<queue<int>> path;
};
vector<route_node> route;

void loadRoute(Graph &Map_graph) {
    string str;
    vector<string> v_str;
    ifstream fcin(DIR_RES"route.txt");
    int i = 0, temp;
    auto node = new route_node();
    while (getline(fcin, str)) {
        stringstream ss(str);
        queue<int> q_path;
        while (ss >> temp)
            q_path.push(temp);
        //cout << temp << endl;
        if (q_path.front() == i) {
            node->path.push_back(q_path);
        } else {
            i = q_path.front();
//            for(auto item:node->path){
//                while(!item.empty()){
//                    cout << item.front() << " ";
//                    item.pop();
//                }
//                cout << endl;
//            }
            route.push_back(*node);
            delete node;
            node = new route_node();
            node->path.push_back(q_path);
        }
    }
    route.push_back(*node);
    delete node;
//   cout << route[6812].path.size() << endl;
//    for(auto route_node:route){
//        for(auto item:route_node.path){
//           while(!item.empty()){
//               cout << item.front() << " ";
//               item.pop();
//           }
//            cout << endl;
//        }
//    }
//    cout << route.size() << endl;
//    stringstream ss(str);
//    {
//        int temp;
//        while (ss >> temp)
//            car->queRoute.push(temp);
//    }
}

void generateVehicle(Graph &G) {
//    for(auto & item:G.road) {
//        std::random_device rd;
//        std::mt19937 gen(rd());
//        std::uniform_int_distribution<> d(0, 100);
//        std::default_random_engine e;
//        e.seed(time(0));
//        item.m_nCongestion_pos = round(d(gen));
//        item.m_nCongestion_neg = round(d(gen));
//        float spec;
//        int id,choosed_path,numVehicle = 50.0 * item.m_dLength/item.m_nCongestion_pos;
//        double distance = item.m_dLength / numVehicle;
//        for (int i = 0; i < numVehicle; i++) {
//           spec = (( 100 - item.m_nCongestion_pos ) + (20-(int)round(d(gen))%20) );
//            id = item.m_CPoint_from.m_nID;
//            choosed_path = e()%route[id].path.size();
//            queue<int> r = route[id].path[choosed_path];
//            Vehicle  car(r,spec,i*distance);
//            item.m_queVehicle_pos.push_back(car);
//            //car->showself();
//        }
//        numVehicle = item.m_nCongestion_neg/2 * item.m_dLength;
//        distance = item.m_dLength / numVehicle;
//        for (int i = 0; i < numVehicle;++i){
//            spec = (( 100 - item.m_nCongestion_neg ) + ( 20 - (int)round(d(gen))%20) )/ 3.6;
//            id = item.m_CPoint_to.m_nID;
//            choosed_path = e()%route[id].path.size();
//            queue<int> r = route[id].path[choosed_path];
//            Vehicle  car(r,spec,-i*distance);
//            item.m_queVehicle_neg.push_back(car);
//            //car->showself();
//        }
//    }
    int choosed_path;
    std::default_random_engine e;
    cout << " route.size(): " << e() % route.size();
    for (int i = 0; i < 50; ++i) {
        auto choose_node = e() % route.size();
        choosed_path = e() % route[choose_node].path.size();
        auto path = route[choose_node].path[choosed_path];
        int outset = path.front();
        path.pop();
        if (path.empty()) {

        } else {
            int througth = path.front();
            RoadNode *p = G.RoadTable[outset].link;
            while (p != nullptr) {
                if (througth == p->junctionID) {
                    Road *road = &G.road[p->roadID];
                    double spec = 5;
                    Vehicle car(route[choose_node].path[choosed_path], spec, 0);
                    G.road[p->roadID].m_queVehicle_pos.push_back(car);
                    road->m_nCongestion_pos = road->m_queVehicle_pos.size() / road->m_dLength * 50;
                    break;
                }
                p = p->link;
            }
            // cout << endl;
        }
    }
//    int count=0;
//    for(auto item:G.road){
//        for(auto it=item.m_queVehicle_pos.begin();it<item.m_queVehicle_pos.end();++it) {
//            it->showself();
//            ++count;
//        }
//    }
//    cout << "count:" <<count << endl;
    //G.road[0].m_queVehicle_pos.front().showself();
}

void runSimulation(Graph &G) {
    auto begin = std::chrono::steady_clock::now();
    double dist;
    for (auto &road:G.road) {
        auto src = road.m_queVehicle_pos;
        decltype(road.m_queVehicle_pos) obj;
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
                    auto *site_road = &G.road[next].m_queVehicle_pos;
                    auto test = G.road[192];
                    site_road->push_back(it);
                }
            } else {
                it.dDistance = dist;
                obj.push_back(it);
            }
        }
        road.m_queVehicle_pos = obj;
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
        flag += road.m_queVehicle_pos.size();
    }
    if (flag == 0) exit(0);
    auto end = std::chrono::steady_clock::now();
    auto diff = (end - begin).count();//end-begin得到一个duration类型
    //std::cout<<std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()<<std::endl;
}
int main() {
    Graph Map_Graph;
    parseMap(Map_Graph, DIR_RES"map.xml");
    //generateTestGraph(&Map_Graph);
    //Map_Graph.show();
    cout << "Parse succeed" << endl;
    loadRoute(Map_Graph);
    generateVehicle(Map_Graph);
    //calcShortestPath(&Map_Graph);
    while (1) {
        runSimulation(Map_Graph);
    }
    cout << "end" << endl;
    return 0;
}







