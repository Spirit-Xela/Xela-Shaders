#ifndef _PLATFORM_CODE_H
#define _PLATFORM_CODE_H

//Windows
#ifdef _WIN32
#define GLFW_EXPOSE_NATIVE_WIN32
//This magic number comes from the following article
//https://www.codeproject.com/Articles/856020/Draw-Behind-Desktop-Icons-in-Windows-plus
#define WORKERW_MESSAGE 0x052C
#endif

//C++
#include <vector>
//Engine
#include "XelaWindow.h"
//OpenGL
#include <GLFW/glfw3native.h>

struct MonitorInfo {
	int x, y, width, height;
};

//Perform window configuration that requires platform-specific code
//This is platform-specific code so it is best kept within its own function
void setupWindow(XelaWindow *win);
//Pauses for a given number of seconds then returns
void delay(double sec);
//Hides the console window
void hideConsole();
//Returns a list of all the monitors' information
std::vector<MonitorInfo> getMonitorList();

//Returns the maximum X coordinate of any window
int getMaxX();
//Returns the maximum Y coordinate of any window
int getMaxY();

#endif