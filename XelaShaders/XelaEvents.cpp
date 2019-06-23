#include "XelaEvents.h"

std::unordered_map<int, KeyInfo> keyBuffer;
std::unordered_map<GLFWwindow *, XelaWindow *> windowList;

XelaKeyCallback keyCB = nullptr;
XelaMouseButtonCallback mouseButtonCB = nullptr;
XelaCursorPosCallback cursorPosCB = nullptr;

void xelaAddWindow(GLFWwindow *key, XelaWindow *window) {
	windowList.emplace(key, window);
}
void xelaAddKeyToBuffer(KeyInfo info) {
	if (keyBuffer.count(info.key)) {
		//Key already exists, update data
		keyBuffer.at(info.key) = info;
	}
	else {
		//Key does not exist, emplace data
		keyBuffer.emplace(info.key, info);
	}
#ifdef XELA_DEBUG_EVENTS
	//Print key
	std::cout << "[Message][XelaEvents] Added key to KeyBuffer: " << info.key << std::endl;
#endif
}
void xelaPressMouse(MouseButtonInfo info) {
	if (mouseButtonCB != nullptr) {
		//Call function
		mouseButtonCB(info.window, info.button, info.action, info.mods);
	}
#ifdef XELA_DEBUG_EVENTS
	//Print button
	std::cout << "[Message][XelaEvents] Processed mouse button: " << info.button << std::endl;
#endif
}
void xelaUpdateCursorPos(CursorPosInfo info) {
	if (cursorPosCB != nullptr) {
		//Call function
		cursorPosCB(info.window, info.xpos, info.ypos);
	}
#ifdef XELA_DEBUG_EVENTS
	//Print button
	std::cout << "[Message][XelaEvents] Processed cursor position: " << info.xpos << ", " << info.ypos << ", " << std::endl;
#endif
}
void xelaProcessEvents() {
	std::unordered_map<int, KeyInfo>::iterator it = keyBuffer.begin(), tmp;
	while (it != keyBuffer.end()) {
		//Call callback
		if (keyCB != nullptr) {
			keyCB(it->second.window, it->second.key, it->second.scancode, it->second.action, it->second.mods);
		}
		//Check for release
		if (it->second.action == GLFW_RELEASE) {
			//Don't repeat this event
			tmp = it;
			tmp++;
			keyBuffer.erase(it);
			it = tmp;
		}
		else {
			it++;
		}
	}
}
void xelaSetKeyCallback(XelaKeyCallback cb) {
	keyCB = cb;
}
void xelaSetMouseButtonCallback(XelaMouseButtonCallback cb) {
	mouseButtonCB = cb;
}
void xelaSetCursorPosCallback(XelaCursorPosCallback cb) {
	cursorPosCB = cb;
}

XelaWindow* getXelaWindow(GLFWwindow *key) {
	if (windowList.count(key))
		return windowList.at(key);
	return nullptr;
}