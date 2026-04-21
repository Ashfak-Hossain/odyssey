#ifndef PLATFORM_H
#define PLATFORM_H

#include "Config.h"

#ifdef PLATFORM_MACOS
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#elif PLATFORM_WINDOWS
#include <GL/glut.h>
#include <GL/gl.h>
#endif

#endif
