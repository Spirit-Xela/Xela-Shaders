#include "ShaderHandler.h"
#include "Main.h"

int num_textures = 0, monitor = 0;
std::vector<ImageInfo> textureList;
std::vector<int> displays;

float FPS = 0, multiplier = 1;

void setCurrentMonitor(int m) {
	monitor = m;
}
void shaderCallback(unsigned int program) {
	//Set uniforms for shaders
	std::vector<MonitorInfo> monitorList = getMonitorList();
	glUniform2f(glGetUniformLocation(program, "resolution"), (float)monitorList[monitor].width, (float)monitorList[monitor].height);
	glUniform1f(glGetUniformLocation(program, "time"), (float)getwin()->getTime() * multiplier);
	glUniform2f(glGetUniformLocation(program, "offset"), (float)monitorList[monitor].x, (float)(getMaxY() - monitorList[monitor].height) - monitorList[monitor].y);
	for (int i = 0; i < textureList.size(); i++) {
		glUniform2f(glGetUniformLocation(program, (textureList[i].name + ".resolution").c_str()), (float)textureList[i].width, (float)textureList[i].height);
	}
}

bool equalIgnoreCase(std::string s1, std::string s2) {
	if (s1.length() != s2.length())
		return false;

	for (int i = 0; i < (int)s1.length(); i++) {
		if (!(s1[i] - 'a' == s2[i] - 'a' || s1[i] - 'a' == s2[i] - 'A' || s1[i] - 'A' == s2[i] - 'a' || s1[i] - 'A' == s2[i] - 'A'))
			return false;
	}
	return true;
}

void processCommand(std::string basePath, std::string cmd, std::string arg, std::string *vPath, std::string *fPath) {
	if (equalIgnoreCase(cmd, "VertexShader")) {
		//Arg = Path to vert shader
		*vPath = arg;
	}
	else if (equalIgnoreCase(cmd, "FragmentShader")) {
		//Arg = Path to fragment shader
		*fPath = arg;
	}
	else if (equalIgnoreCase(cmd, "Fps")) {
		//Arg = Max FPS
		FPS = std::stof(arg);
	}
	else if (equalIgnoreCase(cmd, "Monitor")) {
		//Arg = Monitor number to display on
		displays.push_back(std::stoi(arg) - 1);
	}
	else if (equalIgnoreCase(cmd, "Texture")) {
		//Vars
		int width, height, nChannels;
		//Get name and path
		std::string name = PRESTRING(arg, "=");
		std::string path = POSTSTRING(arg, "=");
		getActor()->getShader()->addImage((basePath + "/" + path).c_str(), (name + ".tex").c_str(), &width, &height, &nChannels, GL_RGBA, GL_RGBA);
		//Insert ImageInfo struct into textureList
		textureList.push_back({ width, height, nChannels, name});
	}
	else if (equalIgnoreCase(cmd, "speed")) {
		//Arg = Speed Multiplier
		multiplier = std::stof(arg);
	}
	else if (equalIgnoreCase(cmd, "HideConsole")) {
		hideConsole();
	}
}

bool loadShaders(std::string configPath, std::string *vShader, std::string *fShader) {
	std::ifstream read;
	std::string line, src, vPath, fPath, cmd, arg;

	//Open config file to be read
	read.open(configPath + "/config.txt");
	if (!read.is_open()) {
		std::cout << "Could not find config file: " << configPath << "/config.txt" << std::endl;
		return false;
	}
	else {
		while (std::getline(read, line)) {
			//Process each line of the config file as a seperate command
			processCommand(configPath, PRESTRING(line, " "), POSTSTRING(line, " "), &vPath, &fPath);
		}
		//Update vPath / fPath to include the root directory as well as the name of the file
		vPath = configPath + "/" + vPath;
		fPath = configPath + "/" + fPath;
	}
	read.close();

	//Open vertex shader and read into vShader
	read.open(vPath.c_str());
	if (!read.is_open()) {
		std::cout << "Could not find vertex shader source file! File path was: " << vPath << std::endl;
		return false;
	}
	else {
		while (std::getline(read, line)) {
			src += line + "\n";
		}
		*vShader = src;
		src.clear();
	}
	read.close();

	//Open fragment shader and read into fShader
	read.open(fPath.c_str());
	if (!read.is_open()) {
		std::cout << "Could not find fragment shader source file! File path was: " << fPath << std::endl;
		return false;
	}
	else {
		while (std::getline(read, line)) {
			src += line + "\n";
		}
		*fShader = src;
		src.clear();
	}
	read.close();
	return true;
}
float getFPS() {
	return FPS;
}
std::vector<int> getDisplays() {
	return displays;
}