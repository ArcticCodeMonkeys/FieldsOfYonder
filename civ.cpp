

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
    // Relative population compared to known civilizations, can be used for decision making in diplomacy, aggression, etc.
    double getPopulationRelative() const { return population.getQuantity() / Math.average(knownCivs.begin(), knownCivs.end(), [](Civilization* c) { return c->getPopulation().getQuantity(); }); }
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
    double getActionWeightByIndex(int index) const {
        // Action weights are based on the civ's tendancies and personalities
        // The aspects are also factored because the actions will result in increases or decreases to those aspects.
        // Trade: =Power, -Happiness, +Population, -Smarts, +Likeability
        // Build: -Power, +Happiness, +Population, =Smarts, -Likeability
        // Attack: +Power, =Happiness, -Population, +Smarts, -Likeability
        // Negotiate: -Power, +Happiness, =Population, -Smarts, +Likeability
        // Invest: +Power, -Happiness, -Population, +Smarts, =Likeability

        double tradeWeight = (1+diplomacy) * (1-happiness) * (1+populationRelative) * (1-smarts) * (1+likeability);
        double buildWeight = (1+tradition) * (1-power) * (1+happiness) * (1+populationRelative) * (1-likeability);
        double attackWeight = (1+aggression) * (1+power)  * (1-populationRelative) * (1+smarts) * (1-likeability);
        double negotiateWeight = (1+flexibility) * (1-power) * (1+happiness) * (1-smarts) * (1+likeability);
        double investWeight = (1+fiscal) * (1+power) * (1-happiness) * (1-populationRelative) * (1+smarts);
        switch (index) {
            case 0: return tradeWeight;
            case 1: return buildWeight;
            case 2: return attackWeight;
            case 3: return negotiateWeight;
            case 4: return investWeight;
            default: return 0;
        }
    }

    int act(const std::vector<std::pair<std::Resource, double>>& globalAverages, std::vector<std::tuple<int, int, int>>& attemptedActions) {
        // Implement decision making logic based on weights and resources
        // For example, if aggression is high and ore is abundant, the civilization might choose to attack
        // If diplomacy is high and water is scarce, it might choose to negotiate for resources
        // This function would prompt a reaction from a target civilization.
        // Action Options: Trade, Build, Attack, Negotiate, Invest.
        // Add logic do not act logic based on how many actions have already been taken.
        // int tradesMade = 0;
        // int buildingsConstructed = 0;
        // int attacksLaunched = 0;
        // int negotiationsInitiated = 0;
        // int investmentsMade = 0;

        // For now, simple logic to prevent infinite loops. Flexibility allows varying amount of actions to be taken, but if too many actions have already been taken, the civilization will choose to not act to prevent infinite loops and encourage strategic decision making.

        if (attemptedActions->size() >= 10 * flexibility && attemptedActions->size() > 1 * (1-flexibility)) { // Limit the number of actions a civilization can take in one turn to prevent infinite loops and encourage strategic decision making
            return 0; // Did not act, too many actions already taken
        }
        
        // Create 3d action matrix based on action weights and the resource we would act upon, for example if we need ore, we will prioritize actions that would give us ore, if we have a lot of ore, we might prioritize actions that would spend ore to gain other resources or advantages
        // The value at x, y, z in the matrix is the action weight for action divided by the ratio of current resource to the specified civilization z, multipled by the relationship with that civilization z.
        double std::vector<std::vector<std::vector<double>>> actionMatrix ;
        // First calculate resource ratios for each civ.
        for (size_t i = 0; i < 5; i++) { // For each resource
            // 0 = Ore, 1 = Wood, 2 = Livestock, 3 = Crop, 4 = Water
            double resourceRatio = globalAverages[i].second / (getResourceByIndex(i).getQuantity() + 1); // > 1 if we have less than average, and < 1 if we have more than average, +1 to prevent division by zero
            for (size_t j = 0; j < knownCivs.size(); j++) { // For each civilization
                // TODO: For building use distance to resource instead of relationship and civ.
                // TODO: For attack, use 1-relationship with civ instead of relationship.
                double relationship = getRelationshipWithCivilization(knownCivs[j]);
                for (size_t k = 0; k < 5; k++) { // For each action
                    actionMatrix[i][j][k] = getActionWeightByIndex(k) * resourceRatio * relationship;
                }
            }
        }

        // Iterate through the matrix and find the action with the highest weight, then attempt that action, and if successful, return 1 to indicate that an action was taken, if not successful, set that action weight to 0 and try again until we find a successful action or exhaust all options
        actionIndex = (0, 0, 0);
        highestWeight = 0;
        for(size_t i = 0; i < 5; i++) {
            for (size_t j = 0; j < knownCivs.size(); j++) {
                for (size_t k = 0; k < 5; k++) {
                    // Check if this action has a higher weight than the current highest, and if it has not already been attempted
                    if (actionMatrix[i][j][k] > highestWeight && std::find(attemptedActions.begin(), attemptedActions.end(), std::make_tuple(i, j, k)) == attemptedActions.end()) {
                        highestWeight = actionMatrix[i][j][k];
                        actionIndex = (i, j, k);
                    }
                }
            }
        }

        // X = Resource, Y = Target Civilization, Z = Action Type

        if(actionIndex == (-1, -1, -1)) {
            return 0; // No valid actions available, did not act
        }

        attemptAction(actionIndex); // Implement the logic for attempting the action based on the action type, target civilization, and resource, this would involve modifying resources, relationships, population, etc. based on the action taken and its success or failure
        attemptedActions.push_back(actionIndex);
        
    }

    void attemptAction(std::tuple<int, int, int> actionIndex) {
        // Implement the logic for attempting the action based on the action type, target civilization, and resource, this would involve modifying resources, relationships, population, etc. based on the action taken and its success or failure
        // For example, if the action is to trade for water with a civilization we have a good relationship with, we might increase our water and decrease their water, and improve our relationship with them.
        // X = Resource, Y = Target Civilization, Z = Action Type
        int x = std::get<0>(actionIndex);
        int y = std::get<1>(actionIndex);
        int z = std::get<2>(actionIndex);
        std::Resource resource = getResourceByIndex(x);
        Civilization* targetCiv = knownCivs[y];
        // Trade: =Power, -Happiness, +Population, -Smarts, +Likeability
        // Build: -Power, +Happiness, +Population, =Smarts, -Likeability
        // Attack: +Power, =Happiness, -Population, +Smarts, -Likeability
        // Negotiate: -Power, +Happiness, =Population, -Smarts, +Likeability
        // Invest: +Power, -Happiness, -Population, +Smarts, =Likeability
        // These actions will also provide the relevant resource
        // They also have a chance of failure, which would result in the opposite effects and a loss of the relevant resource, and the chance of success could be based on our smarts, power, relationship with the target civilization, and some randomness.
        switch (z) {
            case 0: // Trade
                // Implement trade logic, for example, we could offer a certain amount of one resource in
            break;
            case 1: // Build
                // Implement build logic, for example, we could spend resources to build a structure that would
                // increase our resource generation, population, happiness, etc.
            break;
            case 2: // Attack
                // Implement attack logic, for example, we could spend resources to launch an attack on the
                // target civilization, which could result in us gaining resources, improving our relationship with them if successful, or losing resources and worsening our relationship if unsuccessful.
                // Success could be determined by a combination of our power, their power, and some randomness. The outcome could modify our resources, their resources, and our relationship with them.
            break;
            case 3: // Negotiate
                // Implement negotiate logic, for example, we could attempt to negotiate with the target civilization for
                // resources, alliances, non-aggression pacts, etc., which could improve our relationship with them if successful, or worsen it if unsuccessful.
            break;
            case 4: // Invest
                // Implement invest logic, for example, we could spend resources to get a chance to gain a large amount of resources, improve our aspects, or gain other advantages, with the risk of losing resources if unsuccessful.
                // EV of this should be positive, but it would have a higher variance than other actions, and the civilization's smarts could affect the expected value and variance of the investment.
            break;
    }

    void generateResources() {
        // Implement resource generation logic based on tiles and civilization attributes
        // For example, if the civilization has a tile with ore, it might generate ore based on its smarts and power 
        // TODO: Replace this with technology based resource generation, where smarts would determine how efficiently a civilization can extract resources from their tiles, and power would determine how many resources they can extract at once, and different technologies would allow for different types of resource generation and extraction methods.
        for (const auto& tile : tiles) {
            for (const auto& resource : tile.resources) {
                if (resource.getName() == "Ore") {
                    setOre(getOre().getQuantity() + static_cast<int>((1+smarts) * (1 + power/2) * population.getQuantity()));
                } else if (resource.getName() == "Wood") {
                    setWood(getWood().getQuantity() + static_cast<int>((1+smarts) * (1 + power/2) * population.getQuantity()));
                } else if (resource.getName() == "Livestock") {
                    setLivestock(getLivestock().getQuantity() + static_cast<int>((1+smarts) * (1 + power/2) * population.getQuantity()));
                } else if (resource.getName() == "Crop") {
                    setCrop(getCrop().getQuantity() + static_cast<int>((1+smarts) * (1 + power/2) * population.getQuantity()));
                } else if (resource.getName() == "Water") {
                    setWater(getWater().getQuantity() + static_cast<int>((1+smarts) * (1 + power/2) * population.getQuantity()));
                } else if (resource.getName() == "Population") {
                    setPopulation(getPopulation().getQuantity() + static_cast<int>((1+tradition) * (1 + happiness) * population.getQuantity()));
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
    double likeability; // AVG of relationship scores with other civilizations, can be used for decision making in diplomacy, trade, etc.
    std::vector<Tile> tiles;
    std::vector<std::Civilization *> knownCivs; // List of civilizations this civilization is aware of, can be used for diplomacy and interactions
};