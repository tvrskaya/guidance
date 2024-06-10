#ifndef GUIDANCE_FIELD_TYPE_H
#define GUIDANCE_FIELD_TYPE_H

#include <unordered_map>
#include <limits>

constexpr auto kWall{'#'};
constexpr auto kPlace{'0'};
constexpr auto kOne{'1'};
constexpr auto kTwo{'2'};
constexpr auto kThree{'3'};
constexpr auto kFour{'4'};
constexpr auto kFive{'5'};
constexpr auto kSix{'6'};
constexpr auto kSeven{'7'};
constexpr auto kEight{'8'};
constexpr auto kNine{'9'};
constexpr auto kRiver{'R'};
constexpr auto kForest{'F'};
constexpr auto kPath{'*'};
constexpr auto kStart{'S'};
constexpr auto kEnd{'E'};

static std::unordered_map<char, int> cell_costs{{kWall, std::numeric_limits<int>::max()}, {kPlace, 0}, 
{kOne, 1}, {kTwo, 2}, {kThree, 3}, {kFour, 4}, {kFive, 5}, {kSix, 6}, {kSeven, 7}, {kEight, 8},
{kNine, 9}, {kRiver, 10}, {kForest, 15}};

[[nodiscard]]
static int GetCostFromCell(const char& cell) {
    try {
        return cell_costs.at(cell);
    } catch (std::exception &e) {
        return -1;
    }
}

#endif // GUIDANCE_FIELD_TYPE_H 