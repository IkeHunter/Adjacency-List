//
// Created by Isaac Hunter on 4/1/23.
//

#include "AdjacencyList.h"

AdjacencyList::AdjacencyList(int powerIteration) {
    this->powerIteration = powerIteration;
}

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
    graph[fromId].first = getWeight(fromId);
}

int AdjacencyList::getId(std::string &name) {
    if(keys.find(name) == keys.end())
        return -1;
    return keys[name];
}

std::string AdjacencyList::getName(int id) {
    for(auto &url : keys) {
        if(url.second == id)
            return url.first;
    }
    return "";
}

void AdjacencyList::addNode(std::string name) {
    if(getId(name) != -1)
        return;
    int id = (int)keys.size();
    keys[name] = id;
    graph[id] = {0, {}};
}

std::vector<std::string> AdjacencyList::getUrls() {
    std::vector<std::string> urls;
    for(auto &url : keys) {
        urls.push_back(url.first);
    }
    return urls;
}

std::vector<int> AdjacencyList::getAdjacent(int id) {
    return graph[id].second;
}

std::vector<std::string> AdjacencyList::getAdjacent(std::string &name) {
    std::vector<std::string> urls;
    std::vector<int> ids = getAdjacent(getId(name));

    for(auto &id : ids) {
        urls.push_back(getName(id));
    }

    return urls;

}

std::map<int, std::vector<int>> AdjacencyList::getWeights() {
    std::map<int, std::vector<int>> weights;

    for(auto &key : graph) {
        weights[key.first] = getWeights(key.first);
    }

    return weights;
}

std::vector<int> AdjacencyList::getWeights(int id) {
    std::vector<int> weights;

    for(auto &key : graph) {
        for(auto adjacent : key.second.second) {
            if(adjacent == id)
                weights.push_back(key.first);
        }
    }

    return weights;
}
std::vector<std::string> AdjacencyList::getWeights(std::string &name) {
    std::vector<int> idWeights = getWeights(getId(name));
    std::vector<std::string> nameWeights;

    for(auto &id : idWeights) {
        nameWeights.push_back(getName(id));
    }

    return nameWeights;
}



