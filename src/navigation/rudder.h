#ifndef RUDDER_H
#define RUDDER_H

#include <glm/glm.hpp>
#include "hydrosurface.h"

/**
 * @brief Abstract base class for hydrodynamic surfaces (e.g., keel, rudder, sail).
 */
class Rudder : public HydroSurface {
public:
    Rudder(glm::vec2 position);
    ~Rudder() {}

    /**
     * @brief Compute the hydrodynamic force produced by the surface.
     * @param relativeVelocity The velocity of the fluid relative to the surface in body/frame coordinates.
     * @param angleOfAttack The angle between the surface and the oncoming flow.
     * @param density The density of the fluid.
     * @return A glm::vec2 representing the force vector exerted by the surface.
     */
    glm::vec2 computeWForce(const glm::vec2& relativeVelocity, double angleOfAttack, double density) const;

/**
     * @brief Compute the Aerodynamic force produced by the surface.
     * @param relativeVelocity The velocity of the fluid relative to the surface in body/frame coordinates.
     * @param angleOfAttack The angle between the surface and the oncoming flow.
     * @param density The density of the fluid.
     * @return A glm::vec2 representing the force vector exerted by the surface.
     */

    glm::vec2 computeAForce(const glm::vec2& relativeVelocity, double angleOfAttack, double density) const;

    /**
     * @brief Get the position of the rudder.
     * @return A glm::vec2 representing the position of the rudder.
     */

    const glm::vec2& getPosition() const;

    double getRudderAngle() const ;
    void setRudderAngle(double angle) ;
    void incrementRudderAngle(double delta);
    void decrementRudderAngle(double delta); 
    glm::vec2 getCEOtoCOMB() ; // get the distance between the center of effort and the center of mass of boat
    void computeForce(const glm::vec2& wrelativeVelocity,const glm::vec2& arelativeVelocity, double adensity, double wdensity,double wAOA,double aAOA) ;
    const glm::vec2& getForce() const ;
    private:
        double rudderAngle = M_PI;       // radians
        double Area = 1.0; // m^2
        glm::vec2 position{0.0f, 0.0f}; // coordinates on the boat

        glm::vec2 CEOtoBack{-0.5f, 0.0f}; // coordinates on the boat
        glm::vec2 force{0.0f, 0.0f};


};

#endif // RUDDER_H