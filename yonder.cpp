
#include "tile.cpp"
#include "civ.cpp"

class Yonder {
public:
    Yonder() {
        // Initialize the world, civilizations, and tiles here
    }
    void initializeWorld() {
        // Create tiles, assign resources, and set up civilizations
    }

    void setTime(double t) { time = t; }
    double getTime() const { return time; }
    void setTension(double t) { tension = t; }
    double getTension() const { return tension; }
    void setProsperity(double p) { prosperity = p; }
    double getProsperity() const { return prosperity; }
    void setEventChance(double c) { eventChance = c; }
    double getEventChance() const { return eventChance; }
    void addCivilization(const Civilization& civ) {
        civilizations.push_back(civ);
    }
    void removeCivilization(const std::string& name) {
        civilizations.erase(std::remove_if(civilizations.begin(), civilizations.end(),
            [&name](const Civilization& c) { return c.getName() == name; }), civilizations.end());
    }
    int editTile(int x, int y, const Tile& tile) {
        for (auto& t : tiles) {
            if (t.getX() == x && t.getY() == y) {
                t = tile;
                return 0;
            }
        }
        // If tile doesn't exist, return an error code
        return -1;
    }

    // Return a vector of pairs of civilizations and their resources, can be used for displaying global resource information, making decisions based on global resources, etc.
    std::vector<std::pair<std::Civilization, std::vector<std::Resource>>> getGlobalResources() const {
        // Calculate total resources held by summing up resources from all civilizations
        std::vector<std::pair<std::Civilization, std::vector<std::Resource>>>globalResources;
        for (const auto& civ : civilizations) {
            globalResources.emplace_back();
            globalResources.back().first = civ;
            globalResources.back().second.push_back(civ.getOre());
            globalResources.back().second.push_back(civ.getWood());
            globalResources.back().second.push_back(civ.getLivestock());
            globalResources.back().second.push_back(civ.getCrop());
            globalResources.back().second.push_back(civ.getWater());
            globalResources.back().second.push_back(civ.getPopulation());

        }
        return globalResources;
    }

    std:vector<<std::pair <std::Resource, double>> getGlobalAverages() const {
        auto globalResources = getGlobalResources();
        std::vector<std::pair<std::Resource, double>> globalAverages;
        for (size_t i = 0; i < 5; i++) { // For each resource
            // 0 = Ore, 1 = Wood, 2 = Livestock, 3 = Crop, 4 = Water
            double total = 0;
            for (const auto& civ : globalResources) {
                total += civ.second[i].getQuantity();
            }
            globalAverages.emplace_back();
            globalAverages.back().first = globalResources[0].second[i]; // Get the resource type from the first civilization, they should all be the same
            globalAverages.back().second = total / civilizations.size(); // Average quantity of the resource across all civilizations
        }
        
        return globalAverages;
    }

    void checkForEvents() {
        // Check if a random event should occur based on eventChance
        // If an event occurs, modify resources, population, tension, prosperity, etc. accordingly
        if (rand() % 100 < eventChance * 100) {
            // Example event: Natural disaster
            Alert("A natural disaster has occurred!");
            int damage = rand() % 10 + 1; // Random damage between 1 and 10
            for (auto& civ : civilizations) {
                Civilization::setHappiness(civ, Civilization::getHappiness(civ) - damage);
                Civilization::setPopulation(civ, Civilization::getPopulation(civ) - damage);
            }
            tension += 0.05; // Increase tension due to the disaster
            prosperity -= 0.05; // Decrease prosperity due to the disaster
        }
    }

    void Alert(const std::string& message) {
        // Display an alert message to the player, can be used for events, notifications, etc.
        std::cout << "ALERT: " << message << std::endl;
    }

    void run() {
        // Main game loop
        std::vector<std::Civilization> civilizations; // This should be initialized with the civilizations in the world
        while (true) {
            // Update civilizations, handle interactions, etc.
            // Order of operations:
            // 1. Update time and global conditions (tension, prosperity, events)
            // 2. Each civilization gets resources from their tiles
            // 3. Each civilization makes decisions based on their resources and traits, going one by one in a random order
            // 4. Once all civilizations have decided to not act, the loop restarts and time advances
            time++;
            eventChance += 0.01; // Increase event chance over time, can be reset by events
            tension += 0.01; // Increase tension over time, can be reset by events
            prosperity += 0.01; // Increase prosperity over time, can be reset by events
            checkForEvents();
            for (auto& civ : civilizations) {
                Civilization::produceResources(civ);
            }

            // Vector of civs and their attempted actions
            std::vector<std::pair<std::Civilization, std::vector<std::tuple<int, int, int>>>> actingCivs = civilizations; 
            // Each civilization gets to act once, then the next acts, and so on until all civilizations have decided to not act, then the loop restarts and time advances
            while(!actingCivs.empty()) {
                for (auto& civ : actingCivs) {
                    if (Civilization::civ.act(getGlobalAverages()) == "0)") {
                        // If the civilization decides to not act, remove it from the actingCivs vector
                        actingCivs.erase(std::remove_if(actingCivs.begin(), actingCivs.end(),
                            [&civ](const std::pair<std::Civilization, std::vector<std::tuple<int, int, int>>>& c) { return c.first.getName() == civ.getName(); }), actingCivs.end());
                        break;
                    }
                }
            }
        }
    }
private:
    std::vector<Tile> tiles;
    std::vector<Civilization> civilizations;
    double time; // Game time, can be used for events, seasons, etc.
    // TODO: Implement these
    double tension; // Global tension level, can affect diplomacy and conflict
    double prosperity; // Global prosperity level, can affect resource generation and happiness
    double eventChance; // Chance of random events occurring, can affect resources and population
};