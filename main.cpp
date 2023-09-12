#include <iostream>
#include "AdjacencyList.h"

int main() {
    int no_of_lines, power_iterations;
    std::string from, to;
    std::cin >> no_of_lines;
    std::cin >> power_iterations;

    AdjacencyList graph;
    for(int i = 0; i < no_of_lines; i++) {
        std::cin >> from;
        std::cin >> to;
        graph.insertEdge(from, to);
    }
    graph.printPageRank(power_iterations);

    return 0;
}

// test-unit/catch.hpp test-unit/test.cpp