#include "XelaCallbacks.h"

void xelaInitCallbacks(GLFWwindow *window) {
	glfwSetFramebufferSizeCallback(window, &xelaFramebufSizeCallback);
	glfwSetKeyCallback(window, &xelaKeyCallback);
	glfwSetMouseButtonCallback(window, &xelaMouseButtonCallback);
	glfwSetCursorPosCallback(window, &xelaCursorPosCallback);
	glfwSetWindowSizeCallback(window, &xelaWindowSizeCallback);
#ifdef XELA_DEBUG_CALLBACKS
	//Print callback functions
	std::cout << "[Message][XelaCallbacks] Initialized the following callbacks: " << std::endl;
	std::cout << "[Message][XelaCallbacks] ===>| GLFW Framebuffer Size Callback: " << &xelaFramebufSizeCallback << std::endl;
	std::cout << "[Message][XelaCallbacks] ===>| GLFW Key Callback: " << &xelaKeyCallback << std::endl;
	std::cout << "[Message][XelaCallbacks] ===>| GLFW Mouse Button Callback: " << &xelaMouseButtonCallback << std::endl;
	std::cout << "[Message][XelaCallbacks] ===>| GLFW Window Size Callback: " << &xelaWindowSizeCallback << std::endl;
#endif
}
void xelaFramebufSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
void xelaKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	xelaAddKeyToBuffer({ key, scancode, action, mods, getXelaWindow(window) });
#ifdef XELA_DEBUG_CALLBACKS
	//Print key event
	std::cout << "[Message][XelaCallbacks] Logged key event: " << std::endl;
	std::cout << "[Message][XelaCallbacks] ===>| Window: <GLFWwindow> " << window << " == <XelaWindow> " << getXelaWindow(window) << " == <Title> " << getXelaWindow(window)->getTitle() << std::endl;
	std::cout << "[Message][XelaCallbacks] ===>| Key: " << key << " (Scancode: " << scancode << ")" << std::endl;
	std::cout << "[Message][XelaCallbacks] ===>| Action: " << action << " (Mods: " << mods << ")" << std::endl;
#endif
}
void xelaMouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	xelaPressMouse({ button, action, mods, getXelaWindow(window) });
#ifdef XELA_DEBUG_CALLBACKS
	//Print mouse event
	std::cout << "[Message][XelaCallbacks] Logged mouse event: " << std::endl;
	std::cout << "[Message][XelaCallbacks] ===>| Window: <GLFWwindow> " << window << " == <XelaWindow> " << getXelaWindow(window) << " == <Title> " << getXelaWindow(window)->getTitle() << std::endl;
	std::cout << "[Message][XelaCallbacks] ===>| Button: " << button << std::endl;
	std::cout << "[Message][XelaCallbacks] ===>| Action: " << action << " (Mods: " << mods << ")" << std::endl;
#endif
}
void xelaCursorPosCallback(GLFWwindow *window, double xpos, double ypos) {
	xelaUpdateCursorPos({ xpos, ypos, getXelaWindow(window) });
#ifdef XELA_DEBUG_CALLBACKS
	//Print cursor position
	std::wcout << "[Message][XelaCallbacks] Logged new cursor position: " << std::endl;
	std::cout << "[Message][XelaCallbacks] ===>| Window: <GLFWwindow> " << window << " == <XelaWindow> " << getXelaWindow(window) << " == <Title> " << getXelaWindow(window)->getTitle() << std::endl;
	std::cout << "[Message][XelaCallbacks] ===>| Position: " << xpos << ", " << ypos << std::endl;
#endif
}
void xelaWindowSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}