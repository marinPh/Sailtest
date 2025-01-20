
#include "world.h"
#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>

World::World()
{
    // Initialize wind
    pboat = Boat();
    storms = std::vector<Storm *>();
    AIboats = std::vector<Boat *>();
}

glm::vec2 World::getWind(float lat, float lon){
// Placeholder wind function; replace with your own
float w_e = cos(lat);
float w_n = -sin(lat);
for (auto storm : storms)
{
    glm::vec2 stormCenter = storm->getCenter();
    float stormSize = storm->getSize();
    glm::vec2 stormDirection = storm->getDirection();
    glm::vec2 boatPosition = pboat.GetVec();
    glm::vec2 stormToBoat = boatPosition - stormCenter;
    float distance = glm::length(stormToBoat);

  
    float angle = std::atan2(stormToBoat.y, stormToBoat.x);
    glm::vec2 windFromStorm = (stormSize > distance) ?  glm::vec2(0.0f,0.0f): glm::vec2(-std::sin(angle), std::cos(angle)) * stormSize / (distance * distance);
    
    // Scale wind based on storm size and distance
    w_e += windFromStorm.x;
    w_n += windFromStorm.y;
}
return glm::vec2(w_e, w_n);
    
}

void World::draw(sf::RenderWindow& window)
{
    // Draw the boat
    pboat.draw(window);
 
}
