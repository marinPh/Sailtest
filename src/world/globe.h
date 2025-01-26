

#include <SFML/Graphics.hpp>
#include <vector>
#include <GL/glu.h>
#include <glm/vec2.hpp>
#include <storm.h>


class Globe
{
public:
    Globe(float radius,
          unsigned int slices,
          unsigned int stacks,
          sf::RenderWindow& window);
    void draw(std::vector<Storm *>& storms);
    void setCenter(float x, float y, float z);
    void setRotation(float angle, float x, float y, float z);
    void setWindVectors(float *wind3D_x,
                        float *wind3D_y,
                        float *wind3D_z,
                        int latSteps,
                        int lonSteps,
                        float latMin,
                        float latMax,
                        float lonMin,
                        float lonMax,
                        float arrowHeadLength,
                        float arrowHeadWidthFactor);
    void unzoom(float factor);
    void zoom(float factor);
    void rotate(float angle, float x, float y, float z);
    void setPlanarView(float x, float y, float aspect);
    void resetSphericalView(float aspect);
    void update(float dt);
    glm::vec2 getWind(float lat, float lon, std::vector<Storm *>& storms);
    void handleEvents(sf::Event& e,float dt);
    glm::vec2 latLonToXY(float lat, float lon);
    glm::vec2 planeToLatLon(float x_plane, float y_plane);

private:
    float radius;
    unsigned int slices;
    unsigned int stacks;
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    sf::RenderWindow &window;
    sf::View &view;
    bool dragging = false;
    int lastMouseX = 0, lastMouseY = 0;
    float rotationX;
    float rotationY;
};
