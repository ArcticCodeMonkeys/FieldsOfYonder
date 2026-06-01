
#ifndef FIELDS_OF_YONDER_TILE_H
#define FIELDS_OF_YONDER_TILE_H

#include <string>
#include <vector>

#include "resource.h"
using namespace std;

class Tile {
public:
	Tile(int x, int y, string type, string ownerName = "");

	int getX() const;
	int getY() const;

	const string getType() const;
    void setType(string t);

	const string& getOwnerName() const;
	void setOwnerName(const string& name);

private:
	int x;
	int y;
	string type;
	string ownerName;
};

#endif
