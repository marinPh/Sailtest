#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <GL/glu.h>   
#include <vector>
#include <cmath>
#include <iostream>

const float PI = 3.14159265f;

int main() {
    // Create the SFML window with an OpenGL context
    sf::Window window(sf::VideoMode(800, 600), "3D Globe with SFML & OpenGL",
                      sf::Style::Default, sf::ContextSettings(24));
    window.setVerticalSyncEnabled(true);

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glClearDepth(1.f);
    glClearColor(0.f, 0.f, 0.f, 1.f);

    // Setup sphere data
    float radius = 1.0f;
    const unsigned int slices = 40;
    const unsigned int stacks = 40;
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;

    for (unsigned int stack = 0; stack <= stacks; ++stack) {
        float phi = PI * float(stack) / stacks;  // [0, PI]
        for (unsigned int slice = 0; slice <= slices; ++slice) {
            float theta = 2.0f * PI * float(slice) / slices; // [0, 2PI]

            // Spherical to Cartesian conversion
            float x = radius * sin(phi) * cos(theta);
            float y = radius * cos(phi);
            float z = radius * sin(phi) * sin(theta);

            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);
        }
    }

    for (unsigned int stack = 0; stack < stacks; ++stack) {
        for (unsigned int slice = 0; slice < slices; ++slice) {
            int first = (stack * (slices + 1)) + slice;
            int second = first + slices + 1;

            // Create two triangles for each quad on the sphere surface
            indices.push_back(first);
            indices.push_back(second);
            indices.push_back(first + 1);

            indices.push_back(second);
            indices.push_back(second + 1);
            indices.push_back(first + 1);
        }
    }

    // Setup projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat aspect = 800.f / 600.f;
    gluPerspective(45.f, aspect, 0.1f, 100.f);

    float rotationAngle = 0.f;
    bool rotating = false;

    // Define a fixed latitude and longitude for the point (in radians)
    float lat = 45 * (PI / 180.f);  // 45 degrees latitude
    float lon = 90 * (PI / 180.f);  // 90 degrees longitude

    // Convert the latitude/longitude to 3D coordinates on the sphere
    float pointX = radius * cos(lat) * cos(lon);
    float pointY = radius * sin(lat);
    float pointZ = radius * cos(lat) * sin(lon);

    // Main loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::R) {
                    rotating = true; // Start rotating when R key is pressed
                }
            }
        }

        // Update rotation if active
        if(rotating) rotationAngle += 0.5f; // degrees per frame

        // Clear color and depth buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Setup model-view matrix
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(0, 0, 4,   // Camera position
                  0, 0, 0,   // Look at origin
                  0, 1, 0);  // Up vector

        // Apply rotation to the globe
        glRotatef(rotationAngle, 0.f, 1.f, 0.f);

        // Draw the sphere
        glColor3f(0.2f, 0.6f, 0.8f);  // Sphere color
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, vertices.data());
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data());
        glDisableClientState(GL_VERTEX_ARRAY);

        // Draw a small marker at the specified point on the globe
        glPushMatrix();
            glColor3f(1.f, 0.f, 0.f);  // Marker color (red)
            glTranslatef(pointX, pointY, pointZ);
            // Draw a small cube as the marker
            float size = 0.02f;
            glBegin(GL_QUADS);
                // Front face
                glVertex3f(-size, -size,  size);
                glVertex3f( size, -size,  size);
                glVertex3f( size,  size,  size);
                glVertex3f(-size,  size,  size);
                // Back face
                glVertex3f(-size, -size, -size);
                glVertex3f( size, -size, -size);
                glVertex3f( size,  size, -size);
                glVertex3f(-size,  size, -size);
                // Left face
                glVertex3f(-size, -size, -size);
                glVertex3f(-size, -size,  size);
                glVertex3f(-size,  size,  size);
                glVertex3f(-size,  size, -size);
                // Right face
                glVertex3f( size, -size, -size);
                glVertex3f( size, -size,  size);
                glVertex3f( size,  size,  size);
                glVertex3f( size,  size, -size);
                // Top face
                glVertex3f(-size,  size, -size);
                glVertex3f( size,  size, -size);
                glVertex3f( size,  size,  size);
                glVertex3f(-size,  size,  size);
                // Bottom face
                glVertex3f(-size, -size, -size);
                glVertex3f( size, -size, -size);
                glVertex3f( size, -size,  size);
                glVertex3f(-size, -size,  size);
            glEnd();
        glPopMatrix();

        // Finally display the rendered frame on screen
        window.display();
    }

    return 0;
}
