#include "rudder.h"
#include <algorithm>
#include <iostream>
Rudder::Rudder(glm::vec2 position) : position(position) {}

//TODO: revoir tt les calculs d'angle

glm::vec2 Rudder::computeWForce(const glm::vec2& relativeVelocity, double angleOfAttack, double density) const {
    //TODO: must add yawrate so we can get other components of the velocity
    double speed = std::sqrt(relativeVelocity.x * relativeVelocity.x + relativeVelocity.y * relativeVelocity.y);
    //TODO: must be more precise
    // simplified assumption

    int sign = (relativeVelocity.x > 0) ? 1 : -1;

    auto AOT =  rudderAngle -angleOfAttack ;


    // Simplified coefficients (replace with better models as needed)
    double CL = 0.5 * std::sin(2 * rudderAngle);
    double CD = 0.1 + 0.5 * std::sin(rudderAngle) * std::sin(rudderAngle);
   

    double lift = 0.5 * density * speed * speed * Area * CL;
    double dragForce = 0.5 * density * speed * speed * Area * CD* sign;

    

   
    auto drag =  glm::vec2(-dragForce, lift);

    //rotate the force to the boat frame

    float cosYaw = std::cos(angleOfAttack);
    float sinYaw = std::sin(angleOfAttack);



    auto vec = glm::vec2(drag.x * cosYaw - drag.y * sinYaw, drag.x * sinYaw + drag.y * cosYaw);
    //std::cout << "rudder force: " << vec.x << " " << vec.y << std::endl;
    return  vec;
}


glm::vec2 Rudder::getCEOtoCOMB() {


    //get rudder rotation matrix

    float cosYaw = std::cos(rudderAngle);
    float sinYaw = std::sin(rudderAngle);

    // Transform the body-fixed velocity to world coordinates
    glm::vec2 rudderToBack(
        CEOtoBack.x * cosYaw - CEOtoBack.y * sinYaw,
        CEOtoBack.x * sinYaw + CEOtoBack.y * cosYaw
    );

    return rudderToBack + position;


}

glm::vec2 Rudder::computeAForce(const glm::vec2& relativeVelocity, double angleOfAttack, double density) const {
return glm::vec2(0.0f, 0.0f);    
}

const glm::vec2& Rudder::getPosition() const {
    return position;
}
double Rudder::getRudderAngle() const{
    return rudderAngle;
}
void Rudder::setRudderAngle(double angle){
    rudderAngle = angle;
}
void Rudder::incrementRudderAngle(double delta){
    rudderAngle += delta;
    rudderAngle = std::clamp(rudderAngle, 2.0944,2*2.0944); // Clamp between -60 and 60 degrees
}
void Rudder::decrementRudderAngle(double delta){
    rudderAngle -= delta;
    rudderAngle = std::clamp(rudderAngle, 2.0944,2*2.0944); // Clamp between -60 and 60 degrees
}
void Rudder::computeForce(
    const glm::vec2& wrelativeVelocity,
    const glm::vec2& arelativeVelocity, 
    double adensity, 
    double wdensity,
    double wAOA,
    double aAOA)  {
        this->force = computeWForce(wrelativeVelocity, wAOA, wdensity);
}
    
    const glm::vec2& Rudder
::getForce() const {
        return force;
    }

void Rudder::draw(sf::RenderWindow& window,sf::Transform boatTransform,sf::Vector2f origin_point) {
    
     // Create a rectangle shape representing the rudder
    sf::RectangleShape rudder(sf::Vector2f(20, 5));

    // Set the origin of the rudder to the top left of the rectangle
    rudder.setOrigin(0, rudder.getSize().y/2); 

    // Position the rudder relative to the provided origin_point
    // This positions the top-middle of the rudder at origin_point.
    

    rudder.setPosition(origin_point + sf::Vector2f(position.x, position.y)*25.0f);

    // Optionally set rotation or other properties based on rudder's angle if needed
    rudder.setRotation(glm::degrees(rudderAngle));  // if you want to rotate the rudder relative to boat's heading

    // Set a fill color for the rudder for visibility (customize as needed)
    rudder.setFillColor(sf::Color::Red);

    // Draw the rudder using the boat's transform
    window.draw(rudder, boatTransform);


}

