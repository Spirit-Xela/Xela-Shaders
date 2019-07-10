# Xela-Shaders
A simple program that displays GLSL shaders as a Windows desktop background

## Installing

This section explains how to setup a compiled version of XelaShaders to use.

1. 

## Setup IDE

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisite

* [GLFW 3.3](https://www.glfw.org) - Graphics library used for rendering the window
* [GLEW 2.1](http://glew.sourceforge.net/) - Library used to load OpenGL examples
* [Visual Studio](https://visualstudio.microsoft.com/) - IDE I use. Feel free to use another but the instructions here are for VS.

### Setup VS

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
  * VertexShader |PATH|   - |PATH| gives the path to the vertex shader txt relative to config.txt.
  * FragmentShader |PATH| - |PATH| gives the path to the fragment shader txt relative to config.txt.
  * FPS |NUMBER|          - |NUMBER| specifies the maximum fps to use when rendering. Should always be used to save system resources.
  * Monitor |NUMBER|      - |NUMBER| specifies a monitor to display on. If you have 2 monitors and want to use both, this command
                            should appear twice; once with a 1 and the second time with a 2.
  * Texture |NAME|=|PATH| - |NAME| specifies the name of the uniform in the fragment shader. This should always be a uniform Texture.
                            See the section on the fragment shader for details on the Texture struct.
                            |PATH| specifies the path to the image file relative to config.txt. This image should always have 4
                            channels (red, green, blue, alpha).
  * Speed |NUMBER|        - |NUMBER| specified how much to multiply the time uniform by. The time uniform specifies the time in seconds
                            that have passed since the program was started.
  * HideConsole           - Tells the program to hide the console while running the program.

### Vertex Shader
The vertex shader is written in GLSL. The input for the vertex shader should be a single vec3 representing a vertex. XelaShaders sends 4 vertices, (-1, -1), (1, -1), (-1, 1), and (1, 1) (The four corners of the screen), and draws 2 triangles to cover the screen.
The vertex shader only needs to set gl_Position. For most shaders, this means all the vertex shader does is set gl_Position to the input. This could be used, however, to change what area of the screen is being drawn on if needed.

### Fragment Shader 
The fragment shader is written in GLSL. The fragment shader must output a vec4 representing the color of a single pixel. XelaShaders sends the following uniforms to the fragment shader:
  * uniform vec2 resolution - The size of the monitor currently being rendered on in pixels
  * uniform vec2 offset     - a vec2 to add to gl_FragCoord to get what coordinate of the pixel on the current monitor.
                              XelaShaders uses a single square to cover all monitors, but renders to each monitor seperately allowing
                              you to render the same image to each monitor rather than having it stretch across all of them.
  * uniform float time      - A float set to the number of seconds that have passed since XelaShaders was launched.
  * uniform Texture |NAME|  - XelaShaders sends a Texture uniform for every texture specified in config.txt.
                              |NAME| is equal to the name specified in config.txt.
                              The Texture struct contains the following variables:
                                * sampler2D tex   - The texture loaded from the file specified in config.txt.
                                * vec2 resolution - The size of the texture in pixels.

## Authors

* **Alex Morse** - [Spirit Xela](https://github.com/Spirit-Xela)

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details
