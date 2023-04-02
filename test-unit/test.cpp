#include "../main.cpp"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../AdjacencyList.h"
#include <algorithm>


TEST_CASE("Graph Insert", "[flag]") {
    /*** Should insertEdge values, return correct values ***/
    AdjacencyList graph(2);
    std::string input_1 = "google.com";
    std::string input_2 = "facebook.com";

    graph.insertEdge(input_1, input_2);

    std::vector<std::string> a_output = graph.getUrls();
    std::vector<std::string> e_output = {input_1, input_2};

    std::sort(a_output.begin(), a_output.end());
    std::sort(e_output.begin(), e_output.end());

    REQUIRE(e_output.size() == a_output.size());
    REQUIRE(a_output == e_output);
}

TEST_CASE("Graph Links and Accessors", "[flag") {
    /*** Should return correct urls given different connections ***/

    /* Test graph input and edge creation */
    AdjacencyList graph(2);
    std::string input_1 = "google.com";
    std::string input_2 = "facebook.com";
    std::string input_3 = "amazon.com";
    std::string input_4 = "apple.com";

    graph.insertEdge(input_1, input_2);
    graph.insertEdge(input_3, input_4);
    graph.insertEdge(input_1, input_4);

    std::vector<std::string> a_output = graph.getUrls();
    std::vector<std::string> e_output = {input_1, input_2, input_3, input_4};

    std::sort(a_output.begin(), a_output.end());
    std::sort(e_output.begin(), e_output.end());

    REQUIRE(e_output.size() == a_output.size());
    REQUIRE(a_output == e_output);

    /* Test graph adjacency functions */
    std::vector<std::string> a_output_2 = graph.getAdjacent(input_1);  // return input_1 out links
    std::vector<std::string> e_output_2 = {input_2, input_4};
    std::vector<std::string> a_output_3 = graph.getAdjacent(input_2);  // return input_2 out links
    std::vector<std::string> e_output_3 = {};
    std::vector<std::string> a_output_4 = graph.getAdjacent(input_3);  // return input_3 out links
    std::vector<std::string> e_output_4 = {input_4};

    REQUIRE(e_output_2.size() == a_output_2.size());
    REQUIRE(e_output_3.size() == a_output_3.size());
    REQUIRE(e_output_4.size() == a_output_4.size());

    std::sort(a_output_2.begin(), a_output_2.end());
    std::sort(e_output_2.begin(), e_output_2.end());
    std::sort(a_output_3.begin(), a_output_3.end());
    std::sort(e_output_3.begin(), e_output_3.end());
    std::sort(a_output_4.begin(), a_output_4.end());
    std::sort(e_output_4.begin(), e_output_4.end());

    REQUIRE(a_output_2 == e_output_2);
    REQUIRE(a_output_3 == e_output_3);
    REQUIRE(a_output_4 == e_output_4);
}


