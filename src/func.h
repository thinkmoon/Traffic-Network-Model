//
// Created by chauncey on 18-4-24.
//
#include "Graph.h"

#ifndef TRAFFIC_NETWORK_MODEL_FUNC_H
#define TRAFFIC_NETWORK_MODEL_FUNC_H

/**
 * To parse the map
 * @param G the reference of Graph
 * @param MapFileName
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
void StringAddInt(string &str, int i);


/**
 * add road to traffic-network
 * @param G the reference of Graph
 * @param A  point A
 * @param B point B
 * @param length the road's length
 */
void addRoad(Graph &Map_Graph, Point A, Point B, double length);

/**
 * generate a test graph
 * @param G the reference of Graph
 */
void generateTestGraph(Graph *G);

#endif //TRAFFIC_NETWORK_MODEL_FUNC_H
