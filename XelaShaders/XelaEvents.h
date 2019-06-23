#ifndef _XELA_EVENTS_H
#define _XELA_EVENTS_H

//Engine
#include "XelaWindow.h"
#include "XelaDefinitions.h"
//C++
#ifdef XELA_DEBUG_EVENTS
#include <iostream>
#endif
#include <unordered_map>

struct KeyInfo {
	int key, scancode, action, mods;
	XelaWindow *window;
};
struct MouseButtonInfo {
	int button, action, mods;
	XelaWindow *window;
};
struct CursorPosInfo {
	double xpos, ypos;
	XelaWindow *window;
};

typedef void(*XelaKeyCallback)(XelaWindow *window, int key, int scancode, int action, int mods);
typedef void(*XelaMouseButtonCallback)(XelaWindow *window, int button, int action, int mods);
typedef void(*XelaCursorPosCallback)(XelaWindow *window, double xpos, double ypos);

void xelaAddWindow(GLFWwindow *key, XelaWindow *window);
void xelaAddKeyToBuffer(KeyInfo info);
void xelaPressMouse(MouseButtonInfo info);
void xelaUpdateCursorPos(CursorPosInfo info);
void xelaProcessEvents();
void xelaSetKeyCallback(XelaKeyCallback cb);
void xelaSetMouseButtonCallback(XelaMouseButtonCallback cb);
void xelaSetCursorPosCallback(XelaCursorPosCallback cb);

XelaWindow* getXelaWindow(GLFWwindow *key);

#endif