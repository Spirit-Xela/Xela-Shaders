#include "XelaWindow.h"
#include "XelaEvents.h"
#include "XelaCallbacks.h"

XelaWindow::XelaWindow(int sizeX, int sizeY, const char *title, bool fullscreen, int *success, XelaWindow* share) {
	int errCode, windowSizeX, windowSizeY;
	const char *errMsg;
	winTitle = title;

	//Call GLEW/GLFW Init
	if (xelaInit()) {
		*success = XELA_SUCCESS;
	}
	else {
		*success = XELA_ERROR_INIT;
#ifdef XELA_DEBUG_WINDOW
		//Print error
		std::cout << "[ERROR][XelaWindow] Error initializing engine" << std::endl;
#endif
		return;
	}
	//Create a window object
	monitor = glfwGetPrimaryMonitor();
	mode = glfwGetVideoMode(monitor);
	if (sizeX < 0) {
		sizeX = mode->width;
	}
	if (sizeY < 0) {
		sizeY = mode->height;
	}
	window = glfwCreateWindow(sizeX, sizeY, title, fullscreen ? monitor : NULL, share == nullptr ? NULL : share->getGLFWwindow());
	if (window == NULL) {
		//Error occurred
#ifdef XELA_DEBUG_WINDOW
		//Print error
		errCode = glfwGetError(&errMsg);
		std::cout << "[ERROR][XelaWindow] GLFW Error occurred on window creation (" << errCode << "): " << errMsg << std::endl;
#endif
		*success = XELA_ERROR_WINDOW;
		return;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	//Setup callback functions
	xelaInitCallbacks(window);
	glfwGetFramebufferSize(window, &windowSizeX, &windowSizeY);
	glViewport(0, 0, windowSizeX, windowSizeY);
#ifdef XELA_DEBUG_WINDOW
	std::cout << "[Message][XelaInit] Initialized callback functions" << std::endl;
#endif
#ifdef XELA_DEBUG_WINDOW
	//Print window attributes
	std::cout << "[Mesaage][XelaWindow] Window created with the following configuration: " << std::endl;
	std::cout << "[Message][XelaWindow] ===>| Size: " << sizeX << ", " << sizeY << std::endl;
	std::cout << "[Message][XelaWindow] ===>| Title: " << title << std::endl;
	std::cout << "[Message][XelaWindow] ===>| Fullscreen: " << fullscreen << std::endl;
	std::cout << "[Message][XelaWindow] Window created with the following GLFW attributes: " << std::endl;
	std::cout << "[Message][XelaWindow] ===>| Window related attributes: " << std::endl;
	std::cout << "[Message][XelaWindow] ===>| ===>| Focused: " << glfwGetWindowAttrib(window, GLFW_FOCUSED) << std::endl;
	std::cout << "[Message][XelaWindow] ===>| ===>| Iconified: " << glfwGetWindowAttrib(window, GLFW_ICONIFIED) << std::endl;
	std::cout << "[Message][XelaWindow] ===>| ===>| Maximized: " << glfwGetWindowAttrib(window, GLFW_MAXIMIZED) << std::endl;
	std::cout << "[Message][XelaWindow] ===>| ===>| Hovered: " << glfwGetWindowAttrib(window, GLFW_HOVERED) << std::endl;
	std::cout << "[Message][XelaWindow] ===>| ===>| Visible: " << glfwGetWindowAttrib(window, GLFW_VISIBLE) << std::endl;
	std::cout << "[Message][XelaWindow] ===>| ===>| Resizable: " << glfwGetWindowAttrib(window, GLFW_RESIZABLE) << std::endl;
	std::cout << "[Message][XelaWindow] ===>| ===>| Decorated: " << glfwGetWindowAttrib(window, GLFW_DECORATED) << std::endl;
	std::cout << "[Message][XelaWindow] ===>| ===>| Auto Iconify: " << glfwGetWindowAttrib(window, GLFW_AUTO_ICONIFY) << std::endl;
	std::cout << "[Message][XelaWindow] ===>| ===>| Floating: " << glfwGetWindowAttrib(window, GLFW_FLOATING) << std::endl;
	std::cout << "[Message][XelaWindow] ===>| ===>| Transparent Framebuffer: " << glfwGetWindowAttrib(window, GLFW_TRANSPARENT_FRAMEBUFFER) << std::endl;
	std::cout << "[Message][XelaWindow] ===>| ===>| Focus on Show: " << glfwGetWindowAttrib(window, GLFW_FOCUS_ON_SHOW) << std::endl;
	std::cout << "[Message][XelaWindow] ===>| Context related attributes: " << std::endl;
	std::cout << "[Message][XelaWindow] ===>| ===>| Client API: " << (glfwGetWindowAttrib(window, GLFW_CLIENT_API) == GLFW_OPENGL_API ? "OpenGL API" : glfwGetWindowAttrib(window, GLFW_CLIENT_API) == GLFW_OPENGL_ES_API ? "OpenGL ES API" : "No API") << std::endl;
	std::cout << "[Message][XelaWindow] ===>| ===>| Context Creation API: " << (glfwGetWindowAttrib(window, GLFW_CONTEXT_CREATION_API) == GLFW_NATIVE_CONTEXT_API ? "Native Context API" : glfwGetWindowAttrib(window, GLFW_CONTEXT_CREATION_API) == GLFW_EGL_CONTEXT_API ? "EGL Context API" : "Osmesa Context API") << std::endl;
	std::cout << "[Message][XelaWindow] ===>| ===>| Context Version: " << glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MAJOR) << "." << glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MINOR) << "." << glfwGetWindowAttrib(window, GLFW_CONTEXT_REVISION) << std::endl;
	std::cout << "[Message][XelaWindow] ===>| ===>| OpenGL Forward Compatibility: " << glfwGetWindowAttrib(window, GLFW_OPENGL_FORWARD_COMPAT) << std::endl;
	std::cout << "[Message][XelaWindow] ===>| ===>| OpenGL Debug Context: " << glfwGetWindowAttrib(window, GLFW_OPENGL_DEBUG_CONTEXT) << std::endl;
	std::cout << "[Message][XelaWindow] ===>| ===>| OpenGL Profile: " << (glfwGetWindowAttrib(window, GLFW_OPENGL_PROFILE) == GLFW_OPENGL_CORE_PROFILE ? "OpenGL Core Profile" : glfwGetWindowAttrib(window, GLFW_OPENGL_PROFILE) == GLFW_OPENGL_COMPAT_PROFILE ? "OpenGL Compat Profile" : "OpenGL Any Profile") << std::endl;
	std::cout << "[Message][XelaWindow] ===>| ===>| Context Robustness: " << (glfwGetWindowAttrib(window, GLFW_CONTEXT_ROBUSTNESS) == GLFW_LOSE_CONTEXT_ON_RESET ? "Lose Context on Reset" : glfwGetWindowAttrib(window, GLFW_CONTEXT_ROBUSTNESS) == GLFW_NO_RESET_NOTIFICATION ? "No Reset Notification" : "No Robustness") << std::endl;
	std::cout << "[Message][XelaWindow] Window created with the following size: " << std::endl;
	std::cout << "[Message][XelaWindow] ===>| Framebuffer size: " << windowSizeX << ", " << windowSizeY << std::endl;
	glfwGetWindowSize(window, &windowSizeX, &windowSizeY);
	std::cout << "[Message][XelaWindow] ===>| Window size: " << windowSizeX << ", " << windowSizeY << std::endl;
#endif
	//Call second init
	if (xelaInitGLEW()) {
		*success = XELA_SUCCESS;
	}
	else {
		*success = XELA_ERROR_INIT_GLEW;
#ifdef XELA_DEBUG_WINDOW
		//Print error
		std::cout << "[ERROR][XelaWindow] Error initializing GLEW" << std::endl;
#endif
		return;
	}
	xelaAddWindow(window, this);
	//Set clear color
	glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
	//Enable depth testing
	glEnable(GL_DEPTH_TEST);
	//Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#ifdef XELA_DEBUG_WINDOW
	std::cout << "[Message][XelaWindow] Set " << winTitle << " clear color to: " << clearColor.x << ", " << clearColor.y << ", " << clearColor.z << ", " << clearColor.w << std::endl;
#endif
}
XelaWindow::XelaWindow(int sizeX, int sizeY, const char* title, bool fullscreen, int* success, bool decorated, XelaWindow* share) {
	int errCode, windowSizeX, windowSizeY;
	const char* errMsg;
	winTitle = title;

	//Call GLEW/GLFW Init
	if (xelaInit()) {
		*success = XELA_SUCCESS;
	}
	else {
		*success = XELA_ERROR_INIT;
#ifdef XELA_DEBUG_WINDOW
		//Print error
		std::cout << "[ERROR][XelaWindow] Error initializing engine" << std::endl;
#endif
		return;
	}
	//Create a window object
	monitor = glfwGetPrimaryMonitor();
	mode = glfwGetVideoMode(monitor);
	if (sizeX < 0) {
		sizeX = mode->width;
	}
	if (sizeY < 0) {
		sizeY = mode->height;
	}
	glfwWindowHint(GLFW_DECORATED, decorated);
	window = glfwCreateWindow(sizeX, sizeY, title, fullscreen ? monitor : NULL, share == nullptr ? NULL : share->getGLFWwindow());
	if (window == NULL) {
		//Error occurred
#ifdef XELA_DEBUG_WINDOW
		//Print error
		errCode = glfwGetError(&errMsg);
		std::cout << "[ERROR][XelaWindow] GLFW Error occurred on window creation (" << errCode << "): " << errMsg << std::endl;
#endif
		* success = XELA_ERROR_WINDOW;
		return;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	//Setup callback functions
	xelaInitCallbacks(window);
	glfwGetFramebufferSize(window, &windowSizeX, &windowSizeY);
	glViewport(0, 0, windowSizeX, windowSizeY);
#ifdef XELA_DEBUG_WINDOW
	std::cout << "[Message][XelaInit] Initialized callback functions" << std::endl;
#endif
#ifdef XELA_DEBUG_WINDOW
	//Print window attributes
	std::cout << "[Mesaage][XelaWindow] Window created with the following configuration: " << std::endl;
	std::cout << "[Message][XelaWindow] ===>| Size: " << sizeX << ", " << sizeY << std::endl;
	std::cout << "[Message][XelaWindow] ===>| Title: " << title << std::endl;
	std::cout << "[Message][XelaWindow] ===>| Fullscreen: " << fullscreen << std::endl;
	std::cout << "[Message][XelaWindow] Window created with the following GLFW attributes: " << std::endl;
	std::cout << "[Message][XelaWindow] ===>| Window related attributes: " << std::endl;
	std::cout << "[Message][XelaWindow] ===>| ===>| Focused: " << glfwGetWindowAttrib(window, GLFW_FOCUSED) << std::endl;
	std::cout << "[Message][XelaWindow] ===>| ===>| Iconified: " << glfwGetWindowAttrib(window, GLFW_ICONIFIED) << std::endl;
	std::cout << "[Message][XelaWindow] ===>| ===>| Maximized: " << glfwGetWindowAttrib(window, GLFW_MAXIMIZED) << std::endl;
	std::cout << "[Message][XelaWindow] ===>| ===>| Hovered: " << glfwGetWindowAttrib(window, GLFW_HOVERED) << std::endl;
	std::cout << "[Message][XelaWindow] ===>| ===>| Visible: " << glfwGetWindowAttrib(window, GLFW_VISIBLE) << std::endl;
	std::cout << "[Message][XelaWindow] ===>| ===>| Resizable: " << glfwGetWindowAttrib(window, GLFW_RESIZABLE) << std::endl;
	std::cout << "[Message][XelaWindow] ===>| ===>| Decorated: " << glfwGetWindowAttrib(window, GLFW_DECORATED) << std::endl;
	std::cout << "[Message][XelaWindow] ===>| ===>| Auto Iconify: " << glfwGetWindowAttrib(window, GLFW_AUTO_ICONIFY) << std::endl;
	std::cout << "[Message][XelaWindow] ===>| ===>| Floating: " << glfwGetWindowAttrib(window, GLFW_FLOATING) << std::endl;
	std::cout << "[Message][XelaWindow] ===>| ===>| Transparent Framebuffer: " << glfwGetWindowAttrib(window, GLFW_TRANSPARENT_FRAMEBUFFER) << std::endl;
	std::cout << "[Message][XelaWindow] ===>| ===>| Focus on Show: " << glfwGetWindowAttrib(window, GLFW_FOCUS_ON_SHOW) << std::endl;
	std::cout << "[Message][XelaWindow] ===>| Context related attributes: " << std::endl;
	std::cout << "[Message][XelaWindow] ===>| ===>| Client API: " << (glfwGetWindowAttrib(window, GLFW_CLIENT_API) == GLFW_OPENGL_API ? "OpenGL API" : glfwGetWindowAttrib(window, GLFW_CLIENT_API) == GLFW_OPENGL_ES_API ? "OpenGL ES API" : "No API") << std::endl;
	std::cout << "[Message][XelaWindow] ===>| ===>| Context Creation API: " << (glfwGetWindowAttrib(window, GLFW_CONTEXT_CREATION_API) == GLFW_NATIVE_CONTEXT_API ? "Native Context API" : glfwGetWindowAttrib(window, GLFW_CONTEXT_CREATION_API) == GLFW_EGL_CONTEXT_API ? "EGL Context API" : "Osmesa Context API") << std::endl;
	std::cout << "[Message][XelaWindow] ===>| ===>| Context Version: " << glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MAJOR) << "." << glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MINOR) << "." << glfwGetWindowAttrib(window, GLFW_CONTEXT_REVISION) << std::endl;
	std::cout << "[Message][XelaWindow] ===>| ===>| OpenGL Forward Compatibility: " << glfwGetWindowAttrib(window, GLFW_OPENGL_FORWARD_COMPAT) << std::endl;
	std::cout << "[Message][XelaWindow] ===>| ===>| OpenGL Debug Context: " << glfwGetWindowAttrib(window, GLFW_OPENGL_DEBUG_CONTEXT) << std::endl;
	std::cout << "[Message][XelaWindow] ===>| ===>| OpenGL Profile: " << (glfwGetWindowAttrib(window, GLFW_OPENGL_PROFILE) == GLFW_OPENGL_CORE_PROFILE ? "OpenGL Core Profile" : glfwGetWindowAttrib(window, GLFW_OPENGL_PROFILE) == GLFW_OPENGL_COMPAT_PROFILE ? "OpenGL Compat Profile" : "OpenGL Any Profile") << std::endl;
	std::cout << "[Message][XelaWindow] ===>| ===>| Context Robustness: " << (glfwGetWindowAttrib(window, GLFW_CONTEXT_ROBUSTNESS) == GLFW_LOSE_CONTEXT_ON_RESET ? "Lose Context on Reset" : glfwGetWindowAttrib(window, GLFW_CONTEXT_ROBUSTNESS) == GLFW_NO_RESET_NOTIFICATION ? "No Reset Notification" : "No Robustness") << std::endl;
	std::cout << "[Message][XelaWindow] Window created with the following size: " << std::endl;
	std::cout << "[Message][XelaWindow] ===>| Framebuffer size: " << windowSizeX << ", " << windowSizeY << std::endl;
	glfwGetWindowSize(window, &windowSizeX, &windowSizeY);
	std::cout << "[Message][XelaWindow] ===>| Window size: " << windowSizeX << ", " << windowSizeY << std::endl;
#endif
	//Call second init
	if (xelaInitGLEW()) {
		*success = XELA_SUCCESS;
	}
	else {
		*success = XELA_ERROR_INIT_GLEW;
#ifdef XELA_DEBUG_WINDOW
		//Print error
		std::cout << "[ERROR][XelaWindow] Error initializing GLEW" << std::endl;
#endif
		return;
	}
	xelaAddWindow(window, this);
	//Set clear color
	glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
	//Enable depth testing
	glEnable(GL_DEPTH_TEST);
	//Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#ifdef XELA_DEBUG_WINDOW
	std::cout << "[Message][XelaWindow] Set " << winTitle << " clear color to: " << clearColor.x << ", " << clearColor.y << ", " << clearColor.z << ", " << clearColor.w << std::endl;
#endif
}
XelaWindow::~XelaWindow() {
	glfwDestroyWindow(window);
	xelaTerminate();
}

void XelaWindow::update() {
	glfwSwapBuffers(window);
	glfwPollEvents();
	xelaProcessEvents();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void XelaWindow::setShouldClose(bool close) {
	glfwSetWindowShouldClose(window, close);
#ifdef XELA_DEBUG_WINDOW
	//Print new close state
	std::cout << "[Message][XelaWindow] Updated " << winTitle << " should close to " << close << std::endl;
#endif
}
void XelaWindow::setClearColor(XelaVec4<float> rgba) {
	glClearColor(rgba.x, rgba.y, rgba.z, rgba.w);
	clearColor = rgba;
#ifdef XELA_DEBUG_WINDOW
	std::cout << "[Message][XelaWindow] Set " << winTitle << " clear color to: " << clearColor.x << ", " << clearColor.y << ", " << clearColor.z << ", " << clearColor.w << std::endl;
#endif
}
void XelaWindow::setSize(int sizeX, int sizeY) {
	glfwSetWindowSize(window, sizeX, sizeY);
#ifdef XELA_DEBUG_WINDOW
	std::cout << "[Message][XelaWindow] Set " << winTitle << " size to: " << sizeX << ", " << sizeY << std::endl;
#endif
}
void XelaWindow::maximize() {
	int windowSizeX, windowSizeY;
	glfwMaximizeWindow(window);
#ifdef XELA_DEBUG_WINDOW
	std::cout << "[Message][XelaWindow] Maximized " << winTitle << std::endl;
	glfwGetFramebufferSize(window, &windowSizeX, &windowSizeY);
	std::cout << "[Message][XelaWindow] New framebuffer size: " << windowSizeX << ", " << windowSizeY << std::endl;
	glfwGetWindowSize(window, &windowSizeX, &windowSizeY);
	std::cout << "[Message][XelaWindow] New window size: " << windowSizeX << ", " << windowSizeY << std::endl;
#endif
}

bool XelaWindow::shouldClose() {
	return glfwWindowShouldClose(window);
}
void XelaWindow::getSize(int *width, int *height) {
	glfwGetWindowSize(window, width, height);
}
void XelaWindow::getResolution(int *width, int *height) {
	glfwGetFramebufferSize(window, width, height);
}
double XelaWindow::getTime() {
	return glfwGetTime();
}
const char *XelaWindow::getTitle() {
	return winTitle;
}
GLFWwindow *XelaWindow::getGLFWwindow() {
	return window;
}