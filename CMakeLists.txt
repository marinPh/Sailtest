cmake_minimum_required(VERSION 3.5)
project(SailTest)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the SFML package with necessary components
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Find GLM package
find_package(glm REQUIRED CONFIG)  # Using CONFIG mode to get modern CMake target

# List all source files
set(SOURCES
    main.cpp
    src/navigation/boat.cpp
)

# Add the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Add include directories for headers
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/navigation
)

# Link SFML libraries to the executable
target_link_libraries(${PROJECT_NAME}
    sfml-graphics
    sfml-window
    sfml-system
)


target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)

