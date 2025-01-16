#ifndef BOAT_H
#define BOAT_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp> // Optional for printing or interfacing with other libraries

#include <cmath>

class Boat {
public:
    // Physical properties
    double mass = 100.0; // kg
    double inertiaZ = 500.0; // 
    double momentZ = 0.0; // Nm

    // State variables
    glm::vec2 position{0.0f, 0.0f}; // world coordinates
    double yaw = 0.0;               // orientation in radians
    glm::vec2 velocity{0.0f, 0.0f}; // in boat's body frame (surge, sway)
    double yawRate = 0.0;           // angular velocity
    double yawDampingCoefficient = 100.0; // example value; tune as needed
    // Control inputs
    double rudderAngle = 0.0;       // radians

    // Simplified geometry and coefficients
    double rudderArea = 1.0; // m^2
    double keelArea = 2.0; // m^2
    double distanceRudderToCG = 5.0; // meters
    double distanceKeelToCG = 2.0; // meters
    double waterDensity = 1000.0;

    double motorForce = 0.0; // in m^2/s

    // Update function
    void update(double dt);

    void motorIncrement(double dt);
    void motorDecrement(double dt);

    void rudderIncrement(double dt);

    void rudderDecrement(double dt);

    double getRudderPosition();

    glm::vec2 GetVec();
    glm::vec2 GetWVec();

    double getDirection();
    glm::vec2 computeRudderForce();

    glm::vec2 computeKeelForce();

    glm::vec2 computeHullForce();

private:
    
};

#endif
