#ifndef HYDROSURFACE_H
#define HYDROSURFACE_H

#include <glm/glm.hpp>
#include <SFML/Graphics.hpp>

/**
 * @brief Abstract base class for hydrodynamic surfaces (e.g., keel, rudder, sail).
 */
class HydroSurface {
public:
    virtual ~HydroSurface() {}


    virtual glm::vec2 computeWForce(const glm::vec2& relativeVelocity, double angleOfAttack, double density) const = 0;
    virtual glm::vec2 computeAForce(const glm::vec2& relativeVelocity, double angleOfAttack, double density) const = 0;
    virtual const glm::vec2& getPosition() const = 0;
    //TODO:fix order before loosing hair
    virtual void computeForce(const glm::vec2& wrelativeVelocity,const glm::vec2& arelativeVelocity, double adensity, double wdensity,double wAOA,double aAOA) = 0;
    virtual const glm::vec2& getForce() const = 0;
    
    virtual glm::vec2 getCEOtoCOMB() = 0;
    virtual void draw(sf::RenderWindow& window,sf::Transform boatTransform,sf::Vector2f origin_point) = 0;


    
};
#endif // HYDROSURFACE_H