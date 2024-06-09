#ifndef GUIADANCE_MAZE_H
#define GUIADANCE_MAZE_H

#include <vector>
#include <sstream>
#include "field_type.h"

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
        for (const auto& [came_to, from] : path) {
            if (from == end) {
                maze_[from.y][from.x] = kEnd;
                break;
            }
            if (from == start) {
                maze_[from.y][from.x] = kStart;
                break;
            }
            maze_[from.y][from.x] == kPath;
        }
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
