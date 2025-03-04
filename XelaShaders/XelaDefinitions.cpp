#include "XelaDefinitions.h"

const char* xelaVertexShaderBarebones =
"#version 330 core\n"
"layout(location = 0) in vec3 aPos;\n"
"\n"
"void main() {\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"};\n";
const char* xelaFragmentShaderBarebones =
"#version 330 core\n"
"out vec4 FragColor;\n"
"\n"
"void main() {\n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n";