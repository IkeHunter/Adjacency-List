#include "../main.cpp"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../AdjacencyList.h"


TEST_CASE("Graph Insert", "[flag]") {
    /* Should insert values, return correct values */
    AdjacencyList graph;
    std::string input_1 = "google.com";
    std::string input_2 = "facebook.com";

    graph.insert(input_1, input_2);

    std::vector<std::string> a_output = graph.getUrls();
    std::vector<std::string> e_output = {input_1, input_2};

    REQUIRE(e_output.size() == a_output.size());
    REQUIRE(a_output == e_output);
}

