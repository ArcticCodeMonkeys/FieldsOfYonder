
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

	void initializeWorld();

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
	int editTile(int x, int y, const Tile& tile);

	std::vector<std::pair<Civilization, Resources>> getGlobalResources() const;
	Resources getGlobalResourceSum() const;

	void checkForEvents();
	void Alert(const std::string& message);
	void run();

private:
	std::vector<Tile> tiles;
	std::vector<Civilization> civilizations;
	double time;
	double tension;
	double prosperity;
	double eventChance;
};

#endif
