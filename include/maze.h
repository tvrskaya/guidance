#ifndef GUIADANCE_MAZE_H
#define GUIADANCE_MAZE_H

#include <vector>
#include <sstream>
#include "cell_types.h"

namespace guidance {

class Maze {
private:
    std::vector<std::vector<char>> maze_{};
public:
    Maze() = default;

    void PushBackLine(const std::string& line) {
        std::vector<char> l;
        for (const auto& s : line) {
            l.push_back(s);
        }
        maze_.push_back(l);
    }

    void SetPath(const std::unordered_map<MazeVertex, MazeVertex, MazeVertexHash>& path, const MazeVertex start, const MazeVertex end) noexcept {
        std::cout << "Size: " << path.size() << '\n';
        auto current = end;
        while (current != start) {
            current = path.at(current);
            maze_[current.y][current.x] = kPath;
        }
        maze_[start.y][start.x] = kStart;
        maze_[end.y][end.x] = kEnd;
    }

    [[nodiscard]]
    Graph GetGraph() const {
        Graph graph{};
        for (int y = 0; y < maze_.size(); ++y) {
            for (int x = 0; x < maze_[y].size(); ++x) {
                if (maze_[y][x] != kWall) {
                    graph.AddVertex({x, y, GetCostFromCell(maze_[y][x])});
                }
            }
        }
        graph.CalculateNeighbours();
        return graph;
    }

    [[nodiscard]]
    std::string ToString() const noexcept {
        std::stringstream ss;
        for (const auto& y : maze_) {
            for (const auto& x : y) {
                ss << x;
            }
            ss << '\n';
        }
        return ss.str();
    }

};

static std::ostream& operator<<(std::ostream& stream, const Maze& maze) {
    return stream << maze.ToString();
}

} // guidance

#endif // GUIADANCE_MAZE_H
