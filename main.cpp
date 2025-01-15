#include <SFML/Graphics.hpp>
#include <cmath>       // For std::floor
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "boat.h"


int main() {
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;

    Boat boatO = Boat(10, 5, 3, 1000);

    

    // Create the SFML window
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Moving Boat");
    
    // Set up a view that we'll center on the moving boat
    sf::View view(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));

    // Load the boat texture
    sf::Texture boatTexture;
    if (!boatTexture.loadFromFile("../assets/boat.png")) {
        std::cerr << "Failed to load boat texture!\n";
        return -1;
    }

    // Create two sprites using the same texture
    sf::Sprite boat1(boatTexture);

    // Set initial positions
    boat1.setPosition(window.getSize().x / 2, window.getSize().y / 2);
    boat1.setScale(0.5f, 0.5f);
    boat1.setOrigin(boat1.getLocalBounds().width / 2, boat1.getLocalBounds().height / 2);
    boat1.scale(0.1f, 0.1f);
    boat1.setRotation(90.f);

    

    

    float boatSpeedX = 0.f;             // Speed of boat1 on the x-axis
    const float circleRadius = 5.f;     // Radius of the background circles
    const float spacing = 50.f;         // Spacing between circles in the grid

    sf::Clock clock;
    float rotationSpeed = 90.f;  // degrees per second
    sf::Font font;
if (!font.loadFromFile("../assets/spline-sans-mono/SplineSansMono[wght].ttf")) {
    std::cerr << "Failed to load font!" << std::endl;
    return -1;
}


    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        

        sf::Time dt = clock.restart();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            boatO.steerLeft();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            boatO.steerRight();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            boatO.goForward();
        }
      
        auto vec =  boatO.getSpeedVec();

        sf::Text speedText;
        speedText.setFont(font);
        speedText.setCharacterSize(22); // Adjust size as needed
        speedText.setFillColor(sf::Color::Green); // Text color
        speedText.setPosition(5.f, 5.f); // Slight offset from top-left corner
        
        std::string speedStr = "Speed: (" + std::to_string(vec.x) + ", " + std::to_string(vec.y) + ")";
        speedText.setString(speedStr);

        // Update boat1's position along the x-axis
        boat1.move(vec.x, vec.y);
        boat1.setRotation(boatO.getDirection());


        // Center the view on boat1
        view.setCenter(boat1.getPosition());
        window.setView(view);

        // Clear the window with a white background
        window.clear(sf::Color::White);

        // Prepare a circle shape for the dotted background
        sf::CircleShape circle(circleRadius);
        circle.setFillColor(sf::Color(211, 211, 211));  // Light grey color

        // Determine the bounds of the current view
        sf::Vector2f viewCenter = view.getCenter();
        sf::Vector2f viewSize = view.getSize();
        float left   = viewCenter.x - viewSize.x / 2;
        float right  = viewCenter.x + viewSize.x / 2;
        float top    = viewCenter.y - viewSize.y / 2;
        float bottom = viewCenter.y + viewSize.y / 2;

        // Calculate starting positions on the grid that cover the view
        float startX = std::floor(left / spacing) * spacing;
        float startY = std::floor(top / spacing) * spacing;

        // Draw the dotted background grid within the view's bounds
        for (float x = startX; x < right; x += spacing) {
            for (float y = startY; y < bottom; y += spacing) {
                circle.setPosition(x - circleRadius, y - circleRadius);
                window.draw(circle);
            }
        }

        // Draw both boat sprites on top of the background
        window.draw(boat1);
        window.setView(window.getDefaultView());
window.draw(speedText);
window.display();
      


        // Cap the frame rate to approx. 60 FPS
        sf::sleep(sf::milliseconds(16));
    }

    return 0;
}
