

#include "string"
#include "resource.cpp"
#include "tile.cpp"

class Civilization {
public:
    Civilization(const std::string& name)
        : name(name), ore("Ore"), wood("Wood"), livestock("Livestock"), crop("Crop"), water("Water"), population("Population") {}

    // Getters and setters for tiles
    std::string getName() const { return name; }
    std::vector<Tile> getTiles() const { return tiles; }
    Tile getCivCenter() const { return civCenter; }
    void addTile(const Tile& tile) {
        tiles.push_back(tile);
    }
    void removeTile(int x, int y) {
        tiles.erase(std::remove_if(tiles.begin(), tiles.end(),
            [x, y](const Tile& t) { return t.getX() == x && t.getY() == y; }), tiles.end());
    }
    void setCivCenter(const Tile& center) {
        civCenter = center;
    }
    // Getters and setters for weights
    double getAggression() const { return aggression; }
    double getDiplomacy() const { return diplomacy; }
    double getFiscal() const { return fiscal; }
    double getTradition() const { return tradition; }
    double getFlexibility() const { return flexibility; }
    void setAggression(double value) { aggression = value; }
    void setDiplomacy(double value) { diplomacy = value; }
    void setFiscal(double value) { fiscal = value; }
    void setTradition(double value) { tradition = value; }
    void setFlexibility(double value) { flexibility = value; }
    // Getters and setters for aspects
    double getSmarts() const { return smarts; }
    double getPower() const { return power; }
    double getHappiness() const { return happiness; }
    void setSmarts(double value) { smarts = value; }
    void setPower(double value) { power = value; }
    void setHappiness(double value) { happiness = value; }
    // Getters and setters, add and spend for resources
    Resource getOre() const { return ore; }
    Resource getWood() const { return wood; }
    Resource getLivestock() const { return livestock; }
    Resource getCrop() const { return crop; }
    Resource getWater() const { return water; }
    Resource getPopulation() const { return population; }
    void setOre(int quantity) { ore.setQuantity(quantity); }
    void setWood(int quantity) { wood.setQuantity(quantity); }
    void setLivestock(int quantity) { livestock.setQuantity(quantity); }
    void setCrop(int quantity) { crop.setQuantity(quantity); }
    void setWater(int quantity) { water.setQuantity(quantity); }
    void setPopulation(int quantity) { population.setQuantity(quantity); }
    void addOre(int quantity) { ore.setQuantity(ore.getQuantity() + quantity); }
    void addWood(int quantity) { wood.setQuantity(wood.getQuantity() + quantity); }
    void addLivestock(int quantity) { livestock.setQuantity(livestock.getQuantity() + quantity); }
    void addCrop(int quantity) { crop.setQuantity(crop.getQuantity() + quantity); }
    void addWater(int quantity) { water.setQuantity(water.getQuantity() + quantity); }
    void addPopulation(int quantity) { population.setQuantity(population.getQuantity() + quantity); }
    void spendOre(int quantity) { ore.setQuantity(ore.getQuantity() - quantity); }
    void spendWood(int quantity) { wood.setQuantity(wood.getQuantity() - quantity); }
    void spendLivestock(int quantity) { livestock.setQuantity(livestock.getQuantity() - quantity); }
    void spendCrop(int quantity) { crop.setQuantity(crop.getQuantity() - quantity); }
    void spendWater(int quantity) { water.setQuantity(water.getQuantity() - quantity); }
    void spendPopulation(int quantity) { population.setQuantity(population.getQuantity() - quantity); }

    int act() {
        // Implement decision making logic based on weights and resources
        // For example, if aggression is high and ore is abundant, the civilization might choose to attack
        // If diplomacy is high and water is scarce, it might choose to negotiate for resources
        // This function would prompt a reaction from a target civilization.
        // Action Options: Trade, Build, Attack, Negotiate, Invest.
        if(rand() > 0.5) {
            return 1; // Acted
        } else {
            return 0; // Did not act
        }
    }

    void generateResources() {
        // Implement resource generation logic based on tiles and civilization attributes
        // For example, if the civilization has a tile with ore, it might generate ore based on its smarts and power
        for (const auto& tile : tiles) {
            for (const auto& resource : tile.resources) {
                if (resource.getName() == "Ore") {
                    setOre(getOre().getQuantity() + static_cast<int>(smarts * power * population.getQuantity()));
                } else if (resource.getName() == "Wood") {
                    setWood(getWood().getQuantity() + static_cast<int>(smarts * power * population.getQuantity()));
                } else if (resource.getName() == "Livestock") {
                    setLivestock(getLivestock().getQuantity() + static_cast<int>(smarts * power * population.getQuantity()));
                } else if (resource.getName() == "Crop") {
                    setCrop(getCrop().getQuantity() + static_cast<int>(smarts * power * population.getQuantity()));
                } else if (resource.getName() == "Water") {
                    setWater(getWater().getQuantity() + static_cast<int>(smarts * power * population.getQuantity()));
                } else if (resource.getName() == "Population") {
                    setPopulation(getPopulation().getQuantity() + static_cast<int>(tradition * happiness * population.getQuantity()));
                }
            }
        }
    }


private:
    std::string name;

    // Decision making weights (0-1)
    double aggression;
    double diplomacy;
    double fiscal;
    double tradition;
    double flexibility; 
    std::vector<double> weights;
    // Relationships
    std::vector<std::pair<std::Civilization, double>> relationships; // Pair of civilization and relationship score (from 0 to 1)
    // Resources
    Resource ore;
    Resource wood;
    Resource livestock;
    Resource crop;
    Resource water;
    Resource population;
    // Aspects (0-1)
    double smarts;
    double power;
    double happiness;
    Tile civCenter;
    std::vector<Tile> tiles;
};