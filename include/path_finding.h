#ifndef GUIDANCE_PATH_FINDING_H
#define GUIDANCE_PATH_FINDING_H

#include <limits>
#include <math.h>
#include <queue>
#include <unordered_set>

#include "graph.h"
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

        if (current == end) {
            return came_from;
        }

        for (const auto& next : graph.GetNeighbors(current)) {
            if (came_from.find(next) == came_from.end()) {
                reachable.push(next);
                came_from[next] = current;
            }
            if (current == end) {
                return came_from;
            }
        }
    }
    return {};
}

[[nodiscard]]
std::unordered_map<MazeVertex, MazeVertex, MazeVertexHash> 
static dijkstra(const Graph& graph, const MazeVertex& start, const MazeVertex& end) {
    using PQElement = std::pair<int, MazeVertex>;
    std::priority_queue<PQElement, std::vector<PQElement>, std::greater<PQElement>> reachable;
    reachable.emplace(0, start);

    std::unordered_map<MazeVertex, MazeVertex, MazeVertexHash> came_from{};
    came_from[start] = {};

    std::unordered_map<MazeVertex, int, MazeVertexHash> cost_so_far{};
    cost_so_far[start] = 0;

    while(!reachable.empty()) {
        auto current = reachable.top().second;
        reachable.pop();

        if (current == end) {
            return came_from;
        }

        for (const auto& next : graph.GetNeighbors(current)) {
            auto new_cost = cost_so_far[current] + next.cost;
            if (cost_so_far.find(next) == cost_so_far.end() || new_cost < cost_so_far[next]) {
                cost_so_far[next] = new_cost;
                auto priority = new_cost;
                reachable.emplace(priority, next);
                came_from[next] = current;
            }
        }
    }
    return {};
}

[[nodiscard]]
std::unordered_map<MazeVertex, MazeVertex, MazeVertexHash> 
static A_star(const Graph& graph, const MazeVertex& start, const MazeVertex& end) {
    using PQElement = std::pair<int, MazeVertex>;
    std::priority_queue<PQElement, std::vector<PQElement>, std::greater<PQElement>> reachable;
    reachable.emplace(0, start);

    std::unordered_map<MazeVertex, MazeVertex, MazeVertexHash> came_from{};
    came_from[start] = {};

    std::unordered_map<MazeVertex, int, MazeVertexHash> cost_so_far{};
    cost_so_far[start] = 0;

    while(!reachable.empty()) {
        auto current = reachable.top().second;
        reachable.pop();

        if (current == end) {
            return came_from;
        }

        for (const auto& next : graph.GetNeighbors(current)) {
            auto new_cost = cost_so_far[current] + next.cost;
            if (cost_so_far.find(next) == cost_so_far.end() || new_cost < cost_so_far[next]) {
                cost_so_far[next] = new_cost;
                auto priority = new_cost + utils::heuristic(end, next);
                reachable.emplace(priority, next);
                came_from[next] = current;
            }
        }
    }
    return {};
}

} // namespace guidance


#endif // GUIDANCE_PATH_FINDING_H
