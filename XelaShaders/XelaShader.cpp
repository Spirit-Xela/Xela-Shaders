#include "XelaShader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

XelaShader::XelaShader(const char *shaderV, const char *shaderF) {
	//Update shader src based on type and recompile
	srcVert = shaderV;
	srcFrag = shaderF;
	this->compile();
}
XelaShader::~XelaShader() {
	if (srcVert != nullptr)
		delete srcVert;
	if (srcFrag != nullptr)
		delete srcFrag;
}

void XelaShader::compile() {
	int success;
	char infoLog[512];

	if (vertexShader != -1) {
		//This shader has been compiled before, remove the redundant shader
		glDeleteShader(vertexShader);
	}

	//Create vertex shader
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &srcVert, nullptr);
	glCompileShader(vertexShader);

	//Error check
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
#ifdef XELA_DEBUG_SHADER
		//Print error
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		std::cout << "[ERROR][XelaShader] Error compiling vertex shader: " << infoLog << std::endl;
#endif
		//Delete shader and return
		glDeleteShader(vertexShader);
		return;
	}

	if (fragmentShader != -1) {
		//This shader has been compiled before, remove the redundant shader
		glDeleteShader(fragmentShader);
	}

	//Create fragment shader
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &srcFrag, nullptr);
	glCompileShader(fragmentShader);

	//Error check
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
#ifdef XELA_DEBUG_SHADER
		//Print error
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		std::cout << "[ERROR][XelaShader] Error compiling fragment shader: " << infoLog << std::endl;
#endif
		//Delete shaders and return
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		return;
	}

	if (shaderProgram != -1) {
		//This shader has been compiled before, remove the redundant shader
		glDeleteProgram(shaderProgram);
	}

	//Create program
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	//Error Check
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {

	}
}
void XelaShader::setShader(const char *shaderV, const char *shaderF) {
	//Update shader src based on type and recompile
	srcVert = shaderV;
	srcFrag = shaderF;
	this->compile();
}
void XelaShader::addImage(const char *tPath, const char *name, int* width, int* height, int* numChannels, int inputFormat, int textureFormat) {
	//Load data with stb_image
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(tPath, width, height, numChannels, 0);

	//Add new entry in texList
	texList.push_back({ name, 0 });

	//Generate OpenGL texture
	glGenTextures(1, &texList[texList.size() - 1].id);
	glBindTexture(GL_TEXTURE_2D, texList[texList.size() - 1].id);
	glTexImage2D(GL_TEXTURE_2D, 0, inputFormat, *width, *height, 0, textureFormat, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	//Free data
	stbi_image_free(data);
}
void XelaShader::addShaderCallback(XelaShaderCallbackFunction func) {
	shaderCB.push_back(func);
}
void XelaShader::removeShaderCallback(XelaShaderCallbackFunction func) {
	for (int i = 0; i < shaderCB.size(); i++) {
		if (shaderCB[i] == func) {
			shaderCB.erase(shaderCB.begin() + i, shaderCB.begin() + i + 1);
		}
	}
}
void XelaShader::use() {
	//Use program
	glUseProgram(shaderProgram);
	//Set texture uniforms
	for (int i = 0; i < texList.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, texList[i].id);
		glUniform1i(glGetUniformLocation(shaderProgram, texList[i].name), i);
	}
	//Call shaderCB
	for (int i = 0; i < (int)shaderCB.size(); i++) {
		shaderCB[i](shaderProgram);
	}
}