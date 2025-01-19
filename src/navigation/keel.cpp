#include "keel.h"
#include <iostream>
#include <glm/ext/matrix_transform.hpp>

Keel::Keel(glm::vec2 position) : position(position)
{
}

glm::vec2 Keel::computeWForce(const glm::vec2 &relativeVelocity, double angleOfAttack, double density) const
{
    // Step 1: Compute speed and relative flow in body frame
    // Assuming velocity is already in boat’s body frame (surge, sway)
    double u = relativeVelocity.x; // Surge component along boat's axis
    double v = relativeVelocity.y; // Sway component perpendicular to boat's axis
    double speed = std::sqrt(u * u + v * v);
    

    // Step 2: Calculate angle of attack at the keel


    // Step 3: Compute lift and drag using the angle of attack
    double CL = 0.5 * std::sin(2 * angleOfAttack);                             // placeholder formula
    double CD = 0.1 + 0.5 * std::sin(angleOfAttack) * std::sin(angleOfAttack); // placeholder
    // std::cout << "of keel"<< 0.1 << " " << 0.5 << " " << std::sin(angleOfAttack) << "=" << CD << std::endl;



    double lift = 0.5 * density * speed * speed * keelArea * CL;
    //multiply by factor of speed 
    double drag = 0.5 * density * speed * speed * keelArea * CD;
        //std::cout << 0.1 << " " << 0.5 << " " << std::sin(angleOfAttack) << "=" << CD << "-> " << drag << std::endl;

    

    //std::cout << "lift: " << lift << " drag: " << drag << std::endl;

    //should be 

    //apply the force on velocity vector not on boat frame
    //FIXME: y is lift negated?
    auto vec = glm::vec2(-drag, -lift);

    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), static_cast<float>(angleOfAttack), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::vec4 rotatedVec = rotationMatrix * glm::vec4(vec, 0.0f, 1.0f);

    return glm::vec2(rotatedVec);
}

glm::vec2 Keel::computeAForce(const glm::vec2 &relativeVelocity, double angleOfAttack, double density) const
{
    return glm::vec2(0.0f, 0.0f);
}

const glm::vec2 &Keel::getPosition() const
{
    return position;
}

glm::vec2 Keel::getCEOtoCOMB()
{
    return position;
}

void Keel::computeForce(const glm::vec2 &wrelativeVelocity,
                        const glm::vec2 &arelativeVelocity,
                        double adensity,
                        double wdensity,
                        double wAOA,
                        double aAOA)
{

    force = computeWForce(wrelativeVelocity, wAOA, wdensity);
}
const glm::vec2 &Keel::getForce() const
{
    return force;
}
