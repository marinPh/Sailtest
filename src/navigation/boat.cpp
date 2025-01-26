#include "boat.h"
#include "sail.h"
#include <algorithm> // For std::clamp
#include <execution>
#include <future>
#include <iostream>
#include <pstl/glue_numeric_defs.h>
#include <vector>
// Compute a simplified rudder force based on rudder angle and boat speed.

Boat::Boat(sf::Sprite &sprite, glm::vec2 startingPos)
    : rudder(glm::vec2(-2.0f, 0.0f)), keel(glm::vec2(2.0f, 0.0f)), hull(), sail(glm::vec2(0.0f, 0.0f)), sprite(sprite),
      position(startingPos)
{
    // Initialize boat surfaces
    sprite.setPosition(startingPos.x, startingPos.y);
    sprite.setOrigin(startingPos.x, startingPos.y);

    //surfaces.push_back(&rudder);
    //surfaces.push_back(&keel);
    //surfaces.push_back(&hull);
    //surfaces.push_back(&sail);
}

sf::Vector2f Boat::getPosition()
{
    return sf::Vector2f(position.x, position.y);
}


glm::vec2 rotateVector(const glm::vec2 &v, float yaw)
{
    float cosA = std::cos(yaw);
    float sinA = std::sin(yaw);
    return glm::vec2(v.x * cosA - v.y * sinA, v.x * sinA + v.y * cosA);
}

glm::vec2 Boat::getSailEnd()
{
    //get length of sail then rotate it by the sail angle
    auto base = sail.getBase();
    auto angle = sail.getAngle();

    return glm::vec2(base * std::cos(angle), base * std::sin(angle));
}

double Boat::getSailAngle() const
{
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

glm::vec2 Boat::computeSailForce()
{
    return sail.getForce();
}


void Boat::computeForces(const glm::vec2 &wrelativeVelocity,
                         double wdensity,
                         const glm::vec2 &arelativeVelocity,
                         double adensity)
{

    double wAOA = std::atan2(wrelativeVelocity.y, wrelativeVelocity.x);
    double aAOA = std::atan2(arelativeVelocity.y, arelativeVelocity.x);

    std ::cout << "AOA: " << glm::degrees(wAOA) << " " << glm::degrees(aAOA) << std::endl;


    //sail.computeForce(wrelativeVelocity, arelativeVelocity, adensity, wdensity, wAOA, aAOA);

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
void Boat::update(double dt, glm ::vec2 &worldWind)
{
    // Compute forces


    //FIXME: magic wind


    auto relativeWind = rotateVector(worldWind, -yaw);
    std::cout << "relative wind: " << relativeWind.x << " " << relativeWind.y << std::endl;


    //std :: cout << "relative wind: " << relativeWind.x << " " << relativeWind.y << std::endl;

    //std::cout << "relative wind: " << (velocity).x << " " << (velocity).y << std::endl;
    computeForces(velocity, waterDensity, velocity - relativeWind, airDensity);

    //double angleOfAttack = std::atan2(velocity.y, velocity.x); // relative to boat's forward axis
    glm::vec2 totalForce = computeTotalForce() + glm::vec2(motorForce, 0.0);

    // Compute linear acceleration in boat frame
    glm::vec2 acceleration = totalForce / static_cast<float>(mass);

    // Update linear velocity using Euler integration
    velocity += acceleration * static_cast<float>(dt);

    //velocity = glm::vec2(0.0f,0.0f);


    // Compute yaw moment contributions from rudder and keel
    momentZ = computeMomentz();
    //momentZ =0.0;

    // Introduce yaw damping
    double yawDampingCoefficient = 200.0;
    double dampingMoment = -yawDampingCoefficient * yawRate;

    // Total yaw moment including damping
    double momentZ_total = momentZ + dampingMoment;

    // Compute angular acceleration considering damping
    double angularAcc = momentZ_total / inertiaZ;

    // Update yaw rate and yaw angle with damping included
    yawRate += angularAcc * dt;
    //yaw is between -pi and pi
    yaw += yawRate * dt;
    yaw = std::fmod(yaw + M_PI, 2.0 * M_PI) - M_PI;

    // Update position: transform velocity from body to world coordinates based on yaw
    float cosYaw = std::cos(yaw);
    float sinYaw = std::sin(yaw);
    glm::vec2 worldVelocity(velocity.x * cosYaw - velocity.y * sinYaw, velocity.x * sinYaw + velocity.y * cosYaw);
    worldVelocity *= static_cast<float>(dt * 50);
    position += worldVelocity;
    ;
    sprite.move(worldVelocity.x, worldVelocity.y);
    std::cout << "position: " << position.x << " " << position.y << std::endl;
    std::cout << "sprite pos: " << sprite.getPosition().x << "  " << sprite.getPosition().y << std::endl;
}

void Boat::sailIncrement(double dt)
{
    sail.incrementAngle(dt);
}

void Boat::sailDecrement(double dt)
{
    sail.decrementAngle(dt);
}
void Boat::draw(sf::RenderWindow &window)
{
    // Ensure the sprite has a valid texture
    if (!sprite.getTexture()) {
        std::cerr << "Sprite has no texture assigned!" << std::endl;
        return; // Exit the function if the texture is invalid
    }

    // Set the sprite's rotation
    sprite.setRotation(getDirection());

    // Debug sprite properties
    sf::Vector2f position = sprite.getPosition();
    std::cout << "Sprite Position: (" << position.x << ", " << position.y << ")" << std::endl;

    sf::FloatRect spriteBounds = sprite.getGlobalBounds();
    std::cout << "Sprite Bounds: Left=" << spriteBounds.left
              << ", Top=" << spriteBounds.top
              << ", Width=" << spriteBounds.width
              << ", Height=" << spriteBounds.height << std::endl;

    sf::Vector2f scale = sprite.getScale();
    std::cout << "Sprite Scale: (" << scale.x << ", " << scale.y << ")" << std::endl;

    // Check if the sprite is within the view
    sf::View view = window.getView();
    sf::Vector2f viewCenter = view.getCenter();
    sf::Vector2f viewSize = view.getSize();
    sf::FloatRect viewBounds(viewCenter.x - viewSize.x / 2.f, viewCenter.y - viewSize.y / 2.f, viewSize.x, viewSize.y);

    if (!viewBounds.intersects(spriteBounds)) {
        std::cerr << "Sprite is outside the view!" << std::endl;
    }

    // Draw the sprite
    window.draw(sprite);

    // Draw surfaces if any
    sf::Transform sp = sprite.getTransform();
    sf::Vector2f origin_point(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    for (const auto &obj : surfaces) {
        if (!obj) {
            std::cerr << "Null object in surfaces!" << std::endl;
            continue;
        }
        obj->draw(window, sp, origin_point);
    }
}


void Boat::handleEvents(sf::Event &e, float dt)
{
    if (e.type == sf::Event::KeyPressed)
    {
        if (e.key.code == sf::Keyboard::Up)
        {
            motorIncrement(dt);
        }
        else if (e.key.code == sf::Keyboard::Down)
        {
            motorDecrement(dt);
        }
        else if (e.key.code == sf::Keyboard::Left)
        {
            rudderIncrement(dt);
        }
        else if (e.key.code == sf::Keyboard::Right)
        {
            rudderDecrement(dt);
        }
        else if (e.key.code == sf::Keyboard::W)
        {
            sailIncrement(dt);
        }
        else if (e.key.code == sf::Keyboard::S)
        {
            sailDecrement(dt);
        }
    }

}


    void Boat::addSurface(HydroSurface *surface)
    {
        surfaces.push_back(surface);
    }

    void Boat::removeSurface(HydroSurface *surface)
    {
        surfaces.erase(std::remove(surfaces.begin(), surfaces.end(), surface), surfaces.end());
    }
