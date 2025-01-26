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

    double CL = M_PI * std::sin(2 * AOA);
    double CD = 0.1 + std::sin(AOA) * std::sin(AOA)*2;
    std::cout << "CL: " << CL << " CD: " << CD << std::endl;

    //implement use of Reynold's number
    double lift =  density * speed * speed * Area * CL;
    double drag = 0.5 * density * speed * speed * Area * CD;

    auto relativeTowind = glm::vec2(-drag, lift);
    std ::cout << "relative vel: " << relativeVelocity.x << " " << relativeVelocity.y<<  std::endl;
    std ::cout << "relative to wind: " << relativeTowind.x << " " << relativeTowind.y<< "from -> " << glm::degrees(AOA) << "="<< glm::degrees(angleToBoat)  << " + "<< glm::degrees(angleOfAttack) << std::endl;
    
    //rotate the force to the boat frame

    
    float cosYaw = std::cos(angleOfAttack);
    float sinYaw = std::sin(angleOfAttack);

    glm::vec2 worldVelocity(relativeTowind.x * cosYaw - relativeTowind.y * sinYaw,
                            relativeTowind.x * sinYaw + relativeTowind.y * cosYaw);
    std ::cout << "relative to boat: " << worldVelocity.x << " " << worldVelocity.y<< " ppff "<< glm::degrees(std::atan2(worldVelocity.y,worldVelocity.x)) << std::endl;

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
void Sail::draw(sf::RenderWindow& window, sf::Transform boatTransform, sf::Vector2f origin_point) {
    // Create a rectangle shape representing the sail
    sf::RectangleShape sail(sf::Vector2f(50, 10));

    // Set the origin of the sail to the top left of the rectangle
    sail.setOrigin(0, sail.getSize().y/2); 

    // Position the sail relative to the provided origin_point
    // This positions the top-middle of the sail at origin_point.
    

    sail.setPosition(origin_point+sf::Vector2f(position.x, position.y)*10.0f);

    // Optionally set rotation or other properties based on Sail's angle if needed
    sail.setRotation(glm::degrees(angleToBoat));  // if you want to rotate the sail relative to boat's heading

    // Set a fill color for the sail for visibility (customize as needed)
    sail.setFillColor(sf::Color::Green);

    // Draw the sail using the boat's transform
    window.draw(sail, boatTransform);
}


