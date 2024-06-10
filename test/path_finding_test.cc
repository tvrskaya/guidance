#include <gtest/gtest.h>

#include "path_finding.h"
#include "utils.h"
#include "graph.h"

TEST(PathFinding, BreadthFirstSearch) {
    const std::string path = "res/mazes/big_maze.txt";
    guidance::Graph graph{};
    guidance::Maze maze{};
    try {
        graph = guidance::utils::ParseGraph(path);
        maze  = guidance::utils::ParseMaze(path);
    } catch(std::invalid_argument &e) {
        ASSERT_TRUE(false) << e.what();
    }

    std::cout << maze << '\n';
    guidance::MazeVertex start{1, 1};
    guidance::MazeVertex end{6, 5};
    auto maze_path = guidance::breadth_first_search(graph, start, end);
    maze.SetPath(maze_path, start, end);

    std::cout << maze << '\n';

    ASSERT_TRUE(true);
}

TEST(PathFinding, Dijkstra) {
    const std::string path = "res/mazes/big_maze.txt";
    guidance::Graph graph{};
    guidance::Maze maze{};
    try {
        graph = guidance::utils::ParseGraph(path);
        maze  = guidance::utils::ParseMaze(path);
    } catch(std::invalid_argument &e) {
        ASSERT_TRUE(false) << e.what();
    }
    std::cout << maze << '\n';
    guidance::MazeVertex start{1, 1};
    guidance::MazeVertex end{1, 5};
    auto maze_path = guidance::dijkstra(graph, start, end);
    maze.SetPath(maze_path, start, end);

    std::cout << maze << '\n';

    ASSERT_TRUE(true);

}

TEST(PathFinding, AStar) {
    const std::string path = "res/mazes/big_maze.txt";
    guidance::Graph graph{};
    guidance::Maze maze{};
    try {
        graph = guidance::utils::ParseGraph(path);
        maze  = guidance::utils::ParseMaze(path);
    } catch(std::invalid_argument &e) {
        ASSERT_TRUE(false) << e.what();
    }
    std::cout << maze << '\n';
    guidance::MazeVertex start{1, 7};
    guidance::MazeVertex end{13, 1};
    auto maze_path = guidance::A_star(graph, start, end);
    maze.SetPath(maze_path, start, end);

    std::cout << maze << '\n';

    ASSERT_TRUE(true);
}
