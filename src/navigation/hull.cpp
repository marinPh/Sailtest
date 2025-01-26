#include "hull.h"
#include <glm/ext/matrix_transform.hpp>

Hull::Hull()
{
}

glm::vec2 Hull::computeWForce(const glm::vec2 &relativeVelocity, double angleOfAttack, double density) const
{
    double speed = std::sqrt(relativeVelocity.x * relativeVelocity.x + relativeVelocity.y * relativeVelocity.y);
    // Assume hull drag acts opposite to velocity vector
    double hullDragCoefficient = 0.1;
    glm::vec2 dragForce = static_cast<float>(-hullDragCoefficient * 0.5 * density * speed) * relativeVelocity;
    return dragForce;
}

glm::vec2 Hull::computeAForce(const glm::vec2 &relativeVelocity, double angleOfAttack, double density) const
{
    //compute drag and lift from air it is considered as a Symmetrical Airfoil

    double speed = std::sqrt(relativeVelocity.x * relativeVelocity.x + relativeVelocity.y * relativeVelocity.y);


    // Simplified coefficients (replace with better models as needed)
    //implement a turbulence model

    double CL = 0.01 * std::sin(2 * angleOfAttack);
    double CD = 0.1 + 0.5 * std::sin(angleOfAttack) * std::sin(angleOfAttack);

    double lift = 0.5 * density * speed * speed * AWaterLine * CL;
    double drag = 0.5 * density * speed * speed * AWaterLine * CD;

    auto vec = glm::vec2(-drag, lift);

    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), static_cast<float>(angleOfAttack), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::vec4 rotatedVec = rotationMatrix * glm::vec4(vec, 0.0f, 1.0f);

    return glm::vec2(rotatedVec);


}

const glm::vec2 &Hull::getPosition() const
{
    return position;
}

glm::vec2 Hull::getCEOtoCOMB()
{
    return position;
}

void Hull::computeForce(const glm::vec2 &wrelativeVelocity,
                        const glm::vec2 &arelativeVelocity,
                        double adensity,
                        double wdensity,
                        double wAOA,
                        double aAOA)
{

    this->force = computeWForce(wrelativeVelocity, wAOA, wdensity) + computeAForce(arelativeVelocity, aAOA, adensity);
}

const glm::vec2 &Hull::getForce() const
{
    return force;
}

void Hull::draw(sf::RenderWindow &window, sf::Transform boatTransform,sf::Vector2f origin_point){
    
}