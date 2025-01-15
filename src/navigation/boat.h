#ifndef BOAT_H
#define BOAT_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Boat {
    public:
        Boat(int length, int width, int height, int weight);
        void steerRight();
        void steerLeft();
        void goForward();
        int getDirection();
        glm::vec2 getSpeedVec();
    private:
        int length; // Length of the boat in m
        int width; // Width of the boat in m
        int height; // Height of the boat in m
        float weight; // Weight of the boat in kg
        float speed; // Speed of the boat in m/s
        int direction; // Direction of the boat in degrees
    
};
#endif // BOAT_H