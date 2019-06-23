#ifndef _XELA_OBJECT_H
#define _XELA_OBJECT_H

//C++
#include <vector>
//Libs
#include <GL/glew.h>
//Engine
#include "XelaDefinitions.h"
#include "XelaShader.h"

//Location 0 = vertices
//Location 1 = vec4

class XelaObject {
protected:
	unsigned int VBO, VAO, EBO;

	std::vector<float> vertices;
	std::vector<unsigned int> indices;

	XelaShader *shader;

public:
	//Creates a new XelaObject and a new XelaShader with the given GLSL source code
	//ShaderV and ShaderF are required. However, shaderG may be nullptr
	XelaObject(const char* shaderV, const char* shaderF);
	XelaObject(XelaShader *s);

	//Add a vertex to this object
	//Vertices are sent to location 0 in the vertex shader
	void addVertex(XelaVec3<float> vert);
	//Add multiple vertices to this object
	//Vertices are sent to location 0 in the vertex shader
	void addVertices(std::vector<XelaVec3<float>> verts);
	//Add multiple vertices to this object
	//Vertices are sent to location 0 in the vertex shader
	void addVertices(XelaVec3<float> *verts, int count);

	//Remove all vertices from this object
	//Vertices are sent to location 0 in the vertex shader
	void clearVertices();
	//Remove all vertices from this object and set new ones
	//Vertices are sent to location 0 in the vertex shader
	void setVertices(std::vector<XelaVec3<float>> verts);
	//Remove all vertices from this object and set new ones
	//Vertices are sent to location 0 in the vertex shader
	void setVertices(XelaVec3<float> *verts, int count);

	//Add an index to this object
	void addIndex(XelaVec3<unsigned int> ind);
	//Add multiple indices to this object
	void addIndices(std::vector<XelaVec3<unsigned int>> inds);
	//Add multiple indices to this object
	void addIndices(XelaVec3<unsigned int> *inds, int count);

	//Remove all indices from this object
	void clearIndices();
	//Remove all indices from this object and set new ones
	void setIndices(std::vector<XelaVec3<unsigned int>> inds);
	//Remove all indices from this object and set new ones
	void setIndices(XelaVec3<unsigned int> *inds, int count);

	//Updates all the VAO, VBO, EBO data
	void updateData();

	//Sets the shader to be used by this object
	void setShader(XelaShader *s);
	//Returns the shader being used by this object
	XelaShader* getShader();

	//Draws the object on screen
	void draw();
};

#endif