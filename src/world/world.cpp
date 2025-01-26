
#include "world.h"
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

World::World(sf::Sprite& boatS, sf::RenderWindow &window)
    : 
    window(window),
    pboat(boatS, glm::vec2(window.getSize().x / 2, window.getSize().y / 2)),
    globe(1.0f, 40, 40, window), 
    boatS(boatS),
    view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y))
{
    storms = std::vector<Storm *>();
    storms.push_back(new Storm(0.1f, glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f)));
    storms.push_back(new Storm(100000.0f, glm::vec2(300.0f, 0.0f), glm::vec2(400.0f, 0.0f)));
    AIboats = std::vector<Boat *>();
     // Initialize the view to cover the screen dimensions

}


void World::draw(sf::RenderWindow &window)
{
    // Draw the boat
 
    if (isPlanarView)
    {
        pboat.draw(window);
    }
    else
    {
        // Draw the globe
        std::cout << "Drawing Globe" << std::endl;
        globe.draw(storms);
    }
}
// Convert plane coordinates to geographic lat/lon starting from Null Island





void World::update(float dt)
{
    // Update the boat
    //tranform x y coordinates to lat lon
    auto lat = 0.0f;
    auto lon = 0.0f;
    
    glm::vec2 wind = globe.getWind(lat, lon,storms);

    std::cout << "Wind: " << wind.x << ", " << wind.y << std::endl;
    pboat.update(dt, wind);

    // Update the globe
    if (!isPlanarView)
    {
        globe.update(dt);
    }
}

void World::handleEvents(sf::Event& e,float dt)
{
    if (isPlanarView)
    {
        pboat.handleEvents(e,dt);
    }
    else
    {
        globe.handleEvents(e,dt);
    }
}



void World::setPlanarView() {
    isPlanarView = true;
    view.setCenter(pboat.getPosition()); // Center the view on the boat
    window.setView(view);                // Apply the view
}

void World::setSphericalView() {
    isPlanarView = false;
    // No specific SFML view settings for the globe
}