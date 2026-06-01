#include "globals.h"

const std::map<std::string, int> resourceTypes = {
    {"Ore", 0},
    {"Wood", 1},
    {"Livestock", 2},
    {"Crop", 3},
    {"Water", 4},
    {"Population", 5},
    {"Smarts", 6},
    {"Power", 7},
    {"Happiness", 8}
};

const std::map<int, std::string> resourceTypesIndexed = {
    {0, "Ore"},
    {1, "Wood"},
    {2, "Livestock"},
    {3, "Crop"},
    {4, "Water"},
    {5, "Population"},
    {6, "Smarts"},
    {7, "Power"},
    {8, "Happiness"}
};