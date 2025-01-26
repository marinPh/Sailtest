
#ifndef STORM_H
#define STORM_H

#include <glm/vec2.hpp>

class Storm
{
    public:
    Storm(float size, glm::vec2 center, glm::vec2 direction);
    float getSize();
    glm::vec2 getCenter();
    glm::vec2 getDirection(); // storm direction as a speed vector
    void update(float dt);
    private:
    float size;
    glm::vec2 center;
    glm::vec2 direction;

};

#endif // STORM_H