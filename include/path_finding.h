#ifndef GUIDANCE_PATH_FINDING_H
#define GUIDANCE_PATH_FINDING_H

#include <limits>
#include <math.h>
#include <queue>
#include <unordered_set>

#include "maze_graph.h"
#include "utils.h"

namespace guidance {

[[nodiscard]]
std::unordered_map<MazeVertex, MazeVertex, MazeVertexHash> 
static breadth_first_search(const Graph& graph, const MazeVertex& start, const MazeVertex& end) {
    std::queue<MazeVertex> reachable{};
    reachable.push(start);

    std::unordered_map<MazeVertex, MazeVertex, MazeVertexHash> came_from{};
    came_from[start] = {};

    while (!reachable.empty()) {
        auto current = reachable.front();
        reachable.pop();

        std::cout << "Visiting " << current << '\n';
        if (current == end) {
            return came_from;
        }

        for (const auto& next : graph.GetNeighbors(current)) {
            if (came_from.find(next) == came_from.end()) {
                reachable.push(next);
                came_from[next] = current;
            }
        }

    }
}


} // namespace guidance


#endif // GUIDANCE_PATH_FINDING_H
