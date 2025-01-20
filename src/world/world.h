#ifndef WORLD_H
#define WORLD_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <SFML/OpenGL.hpp>
#include <boat.h>
#include <cmath>
#include <glm/vec2.hpp>
#include "storm.h"

class World
{
public:
    World();
    void draw(sf::RenderWindow &window);
    void update(float dt);
    void handleInput();
    glm::vec2 getWind(float lat, float lon); // Get wind velocity on north-east plane
    glm::vec2 getBoatPosition();
    float getBoatYaw();
    float getBoatSpeed();

private:
    Boat pboat;
    std::vector<Boat *> AIboats;
    std::vector<Storm *> storms;
    

};

#endif // WORLD_H
