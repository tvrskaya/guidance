#include <gtest/gtest.h>
#include <string>

#include "utils.h"

TEST(ParseGraph, SimpleMaze) {
    const std::string path = "res/mazes/simple_maze.txt";
    guidance::Graph graph{};
    try {
        graph = guidance::utils::ParseGraph(path);
    } catch(std::invalid_argument &e) {
        ASSERT_TRUE(false) << e.what();
    }

    ASSERT_TRUE(graph.Size() == 4) << "Size: " << graph.Size();

    for (const auto& [first, second] : graph) {
        EXPECT_TRUE(second.size() == 2);
    }

    EXPECT_TRUE(true);
}

TEST(ParseGraph, HardMaze) {
    const std::string path = "res/mazes/hard_maze.txt";
    guidance::Graph graph{};
    try {
        graph = guidance::utils::ParseGraph(path);
    } catch(std::invalid_argument &e) {
        ASSERT_TRUE(false) << e.what();
    }

    std::fstream f(path, std::ios_base::in);
    ASSERT_TRUE(f.is_open());

    int places_count = 0;
    std::string line;
    while(std::getline(f, line)) {
        for (const auto s : line) {
            if (s != kWall) {
                ++places_count;
            }
        }
    }

    ASSERT_TRUE(graph.Size() == places_count) << "Size: " << graph.Size() << " Places: " << places_count;
}
