#include <gtest/gtest.h>
#include "path_finding.h"
#include "utils.h"
#include "maze_graph.h"

TEST(PathFinding, SimplePathFinder) {
    const std::string path = "res/mazes/hard_maze.txt";
    guidance::Graph graph;
    try {
        graph = guidance::utils::ParseGraph(path);
    } catch(std::invalid_argument &e) {
        ASSERT_TRUE(false) << e.what();
    }

    auto maze_path = guidance::breadth_first_search(graph, {1, 1}, {6, 5});   

    ASSERT_TRUE(true);
}
