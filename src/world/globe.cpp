#include "globe.h"
#include <GL/glu.h>
#include <GL/glut.h> // Ensure this line is present
#include <cmath>
#include <glm/glm.hpp>


Globe::Globe(float radius, unsigned int slices, unsigned int stacks, sf::RenderWindow &window)
    : radius(radius), slices(slices), stacks(stacks), rotationX(0.f), rotationY(0.f), window(window), view(view)
{
   
 

    // Generate vertices and indices for the sphere
    for (unsigned int stack = 0; stack <= stacks; ++stack) {
        float phi = M_PI * float(stack) / stacks;
        for (unsigned int slice = 0; slice <= slices; ++slice) {
            float theta = 2.0f * M_PI * float(slice) / slices;
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
            indices.push_back(first);
            indices.push_back(second);
            indices.push_back(first + 1);
            indices.push_back(second);
            indices.push_back(second + 1);
            indices.push_back(first + 1);
        }
    }
}
// Convert plane coordinates to geographic lat/lon starting from Null Island
glm::vec2 Globe::planeToLatLon(float x_plane, float y_plane)
{
    // 1. Compute east and north displacements
    float E = x_plane;  // eastward component
    float N = -y_plane; // northward component since +y_plane is southward

    // 2. Compute distance and bearing
    float d = std::sqrt(E * E + N * N);
    float theta = std::atan2(E, N); // bearing from north, clockwise towards east

    // 3. Compute angular distance
    float delta = d / radius; // angular distance in radians

    // 4. Compute latitude (phi2) and longitude (lambda2)
    return glm::vec2(std::asin(std::sin(delta) * std::cos(theta)),
                     std::atan2(std::sin(theta) * std::sin(delta), std::cos(delta)));
}

glm::vec2 Globe::latLonToXY(float lat, float lon)
{
    // 1. Convert lat/lon to plane coordinates
    
    float phi = lat;
    float lambda = lon;
    float x_plane = radius * std::cos(phi) * std::sin(lambda);
    float y_plane = -radius * std::sin(phi);
    return glm::vec2(x_plane, y_plane);
}


 glm::vec2 Globe::getWind(float lat, float lon, std::vector<Storm *>& storms)
{
    // Placeholder wind function; replace with your own
    float w_e = cos(lat);
    float w_n = -sin(lat);

    auto pos = latLonToXY(lat, lon);

    for (auto storm : storms)
    {
        glm::vec2 stormCenter = storm->getCenter();
        float stormSize = storm->getSize();
        glm::vec2 stormDirection = storm->getDirection();
        
    
        glm::vec2 stormToBoat = pos - stormCenter;
        float distance = glm::length(stormToBoat);


        float angle = std::atan2(stormToBoat.y, stormToBoat.x);
        glm::vec2 windFromStorm =
            (stormSize > distance) ? glm::vec2(0.0f, 0.0f)
                                   : glm::vec2(-std::sin(angle), std::cos(angle)) * stormSize / (distance );

        // Scale wind based on storm size and distance
        w_e += windFromStorm.x;
        w_n += windFromStorm.y;
    }
    return glm::vec2(w_e, w_n);
}

void Globe::draw(std::vector<Storm *>& storms)
{
    // Clear color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set up projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat aspect = static_cast<GLfloat>(window.getSize().x) / window.getSize().y;
    gluPerspective(45.f, aspect, 0.1f, 100.f); // Field of View, Aspect Ratio, Near Plane, Far Plane

    // Set up modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 4,   // Eye position
              0, 0, 0,   // Look-at point
              0, 1, 0);  // Up vector

    // Apply rotations based on user input
    glRotatef(rotationX, 1.f, 0.f, 0.f);
    glRotatef(rotationY, 0.f, 1.f, 0.f);

    // Ensure depth testing and face culling are enabled
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW); // Ensure front faces are defined counter-clockwise
    

    // Draw the sphere
    glColor3f(0.2f, 0.6f, 0.8f); // Blueish color
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices.data());
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, indices.data());
    glDisableClientState(GL_VERTEX_ARRAY);

    // Draw marker (ensure it's correctly positioned and respects depth testing)
    glPushMatrix();
    glColor3f(1.f, 0.f, 0.f); // Red color for marker

    // Marker fixed latitude and longitude (in radians)
    float lat = 45 * (M_PI / 180.f);
    float lon = 90 * (M_PI / 180.f);
    float pointX = radius * cos(lat) * cos(lon);
    float pointY = radius * sin(lat);
    float pointZ = radius * cos(lat) * sin(lon);
    glTranslatef(pointX, pointY, pointZ);

    float size = 0.02f;
    glBegin(GL_QUADS);
        // Front face
        glVertex3f(-size, -size, size);
        glVertex3f(size, -size, size);
        glVertex3f(size, size, size);
        glVertex3f(-size, size, size);
        // Back face
        glVertex3f(-size, -size, -size);
        glVertex3f(size, -size, -size);
        glVertex3f(size, size, -size);
        glVertex3f(-size, size, -size);
        // Left face
        glVertex3f(-size, -size, -size);
        glVertex3f(-size, -size, size);
        glVertex3f(-size, size, size);
        glVertex3f(-size, size, -size);
        // Right face
        glVertex3f(size, -size, -size);
        glVertex3f(size, -size, size);
        glVertex3f(size, size, size);
        glVertex3f(size, size, -size);
        // Top face
        glVertex3f(-size, size, -size);
        glVertex3f(size, size, -size);
        glVertex3f(size, size, size);
        glVertex3f(-size, size, size);
        // Bottom face
        glVertex3f(-size, -size, -size);
        glVertex3f(size, -size, -size);
        glVertex3f(size, -size, size);
        glVertex3f(-size, -size, size);
    glEnd();
    glPopMatrix();

    // Draw wind vectors as before...
    // Ensure they are correctly positioned and respect depth testing

    // Note: Buffer swapping (window.display()) should be handled outside this function



    glColor3f(1.f, 1.f, 1.f); // White wireframe
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, indices.data());
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


    // Draw wind vectors on globe
    // Draw wind vectors on globe with arrowheads
    const int latSteps = 10;
    const int lonSteps = 20;
    float latMin = -M_PI / 2, latMax = M_PI / 2;
    float lonMin = -M_PI, lonMax = M_PI;

    glLineWidth(1.5f);
    glColor3f(1.f, 1.f, 0.f);

    // Parameters for arrowhead
    float arrowHeadLength = 0.05f;     // Length of arrowhead lines
    float arrowHeadWidthFactor = 0.3f; // Controls arrowhead width

    glBegin(GL_LINES);
    for (int i = 0; i <= latSteps; ++i)
    {
        float lat = latMin + (latMax - latMin) * i / float(latSteps);
        for (int j = 0; j <= lonSteps; ++j)
        {
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
            auto wind = getWind(lat, lon, storms);
            float w_e = wind.x;
            float w_n = wind.y;

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
            float len = sqrt(wind3D_x * wind3D_x + wind3D_y * wind3D_y + wind3D_z * wind3D_z);
            if (len > 0)
            {
                float D_x = wind3D_x / len;
                float D_y = wind3D_y / len;
                float D_z = wind3D_z / len;

                // Find a perpendicular vector for arrowhead orientation
                float up_x = 0.f, up_y = 1.f, up_z = 0.f;
                // If D is nearly parallel to up, change up vector
                if (fabs(D_x - up_x) < 1e-3 && fabs(D_y - up_y) < 1e-3 && fabs(D_z - up_z) < 1e-3)
                {
                    up_x = 1.f;
                    up_y = 0.f;
                    up_z = 0.f;
                }
                // perp1 = normalize(cross(D, up))
                float perp1_x = D_y * up_z - D_z * up_y;
                float perp1_y = D_z * up_x - D_x * up_z;
                float perp1_z = D_x * up_y - D_y * up_x;
                float perp1_len = sqrt(perp1_x * perp1_x + perp1_y * perp1_y + perp1_z * perp1_z);
                if (perp1_len > 0)
                {
                    perp1_x /= perp1_len;
                    perp1_y /= perp1_len;
                    perp1_z /= perp1_len;
                }

                // Compute two arrowhead arms directions
                float factor = arrowHeadWidthFactor;
                float arm1_x = -D_x + factor * perp1_x;
                float arm1_y = -D_y + factor * perp1_y;
                float arm1_z = -D_z + factor * perp1_z;
                float arm1_len = sqrt(arm1_x * arm1_x + arm1_y * arm1_y + arm1_z * arm1_z);
                if (arm1_len > 0)
                {
                    arm1_x /= arm1_len;
                    arm1_y /= arm1_len;
                    arm1_z /= arm1_len;
                }

                float arm2_x = -D_x - factor * perp1_x;
                float arm2_y = -D_y - factor * perp1_y;
                float arm2_z = -D_z - factor * perp1_z;
                float arm2_len = sqrt(arm2_x * arm2_x + arm2_y * arm2_y + arm2_z * arm2_z);
                if (arm2_len > 0)
                {
                    arm2_x /= arm2_len;
                    arm2_y /= arm2_len;
                    arm2_z /= arm2_len;
                }

                // Draw arrowhead lines at the end of the main line
                glVertex3f(endX, endY, endZ);
                glVertex3f(endX + arrowHeadLength * arm1_x,
                           endY + arrowHeadLength * arm1_y,
                           endZ + arrowHeadLength * arm1_z);

                glVertex3f(endX, endY, endZ);
                glVertex3f(endX + arrowHeadLength * arm2_x,
                           endY + arrowHeadLength * arm2_y,
                           endZ + arrowHeadLength * arm2_z);
            }
        }
    }
    glEnd();
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Switch back to fill mode

}

void Globe::update(float dt)
{
}


void Globe::setPlanarView(float x, float y, float aspect)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(x - aspect, x + aspect, y - 1.0f, y + 1.0f, -1.0f, 1.0f); // Adjust the orthographic projection as needed
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Globe::handleEvents(sf::Event &e, float dt)
{
    if (e.type == sf::Event::MouseButtonPressed)
    {
        if (e.mouseButton.button == sf::Mouse::Left)
        {
            dragging = true;
            lastMouseX = e.mouseButton.x;
            lastMouseY = e.mouseButton.y;
        }
    }
    else if (e.type == sf::Event::MouseButtonReleased)
    {
        if (e.mouseButton.button == sf::Mouse::Left)
        {
            dragging = false;
        }
    }
    else if (e.type == sf::Event::MouseMoved)
    {
        if (dragging)
        {
            int deltaX = e.mouseMove.x - lastMouseX;
            int deltaY = e.mouseMove.y - lastMouseY;
            lastMouseX = e.mouseMove.x;
            lastMouseY = e.mouseMove.y;
            rotationX += deltaY;
            rotationY += deltaX;
        }
    }
}


void Globe::resetSphericalView(float aspect)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.f, aspect, 0.1f, 100.f); // Perspective for sphere
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}