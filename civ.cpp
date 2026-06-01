#include "civ.h"

#include <algorithm>
#include "globals.h"

Civilization::Civilization(const std::string& name, double aggression = 0.5, double diplomacy = 0.5, double fiscal = 0.5, double tradition = 0.5, double flexibility = 0.5, std::map<std::string, Civilization*> civMap = {}, std::map<int, std::string> civList = {}, std::vector<std::pair<Civilization*, double>> relationships = {}, Resources resources = Resources(), std::vector<Tile*> tiles = {}, Tile* civCenter = new Tile(0, 0, "Field"))
    : name(name),
      aggression(aggression),
      diplomacy(diplomacy),
      fiscal(fiscal),
      tradition(tradition),
      flexibility(flexibility),
      civMap(civMap),
      civList(civList),
      relationships(relationships),
      resources(resources),
      tiles(tiles),
      civCenter(civCenter) {}

std::string Civilization::getName() const {
    return name;
}

std::vector<Tile*> Civilization::getTiles() const {
    return tiles;
}

Tile* Civilization::getCivCenter() const {
    return civCenter;
}

void Civilization::addTile(Tile* tile) {
    tiles.push_back(tile);
}

void Civilization::removeTile(int x, int y) {
    tiles.erase(std::remove_if(tiles.begin(), tiles.end(),
                               [x, y](const Tile& t) {
                                   return t.getX() == x && t.getY() == y;
                               }),
                tiles.end());
}

void Civilization::setCivCenter(Tile* center) {
    civCenter = center;
}

double Civilization::getAggression() const {
    return aggression;
}

double Civilization::getDiplomacy() const {
    return diplomacy;
}

double Civilization::getFiscal() const {
    return fiscal;
}

double Civilization::getTradition() const {
    return tradition;
}

double Civilization::getFlexibility() const {
    return flexibility;
}

void Civilization::setAggression(double value) {
    aggression = value;
}

void Civilization::setDiplomacy(double value) {
    diplomacy = value;
}

void Civilization::setFiscal(double value) {
    fiscal = value;
}

void Civilization::setTradition(double value) {
    tradition = value;
}

void Civilization::setFlexibility(double value) {
    flexibility = value;
}

double Civilization::getResourceRelative(const string& resourceType) const {
    if (civList.empty()) {
        return 1.0;
    }

    double total = 0.0;
    for (const auto& pair : civMap) {
        total += pair.second->getResource(resourceType);
    }

    double average = total / static_cast<double>(civList.size());
    if (average <= 0.0) {
        return 1.0;
    }

    return static_cast<double>(getResource(resourceType)) / average;
}

void Civilization::setResource(string type, int quantity) {
    resources.setResourceQuantity(type, quantity);
}

void Civilization::setResource(int index, int quantity) {
    resources.setResourceQuantity(index, quantity);
}

void Civilization::setResources(const map<string, int>& newResources) {
    resources.setResources(newResources);
}

Resources Civilization::getResources() const {
    return resources;
}

double Civilization::getActionWeightByIndex(int index) const {
    double populationRelative = getResourceRelative("Population");
    double smarts = getResourceRelative("Smarts");
    double power = getResourceRelative("Power");
    double happiness = getResourceRelative("Happiness");
    double likeability = 0.0;
    for (const auto& relation : relationships) {
        likeability += relation.second;
    }
    likeability /= static_cast<double>(relationships.size() + 1);

    double tradeWeight = (1 + diplomacy) * (1 - happiness) * (1 + populationRelative) * (1 - smarts) *
                         (1 + likeability);
    double buildWeight = (1 + tradition) * (1 - power) * (1 + happiness) * (1 + populationRelative) *
                         (1 - likeability);
    double attackWeight = (1 + aggression) * (1 + power) * (1 - populationRelative) * (1 + smarts) *
                          (1 - likeability);
    double negotiateWeight = (1 + flexibility) * (1 - power) * (1 + happiness) * (1 - smarts) *
                             (1 + likeability);
    double investWeight = (1 + fiscal) * (1 + power) * (1 - happiness) * (1 - populationRelative) *
                          (1 + smarts);

    switch (index) {
        case 0:
            return tradeWeight;
        case 1:
            return buildWeight;
        case 2:
            return attackWeight;
        case 3:
            return negotiateWeight;
        case 4:
            return investWeight;
        default:
            return 0.0;
    }
}

int Civilization::act(std::vector<std::tuple<int, int, int>>& attemptedActions) {
    if (attemptedActions.size() >= static_cast<size_t>(10 * flexibility) &&
        attemptedActions.size() > static_cast<size_t>(1 * (1 - flexibility))) {
        return 0;
    }

    std::vector<std::vector<std::vector<double>>> actionMatrix(
        5, std::vector<std::vector<double>>(civList.size(), std::vector<double>(5, 0.0)));

    for (auto & resource : resourceTypes) {
        string resourceType = resource.first;
        // Resource ratio is the civilization's quantity of the resource divided by the average quantity of that resource among known civilizations (plus one to avoid division by zero)
        double resourceRatio = getResourceRelative(resourceType);
        for (size_t j = 0; j < civList.size(); j++) {
            double relationship = getRelationshipWithCivilization(civMap[civList[j]]);
            for (size_t k = 0; k < 5; k++) {
                actionMatrix[resourceTypes.at(resourceType)][j][k] = getActionWeightByIndex(static_cast<int>(k)) * resourceRatio * relationship;
            }
        }
    }

    std::tuple<int, int, int> actionIndex(-1, -1, -1);
    double highestWeight = 0.0;

    for (size_t i = 0; i < 5; i++) {
        for (size_t j = 0; j < civList.size(); j++) {
            for (size_t k = 0; k < 5; k++) {
                std::tuple<int, int, int> candidate(static_cast<int>(i), static_cast<int>(j),
                                                    static_cast<int>(k));
                if (actionMatrix[i][j][k] > highestWeight &&
                    std::find(attemptedActions.begin(), attemptedActions.end(), candidate) ==
                        attemptedActions.end()) {
                    highestWeight = actionMatrix[i][j][k];
                    actionIndex = candidate;
                }
            }
        }
    }

    if (std::get<0>(actionIndex) == -1) {
        return 0;
    }

    attemptAction(actionIndex);
    attemptedActions.push_back(actionIndex);
    return 1;
}

int Civilization::getResource(string type) const {
    return resources.getResourceQuantity(type);
}

int Civilization::getResource(int index) const {
    return resources.getResourceQuantity(resourceTypesIndexed.at(index));
}

void Civilization::attemptAction(std::tuple<int, int, int> actionIndex) {
    int x = std::get<0>(actionIndex);
    int y = std::get<1>(actionIndex);
    int z = std::get<2>(actionIndex);
    string resourceType = resourceTypesIndexed.at(x);
    Civilization* targetCiv = civMap[civList[y]];

    switch (z) {
        case 0:
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        default:
            break;
    }
}


void Civilization::generateResources() {
    for (const auto& tile : tiles) {
        string resource = tile->getType();
        if (resource == "Ore") {
            resources.addResource("Ore", 1);
        } else if (resource == "Wood") {
            resources.addResource("Wood", 1);
        } else if (resource == "Livestock") {
            resources.addResource("Livestock", 1);
        } else if (resource == "Crop") {
            resources.addResource("Crop", 1);
        } else if (resource == "Water") {
            resources.addResource("Water", 1);
        }
    }
}

double Civilization::getRelationshipWithCivilization(const Civilization* civ) const {
    for (const auto& relation : relationships) {
        if (relation.first == civ) {
            return relation.second;
        }
    }
    return 1.0;
}