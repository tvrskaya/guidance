#include <gtest/gtest.h>
#include <iostream>

#include "utils.h"
#include "maze.h"

TEST(ParseMaze, SimpleMaze) {
    const std::string path = "res/mazes/simple_maze.txt";
    guidance::Maze maze{};
    try {
        maze = guidance::utils::ParseMaze(path);
    } catch(std::invalid_argument &e) {
        ASSERT_TRUE(false) << e.what();
    }

    std::cout << maze << '\n';
    ASSERT_TRUE(true);
}