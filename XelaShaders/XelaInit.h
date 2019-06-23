#ifndef _XELA_INIT_H
#define _XELA_INIT_H

//Engine
#include "XelaDefinitions.h"
//OpenGL
#include <GL/glew.h> 
#include <GLFW/glfw3.h>
//C++
#ifdef XELA_DEBUG_INIT
#include <iostream>
#endif

bool xelaInit();
bool xelaInitGLEW();
bool xelaTerminate();

#endif