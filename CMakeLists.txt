cmake_minimum_required(VERSION 3.10)
project(Odyssey)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Platform Specific
if(APPLE)
  set(PLATFORM_NAME "MACOS")
  add_compile_options(-fPIC -Wno-deprecated-declarations)
elseif(WIN32)
  set(PLATFORM_NAME "WINDOWS")
  add_compile_options(/W4)
endif()

#packages
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

#config header 
configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/include/Config.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/Config.h"
)

#include dirs
include_directories(include)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

file(GLOB SOURCES src/*.cpp)

add_executable(odyssey ${SOURCES})
target_link_libraries(odyssey OpenGL::GL GLUT::GLUT)