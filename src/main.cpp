#include "stdafx.h"

#include "func.h"

int main() {
    Graph Map_Graph;
    parseMap(Map_Graph, "../map.xml");
    //generateTestGraph(&Map_Graph);
    //Map_Graph.showRoadTable(0);
    cout << "Parse succeed" << endl;
    //CalcShortestPath(&Map_Graph);
    return 0;
}







