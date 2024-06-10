#ifndef GUIDANCE_UTILS_H
#define GUIDANCE_UTILS_H

#include <iostream>
#include <vector>
#include <math.h>
#include <memory>
#include <string>
#include <fstream>

#include "cell_types.h"
#include "graph.h"
#include "maze.h"

namespace guidance::utils {

[[nodiscard]]
static bool IsPlace(const char symbol) {
    if (symbol >= 0x30 && symbol <= 0x31) {
        if (symbol == kPlace) {
            return true;
        }
        return false;
    }
}

[[nodiscard]]
static Maze ParseMaze(const std::string& path) {
    std::fstream f(path, std::ios_base::in);
    if (!f.is_open()) {
        throw std::invalid_argument("Can't open file");
    }

    guidance::Maze maze{};
    std::string line;
    while(std::getline(f, line)) {
        maze.PushBackLine(line);
    }
    f.close();

    return maze;
}

[[nodiscard]]
static Graph ParseGraph(const std::string& path) {
    std::fstream f(path, std::ios_base::in);
    if (!f.is_open()) {
        throw std::invalid_argument("Can't open file");
    }

    guidance::Graph graph{};

    std::string line;
    int x = 0;
    int y = 0;
    while (std::getline(f, line)) {
        for (const auto& s : line) {
            if (s != kWall) {
                graph.AddVertex({x, y, GetCostFromCell(s)});
            }
            ++x;
        }       
        ++y; 
        x = 0;
    }
    f.close();
    
    graph.CalculateNeighbours();

    return graph;
}

static int heuristic(const MazeVertex& v1, const MazeVertex& v2) {
    return std::abs(v1.x - v1.y) + std::abs(v2.x - v2.y);
}

} // namespace lighthouse::utils


#endif // GUIDANCE_UTILS_H
