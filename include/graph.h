#ifndef GUIDANCE_GRAPH_H
#define GUIDANCE_GRAPH_H

#include <vector>
#include <memory>
#include <sstream>
#include <iostream>

namespace guidance {

struct MazeVertex;

using MazeVertexPtr = std::shared_ptr<MazeVertex>;

struct MazeVertex {
    int x;
    int y;
    int cost;

    MazeVertex() = default;
    MazeVertex(int x, int y, int cost = 0) : x{x}, y{y}, cost(cost)  {}

    bool operator==(const MazeVertex& other) const {
        return x == other.x && y == other.y;
    }
    bool operator!=(const MazeVertex& other) const {
        return !(*this == other);
    }
    bool operator<(const MazeVertex& other) const {
        return (this->x + this->y) < (other.x + other.y);
    }
    bool operator>(const MazeVertex& other) const {
        return !(*this < other);
    }

};

static std::ostream& operator<<(std::ostream& stream, const MazeVertex& v) {
    return stream << v.x << " " << v.y;
}

struct MazeVertexHash {
    std::size_t operator()(const MazeVertex& v) const noexcept {
        return std::hash<int>()(v.x) ^ (std::hash<int>()(v.y) << 1);
    }
};

// struct MazeVertexCompare {
//     operator()(const MazeVertex& v1, const MazeVertex& v2) {

//     }
// };

class Graph {
private:
    std::unordered_map<MazeVertex, std::vector<MazeVertex>, MazeVertexHash> edges_;
public:
    void AddVertex(const MazeVertex& v) {
        edges_[v] = {};
    }

    void AddNeighbor(const MazeVertex& v, const MazeVertex& neigh) {
        edges_[v].push_back(neigh);
    }

    [[nodiscard]]
    auto begin() const noexcept {
        return edges_.begin();
    }

    [[nodiscard]]
    auto end() const noexcept {
        return edges_.end();
    }

    [[nodiscard]]
    size_t Size() const noexcept {
        return edges_.size();
    }

    void CalculateNeighbours() {
        for (auto& [v1, neighs1] : edges_) {
            for (auto& [v2, neighs2] : edges_) {
                if ((abs(v1.x - v2.x) == 1 && abs(v1.y - v2.y) == 0) || 
                (abs(v1.x - v2.x) == 0 && abs(v1.y - v2.y) == 1)) {
                    neighs1.push_back(v2);
                }
            }
        }
    }

    std::vector<MazeVertex> GetNeighbors(MazeVertex& v) const {
        return edges_.at(v);
    }

};

} // namespace guidance


#endif // GUIDANCE_GRAPH_H
