//
// Created by Isaac Hunter on 4/1/23.
//
#ifndef PROJECT_2_ADJACENCYLIST_H
#define PROJECT_2_ADJACENCYLIST_H

#include <iostream>
#include <map>
#include <vector>

/** Adjacency List Implementation of Graph **/
/*====================
 * Weight: 1/out-degree
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
 * TODO: create tests
 * TODO: create accessors
 * TODO: create insert
 * TODO: create page rank
 */

class AdjacencyList {
private:
    /** Main Graph **/
    std::map<std::string, int> key;  // key[name] = id
    std::map<int, std::pair<float, std::vector<int>>> graph;  // graph[id] = {weight, {adjacent nodes}}

    /** Page Rank **/
    int powerIteration;

    /** Helper Functions **/
    int getID(std::string name);
    float getWeight(int id);
    std::string getName(int id);

    /** Manipulation **/
    void addNode(std::string name);
    void addNode(int id);

public:
    /** Constructors **/
    AdjacencyList();
    ~AdjacencyList();

    /** Manipulation **/
    void insert(std::string from, std::string to);  // graph[from] = {_, {...,to}}

    /** Accessors **/
//    std::vector<int> getKeys();  // get all keys in graph
    std::vector<int> getAdjacent(int id);  // get all adjacent nodes to id
    std::vector<std::string> getAdjacent(std::string);  // get adjacent nodes to name from id
    std::map<std::string, float> getWeights();  // get all weights in graph

    std::vector<std::string> getUrls();  // get all urls in graph

    /** Page Rank **/
    std::map<std::string, float> getRanks();  // get page rank for all nodes
    std::map<int, float> getRanks(int iteration, std::map<int, std::vector<int>> &weights, std::map<int, float> previousIteration);  // return page rank from weights and previous iteration values

};


#endif //PROJECT_2_ADJACENCYLIST_H
