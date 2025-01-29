#include "gameConfig.h"

const std::unordered_map<GameConfig::directions, std::pair<int, int>> GameConfig::directionPairs = {
    {GameConfig::directions::UP,    {0, -1}},
    {GameConfig::directions::DOWN,  {0, 1}},
    {GameConfig::directions::LEFT,  {-1, 0}},
    {GameConfig::directions::RIGHT, {1, 0}}
};