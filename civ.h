
#ifndef FIELDS_OF_YONDER_CIV_H
#define FIELDS_OF_YONDER_CIV_H

#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include "resource.h"
#include "tile.h"

using namespace std;

class Civilization {
public:
	explicit Civilization(const std::string& name, double aggression = 0.5, double diplomacy = 0.5, double fiscal = 0.5, double tradition = 0.5, double flexibility = 0.5, std::map<std::string, Civilization*> civMap = {}, std::map<int, std::string> civList = {}, std::vector<std::pair<Civilization*, double>> relationships = {}, Resources resources = Resources(), std::vector<Tile*> tiles = {}, Tile* civCenter = new Tile(0, 0, "Field"));
	std::string getName() const;
	std::vector<Tile*> getTiles() const;
	Tile* getCivCenter() const;
	void addTile(Tile* tile);
	void removeTile(int x, int y);
	void setCivCenter(Tile* center);

	double getAggression() const;
	double getDiplomacy() const;
	double getFiscal() const;
	double getTradition() const;
	double getFlexibility() const;
	void setAggression(double value);
	void setDiplomacy(double value);
	void setFiscal(double value);
	void setTradition(double value);
	void setFlexibility(double value);

	void setResource(string type, int quantity);
    void setResource(int index, int quantity);
    int getResource(string type) const;
    int getResource(int index) const;
    void setResources(const map<string, int>& newResources);
    Resources getResources() const;
    double getResourceRelative(const string& resourceType) const;

	double getActionWeightByIndex(int index) const;
	int act(std::vector<std::tuple<int, int, int>>& attemptedActions);
	void attemptAction(std::tuple<int, int, int> actionIndex);
	void generateResources();

private:
	double getRelationshipWithCivilization(const Civilization* civ) const;

	std::string name;

	double aggression;
	double diplomacy;
	double fiscal;
	double tradition;
	double flexibility;

	std::vector<std::pair<Civilization*, double>> relationships;

	Resources resources;

	std::vector<Tile*> tiles;
	std::map<std::string, Civilization*> civMap;
    std::map<int, std::string> civList;
	Tile* civCenter;
};

#endif
