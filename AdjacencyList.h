//
// Created by Isaac Hunter on 4/1/23.
//
#ifndef PROJECT_2_ADJACENCYLIST_H
#define PROJECT_2_ADJACENCYLIST_H

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <iomanip>

/** Adjacency List Implementation of Graph **/
/*====================
 * Weight: 1/out-degree
 * Weights: {inbound ids}
 *
 * Key: url name -> id
 * Graph: url id -> {weight, {adjacent nodes}}
 *
 * Page Rank:
 * 1. create following maps:
 *  a. weights: id -> {inbound ids}
 *  b. previousIteration: id -> value
 * 2. for n[m] multiply weights[m] with previousIteration[m], add values to currentIteration[n]
 * 3. return currentIteration
 *
 * =====================*/
/**
 * DONE: create base class
 * DONE: create tests
 * DONE: create accessors
 * DONE: create insertEdge
 * DONE: create getInBoundUrls
 * DONE: create page rank
 * DONE: clean up, make accessible for grade scope
 */

class AdjacencyList {
private:
    /** Main Graph **/
    std::map<std::string, int> keys;  // keys[name] = id
    std::map<int, std::pair<float, std::vector<int>>> graph;  // graph[id] = {weight, {adjacent nodes}}

    /** Helper Functions **/
    int getId(std::string &name);
    float getWeight(int id);

    std::string getName(int id);

    /** Manipulation **/
    void addNode(std::string name);

public:

    /** Manipulation **/
    void insertEdge(std::string from, std::string to);  // graph[from] = {_, {...,to}}



    /** Page Rank **/
    std::map<int, std::vector<int>> getInBoundUrls();  // get list of weights for all ids
    std::vector<int> getInBoundUrls(int id);  // get list of weights for id
    std::vector<std::string> getInBoundUrls(std::string &name);  // get list of weights for name
    std::map<int, float> pageRank(int iterations);

    void printPageRank(int iterations);
};


#endif //PROJECT_2_ADJACENCYLIST_H
