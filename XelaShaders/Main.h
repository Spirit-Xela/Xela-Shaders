#ifndef _MAIN_H
#define _MAIN_H

//C++
#include <iostream>
#include <string>
#include <vector>
//Engine
#include "XelaWindow.h"
#include "XelaObject.h"
//Xela Shaders
#include "PlatformCode.h"
#include "ShaderHandler.h"

XelaWindow *getwin();
XelaObject *getActor();
int main(int argc, char **argv);

#endif