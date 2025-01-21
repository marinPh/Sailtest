#include <SFML/Graphics.hpp>
#include <cmath> // For std::floor
#include <iostream>

#include "boat.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

sf::Vector2f rotateVector(const sf::Vector2f& v, float degrees) {
    float radians = (degrees-90) * 3.14159265f / 180.f;
    float cosA = std::cos(radians);
    float sinA = std::sin(radians);
    return sf::Vector2f(v.x * cosA - v.y * sinA,
                        v.x * sinA + v.y * cosA);
}


void drawVector(sf::RenderWindow& window, const sf::Vector2f& start, const sf::Vector2f& end, const sf::Color& color) {
    sf::Vertex line[] = {
        sf::Vertex(start, color),
        sf::Vertex(end, color)
    };
    window.draw(line, 2, sf::Lines);
}

sf::Text metaData(sf::Font& font, std::string str, float x, float y) {
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(22);           // Adjust size as needed
    text.setFillColor(sf::Color::Green); // Text color
    text.setPosition(x, y);              // Slight offset from top-left corner
    text.setString(str);
    return text;
}
//both vectors are in boat frame
void drawSail(sf::RenderWindow& window, const sf::Vector2f& mast, const sf::Vector2f& end, const sf::Color& color, Boat& boatO,sf::Vector2f& position) {

    //must convert to world frame


    sf::Vector2f worldMast = rotateVector(mast, boatO.getDirection()) + position;
    sf::Vector2f worldEnd = rotateVector(end, boatO.getDirection()) + position;
    //std::cout << "world mast: " << position.x << " " << position.y << std::endl;
    sf::Vertex line[] = {
        sf::Vertex(worldMast, color),
        sf::Vertex(worldEnd, color)
    };
    window.draw(line, 100, sf::Lines);
}



void wasd(Boat& boatO, sf::Time dt) {
     if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            boatO.rudderIncrement(dt.asSeconds());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            boatO.rudderDecrement(dt.asSeconds());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            boatO.motorIncrement(dt.asSeconds());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            boatO.motorDecrement(dt.asSeconds());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            sf::sleep(sf::milliseconds(100000));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        {
           boatO.sailIncrement(dt.asSeconds());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        {
            boatO.sailDecrement(dt.asSeconds());
        }
}

int main()
{
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;

    
    // Create the SFML window
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Moving Boat");

    // Set up a view that we'll center on the moving boat
    sf::View view(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));

    // Load the boat texture
    sf::Texture boatTexture;
    if (!boatTexture.loadFromFile("../assets/boat.png"))
    {
        std::cerr << "Failed to load boat texture!\n";
        return -1;
    }

    // Create two sprites using the same texture
    sf::Sprite boatS(boatTexture);
    boatS.setScale(0.5f, 0.5f);
    boatS.setOrigin(boatS.getLocalBounds().width / 2, boatS.getLocalBounds().height / 2);
    Boat boatO = Boat(boatS,glm::vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));

    // Set initial positions
    //boat1.setPosition(window.getSize().x / 2, window.getSize().y / 2);
    //
    //
    //boat1.scale(0.1f, 0.1f);
    //boat1.setRotation(90.f);


    float boatSpeedX = 0.f;         // Speed of boat1 on the x-axis
    const float circleRadius = 5.f; // Radius of the background circles
    const float spacing = 50.f;     // Spacing between circles in the grid

    sf::Clock clock;
    float rotationSpeed = 90.f; // degrees per second
    sf::Font font;
    if (!font.loadFromFile("../assets/spline-sans-mono/SplineSansMono[wght].ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
        return -1;
    }


    float barWidth = 200.f;
    float barHeight = 20.f;
    float margin = 10.f; // distance from edges




auto worldWind = glm::vec2(0.0f, 3.0f);
    // Main loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        sf::Time dt = clock.restart();

        boatO.update(dt.asSeconds(),worldWind);

        auto vec = boatO.GetWVec();

        wasd(boatO, dt);
        auto revVel = boatO.GetVec();

        auto AoT = std::atan2(revVel.y, revVel.x);
       

        auto F_r = boatO.computeRudderForce(AoT);
        auto F_keel = boatO.computeKeelForce(AoT);
        auto speedText = metaData(font, "Speed: " + std::to_string(std::sqrt(vec.x * vec.x + vec.y * vec.y)), 5.f, 5.f);
        auto frc = metaData(font, "forces: " + std::to_string(boatO.computeTotalForce().x) + " " + std::to_string(boatO.computeTotalForce().y), 5.f, 50.f);
        auto diry = metaData(font, "Direction: " + std::to_string(boatO.getDirection()), 5.f, 100.f);
        auto vel = metaData(font, "vel: " + std::to_string(boatO.velocity.x) + "," + std::to_string(boatO.velocity.y), 5.f, 150.f);
        auto moment = metaData(font, "moment = "+ std::to_string(F_r.y)+" * "+std::to_string(boatO.distanceRudderToCG)+" + "+std::to_string(F_keel.y) +"*"+std::to_string(boatO.distanceRudderToCG) + "=" + std::to_string(boatO.momentZ) , 5.f, 250.f);
        auto angularVec = metaData(font,"angularAcce = " + std::to_string((boatO.yawRate)) , 5.f, 300.f);
        auto velw = metaData(font, "worldvel: " + std::to_string(boatO.GetWVec().x) + "," + std::to_string(boatO.GetWVec().y), 5.f, 200.f);
       
        // Update boat1's position along the x-axis
        //boat1.move(vec.x, vec.y);
        //boat1.setRotation(boatO.getDirection()+90);
        // Center the view on boat1
        view.setCenter(boatO.getPosition());
        window.setView(view);

        // Clear the window with a white background
        window.clear(sf::Color::White);

        // Prepare a circle shape for the dotted background
        sf::CircleShape circle(circleRadius);
        circle.setFillColor(sf::Color(211, 211, 211)); // Light grey color
        // Determine the bounds of the current view
        sf::Vector2f viewCenter = view.getCenter();
        sf::Vector2f viewSize = view.getSize();
        float left = viewCenter.x - viewSize.x / 2;
        float right = viewCenter.x + viewSize.x / 2;
        float top = viewCenter.y - viewSize.y / 2;
        float bottom = viewCenter.y + viewSize.y / 2;

        // Calculate starting positions on the grid that cover the view
        float startX = std::floor(left / spacing) * spacing;
        float startY = std::floor(top / spacing) * spacing;

        // Draw the dotted background grid within the view's bounds
        for (float x = startX; x < right; x += spacing)
        {
            for (float y = startY; y < bottom; y += spacing)
            {
                circle.setPosition(x - circleRadius, y - circleRadius);
                window.draw(circle);
            }
        }

        // Get boat's global position and rotation (yaw)
        sf::Vector2f boatPos = boatO.getPosition();
        float yaw = boatO.getDirection() + 90;  // Assuming sprite rotation matches boat's yaw
        
        // Local offset from center to back (assuming boat image points upward and back is downward)
        //sf::Vector2f localBackOffset(0.f, boat1.getLocalBounds().height / 2.f);
        
        // Rotate local back offset by boat's yaw to get world-space offset
        //sf::Vector2f rotatedBackOffset = rotateVector(localBackOffset, yaw);
        
        // Compute starting position at the back of the icon
        //sf::Vector2f backStartPos = boatPos + rotatedBackOffset;
        double rudderAngle = boatO.getRudderPosition(); // in  radians
        glm::vec2 vecA  = boatO.computeSailForce();
        
        glm::vec2 vecB = glm::vec2(glm::cos(rudderAngle), glm::sin(rudderAngle))*50.0f;
        //glm::vec2 vecB = boatO.computeRudderForce(AoT);

        sf::Vector2f vecF = sf::Vector2f(boatO.getSailEnd().x*100, boatO.getSailEnd().y*100);
        sf::Vector2f vecS = sf::Vector2f(boatO.GetVec().x, boatO.GetVec().y);
        sf::Vector2f wind = sf::Vector2f(worldWind.x, worldWind.y);

        sf::Vector2f rotatedVecA = rotateVector(sf::Vector2f(vecA.x, vecA.y), yaw);
        sf::Vector2f rotatedVecB = rotateVector(sf::Vector2f(vecB.x, vecB.y), yaw);
        sf::Vector2f rotatedVecF = rotateVector(sf::Vector2f(vecF.x, vecF.y), yaw);
        sf::Vector2f rotatedVecS = rotateVector(sf::Vector2f(boatO.GetWVec().x, boatO.GetWVec().y), yaw);
        //sf::Vector2f rotatedVecA = sf::Vector2f(vecA.x, vecA.y);
        //sf::Vector2f rotatedVecB = sf::Vector2f(vecB.x, vecB.y);
        //sf::Vector2f rotatedVecF = sf::Vector2f(boatO.motorForce, 0);
        //sf::Vector2f rotatedVecS = sf::Vector2f(boatO.GetVec().x, boatO.GetVec().y);

        sf::Vector2f startPosA = boatPos; 
        sf::Vector2f endPosA = startPosA + rotatedVecA;

        sf::Vector2f startPosB = boatPos;
        sf::Vector2f endPosB = startPosB + rotatedVecB*(10.0f);
        
        sf::Vector2f startPosF = boatPos;
        sf::Vector2f endPosF = startPosF + rotatedVecF;
        //std :: cout << "startposF: " << boatO.getSailAngle()<< std::endl;

        sf::Vector2f startPosS = boatPos;
        sf::Vector2f endPosS = startPosS + rotatedVecS;

        sf::Vector2f startPosWind = boatPos;
        sf::Vector2f endPosWind = startPosWind + wind* 10.0f;

        // Draw the vectors
        drawVector(window, startPosA, endPosA, sf::Color::Red);
        drawVector(window, startPosB, endPosB, sf::Color::Blue);
        drawVector(window, startPosF, endPosF, sf::Color::Green);
        drawVector(window, startPosS, endPosS, sf::Color::Black);
        drawVector(window, startPosWind, endPosWind, sf::Color::Magenta);
        //drawSail(window, sf::Vector2f(0.f, 0.f), sf::Vector2f(boatO.getSailEnd().x, boatO.getSailEnd().y), sf::Color::Green, boatO, boatPos);

        // Draw both boat sprites on top of the background
        //window.draw(boat1);
        boatO.draw(window);
        window.setView(window.getDefaultView());
        window.draw(speedText);
        window.draw(frc);
        window.draw(diry);
        window.draw(moment);
        window.draw(velw);
        window.draw(vel);
        window.draw(angularVec);
       //wa window.draw(dir);
        

        window.display();


        // Cap the frame rate to approx. 60 FPS
        sf::sleep(sf::milliseconds(16));
    }

    return 0;
}
