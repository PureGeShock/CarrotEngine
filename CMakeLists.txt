cmake_minimum_required(VERSION 3.0)

project(CarrotEngine)
set(CMAKE_BUILD_TYPE Debug)

# Autogenerated Config file
set(ENGINE_VERSION 0.1.0)
set(CURRENT_PLATFORM ${CMAKE_SYSTEM_NAME})
set(PROJECT_CONFIGURATION ${CMAKE_BUILD_TYPE})
set(WRITE_LOGS_TO_LOGFILE 1)
set(PROJECT_NAME CarrotEngine)

set(CONFIG_IN_PATH "Scripts/Config.h.in")
set(CONFIG_PATH "../src/Engine/Config.h")
configure_file("${CONFIG_IN_PATH}" "${CONFIG_PATH}")

# CMake C++ flags
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

# The following folder will be included
include_directories("${PROJECT_SOURCE_DIR}")

# Compile all .h and .cpp files
file(GLOB_RECURSE AllFilesInSrc
    "${PROJECT_SOURCE_DIR}/src/*.h"
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

set(LinuxPlatformDir Scripts/Linux)
set(WindowsPlatformDir Scripts/Windows)

include_directories("${LinuxPlatformDir}")
include_directories("${WindowsPlatformDir}")

if (UNIX)
    add_subdirectory("${LinuxPlatformDir}")
elseif(WIN32)
    add_subdirectory("${WindowsPlatformDir}")
endif()