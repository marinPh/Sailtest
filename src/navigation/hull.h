#ifndef HULL_H
#define HULL_H

#include <glm/glm.hpp>
#include "hydrosurface.h"

/**
 * @brief 
 */
class Hull : public HydroSurface {
public:
    Hull();
    
    ~Hull() {}

  
    glm::vec2 computeWForce(const glm::vec2& relativeVelocity, double angleOfAttack, double density) const;
    glm::vec2 computeAForce(const glm::vec2& relativeVelocity, double angleOfAttack, double density) const;
    const glm::vec2& getPosition() const;
    glm::vec2 getCEOtoCOMB();
    void computeForce(const glm::vec2& wrelativeVelocity,const glm::vec2& arelativeVelocity, double adensity, double wdensity,double wAOA,
                        double aAOA);
    const glm::vec2& getForce() const;
    private:
        glm::vec2 position{0.0f, 0.0f}; // coordinates on the boat
        glm::vec2 force{0.0f, 0.0f}; // coordinates on the boat
        //TODO: add the coefficients here
        double AWaterLine = 2.0; // m^2

};
#endif // KEEL_H