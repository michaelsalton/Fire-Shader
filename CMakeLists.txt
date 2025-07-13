cmake_minimum_required(VERSION 3.10)
project(FireShader)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Add executable
add_executable(FireShader 
    src/main.cpp
)

# Link SFML libraries
target_link_libraries(FireShader 
    sfml-graphics 
    sfml-window 
    sfml-system
)

# Copy shaders to build directory
file(COPY shaders DESTINATION ${CMAKE_BINARY_DIR})