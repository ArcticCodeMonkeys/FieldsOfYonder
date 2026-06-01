
#include "tile.h"

using namespace std;

Tile::Tile(int x, int y, string type, string ownerName)
    : x(x), y(y), type(type), ownerName(ownerName) {}

int Tile::getX() const {
    return x;
}

int Tile::getY() const {
    return y;
}

const string Tile::getType() const {
    return type;
}

void Tile::setType(string t) {
    type = t;
}

const string& Tile::getOwnerName() const {
    return ownerName;
}

void Tile::setOwnerName(const string& name) {
    ownerName = name;
}