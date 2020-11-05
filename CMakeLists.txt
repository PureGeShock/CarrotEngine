cmake_minimum_required(VERSION 3.0)
project (CarrotEngine)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(SDL2 REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS})

# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# The following folder will be included
include_directories("${PROJECT_SOURCE_DIR}")

add_executable(CarrotEngine src/main.cpp)

target_link_libraries(CarrotEngine ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${SDL2_LIBRARIES})