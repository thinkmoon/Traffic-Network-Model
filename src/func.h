//
// Created by chauncey on 18-4-24.
//
#include "Graph.h"


#ifndef TRAFFIC_NETWORK_MODEL_FUNC_H
#define TRAFFIC_NETWORK_MODEL_FUNC_H
typedef struct {
    string strPath;
    int num = 0;
} RoutePath;
/**
 * 解析地图
 * @param G 图类的引用
 * @param MapFileName 地图的文件地址
 */
void parseMap(Graph &Map_Graph, const char *MapFileName);

/**
 * Use the Dijkstra algorithm to calculate the shortest path
 * @param G the graph object
 */
void calcShortestPath(Graph *G);

/**
 * Add an integer after a string
 * @param str String to be added
 * @param i The integer to add
 */
void RoutePathAddInt(RoutePath &routePath, int i);

/**
 * generate a test graph
 * @param G the reference of Graph
 */
void generateTestGraph(Graph *G);

#endif //TRAFFIC_NETWORK_MODEL_FUNC_H
