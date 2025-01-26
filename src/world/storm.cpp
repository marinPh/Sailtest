#include "storm.h"

Storm::Storm(float size, glm::vec2 center, glm::vec2 direction) : size(size), center(center), direction(direction)
{
}

float Storm::getSize()
{
    return size;
}

glm::vec2 Storm::getCenter()
{
    return center;
}

glm::vec2 Storm::getDirection()
{
    return direction;
}

void Storm::update(float dt)
{
    center += direction * dt;
}

