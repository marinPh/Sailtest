#ifndef BOAT_H
#define BOAT_H


#include "hull.h"
#include "hydrosurface.h" // Include the header file for HydroSurface
#include "keel.h"
#include "rudder.h"
#include "sail.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> // Optional for matrix transformations
#include <glm/gtc/type_ptr.hpp>         // Optional for printing or interfacing with other libraries
#include <vector>

class Boat
{
public:
    Boat(sf::Sprite& sprite,glm::vec2 startingPos);
    // Physical properties
    double mass = 100.0;     // kg
    double inertiaZ = 500.0; //
    double momentZ = 0.0;    // Nm


    // State variables
    glm::vec2 position{0.0f, 0.0f};       // world coordinates
    double yaw = 0.0;                     // orientation in radians
    glm::vec2 velocity{0.0f, 0.0f};       // in boat's body frame (surge, sway)
    double yawRate = 0.0;                 // angular velocity
    double yawDampingCoefficient = 100.0; // example value; tune as needed
    // Control inputs


    // Simplified geometry and coefficients

    double keelArea = 2.0;           // m^2
    double distanceRudderToCG = 5.0; // meters
    double distanceKeelToCG = 2.0;   // meters
    double waterDensity = 1000.0;    // kg/m^3
    double airDensity = 1.225;       // kg/m^3
    double motorForce = 0.0;         // in m^2/s

    double sailArea = 2.0; // m^2

    // Update function
    void update(double dt, glm::vec2 &worldWind);

    void motorIncrement(double dt);
    void motorDecrement(double dt);

    sf::Vector2f getPosition();

    void setRudderAngle(double angle);
    void rudderIncrement(double dt);
    void rudderDecrement(double dt);
    double getRudderPosition();

    void sailIncrement(double dt);
    void sailDecrement(double dt);
    glm::vec2 getSailEnd();
    double getSailAngle() const;

    glm::vec2 GetVec();
    glm::vec2 GetWVec();
    double getDirection();

    glm::vec2 computeRudderForce(double angleOfAttack);
    glm::vec2 computeKeelForce(double angleOfAttack);
    glm::vec2 computeHullForce();
    glm::vec2 computeSailForce();

    void computeForces(const glm::vec2 &wrelativeVelocity,
                       double wdensity,
                       const glm::vec2 &arelativeVelocity,
                       double adensity);
    glm::vec2 computeTotalForce();

    void addSurface(HydroSurface *surface);
    void removeSurface(HydroSurface *surface);

    void draw(sf::RenderWindow &window);


private:
    double computeMomentz();
    sf::Sprite& sprite;

    Rudder rudder;
    Keel keel;
    Hull hull;
    Sail sail;

    //list of hydrodynamic surfaces
    std::vector<HydroSurface *> surfaces;
};

#endif
