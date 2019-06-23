#ifndef _XELA_CALLBACKS_H
#define _XELA_CALLBACKS_H

//Engine
#include "XelaEvents.h"
//OpenGL
#include <GLFW/glfw3.h>
//C++
#ifdef XELA_DEBUG_CALLBACKS
#include <iostream>
#endif

//Initialize callback functions
void xelaInitCallbacks(GLFWwindow *window);
//Handle window resizing
void xelaFramebufSizeCallback(GLFWwindow *window, int width, int height);
//Handle key presses
void xelaKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
//Handle mouse events
void xelaMouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
//Handle mouse movement
void xelaCursorPosCallback(GLFWwindow *window, double xpos, double ypos);
//Handle window resizing
void xelaWindowSizeCallback(GLFWwindow* window, int width, int height);

#endif