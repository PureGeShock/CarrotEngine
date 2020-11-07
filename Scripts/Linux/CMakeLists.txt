cmake_minimum_required(VERSION 3.0)
cmake_policy(SET CMP0072 OLD)

# OPENGL, GLEW
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
if(NOT OpenGL_FOUND OR NOT GLEW_FOUND)
    execute_process(
        COMMAND bash "${CMAKE_CURRENT_SOURCE_DIR}/Install_OpenGL.sh"
    )
endif()

# SDL2
find_package(SDL2 REQUIRED)
if(NOT SDL2_FOUND)
    execute_process(
        COMMAND bash "${CMAKE_CURRENT_SOURCE_DIR}/Install_SDL2.sh"
    )
endif()

include_directories(
    ${OPENGL_INCLUDE_DIR} 
    ${GLEW_INCLUDE_DIRS} 
    ${SDL2_INCLUDE_DIRS})

# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin/Linux)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

add_executable(CarrotEngine ${AllFilesInSrc})

target_link_libraries(CarrotEngine
    ${OPENGL_LIBRARIES} 
    ${GLEW_LIBRARIES} 
    ${SDL2_LIBRARIES})