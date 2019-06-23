# Xela-Shaders
A simple program that displays GLSL shaders as a Windows desktop background

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

* [GLFW 3.3](https://www.glfw.org) - Graphics library used for rendering the window
* [GLEW 2.1](http://glew.sourceforge.net/) - Library used to load OpenGL examples
* [Visual Studio](https://visualstudio.microsoft.com/) - IDE I use. Feel free to use another but the examples here are for VS.

### Installing

1. Download/extract GLFW and GLEW into their own folders.
2. Download/extract this repository into its own folder.
3. Open XelaShaders.sln using Visual Studio.
4. Under solution explorer on the right, right-click the project XelaShaders and select properties.
5. Go to C/C++ -> General
6. Edit Additional Include Directories and add the paths to the GLFW and GLEW include folders.
STEP 6 IMAGE
7. Go to Liner -> General
8. Edit Additional Library Directories and add the paths to the GLFW and GLEW library folders.
STEP 8 IMAGE
9. Go to Linker -> Input
10. Edit Additional Dependencies and add the following:
  * opengl32.lib
  * glfw3.lib
  * glew32.lib
11. Select OK to close the properties window

## Using XelaShaders

When this program is run, if no command line arguments were given, the program will prompt you for the path the the shader directory.
This is the path to the folder where config.txt is located. If a command line argument was given, that argument is assumed to be the
path.

### Config.txt

This file should always be named config.txt (all lowercase). Each line of text in this file may be one of the following:
  * VertexShader <path>   - <path> gives the path to the vertex shader txt relative to config.txt.
  * FragmentShader <path> - <path> gives the path to the fragment shader txt relative to config.txt.
  * FPS <number>          - <number> specifies the maximum fps to use when rendering. Should always be used to save system resources.
  * Monitor <number>      - <number> specifies a monitor to display on. If you have 2 monitors and want to use both, this command
                            should appear twice; once with a 1 and the second time with a 2.
  * Texture <name>=<path> - <name> specifies the name of the uniform in the fragment shader. This should always be a uniform Texture.
                            See the section on the fragment shader for details on the Texture struct.
                            <path> specifies the path to the image file relative to config.txt. This image should always have 4
                            channels (red, green, blue, alpha).
  * Speed <number>        - <number> specified how much to multiply the time uniform by. The time uniform specifies the time in seconds
                            that have passed since the program was started.
  * HideConsole           - Tells the program to hide the console while running the program.
                              
### Fragment Shader 

## Authors

* **Alex Morse** - [Spirit Xela](https://github.com/Spirit-Xela)

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
