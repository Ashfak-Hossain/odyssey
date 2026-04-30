cmake_minimum_required(VERSION 3.10)
project(Odyssey)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Platform Specific
if(APPLE)
  set(PLATFORM_NAME "MACOS")
  # add_compile_options(-Wno-deprecated-declarations)
  add_compile_options(-fPIC -Wno-deprecated-declarations)
elseif(WIN32)
  set(PLATFORM_NAME "WINDOWS")
  add_compile_options(/W4)
endif()

# packages
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

# genearate config file in build dir
configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/config/Config.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/Config.h"
)

# Copy config headers into build dir so Config.h can #include them
file(GLOB CONFIG_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/config/*.h")
file(COPY ${CONFIG_HEADERS} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

#include dirs
include_directories(include)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# all source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(odyssey ${SOURCES})

# private include path for the game itself
target_include_directories(odyssey PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"   
    "${CMAKE_CURRENT_BINARY_DIR}"           
)

target_link_libraries(odyssey OpenGL::GL GLUT::GLUT)