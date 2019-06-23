#include "XelaInit.h"

bool initialized = false;

bool xelaInit() {
	int suc, glfwMajor, glfwMinor, glfwRevision, errCode;
	const char *errMsg;

	if (initialized)
		return true;

	//Init GLFW
	suc = glfwInit();
	if (suc != GLFW_TRUE) {
#ifdef XELA_DEBUG_INIT
		//Print error
		errCode = glfwGetError(&errMsg);
		std::cout << "[ERROR][XelaInit] Error initializing GLFW (" << errCode << "): " << errMsg << std::endl;
#endif
		glfwTerminate();
		return false;
	}
	glfwGetVersion(&glfwMajor, &glfwMinor, &glfwRevision);
#ifdef XELA_DEBUG_INIT
	//Print glfw version
	std::cout << "[Message][XelaInit] Initialized GLFW " << glfwMajor << "." << glfwMinor << "." << glfwRevision << std::endl;
#endif

	//Configure GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, XELA_GLFW_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, XELA_GLFW_MINOR);
	glfwWindowHint(GLFW_OPENGL_PROFILE, XELA_PROFILE);
	glfwWindowHint(GLFW_DOUBLEBUFFER, XELA_DOUBLE_BUFFERED);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, XELA_FORWARD_COMPAT);
	glfwWindowHint(GLFW_RESIZABLE, XELA_RESIZABLE);
#ifdef XELA_DEBUG_INIT
	//Print configuration
	std::cout << "[Message][XelaInit] Configured GLFW " << glfwMajor << "." << glfwMinor << "." << glfwRevision << std::endl;
	std::cout << "[Message][XelaInit] ===>| OpenGL Version: " << XELA_GLFW_MAJOR << "." << XELA_GLFW_MINOR << std::endl;
	std::cout << "[Message][XelaInit] ===>| OpenGL Profile: " << XELA_PROFILE << std::endl;
	std::cout << "[Message][XelaInit] ===>| Double Buffered: " << XELA_DOUBLE_BUFFERED << std::endl;
	std::cout << "[Message][XelaInit] ===>| Forward Compatible: " << XELA_FORWARD_COMPAT << std::endl;
	std::cout << "[Message][XelaInit] ===>| Resizable: " << XELA_RESIZABLE << std::endl;
#endif

	initialized = true;
	return true;
}
bool xelaInitGLEW() {
	GLenum err;
	glewExperimental = GL_TRUE;
	//Init GLEW
	err = glewInit();
	if (err != GLEW_OK) {
#ifdef XELA_DEBUG_INIT
		std::cout << "[ERROR][XelaInit] Error initializing GLEW: " << glewGetErrorString(err) << std::endl;
#endif
		return false;
	}
#ifdef XELA_DEBUG_INIT
	//Print glew version
	std::cout << "[Message][XelaInit] Initialized GLEW " << glewGetString(GLEW_VERSION) << std::endl;
#endif
	return true;
}
bool xelaTerminate() {
	glfwTerminate();
	initialized = false;
	return true;
}