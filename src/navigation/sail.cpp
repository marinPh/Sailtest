#include "sail.h"
#include <cmath> // For M_PI
#include <algorithm> // For std::clamp
#include <iostream>

Sail::Sail(glm::vec2 position) : position(position)
{
}

glm::vec2 Sail::computeWForce(const glm::vec2 &relativeVelocity, double angleOfAttack, double density) const
{
    return glm::vec2(0.0f, 0.0f);
}

glm::vec2 Sail::computeAForce(const glm::vec2 &relativeVelocity, double angleOfAttack, double density) const
{
    //compute lift and drag from air

    double speed = std::sqrt(relativeVelocity.x * relativeVelocity.x + relativeVelocity.y * relativeVelocity.y);


    double AOA = angleToBoat - angleOfAttack; // simplified assumption

    // Simplified coefficients (replace with better models as needed)
    //implement a turbulence model

    double CL = 0.5 *M_PI * std::sin(2 * AOA);
    double CD = 0.1 + 0.5 * std::sin(AOA) * std::sin(AOA)*2.1;
    std::cout << "CL: " << CL << " CD: " << CD << std::endl;

    //implement use of Reynold's number
    double lift =  density * speed * speed * Area * CL;
    double drag = 0.5 * density * speed * speed * Area * CD;

    auto relativeTowind = glm::vec2(-drag, lift);

    std ::cout << "relative to wind: " << relativeTowind.x << " " << relativeTowind.y<< "from -> " << glm::degrees(AOA) << "  "<< glm::degrees(angleOfAttack) << std::endl;
    
    //rotate the force to the boat frame

    
    float cosYaw = std::cos(angleOfAttack);
    float sinYaw = std::sin(angleOfAttack);

    glm::vec2 worldVelocity(relativeTowind.x * cosYaw - relativeTowind.y * sinYaw,
                            relativeTowind.x * sinYaw + relativeTowind.y * cosYaw);
    std ::cout << "relative to boat: " << worldVelocity.x << " " << worldVelocity.y<< std::endl;

    // For simplicity, assume drag acts along -x and lift along y-axis of boat frame.

    // negated because the force is opposite to the velocity
    return worldVelocity;
}

glm::vec2 Sail::getCEOtoCOMB()
{
    auto original = glm::vec2(-0.5f, 0.0f);

    float cosYaw = std::cos(angleToBoat);
    float sinYaw = std::sin(angleToBoat);

    glm::vec2 positionToMast(original.x * cosYaw - original.y * sinYaw, original.x * sinYaw + original.y * cosYaw);

    return positionToMast + position;
}

void Sail::computeForce(const glm::vec2 &wrelativeVelocity,
                        const glm::vec2 &arelativeVelocity,
                        double adensity,
                        double wdensity,
                        double wAOA,
                        double aAOA)
{
    this->force = computeAForce(arelativeVelocity, aAOA, adensity);
}

const glm::vec2 &Sail::getForce() const
{
    return force;
}

double Sail::getAngle() const
{
    return angleToBoat;
}

double Sail::getBase() const
{
    return base;
}

void Sail::incrementAngle(double delta)
{
    angleToBoat += delta;
    angleToBoat = std::clamp(angleToBoat, -maxAngle, maxAngle); // Clamp between -60 and 60 degrees
}

void Sail::decrementAngle(double delta)
{
    angleToBoat -= delta;
    angleToBoat = std::clamp(angleToBoat, -maxAngle, maxAngle); // Clamp between -60 and 60 degrees
}

const glm::vec2& Sail::getPosition() const{
    return position;
}
