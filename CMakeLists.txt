cmake_minimum_required(VERSION 3.10)
project(SailTest)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the SFML package with necessary components
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
set(OpenGL_GL_PREFERENCE GLVND)

find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)
# Remove these lines if not required



# Find GLM package
find_package(glm REQUIRED CONFIG)  # Using CONFIG mode to get modern CMake target

# List all source files
set(SOURCES
        main.cpp
        src/navigation/boat.cpp
        src/navigation/rudder.cpp   # Add Rudder source file
    src/navigation/keel.cpp     # Add Keel source file
    src/navigation/hull.cpp     # Add Hull source file
        src/navigation/sail.cpp     # Add Sail source file
)

# Add the executable
add_executable(${PROJECT_NAME} ${SOURCES})

add_executable(Sphere src/sphere.cpp)  # Add Sphere executable
##add_executable(Sphere src/sphere.cpp)  # Add Sphere executable

add_executable(newMain 
        src/newMain.cpp
    src/world/world.cpp
    src/navigation/boat.cpp
    src/navigation/rudder.cpp
    src/navigation/keel.cpp
    src/navigation/hull.cpp
    src/navigation/sail.cpp
    src/world/globe.cpp
    src/world/storm.cpp)  # Add newMain executable

target_include_directories(newMain PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/navigation
        ${CMAKE_CURRENT_SOURCE_DIR}/src/world
)

# Add include directories for headers
target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/navigation
        ${CMAKE_CURRENT_SOURCE_DIR}/src/world
)
target_link_libraries(newMain PRIVATE sfml-window sfml-system GL GLU  sfml-graphics sfml-window sfml-system ${OPENGL_LIBRARIES} )


target_link_libraries(Sphere PRIVATE sfml-window sfml-system GL GLU  sfml-graphics sfml-window sfml-system GL GLU ${OPENGL_LIBRARIES}  )


# Link SFML libraries to the executable
target_link_libraries(${PROJECT_NAME}
        sfml-graphics
        sfml-window
        sfml-system
)


target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)

