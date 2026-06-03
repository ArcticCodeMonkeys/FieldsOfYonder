#include "yonder.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <sstream>

Yonder::Yonder()
    : time(0.0), tension(0.0), prosperity(0.0), eventChance(0.0) {
    // Initialize the world, civilizations, and tiles here
    initializeWorld();
}

Yonder::Yonder(const std::string& filename)
    : time(0.0), tension(0.0), prosperity(0.0), eventChance(0.0) {
    // Load the world, civilizations, and tiles from the specified file
    // For now, we'll just call initializeWorld() to set up a default world
    
    // Format: JSON like objects, three types: Civ, Tiles, and World
    // Eg.
    // Civ {
    //  CivName: "Rome"
    //  Ore: 10
    //  Wood: 10
    //  Livestock: 10
    //  Crop: 10
    //  Water: 10
    //  Smarts: 0.4
    //  Power: 0.4
    //  Happiness: 0.5
    //  Agression: 0.5
    //  Diplomacy: 0.5
    //  Fiscal: 0.5
    //  Tradition: 0.2
    //  Flexibility: 0.2
    //  Relationships {
    //     Greece: 0.7
    //     Spain: 0.2
    //  }
    // }
    // Tiles eg.
    // Tiles {
    //     Row {
    //         Field
    //         Field
    //         Crop
    //         Crop
    //         Livestock
    //         Field
    //     }
    //     Row {
    //         Field
    //         Ore
    //         Field
    //         Ore
    //         Wood
    //         Wood
    //     }
    //     Row {
    //         Water
    //         Water
    //         Water
    //         Water
    //         Wood
    //         Wood
    //     }
    //     Row {
    //         Field
    //         Crop
    //         Crop
    //         Crop
    //         Water
    //         Water
    //     }
    //     Row {
    //         Ore
    //         Wood
    //         Field
    //         Livestock
    //         Field
    //         Field
    //     }
    //     Row {
    //         Field
    //         Crop
    //         Livestock
    //         Field
    //         Ore
    //         Ore
    //     }
    // }  
    // World eg.
    //World {
    //World {
    //     Tension: 0
    //     Prosperity: 0
    //     Chance: 0.5
    //}

    std::ifstream file("../" + filename);
    std::string line;
    cout << "Loading world from file: " << filename << endl;
    while (std::getline(file, line)) {
        std::cout << "Read line: [" << line << "]" << std::endl;
        if (line.find("Civ {") != std::string::npos) {
            cout << "Parsing civilization data..." << endl;
            // Read civ data and create a Civilization object
            parseCivilization(file);
        } else if (line.find("Tiles {") != std::string::npos) {
            cout << "Parsing tile data..." << endl;
            // Read tile data and create Tile objects
            parseTiles(file);
        } else if (line.find("World {") != std::string::npos) {
            cout << "Parsing world data..." << endl;
            // Read world data and set time, tension, prosperity, and eventChance
            parseWorld(file);
        }
    }
    std::cout << "Finished loading world from file." << std::endl;

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

void Yonder::parseCivilization(std::ifstream& file) {
    Civilization civ("");
    std::string line;
    while(std::getline(file, line)) {
        if (line.find("}") != std::string::npos) {
            break; // End of civilization block
        }
        if(line.find("Name: ") != std::string::npos) {
            std::string name = line.substr(line.find("Name: ") + 6);
            // Create a new Civilization object with the name and default values
            civ.setName(name);
        } else if (line.find("Ore: ") != std::string::npos) {
            int ore = std::stoi(line.substr(line.find("Ore: ") + 5));
            civ.setResource("Ore", ore);
        } else if (line.find("Wood: ") != std::string::npos) {
            int wood = std::stoi(line.substr(line.find("Wood: ") + 6));
            civ.setResource("Wood", wood);
        } else if (line.find("Livestock: ") != std::string::npos) {
            int livestock = std::stoi(line.substr(line.find("Livestock: ") + 11));
            civ.setResource("Livestock", livestock);
        } else if (line.find("Crop: ") != std::string::npos) {
            int crop = std::stoi(line.substr(line.find("Crop: ") + 6));
            civ.setResource("Crop", crop);
        } else if (line.find("Water: ") != std::string::npos) {
            int water = std::stoi(line.substr(line.find("Water: ") + 7));
            civ.setResource("Water", water);
        } else if (line.find("Smarts: ") != std::string::npos) {
            double smarts = std::stod(line.substr(line.find("Smarts: ") + 8));
            civ.setResource("Smarts", smarts);
        } else if (line.find("Power: ") != std::string::npos) {
            double power = std::stod(line.substr(line.find("Power: ") + 7));
            civ.setResource("Power", power);
        } else if (line.find("Happiness: ") != std::string::npos) {
            double happiness = std::stod(line.substr(line.find("Happiness: ") + 11));
            civ.setResource("Happiness", happiness);
        } else if (line.find("Aggression: ") != std::string::npos) {
            double aggression = std::stod(line.substr(line.find("Aggression: ") + 12));
            civ.setAggression(aggression);
        } else if (line.find("Diplomacy: ") != std::string::npos) {
            double diplomacy = std::stod(line.substr(line.find("Diplomacy: ") + 11));
            civ.setDiplomacy(diplomacy);
        } else if (line.find("Fiscal: ") != std::string::npos) {
            double fiscal = std::stod(line.substr(line.find("Fiscal: ") + 7));
            civ.setFiscal(fiscal);
        } else if (line.find("Tradition: ") != std::string::npos) {
            double tradition = std::stod(line.substr(line.find("Tradition: ") + 11));
            civ.setTradition(tradition);
        } else if (line.find("Flexibility: ") != std::string::npos) {
            double flexibility = std::stod(line.substr(line.find("Flexibility: ") + 13));
            civ.setFlexibility(flexibility);
        } else if (line.find("CivCenter: ") != std::string::npos) {
            std::string coords = line.substr(line.find("CivCenter: ") + 11);
            // Assuming format "CivCenter: x y"
            std::istringstream iss(coords);
            int x, y;
            iss >> x >> y;
            for (auto& tile : tiles) {  // non-const reference so pointer stays valid
                if (tile.getX() == x && tile.getY() == y) {
                    civ.setCivCenter(&tile);
                    civ.addTile(&tile);  // also add it as an owned tile
                    break;
                }
            }
        } else if (line.find("Color: ") != std::string::npos) {
            std::string color = line.substr(line.find("Color: ") + 7);
            civ.setColor(color);
        } else if (line.find("Relationships {") != std::string::npos) {
            // Read relationships
            while(std::getline(file, line)) {
                if (line.find("}") != std::string::npos) {
                    break; // End of relationships block
                }
                size_t colonPos = line.find(": ");
                if (colonPos != std::string::npos) {
                    std::string otherCivName = line.substr(0, colonPos);
                    double relationshipValue = std::stod(line.substr(colonPos + 2));
                    // Store the relationship in the Civilization object
                    // Note: We will need to resolve the other civilization's pointer after we have read all civilizations
                    // TODO: Store relationships in a temporary structure and resolve after reading all civilizations
                }
            }
        }
    }
    addCivilization(civ);
}

void Yonder::parseTiles(std::ifstream& file) {
    std::string line;
    int y = 0;
    while(std::getline(file, line)) {
        if (line.find("}") != std::string::npos) {
            worldHeight = y;
            break; // End of tiles block
        }
        if (line.find("Row {") != std::string::npos) {
            int x = 0;
            while(std::getline(file, line)) {
                if (line.find("}") != std::string::npos) {
                    break; // End of row block
                }
                line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end()); // Remove whitespace
                // Create a new Tile object with the type and coordinates (x, y)
                Tile tile(x, y, line);
                addTile(tile);
                x++;
            }
            worldWidth = max(worldWidth, x);
            y++;
        }
    }
}

void Yonder::parseWorld(std::ifstream& file) {
    std::string line;
    while(std::getline(file, line)) {
        if (line.find("}") != std::string::npos) {
            break; // End of world block
        }
        if (line.find("Tension: ") != std::string::npos) {
            double tension = std::stod(line.substr(line.find("Tension: ") + 9));
            setTension(tension);
        } else if (line.find("Prosperity: ") != std::string::npos) {
            double prosperity = std::stod(line.substr(line.find("Prosperity: ") + 12));
            setProsperity(prosperity);
        } else if (line.find("Chance: ") != std::string::npos) {
            double eventChance = std::stod(line.substr(line.find("Chance: ") + 8));
            setEventChance(eventChance);
        }
    }
}


void Yonder::initializeWorld() {
    // Create tiles, assign resources, and set up civilizations
    for (int x = 0; x < 20; ++x) {
        for (int y = 0; y < 20; ++y) {
            tiles.emplace_back(x, y, "Field");
        }
    }

    for (int i = 0; i < 5; i++) {
        // Note, civ name is of type const std::string& name, so we need to create a temporary string to pass to the constructor
        const std::string civName = "Civ-" + std::to_string(i);
        Civilization civ(civName, 0.5, 0.5, 0.5, 0.5, 0.5);
        civilizations.emplace_back(civ);
        civilizations.back().addTile(&tiles[i * 4]);
        civilizations.back().setCivCenter(&tiles[i * 4]);
        for (auto& pair : resourceTypes) {
            civilizations.back().setResource(pair.first, 10);
        }
    }

    for (size_t i = 0; i < civilizations.size(); i++) {
        std::vector<std::pair<Civilization*, double>> relationships;
        for (size_t j = 0; j < civilizations.size(); j++) {
            if (i != j) {
                relationships.emplace_back(&civilizations[j], 0.5);
            }
        }
        civilizations[i].setRelationships(relationships);
    }
}

void Yonder::printState() const {
    for (const auto& civ : civilizations) {
        std::cout << "Civilization: " << civ.getName() << std::endl;
        std::cout << "Resources: " << std::endl;
        for (const auto& pair : resourceTypes) {
            std::cout << "  " << pair.first << ": " << civ.getResource(pair.first) << std::endl;
        }
        std::cout << "Relationships: " << std::endl;
        for (const auto& rel : civ.getRelationships()) {
            std::cout << "  " << rel.first->getName() << ": " << rel.second << std::endl;
        }
        for(const auto& tile : civ.getTiles()) {
            std::cout << "  Tile (" << tile->getX() << ", " << tile->getY() << "): " << tile->getType() << std::endl;
        }
        std::cout << std::endl;
    }

    for (const auto& tile : tiles) {
        std::cout << "Tile (" << tile.getX() << ", " << tile.getY() << "): " << tile.getType() << std::endl;
    }
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

void Yonder::addTile(const Tile& tile) {
    tiles.push_back(tile);
}

std::vector<Tile> Yonder::getTiles() const {
    return tiles;
}

Civilization* Yonder::getCivilization(const std::string& name) {
    for (auto& civ : civilizations) {
        if (civ.getName() == name) {
            return &civ;
        }
    }
    return nullptr;
}
vector<Civilization> Yonder::getCivilizations() const {
    return civilizations;
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