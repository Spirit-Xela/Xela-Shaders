#include "Main.h"

XelaWindow *window;
int win = 0;

XelaObject *actor;
XelaShader *shader;

std::vector<MonitorInfo> monitors;
std::vector<int> targets;

XelaWindow *getwin() {
	return window;
}
XelaObject *getActor() {
	return actor;
}

void init(std::string *vertSrc, std::string *fragSrc) {
	//Setup the actor object
	actor->getShader()->setShader((*vertSrc).c_str(), (*fragSrc).c_str());
	actor->addVertices({ { -1, -1, 0 }, { 1, -1, 0 }, { -1, 1, 0 }, { 1, 1, 0 } });
	actor->addIndices({ { 0, 1, 2 }, { 1, 2, 3 } });
	actor->getShader()->addShaderCallback(&shaderCallback);
	actor->updateData();

	//Configure the window
	window->setClearColor({ 0, 0, 0, 0 });
	window->maximize();
	glfwSetWindowAttrib(window->getGLFWwindow(), GLFW_FOCUSED, GL_FALSE);
	setupWindow(window);

	//Retrieve necessary data for loop
	monitors = getMonitorList();
	targets = getDisplays();
}

void loop() {
	//Render for each monitor
	for (int i = 0; i < targets.size(); i++) {
		setCurrentMonitor(targets[i]);
		//The math on the y position is due to Windows (0, 0) being top left and OpenGL (0, 0) being bottom left
		glViewport(monitors[targets[i]].x, (getMaxY() -monitors[targets[i]].height) - monitors[targets[i]].y, monitors[targets[i]].width, monitors[targets[i]].height);
		actor->draw();
	}
	//Swap buffers/clear
	window->update();
}

int main(int argc, char **argv) {
	std::string vertexShader, fragmentShader;

	int winSuccess;
	std::string path;

	//If a path argument was provided, use that
	//Otherwise, prompt for path to shader folder
	if (argc > 1) {
		path = argv[1];
	}
	else {
		std::cout << "Path to shader folder: ";
		std::getline(std::cin, path);
	}

	//Create window
	window = new XelaWindow(1, 1, "Shader Display", false, &winSuccess, false);
	//Load shaders
	shader = new XelaShader("#version 330 core\nvoid main() {};", "#version 330 core\nvoid main() {};");
	actor = new XelaObject(shader);
	if (!loadShaders(path, &vertexShader, &fragmentShader)) {
		return -1;
	}
	//Initialize game
	init(&vertexShader, &fragmentShader);
	//Free memory
	path.clear();
	vertexShader.clear();
	fragmentShader.clear();
	if (winSuccess == XELA_SUCCESS) {
		//Run loop
		if (getFPS() <= 0) {
			while (!window->shouldClose()) {
				loop();
			}
		}
		else {
			//If FPS limit set delay for 1/fps between frames
			double time = 1 / getFPS();
			while (!window->shouldClose()) {
				loop();
				delay(time);
			}
		}
	}
	delete window;

	return 0;
}