#include "PlatformCode.h"

std::vector<MonitorInfo> monitorList;
int maxX = 0, maxY = 0;

#ifdef _WIN32
void setShaderWindowParent(HWND shaderWindow) {
	bool search = true;
	HWND curr = NULL, child = NULL;
	//Find program manager and send message to create extra WorkerW window
	child = FindWindowEx(NULL, NULL, "Progman", "Program Manager");
	SendMessageTimeout(child, WORKERW_MESSAGE, 0, 0, SMTO_NORMAL, 1000, NULL);
	//Find the new WorkerW window
	while (search) {
		curr = FindWindowEx(NULL, curr, "WorkerW", NULL);
		child = FindWindowEx(curr, NULL, "SHELLDLL_DefView", NULL);
		if (child != NULL) {
			search = false;
		}
	}
	//Go one more WorkerW down and set that as the parent
	child = FindWindowEx(NULL, curr, "WorkerW", NULL);
	SetParent(shaderWindow, child);
}
#endif

void setupWindow(XelaWindow *win) {
	int count, minX = 0, minY = 0;
	GLFWmonitor** monitors;
	const GLFWvidmode* mode;

	//Get all monitors
	monitors = glfwGetMonitors(&count);
	//Store the lowest/highest x/y coordinate of any monitor and store each monitor's specs
	for (int i = 0; i < count; i++) {
		int x, y;
		glfwGetMonitorPos(monitors[i], &x, &y);
		if (x < minX)
			minX = x;
		if (y < minY)
			minY = y;

		mode = glfwGetVideoMode(monitors[i]);
		if (x + mode->width > maxX)
			maxX = x + mode->width;
		if (y + mode->height > maxY)
			maxY = y + mode->height;

		monitorList.push_back({ x, y, mode->width, mode->height });
	}
	//Update the x/y position so that the lowest x/y value is (0, 0)
	for (int i = 0; i < count; i++) {
		monitorList[i].x -= minX;
		monitorList[i].y -= minY;
	}

	//Windows code
#ifdef _WIN32
	HWND window = glfwGetWin32Window(win->getGLFWwindow());
	//Allow the window to be transparent and ensure no input is sent to the window
	LONG curr = GetWindowLong(window, GWL_EXSTYLE);
	SetWindowLong(window, GWL_EXSTYLE, curr | WS_EX_TRANSPARENT | WS_EX_LAYERED);
	//Set the windows parent to desktop then reposition/resize it to cover all monitors
	setShaderWindowParent(window);
	SetWindowPos(window, HWND_BOTTOM, 0, 0, maxX - minX, maxY - minY, SWP_NOACTIVATE);
#endif
}

void delay(double sec) {
	//Windows code
#ifdef _WIN32
	Sleep(sec * 1000);
#endif
}

void hideConsole() {
#ifdef _WIN32
	//Hide the console
	ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif
}

std::vector<MonitorInfo> getMonitorList() {
	return monitorList;
}

int getMaxX() {
	return maxX;
}
int getMaxY() {
	return maxY;
}