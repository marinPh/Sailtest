#ifndef KEEL_H
#define KEEL_H

#include <glm/glm.hpp>
#include "hydrosurface.h"
#include <SFML/Graphics.hpp>

/**
 * @brief 
 */
class Keel : public HydroSurface {
public:
    Keel(glm::vec2 position) ;
    ~Keel() {}

  
    glm::vec2 computeWForce(const glm::vec2& relativeVelocity, double angleOfAttack, double density) const;
    glm::vec2 computeAForce(const glm::vec2& relativeVelocity, double angleOfAttack, double density) const;
    const glm::vec2& getPosition() const;
    glm::vec2 getCEOtoCOMB();
    void computeForce(const glm::vec2& wrelativeVelocity,const glm::vec2& arelativeVelocity, double adensity, double wdensity,double wAOA,double aAOA);
    const glm::vec2& getForce() const;
    void draw(sf::RenderWindow& window,sf::Transform boatTransform,sf::Vector2f origin_point);
    

    private:
        glm::vec2 position{0.0f, 0.0f}; // coordinates on the boat
        double keelArea = 2.0; // m^2
        glm::vec2 force{0.0f, 0.0f};    

};
#endif // KEEL_H