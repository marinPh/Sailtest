#include "boat.h"

Boat::Boat(int length, int width, int height, int weight) {
    this->length = length;
    this->width = width;
    this->height = height;
    this->weight = weight;
    this->speed = 0;
    this->direction = 90;
}

void Boat::steerRight() {
    this->direction = (direction + 1) % 360;
}

void Boat::steerLeft() {
    this->direction= (direction - 1) % 360;
}

void Boat::goForward() {
    this->speed = this->speed+ 0.10f;
}

glm::vec2 Boat::getSpeedVec() {
    auto radDir = glm::radians(static_cast<float>(direction-90));  // Convert to float
    return glm::vec2(speed * cos(radDir), speed * sin(radDir));
}

int Boat::getDirection() {
    return direction;
}

