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

TEST_CASE("Graph Links and Accessors", "[flag]") {
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

TEST_CASE("Page Rank Single Weights", "[flags]") {
    /*** Should return correct weights for urls ***/
    /*
     * Weights are created with the urls that link to the given url,
     * making the weights the inbound urls, and the in-degree the number of weights.
     *
     * This logic is used to find 1/d, where d is the out-degree of the weight.
     */

    /* Insert urls */
    AdjacencyList graph(2);
    std::string input_1 = "google.com";
    std::string input_2 = "facebook.com";
    std::string input_3 = "amazon.com";
    std::string input_4 = "apple.com";

    graph.insertEdge(input_1, input_2);
    graph.insertEdge(input_3, input_4);
    graph.insertEdge(input_1, input_4);

    /* Test single weights */
    std::vector<std::string> a_output = graph.getInBoundUrls(input_4);
    std::vector<std::string> e_output = {input_1, input_3};

    std::vector<std::string> a_output_2 = graph.getInBoundUrls(input_1);
    std::vector<std::string> e_output_2 = {};

    REQUIRE(e_output.size() == a_output.size());
    REQUIRE(e_output_2.size() == a_output_2.size());

    std::sort(a_output.begin(), a_output.end());
    std::sort(e_output.begin(), e_output.end());
    std::sort(a_output_2.begin(), a_output_2.end());
    std::sort(e_output_2.begin(), e_output_2.end());

    REQUIRE(a_output == e_output);
    REQUIRE(a_output_2 == e_output_2);
}

TEST_CASE("Page Rank All Weights", "[flags]") {
    /*** Should return all correct weights for urls ***/

    AdjacencyList graph(2);
    std::string input_0 = "google.com";
    std::string input_1 = "facebook.com";
    std::string input_2 = "amazon.com";
    std::string input_3 = "apple.com";

    graph.insertEdge(input_0, input_1);
    graph.insertEdge(input_2, input_3);
    graph.insertEdge(input_0, input_3);

    std::map<int, std::vector<int>> a_output_3 = graph.getInBoundUrls();
    std::map<int, std::vector<int>> e_output_3 = {
            {0, {}},
            {1, {0}},
            {2, {}},
            {3, {0, 2}}
    };

    REQUIRE(e_output_3.size() == a_output_3.size());
    for(auto &key : a_output_3) {
        REQUIRE(e_output_3[key.first] == key.second);
    }
}

TEST_CASE("Test Page Rank with power iteration of 2", "[flags]") {
    /*** Should return correct page rank for urls with page rank of 2 ***/

    AdjacencyList graph(2);
    std::string input_0 = "google.com";
    std::string input_1 = "facebook.com";
    std::string input_2 = "amazon.com";
    std::string input_3 = "apple.com";

    graph.insertEdge(input_0, input_1);
    graph.insertEdge(input_2, input_3);
    graph.insertEdge(input_0, input_3);

    std::map<int, float> a_output = graph.pageRank(2);
    std::map<int, float> e_output = {
            {0, 0},
            {1, (float)1/8},
            {2, 0},
            {3, (float)3/8}
    };

    REQUIRE(e_output.size() == a_output.size());
    for(auto &key : a_output) {
        REQUIRE(e_output[key.first] == key.second);
    }

}

TEST_CASE("Test Page Rank with power iteration of 3", "[flags]") {
    /*** Should return correct page rank for urls with page rank of 2 ***/

    AdjacencyList graph(3);
    std::string input_0 = "google.com";
    std::string input_1 = "facebook.com";
    std::string input_2 = "amazon.com";
    std::string input_3 = "apple.com";

    graph.insertEdge(input_0, input_1);
    graph.insertEdge(input_2, input_3);
    graph.insertEdge(input_0, input_3);

    std::map<int, float> a_output = graph.pageRank(3);
    std::map<int, float> e_output = {
            {0, 0},
            {1, 0},
            {2, 0},
            {3, 0}
    };

    REQUIRE(e_output.size() == a_output.size());
    for(auto &key : a_output) {
        REQUIRE(e_output[key.first] == key.second);
    }

}

TEST_CASE("Test Page Rank with Larger Data Graph", "[flags]") {
    /*** Should return correct page rank for urls with page rank of 3 ***/

    // Power Iterations = 2
    AdjacencyList graph(2);
    std::string input_0 = "google.com";
    std::string input_1 = "facebook.com";
    std::string input_2 = "amazon.com";
    std::string input_3 = "apple.com";
    std::string input_4 = "microsoft.com";
    std::string input_5 = "tesla.com";
    std::string input_6 = "nvidia.com";
    std::string input_7 = "amd.com";

    graph.insertEdge(input_0, input_1);
    graph.insertEdge(input_1, input_2);
    graph.insertEdge(input_2, input_3);
    graph.insertEdge(input_3, input_4);
    graph.insertEdge(input_4, input_5);
    graph.insertEdge(input_5, input_6);
    graph.insertEdge(input_6, input_7);
    graph.insertEdge(input_7, input_0);

    graph.insertEdge(input_5, input_1);
    graph.insertEdge(input_4, input_2);
    graph.insertEdge(input_2, input_0);
    graph.insertEdge(input_1, input_0);
    graph.insertEdge(input_5, input_7);

    std::map<int, float> a_output = graph.pageRank(2);
    std::map<int, float> e_output = {
            {0, (float)1/4},
            {1, (float)1/6},
            {2, (float)1/8},
            {3, (float)1/16}, //
            {4, (float)1/8},
            {5, (float)1/16}, //
            {6, (float)1/24},
            {7, (float)1/6}
    };

    REQUIRE(e_output.size() == a_output.size());
    for(auto &key : a_output) {
        REQUIRE(e_output[key.first] == key.second);
    }

    std::map<int, float> a_output_2 = graph.pageRank(3);
    std::map<int, float> e_output_2 = {
            {0, (float)5/16},
            {1, (float)13/48},
            {2, (float)7/48},
            {3, (float)1/16},
            {4, (float)1/16},
            {5, (float)1/16},
            {6, (float)1/48},
            {7, (float)1/16}
    };

    REQUIRE(e_output_2.size() == a_output_2.size());
    for(auto &key : a_output_2) {
        REQUIRE(Approx(e_output_2[key.first]) ==key.second);
    }
}



