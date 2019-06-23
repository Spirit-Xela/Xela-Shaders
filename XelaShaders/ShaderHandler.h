#ifndef _SHADER_HANDLER_H
#define _SHADER_HANDLER_H

#define PRESTRING(a, b) a.substr(0, a.find(b))
#define POSTSTRING(a, b) a.substr(a.find(b) + 1, a.length() - 1)

//C++
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
//OpenGL
#include <GL/glew.h>
//Engine
#include "XelaWindow.h"
//Xela Shaders
#include "PlatformCode.h"

struct ImageInfo {
	int width, height, numChannels;
	std::string name;
};

//Sets which monitor is currently being rendered on so that shaderCallback can set uniforms properly
void setCurrentMonitor(int m);
//Called every frame once the shader is enabled to ensure uniforms are updated appropriately
void shaderCallback(unsigned int program);
//Reads the config file, processes the commands inside, and loads the vertex/fragment shader specified
bool loadShaders(std::string configPath, std::string* vShader, std::string* fShader);
//Returns the max FPS the display should reach
//A value of 0 or less means there is no limit
float getFPS();
//Returns integers representing which monitors should be rendered on
std::vector<int> getDisplays();

#endif