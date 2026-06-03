
#ifndef FIELDS_OF_YONDER_YONDER_H
#define FIELDS_OF_YONDER_YONDER_H

#include <string>
#include <utility>
#include <vector>

#include "civ.h"
#include "resource.h"
#include "tile.h"

class Yonder {
public:
	Yonder();
	Yonder(const std::string& filename);

	void initializeWorld();
	void printState() const;

	void parseCivilization(std::ifstream& file);
	void parseTiles(std::ifstream& file);
	void parseWorld(std::ifstream& file);


	void setTime(double t);
	double getTime() const;
	void setTension(double t);
	double getTension() const;
	void setProsperity(double p);
	double getProsperity() const;
	void setEventChance(double c);
	double getEventChance() const;

	void addCivilization(const Civilization& civ);
	void removeCivilization(const std::string& name);
	Civilization* getCivilization(const std::string& name);
	vector<Civilization> getCivilizations() const;
	void addTile(const Tile& tile);
	int editTile(int x, int y, const Tile& tile);
	std::vector<Tile> getTiles() const;
	int getWorldWidth() const { return worldWidth; }
	int getWorldHeight() const { return worldHeight; }

	std::vector<std::pair<Civilization, Resources>> getGlobalResources() const;
	Resources getGlobalResourceSum() const;

	void checkForEvents();
	void Alert(const std::string& message);
	void run();

private:
	std::vector<Tile> tiles;
	int worldWidth;
	int worldHeight;
	std::vector<Civilization> civilizations;
	double time;
	double tension;
	double prosperity;
	double eventChance;
};

#endif
