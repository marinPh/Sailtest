#include "boat.h"
#include "world.h"
#include <SFML/Graphics.hpp>
#include <cmath> // For std::floor
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

sf::Vector2f rotateVector(const sf::Vector2f &v, float degrees)
{
    float radians = (degrees - 90) * 3.14159265f / 180.f;
    float cosA = std::cos(radians);
    float sinA = std::sin(radians);
    return sf::Vector2f(v.x * cosA - v.y * sinA, v.x * sinA + v.y * cosA);
}

void drawVector(sf::RenderWindow &window, const sf::Vector2f &start, const sf::Vector2f &end, const sf::Color &color)
{
    sf::Vertex line[] = {sf::Vertex(start, color), sf::Vertex(end, color)};
    window.draw(line, 2, sf::Lines);
}

sf::Text metaData(sf::Font &font, std::string str, float x, float y)
{
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(22);           // Adjust size as needed
    text.setFillColor(sf::Color::Green); // Text color
    text.setPosition(x, y);              // Slight offset from top-left corner
    text.setString(str);
    return text;
}

int main()
{

    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;

    // Create the SFML window
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),
                            "Moving Boat",
                            sf::Style::Default,
                            sf::ContextSettings(24));
auto find = window.getSize();
    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(60);
std ::cout << "size: " << find.x << " " << find.y << std::endl;
    // Load the boat texture
    sf::Texture boatTexture;
    if (!boatTexture.loadFromFile("../assets/boat.png"))
    {
        std::cerr << "Failed to load boat texture!\n";
        return -1;
    }


    // Create the boat sprite and set its origin to the center
    sf::Sprite boatS(boatTexture);
    boatS.setScale(0.5f, 0.5f);
    boatS.setOrigin(boatS.getLocalBounds().width / 2, boatS.getLocalBounds().height / 2);
    World world(boatS, window);

    sf::Clock clock;
    bool isPlanarView = true;
    sf::Time dt = clock.restart();

    // Main loop
    while (window.isOpen())
    {
        sf::Event event;


        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else
            {
                world.handleEvents(event, dt.asSeconds());
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::P)
                {
                    isPlanarView = !isPlanarView;
                    if (isPlanarView)
                    {
                        world.setPlanarView(); // Center on (0, 0) for example
                    }
                    else
                    {
                        world.setSphericalView();
                    }
                }
            }
        }
        dt = clock.restart();
        world.update(dt.asSeconds());

        // Clear the window with a white background
        window.clear(sf::Color::White);
        sf::sleep(sf::milliseconds(16));
        // Draw the world
        world.draw(window);

        // Display the window contents
        window.display();

        // Cap the frame rate to approx. 60 FPS
    }

    return 0;
}