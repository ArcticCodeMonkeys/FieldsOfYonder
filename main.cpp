#include "yonder.h"
#include <iostream>
#include "SFML/Graphics.hpp"


using namespace std;

// const int WINDOW_WIDTH = 32*20;
// const int WINDOW_HEIGHT = 32*18;
const int TILE_SIZE = 128; 

void renderTiles(const std::vector<Tile>& tiles, sf::RenderWindow& window) {
    for (const auto& tile : tiles) {
        // Render the tile based on its type and owner
        // This is a placeholder for actual rendering logic
        // Use SFML
        sf::RectangleShape rectangle(sf::Vector2f(TILE_SIZE, TILE_SIZE));
        sf::Vector2f position(tile.getX() * TILE_SIZE, tile.getY() * TILE_SIZE);
        // place the tile slightly smaller than the tile size to create a border effect, rendering a black border around the tile
        sf::RectangleShape border(sf::Vector2f(TILE_SIZE, TILE_SIZE));
        border.setPosition(position);
        border.setFillColor(sf::Color::Black);
        window.draw(border);
        // move and shrink the colored rectangle to create a border effect
        rectangle.setSize(sf::Vector2f(TILE_SIZE - 2, TILE_SIZE - 2));
        position += sf::Vector2f(1, 1);
        rectangle.setPosition(position);
        if (tile.getType() == "Field") {
            sf::Color fieldColor(34, 139, 34); // Green color for fields
            rectangle.setFillColor(fieldColor); // Green color for fields
        } else if (tile.getType() == "Ore") {
            sf::Color oreColor(128, 128, 128); // Gray color for ore
            rectangle.setFillColor(oreColor); // Gray color for ore
        } else if (tile.getType() == "Wood") {
            sf::Color woodColor(139, 69, 19); // Brown color for wood
            rectangle.setFillColor(woodColor); // Brown color for wood
        } else if (tile.getType() == "Water") {
            sf::Color waterColor(0, 0, 255); // Blue color for water
            rectangle.setFillColor(waterColor); // Blue color for water
        } else if (tile.getType() == "Livestock") {
            sf::Color livestockColor(255, 255, 0); // Yellow color for livestock
            rectangle.setFillColor(livestockColor); // Yellow color for livestock
        } else if (tile.getType() == "Crop") {
            sf::Color cropColor(0, 255, 255); // Cyan color for crops
            rectangle.setFillColor(cropColor); // Cyan color for crops
        } else {
            rectangle.setFillColor(sf::Color::Black); // Default color for unknown types
        }
        window.draw(rectangle);
    }
}

void renderCivs(const std::vector<Civilization>& civs, sf::RenderWindow& window) {
    for (const auto& civ : civs) {
        // Render the civilization based its list of tiles
        // Print statement for debugging
        const std::string color = civ.getColor();
        sf::Color civColor;
        if (color == "Red") {
            civColor = sf::Color::Red;
        } else if (color == "Green") {
            civColor = sf::Color::Green;
        } else if (color == "Blue") {
            civColor = sf::Color::Blue;
        } else if (color == "Yellow") {
            civColor = sf::Color::Yellow;
        } else if (color == "Cyan") {
            civColor = sf::Color::Cyan;
        } else if (color == "Magenta") {
            civColor = sf::Color::Magenta;
        } else {
            civColor = sf::Color::White; // Default color for unknown colors
        }
        for (const auto& tile : civ.getTiles()) {
            sf::CircleShape circle(TILE_SIZE / 4);
            
            sf::Vector2f position(tile->getX() * TILE_SIZE + (TILE_SIZE/4), tile->getY() * TILE_SIZE + (TILE_SIZE/4));
            circle.setPosition(position);
            circle.setFillColor(civColor); // Use the civilization's color
            window.draw(circle);
        }
    }
}

int main() {
    Yonder yonder("firstField.yndr");
    yonder.printState();
    sf::RenderWindow window(sf::VideoMode({static_cast<unsigned int>(yonder.getWorldWidth() * TILE_SIZE), static_cast<unsigned int>(yonder.getWorldHeight() * TILE_SIZE)}), "Fields of Yonder");
    while(window.isOpen()) {
        
        while (const std::optional event = window.pollEvent())
        {
            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // Clear screen
        window.clear();

        renderTiles(yonder.getTiles(), window);
        renderCivs(yonder.getCivilizations(), window);
        // Update the window
        window.display();

    }
}


