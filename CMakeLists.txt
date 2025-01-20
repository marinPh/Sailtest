cmake_minimum_required(VERSION 3.10)
project(SailTest)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the SFML package with necessary components
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

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
#add_executable(Sphere src/sphere.cpp)  # Add Sphere executable

# Add include directories for headers
target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/navigation
)
#target_link_libraries(Sphere PRIVATE sfml-window sfml-system GL GLU  sfml-graphics sfml-window sfml-system)

# Link SFML libraries to the executable
target_link_libraries(${PROJECT_NAME}
        sfml-graphics
        sfml-window
        sfml-system
)


target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)

