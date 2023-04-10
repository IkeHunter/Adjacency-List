//
// Created by Isaac Hunter on 4/1/23.
//

#include "AdjacencyList.h"

/**
 * Insert an edge into the graph
 *
 * @param from - first value of input
 * @param to - second value of input
 */
void AdjacencyList::insertEdge(std::string from, std::string to) {
    int fromId = getId(from);
    int toId = getId(to);

    if(fromId == -1) {
        addNode(from);
        fromId = getId(from);
    }
    if(toId == -1) {
        addNode(to);
        toId = getId(to);
    }

    graph[fromId].second.push_back(toId);
    graph[fromId].first = graph[fromId].second.size();
}

/**
 * Get Id from name
 * Iterates through internal keys map to find the id of the node
 *
 * @param name - url value of node
 * @return id of node
 * @return -1 if url does not exist
 */
int AdjacencyList::getId(std::string &name) {
    if(keys.find(name) == keys.end())
        return -1;
    return keys[name];
}

/**
 * Get name from id
 * Iterates through internal keys map to find the name of the node
 *
 * @param id - id of node
 * @return name of node
 * @return "" if id does not exist
 */
std::string AdjacencyList::getName(int id) {
    for(auto &url : keys) {
        if(url.second == id)
            return url.first;
    }
    return "";
}

/**
 * Add Node to graph
 * Adds a node to the graph and keys map, sets weight to 0 initially
 * Sets id to the size of the keys map before addition
 *
 * @param id - id of node
 * @return weight of node
 * @return -1 if id does not exist
 */
void AdjacencyList::addNode(std::string name) {
    if(getId(name) != -1)
        return;
    int id = (int)keys.size();
    keys[name] = id;
    graph[id] = {0, {}};
}

/**
 * Get Inbound Urls
 * Iterates through the graph and returns a map of all urls that link to
 * each "to" url in the graph. Original graph is from -> {to}, this returns
 * a map structure of to -> {from}
 *
 * @return map<int, vector<int>> of all "to" urls and their "from" urls
 *
 * @param id - id of url
 * @return vector<int> of inbound urls
 */
std::map<int, std::vector<int>> AdjacencyList::getInBoundUrls() {
    std::map<int, std::vector<int>> weights;

    for(auto &key : graph) {
        weights[key.first] = getInBoundUrls(key.first);
    }

    return weights;
}
std::vector<int> AdjacencyList::getInBoundUrls(int id) {
    std::vector<int> weights;

    for(auto &key : graph) {
        for(auto adjacent : key.second.second) {
            if(adjacent == id)
                weights.push_back(key.first);
        }
    }

    return weights;
}
std::vector<std::string> AdjacencyList::getInBoundUrls(std::string &name) {
    std::vector<int> idWeights = getInBoundUrls(getId(name));
    std::vector<std::string> nameWeights;

    for(auto &id : idWeights) {
        nameWeights.push_back(getName(id));
    }

    return nameWeights;
}

/**
 * Get Weight of url
 *
 * @param id - id of url
 * @return float weight of url
 * @return -1 if id does not exist
 */
float AdjacencyList::getWeight(int id) {
    if(graph.find(id) == graph.end())
        return -1;
    return graph[id].first;
}

/**
 * Get Page Rank of urls in graph
 *
 * @param iterations - number of power iterations to run
 * @return map<int, float> of all urls and their page rank value
 */
std::map<int, float> AdjacencyList::pageRank(int iterations) {
    std::map<int, std::vector<int>> weights = getInBoundUrls();  // O(n*m)
    std::map<int, float> pageRanks;

    for(auto &key : graph) {  // O(n)
        pageRanks[key.first] = 1.0f / graph.size();
    }

    for(int i = 1; i < iterations; i++) {  // O(i*n^2)
        std::map<int, float> currentIteration;

        for(auto &from : graph) {  // O(n)
            currentIteration[from.first] = 0;
        }

        for(auto &from : graph) {  // O(n^2)
            for(auto &to : weights[from.first]) {  // O(n)
                if(getWeight(to) != 0.0f) {  // O(1)
                    float calcValue = pageRanks[to] / getWeight(to);
                    currentIteration[from.first] += calcValue;
                }
            }
        }

        pageRanks = currentIteration;
    }
    return pageRanks;

}

/**
 * Print Page Rank of urls in graph
 * Calls pageRank and prints the results like
 * "[url] [pageRank]"
 *
 * @param iterations - number of power iterations to run
 */
void AdjacencyList::printPageRank(int iterations) {
    std::map<int, float> pageRanks = pageRank(iterations);
    std::map<std::string, float, std::less<std::string>> pageRankNames;

    for(auto &pageRank : pageRanks) {
        pageRankNames[getName(pageRank.first)] = pageRank.second;
    }

    for(auto &pageRank : pageRankNames) {
        std::cout << pageRank.first << " " << std::setprecision(2) << std::fixed << std::showpoint << pageRank.second << std::endl;
    }
}



