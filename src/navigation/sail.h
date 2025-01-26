#ifndef SAIL_H
#define SAIL_H

#include <glm/glm.hpp>
#include "hydrosurface.h"
#include <SFML/Graphics.hpp>


/**
 * @brief 
 */
class Sail : public HydroSurface {
public:
    Sail(glm::vec2 position);
    ~Sail() {}

  
    glm::vec2 computeWForce(const glm::vec2& relativeVelocity, double angleOfAttack, double density) const;
    glm::vec2 computeAForce(const glm::vec2& relativeVelocity, double angleOfAttack, double density) const;
    const glm::vec2& getPosition() const;
    void incrementAngle(double delta);
    void decrementAngle(double delta);
    glm::vec2 getCEOtoCOMB();

    void computeForce(const glm::vec2 &wrelativeVelocity,
                      const glm::vec2 &arelativeVelocity,
                      double adensity,
                      double wdensity,
                      double wAOA,
                      double aAOA);
    const glm::vec2& getForce() const;

    double getAngle() const;
    double getBase() const;

    void draw(sf::RenderWindow& window, sf::Transform boatTransform,sf::Vector2f origin_point);

    private:

        double base = 1.0; // meters
        glm::vec2 position{0.0f, 0.0f}; // coordinates on the boat
        double Area = 2.0; // m^2
        double angleToBoat = M_PI; // radians
        double criticalAngle = 18.0; // degrees
        double centerOfEffortToMast = 0.5; // meters 
        double maxAngle = 90.0; // degrees
        glm::vec2 force{0.0f, 0.0f};





};
#endif // SAIL_H