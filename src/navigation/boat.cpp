#include "boat.h"
#include <algorithm> // For std::clamp
#include <execution>
#include <future>
#include <iostream>
#include <pstl/glue_numeric_defs.h>
#include <vector>
#include "sail.h"
// Compute a simplified rudder force based on rudder angle and boat speed.

Boat::Boat() : rudder(glm::vec2(-2.0f, 0.0f)), keel(glm::vec2(2.0f, 0.0f)), hull(), sail(glm::vec2(0.0f, 0.0f))
{
    surfaces.push_back(&rudder);
    surfaces.push_back(&keel);
    surfaces.push_back(&hull);
    //surfaces.push_back(&sail);
}

glm::vec2 rotateVector(const glm::vec2 &v, float yaw)
{
    float cosA = std::cos(yaw);
    float sinA = std::sin(yaw);
    return glm::vec2(v.x * cosA - v.y * sinA, v.x * sinA + v.y * cosA);
}

glm::vec2 Boat::getSailEnd(){
    //get length of sail then rotate it by the sail angle
    auto base =sail.getBase();
    auto angle = sail.getAngle();

    return glm::vec2(base * std::cos(angle), base * std::sin(angle));
}

double Boat::getSailAngle() const {
    return sail.getAngle();
}

void Boat::setRudderAngle(double angle)
{
    rudder.setRudderAngle(angle);
}


glm::vec2 Boat::computeRudderForce(double angleOfAttack)
{
    // Compute the force produced by the rudder
    glm::vec2 F_rudder = surfaces[0]->computeWForce(velocity, angleOfAttack, waterDensity);
    return F_rudder;
}

void Boat::motorIncrement(double dt)
{
    motorForce += 100.0 * dt;
}

void Boat::motorDecrement(double dt)
{
    motorForce -= 100.0 * dt;
}

void Boat::rudderIncrement(double dt)
{
    rudder.incrementRudderAngle(dt);
}

void Boat::rudderDecrement(double dt)
{
    rudder.decrementRudderAngle(dt);
}

double Boat::getDirection()
{
    return glm::degrees(yaw);
}

glm::vec2 Boat::GetVec()
{
    return velocity;
}

glm::vec2 Boat::GetWVec()
{
    float cosYaw = std::cos(yaw);
    float sinYaw = std::sin(yaw);

    // Transform the body-fixed velocity to world coordinates
    glm::vec2 worldVelocity(velocity.x * cosYaw - velocity.y * sinYaw, velocity.x * sinYaw + velocity.y * cosYaw);

    return worldVelocity;
}

double Boat::getRudderPosition()
{
    return rudder.getRudderAngle();
}

// Compute a simplified keel force
glm::vec2 Boat::computeKeelForce(double angleOfAttack)
{

    return keel.computeWForce(velocity, angleOfAttack, waterDensity);
}


// Compute a simplified hull force (e.g., drag opposing forward motion)
glm::vec2 Boat::computeHullForce()
{
    return hull.getForce();
}


void Boat::computeForces(const glm::vec2 &wrelativeVelocity,
                         double wdensity,
                         const glm::vec2 &arelativeVelocity,
                         double adensity)
{

    auto wAOA = std::atan2(wrelativeVelocity.y, wrelativeVelocity.x);
    auto aAOA = std::atan2(arelativeVelocity.y, arelativeVelocity.x);

    std::vector<std::future<void>> futures;

    for (const auto &obj : surfaces)
    {
        // Launch computation asynchronously
        futures.push_back(
            std::async(std::launch::async,
                       [obj, &wrelativeVelocity, wdensity, &arelativeVelocity, adensity, wAOA, aAOA] {
                           obj->computeForce(wrelativeVelocity, arelativeVelocity, adensity, wdensity, wAOA, aAOA);
                       }));
    }
    // Wait for all computations to complete
    for (auto &f : futures)
    {
        f.get();
    }
}


glm::vec2 Boat::computeTotalForce()
{
    glm::vec2 totalForce{0.0f, 0.0f};
    for (const auto &obj : surfaces)
    {
        totalForce += obj->getForce();
    }
    return totalForce;
}


float crossProduct(const glm::vec2 &a, const glm::vec2 &b)
{
    return a.x * b.y - a.y * b.x;
}
double Boat::computeMomentz()
{
    double totalForce = 0.0;
    for (const auto &obj : surfaces)
    {
        totalForce += crossProduct(obj->getCEOtoCOMB(), obj->getForce());
    }
    return totalForce;
}
// Update boat state over time step dt
void Boat::update(double dt)
{
    // Compute forces


    //FIXME: magic wind

    auto worldWind = glm::vec2(0.0f, 5.0f);

    auto relativeWind = rotateVector(worldWind, yaw);

    //std::cout << "relative wind: " << (velocity).x << " " << (velocity).y << std::endl;
    computeForces(velocity, waterDensity, velocity + relativeWind, airDensity);

    double angleOfAttack = std::atan2(velocity.y, velocity.x); // relative to boat's forward axis
    glm::vec2 totalForce = computeTotalForce() + glm::vec2(motorForce, 0.0);

    // Compute linear acceleration in boat frame
    glm::vec2 acceleration = totalForce / static_cast<float>(mass);

    // Update linear velocity using Euler integration
    velocity += acceleration * static_cast<float>(dt);


    // Compute yaw moment contributions from rudder and keel
    momentZ = computeMomentz();

    // Introduce yaw damping
    double yawDampingCoefficient = 200.0;
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
    glm::vec2 worldVelocity(velocity.x * cosYaw - velocity.y * sinYaw, velocity.x * sinYaw + velocity.y * cosYaw);
    position += worldVelocity * static_cast<float>(dt);
}

void Boat::sailIncrement(double dt)
{
    sail.incrementAngle(dt);
}

void Boat::sailDecrement(double dt)
{
    sail.decrementAngle(dt);
}
