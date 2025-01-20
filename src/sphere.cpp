// main.cpp
#include <GL/glu.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <vector>

int main()
{
    sf::Window window(sf::VideoMode(800, 600),
                      "3D Globe with Drag Rotation",
                      sf::Style::Default,
                      sf::ContextSettings(24));
    window.setVerticalSyncEnabled(true);

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glClearDepth(1.f);
    glClearColor(0.f, 0.f, 0.f, 1.f);

    // Sphere creation data
    float radius = 1.0f;
    const unsigned int slices = 40;
    const unsigned int stacks = 40;
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;

    for (unsigned int stack = 0; stack <= stacks; ++stack)
    {
        float phi = M_PI * float(stack) / stacks;
        for (unsigned int slice = 0; slice <= slices; ++slice)
        {
            float theta = 2.0f * M_PI * float(slice) / slices;
            float x = radius * sin(phi) * cos(theta);
            float y = radius * cos(phi);
            float z = radius * sin(phi) * sin(theta);
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);
        }
    }

    for (unsigned int stack = 0; stack < stacks; ++stack)
    {
        for (unsigned int slice = 0; slice < slices; ++slice)
        {
            int first = (stack * (slices + 1)) + slice;
            int second = first + slices + 1;
            indices.push_back(first);
            indices.push_back(second);
            indices.push_back(first + 1);

            indices.push_back(second);
            indices.push_back(second + 1);
            indices.push_back(first + 1);
        }
    }

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat aspect = 800.f / 600.f;
    gluPerspective(45.f, aspect, 0.1f, 100.f);

    // Variables for drag-based rotation
    bool dragging = false;
    int lastMouseX = 0, lastMouseY = 0;
    float rotationX = 0.f, rotationY = 0.f;

    // Marker fixed latitude and longitude (in radians)
    float lat = 45 * (M_PI / 180.f);
    float lon = 90 * (M_PI / 180.f);
    float pointX = radius * cos(lat) * cos(lon);
    float pointY = radius * sin(lat);
    float pointZ = radius * cos(lat) * sin(lon);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    dragging = true;
                    lastMouseX = event.mouseButton.x;
                    lastMouseY = event.mouseButton.y;
                }
            }
            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                    dragging = false;
            }
            if (event.type == sf::Event::MouseMoved && dragging)
            {
                int currentX = event.mouseMove.x;
                int currentY = event.mouseMove.y;
                int deltaX = currentX - lastMouseX;
                int deltaY = currentY - lastMouseY;
                rotationY += deltaX * 0.5f;
                rotationX += deltaY * 0.5f;
                lastMouseX = currentX;
                lastMouseY = currentY;
            }
        }

        // Clear buffers and set up camera
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(0, 0, 4,  0, 0, 0,  0, 1, 0);

        // Apply rotations from drag input
        glRotatef(rotationX, 1.f, 0.f, 0.f);
        glRotatef(rotationY, 0.f, 1.f, 0.f);

        // Draw the sphere
        glColor3f(0.2f, 0.6f, 0.8f);
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, vertices.data());
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data());
        glDisableClientState(GL_VERTEX_ARRAY);

        // Draw marker
        glPushMatrix();
        glColor3f(1.f, 0.f, 0.f);
        glTranslatef(pointX, pointY, pointZ);
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

        // Draw wind vectors on globe
                // Draw wind vectors on globe with arrowheads
        const int latSteps = 10;
        const int lonSteps = 20;
        float latMin = -M_PI/2, latMax = M_PI/2;
        float lonMin = -M_PI, lonMax = M_PI;

        glLineWidth(1.5f);
        glColor3f(1.f, 1.f, 0.f);

        // Parameters for arrowhead
        float arrowHeadLength = 0.05f;     // Length of arrowhead lines
        float arrowHeadWidthFactor = 0.3f; // Controls arrowhead width

        glBegin(GL_LINES);
        for (int i = 0; i <= latSteps; ++i) {
            float lat = latMin + (latMax - latMin) * i / float(latSteps);
            for (int j = 0; j <= lonSteps; ++j) {
                float lon = lonMin + (lonMax - lonMin) * j / float(lonSteps);

                // Compute position on sphere
                float x = cos(lat) * cos(lon);
                float y = sin(lat);
                float z = cos(lat) * sin(lon);

                // Tangent basis vectors
                float E_x = -sin(lon);
                float E_y = 0.f;
                float E_z = cos(lon);

                float N_x = -sin(lat) * cos(lon);
                float N_y = cos(lat);
                float N_z = -sin(lat) * sin(lon);

                // Placeholder wind function; replace with your own
                float w_e = cos(lat);
                float w_n = -sin(lat);

                // Compute 3D wind vector
                float wind3D_x = w_e * E_x + w_n * N_x;
                float wind3D_y = w_e * E_y + w_n * N_y;
                float wind3D_z = w_e * E_z + w_n * N_z;

                // Scale for visualization
                float scale = 0.2f;
                float endX = x + wind3D_x * scale;
                float endY = y + wind3D_y * scale;
                float endZ = z + wind3D_z * scale;

                // Draw main wind line
                glVertex3f(x, y, z);
                glVertex3f(endX, endY, endZ);

                // Compute normalized wind direction D
                float len = sqrt(wind3D_x*wind3D_x + wind3D_y*wind3D_y + wind3D_z*wind3D_z);
                if(len > 0) {
                    float D_x = wind3D_x / len;
                    float D_y = wind3D_y / len;
                    float D_z = wind3D_z / len;

                    // Find a perpendicular vector for arrowhead orientation
                    float up_x = 0.f, up_y = 1.f, up_z = 0.f;
                    // If D is nearly parallel to up, change up vector
                    if(fabs(D_x - up_x) < 1e-3 && fabs(D_y - up_y) < 1e-3 && fabs(D_z - up_z) < 1e-3) {
                        up_x = 1.f; up_y = 0.f; up_z = 0.f;
                    }
                    // perp1 = normalize(cross(D, up))
                    float perp1_x = D_y*up_z - D_z*up_y;
                    float perp1_y = D_z*up_x - D_x*up_z;
                    float perp1_z = D_x*up_y - D_y*up_x;
                    float perp1_len = sqrt(perp1_x*perp1_x + perp1_y*perp1_y + perp1_z*perp1_z);
                    if(perp1_len > 0) {
                        perp1_x /= perp1_len;
                        perp1_y /= perp1_len;
                        perp1_z /= perp1_len;
                    }

                    // Compute two arrowhead arms directions
                    float factor = arrowHeadWidthFactor;
                    float arm1_x = -D_x + factor*perp1_x;
                    float arm1_y = -D_y + factor*perp1_y;
                    float arm1_z = -D_z + factor*perp1_z;
                    float arm1_len = sqrt(arm1_x*arm1_x + arm1_y*arm1_y + arm1_z*arm1_z);
                    if(arm1_len > 0) {
                        arm1_x /= arm1_len;
                        arm1_y /= arm1_len;
                        arm1_z /= arm1_len;
                    }

                    float arm2_x = -D_x - factor*perp1_x;
                    float arm2_y = -D_y - factor*perp1_y;
                    float arm2_z = -D_z - factor*perp1_z;
                    float arm2_len = sqrt(arm2_x*arm2_x + arm2_y*arm2_y + arm2_z*arm2_z);
                    if(arm2_len > 0) {
                        arm2_x /= arm2_len;
                        arm2_y /= arm2_len;
                        arm2_z /= arm2_len;
                    }

                    // Draw arrowhead lines at the end of the main line
                    glVertex3f(endX, endY, endZ);
                    glVertex3f(endX + arrowHeadLength*arm1_x,
                               endY + arrowHeadLength*arm1_y,
                               endZ + arrowHeadLength*arm1_z);

                    glVertex3f(endX, endY, endZ);
                    glVertex3f(endX + arrowHeadLength*arm2_x,
                               endY + arrowHeadLength*arm2_y,
                               endZ + arrowHeadLength*arm2_z);
                }
            }
        }
        glEnd();

        window.display();
    }

    return 0;
}
