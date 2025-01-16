#include "boat.h"
#include <algorithm> // For std::clamp
// Compute a simplified rudder force based on rudder angle and boat speed.
glm::vec2 Boat::computeRudderForce() {
    double speed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
    //TODO: must be more precise
    double angleOfAttack = rudderAngle; // simplified assumption

    // Simplified coefficients (replace with better models as needed)
    double CL = 0.5 * std::sin(2 * angleOfAttack);
    double CD = 0.1 + 0.5 * std::sin(angleOfAttack) * std::sin(angleOfAttack);

    double lift = 0.5 * waterDensity * speed * speed * rudderArea * CL;
    double drag = 0.5 * waterDensity * speed * speed * rudderArea * CD;

    // For simplicity, assume drag acts along -x and lift along y-axis of boat frame.
    return glm::vec2(-drag, -lift);
}

void Boat::motorIncrement(double dt) {
    motorForce += 100.0 * dt;
}

void Boat::motorDecrement(double dt) {
    motorForce -= 100.0 * dt;
}

void Boat::rudderIncrement(double dt) {
    rudderAngle += 1.0 * dt;
    rudderAngle = std::clamp(rudderAngle, -1.2,1.2); // Clamp between -60 and 60 degrees
}

void Boat::rudderDecrement(double dt) {
    rudderAngle -= 1.0 * dt;
    rudderAngle = std::clamp(rudderAngle, -1.2,1.2); // Clamp between -60 and 60 degrees
}

double Boat::getDirection() {
    

    return glm::degrees(yaw) ;
}

glm::vec2 Boat::GetVec() {
    float cosYaw = std::cos(yaw);
    float sinYaw = std::sin(yaw);

    // Transform the body-fixed velocity to world coordinates
    glm::vec2 worldVelocity(
        velocity.x * cosYaw - velocity.y * sinYaw,
        velocity.x * sinYaw + velocity.y * cosYaw
    );

    return velocity;
}

glm::vec2 Boat::GetWVec() {
    float cosYaw = std::cos(yaw);
    float sinYaw = std::sin(yaw);

    // Transform the body-fixed velocity to world coordinates
    glm::vec2 worldVelocity(
        velocity.x * cosYaw - velocity.y * sinYaw,
        velocity.x * sinYaw + velocity.y * cosYaw
    );

    return worldVelocity;
}

double Boat:: getRudderPosition() {
        return rudderAngle;
    }



// Compute a simplified keel force
glm::vec2 Boat::computeKeelForce() {
    // Step 1: Compute speed and relative flow in body frame
    // Assuming velocity is already in boat’s body frame (surge, sway)
    double u = velocity.x;  // Surge component along boat's axis
    double v = velocity.y;  // Sway component perpendicular to boat's axis
    double speed = std::sqrt(u*u + v*v);

    // Step 2: Calculate angle of attack at the keel
    double angleOfAttack = std::atan2(v, u); // relative to boat's forward axis

    // Step 3: Compute lift and drag using the angle of attack
    double CL = 0.5 * std::sin(2 * angleOfAttack); // placeholder formula
    double CD = 0.1 + 0.5 * std::sin(angleOfAttack) * std::sin(angleOfAttack); // placeholder

    double lift = 0.5 * waterDensity * speed * speed * keelArea * CL;
    double drag = 0.5 * waterDensity * speed * speed * keelArea * CD;

    // Assuming:
    // - drag acts opposite to flow (along negative surge axis),
    // - lift acts perpendicular to flow (lateral force).
    // Convert these forces back into boat’s frame if necessary.
    // Here we assume simplified directions:
    return glm::vec2(-drag, -lift);
}


// Compute a simplified hull force (e.g., drag opposing forward motion)
glm::vec2 Boat::computeHullForce() {
    double speed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
    // Assume hull drag acts opposite to velocity vector
    double hullDragCoefficient = 0.5;
    glm::vec2 dragForce = static_cast<float>(-hullDragCoefficient * 0.5 * waterDensity * speed )* velocity;
    return dragForce;
}



// Update boat state over time step dt
void Boat::update(double dt) {
    // Compute forces
    glm::vec2 F_rudder = computeRudderForce();
    glm::vec2 F_keel = computeKeelForce();
    glm::vec2 F_hull = computeHullForce();

    // Sum forces in boat frame
    glm::vec2 totalForce = F_rudder + F_keel + F_hull + glm::vec2(motorForce, 0.0);

    // Compute linear acceleration in boat frame
    glm::vec2 acceleration = totalForce / static_cast<float>(mass);

    // Update linear velocity using Euler integration
    velocity += acceleration * static_cast<float>(dt);

    
    // Compute yaw moment contributions from rudder and keel
    momentZ = F_rudder.y * distanceRudderToCG + F_keel.y * distanceKeelToCG;

    // Introduce yaw damping
    double yawDampingCoefficient =300.0;
    double dampingMoment = -yawDampingCoefficient * yawRate;

    // Total yaw moment including damping
    double momentZ_total = momentZ + dampingMoment;

    // Compute angular acceleration considering damping
    double angularAcc = momentZ_total / inertiaZ;

    


    // Update yaw rate and yaw angle with damping included
    yawRate += angularAcc * dt;
    yaw += yawRate * dt;


    // Update position: transform velocity from body to world coordinates based on yaw
    float cosYaw = std::cos(yaw);
    float sinYaw = std::sin(yaw);
    glm::vec2 worldVelocity(
            velocity.x * cosYaw - velocity.y * sinYaw,
            velocity.x * sinYaw + velocity.y * cosYaw
    );
    position += worldVelocity * static_cast<float>(dt);
}
