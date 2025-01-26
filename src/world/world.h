#ifndef WORLD_H
#define WORLD_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <SFML/OpenGL.hpp>
#include <boat.h>
#include <cmath>
#include <glm/vec2.hpp>
#include "storm.h"
#include "globe.h"

class World
{
public:
    World(sf::Sprite& boatS, sf::RenderWindow& window);
    void draw(sf::RenderWindow &window);
    void update(float dt);
    void handleInput();
    glm::vec2 getWind(float lat, float lon); // Get wind velocity on north-east plane
    glm::vec2 getBoatPosition();
    float getBoatYaw();
    float getBoatSpeed();
    void setPlanarView();
    void setSphericalView();
    void handleEvents(sf::Event& e,float dt);
    glm::vec2 latLonToXY(float lat, float lon);

private:
    Boat pboat;
    std::vector<Boat *> AIboats;
    std::vector<Storm *> storms;
    sf::RenderWindow& window;
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;
    sf::View view;
    Globe globe;
    bool isPlanarView = true;
    sf::Sprite boatS;


};

#endif // WORLD_H
