#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class HydrodynamicSurface {
public:
    virtual ~HydrodynamicSurface() {}

    // Compute force based on relative velocity and angle of attack.
    virtual Vector2 computeForce(const Vector2 &relativeVelocity, double angleOfAttack) = 0;

    virtual double computeMoment(const Vector2 &relativeVelocity, double angleOfAttack, double momentArm) = 0;
};