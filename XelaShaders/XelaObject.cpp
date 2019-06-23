#include "XelaObject.h"

XelaObject::XelaObject(const char* shaderV, const char* shaderF) {
	//Generate array/buffers for this object
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	//Create new shader object
	shader = new XelaShader(shaderV, shaderF);
}
XelaObject::XelaObject(XelaShader *s) {
	//Generate array/buffers for this object
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	//Store shader pointer
	shader = s;
}

void XelaObject::updateData() {
	//Bind vertex array and buffer
	glBindVertexArray(VAO);

	//Save vertex data to buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

	//Save index data to buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);

	//Configure vertex attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void XelaObject::addVertex(XelaVec3<float> vert) {
	vertices.push_back(vert.x);
	vertices.push_back(vert.y);
	vertices.push_back(vert.z);
}
void XelaObject::addVertices(std::vector<XelaVec3<float>> verts) {
	for (int i = 0; i < verts.size(); i++) {
		vertices.push_back(verts[i].x);
		vertices.push_back(verts[i].y);
		vertices.push_back(verts[i].z);
	}
}
void XelaObject::addVertices(XelaVec3<float>* verts, int count) {
	for (int i = 0; i < count; i++) {
		vertices.push_back(verts[i].x);
		vertices.push_back(verts[i].y);
		vertices.push_back(verts[i].z);
	}
}
void XelaObject::clearVertices() {
	vertices.clear();
}
void XelaObject::setVertices(std::vector<XelaVec3<float>> verts) {
	vertices.clear();
	for (int i = 0; i < verts.size(); i++) {
		vertices.push_back(verts[i].x);
		vertices.push_back(verts[i].y);
		vertices.push_back(verts[i].z);
	}
}
void XelaObject::setVertices(XelaVec3<float>* verts, int count) {
	vertices.clear();
	for (int i = 0; i < count; i++) {
		vertices.push_back(verts[i].x);
		vertices.push_back(verts[i].y);
		vertices.push_back(verts[i].z);
	}
}

void XelaObject::addIndex(XelaVec3<unsigned int> ind) {
	indices.push_back(ind.x);
	indices.push_back(ind.y);
	indices.push_back(ind.z);
}
void XelaObject::addIndices(std::vector<XelaVec3<unsigned int>> inds) {
	for (int i = 0; i < inds.size(); i++) {
		indices.push_back(inds[i].x);
		indices.push_back(inds[i].y);
		indices.push_back(inds[i].z);
	}
}
void XelaObject::addIndices(XelaVec3<unsigned int>* inds, int count) {
	for (int i = 0; i < count; i++) {
		indices.push_back(inds[i].x);
		indices.push_back(inds[i].y);
		indices.push_back(inds[i].z);
	}
}
void XelaObject::clearIndices() {
	indices.clear();
}
void XelaObject::setIndices(std::vector<XelaVec3<unsigned int>> inds) {
	indices.clear();
	for (int i = 0; i < inds.size(); i++) {
		indices.push_back(inds[i].x);
		indices.push_back(inds[i].y);
		indices.push_back(inds[i].z);
	}
}
void XelaObject::setIndices(XelaVec3<unsigned int>* inds, int count) {
	indices.clear();
	for (int i = 0; i < count; i++) {
		indices.push_back(inds[i].x);
		indices.push_back(inds[i].y);
		indices.push_back(inds[i].z);
	}
}

void XelaObject::setShader(XelaShader *s) {
	shader = s;
}
XelaShader *XelaObject::getShader() {
	return shader;
}

void XelaObject::draw() {
	//Use program, bind VAO, draw, unbind VAO
	shader->use();
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}