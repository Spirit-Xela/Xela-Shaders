#ifndef _XELA_DEFINITIONS_H
#define _XELA_DEFINITIONS_H

//Data
//=====================================================================
template<typename T>
struct XelaVec2 {
	T x, y;
};
template<typename T>
struct XelaVec3 {
	T x, y, z;
};
template<typename T>
struct XelaVec4 {
	T x, y, z, w;
};
//=====================================================================

//Debug
//=====================================================================
//#define XELA_DEBUG_CALLBACKS
//#define XELA_DEBUG_EVENTS
#define XELA_DEBUG_INIT
#define XELA_DEBUG_WINDOW
#define XELA_DEBUG_SHADER
//=====================================================================

//Shaders
//=====================================================================
typedef void(*XelaShaderCallbackFunction)(unsigned int program);
struct XelaImageInfo {
	const char *name;
	unsigned int id;
};
//=====================================================================

//Init
//=====================================================================
#define XELA_GLFW_MAJOR 3
#define XELA_GLFW_MINOR 3
#define XELA_RESIZABLE GLFW_TRUE
#define XELA_DOUBLE_BUFFERED GLFW_TRUE
#define XELA_FORWARD_COMPAT GLFW_TRUE
#define XELA_PROFILE GLFW_OPENGL_CORE_PROFILE
#define XELA_TRANSPARENT_FRAMEBUFFER GL_TRUE
//=====================================================================

//Errors
//=====================================================================
#define XELA_SUCCESS 1
#define XELA_ERROR_INIT 2
#define XELA_ERROR_WINDOW 3
#define XELA_ERROR_INIT_GLEW 4
//=====================================================================

#endif