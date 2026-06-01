#include "yonder.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>

Yonder::Yonder()
    : time(0.0), tension(0.0), prosperity(0.0), eventChance(0.0) {
    // Initialize the world, civilizations, and tiles here
}

void Yonder::initializeWorld() {
    // Create tiles, assign resources, and set up civilizations
}

void Yonder::setTime(double t) {
    time = t;
}

double Yonder::getTime() const {
    return time;
}

void Yonder::setTension(double t) {
    tension = t;
}

double Yonder::getTension() const {
    return tension;
}

void Yonder::setProsperity(double p) {
    prosperity = p;
}

double Yonder::getProsperity() const {
    return prosperity;
}

void Yonder::setEventChance(double c) {
    eventChance = c;
}

double Yonder::getEventChance() const {
    return eventChance;
}

void Yonder::addCivilization(const Civilization& civ) {
    civilizations.push_back(civ);
}

void Yonder::removeCivilization(const std::string& name) {
    civilizations.erase(std::remove_if(civilizations.begin(), civilizations.end(),
                                       [&name](const Civilization& c) {
                                           return c.getName() == name;
                                       }),
                        civilizations.end());
}

int Yonder::editTile(int x, int y, const Tile& tile) {
    for (auto& t : tiles) {
        if (t.getX() == x && t.getY() == y) {
            t = tile;
            return 0;
        }
    }
    return -1;
}

std::vector<std::pair<Civilization, Resources>> Yonder::getGlobalResources() const {
    std::vector<std::pair<Civilization, Resources>> globalResources;
    for (const auto& civ : civilizations) {
        globalResources.emplace_back(civ, civ.getResources());
    }
    return globalResources;
}

Resources Yonder::getGlobalResourceSum() const {
    Resources total;
    for (const auto& civ : civilizations) {
        for (const auto& pair : resourceTypes) {
            total.addResource(pair.first, civ.getResource(pair.first));
        }
    }
    return total;
}

void Yonder::checkForEvents() {
    if (std::rand() % 100 < eventChance * 100) {
        Alert("A natural disaster has occurred!");
        int damage = std::rand() % 10 + 1;
        for (auto& civ : civilizations) {
            civ.setResource("Food", std::max(0, civ.getResource("Food") - damage));
            civ.setResource("Population", std::max(0, civ.getResource("Population") - damage));
        }
        tension += 0.05;
        prosperity -= 0.05;
    }
}

void Yonder::Alert(const std::string& message) {
    std::cout << "ALERT: " << message << std::endl;
}

void Yonder::run() {
    while (true) {
        time++;
        eventChance += 0.01;
        tension += 0.01;
        prosperity += 0.01;
        checkForEvents();
        for (auto& civ : civilizations) {
            civ.generateResources();
        }

        std::vector<std::pair<Civilization, std::vector<std::tuple<int, int, int>>>> actingCivs;
        for (const auto& civ : civilizations) {
            actingCivs.emplace_back(civ, std::vector<std::tuple<int, int, int>>{});
        }

        while (!actingCivs.empty()) {
            for (auto it = actingCivs.begin(); it != actingCivs.end();) {
                if (it->first.act(it->second) == 0) {
                    it = actingCivs.erase(it);
                } else {
                    ++it;
                }
            }
        }
    }
}