#ifndef _XELA_SHADER_H
#define _XELA_SHADER_H

//OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>
//Engine
#include "XelaDefinitions.h"
//C++
#include <vector>
#ifdef XELA_DEBUG_SHADER
#include <iostream>
#endif

class XelaShader {
protected:
	unsigned int vertexShader = -1, fragmentShader = -1, shaderProgram = -1;

	const char *srcVert = nullptr;
	const char *srcFrag = nullptr;

	std::vector<XelaImageInfo> texList;

	std::vector<XelaShaderCallbackFunction> shaderCB;

	void compile();
public:
	//Creates a new XelaShader and compiles the given GLSL source code
	XelaShader(const char *shaderV, const char *shaderF);
	~XelaShader();

	//Sets the shader to use
	void setShader(const char *shaderV, const char *shaderF);
	//Loads an image from the file path specified and adds it to a list of textures to send to the shader as uniforms under the name specified.
	void addImage(const char *tPath, const char *name, int *width, int *height, int *numChannels, int inputFormat, int textureFormat);
	//Defines a callback function to be called whenever this shader is applied
	//Use this function to declare uniforms or perform other operations dependent on the shader being activated first
	void addShaderCallback(XelaShaderCallbackFunction func);
	//Removes a function from the list of functions to be called whenever this shader is applied
	void removeShaderCallback(XelaShaderCallbackFunction func);
	//Activates this shader
	void use();
};

#endif