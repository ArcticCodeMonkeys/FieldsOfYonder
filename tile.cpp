
#include "resource.cpp"
#include "civ.cpp"
#include <vector>

class Tile {
public:
    Tile(int x, int y) : x(x), y(y) {}

    int getX() const { return x; }
    int getY() const { return y; }
    int x;
    int y;
    std::vector<Resource> resources; // Array of resources on the tile
    Civilization* owner; // Pointer to the civilization that owns the tile
};