
# Ray Tracer

## Platform and Libraries Used

I have used the Windows operating system to build this project, alongwith the following technologies:

- **Libraries for OpenGL:** GLFW and GLEW were used to run the sampleTexture.cpp program provided in the assignment. This allowed for an image to be used as output for the Ray Tracer.

- **MinGW:** MinGW binaries were installed to run the project. The project uses the Clang++ compiler along with the lldb linker.

- **Premake5:** I used premake as a build system for my project since it was easier to build the project with multiple source files and headers.

- **Make:** Premake acts as a makefile generator, and the project can be compiled by using the make package.

- **CImg:** CImg is a C++ library to manipulate and save images on disk. This is used to create an animation with the Ray Tracer.

- **Visual Studio Code:** This was used as an IDE to edit and run the project. The tasks.json and launch.json configuration files were used to automatically run premake5 and then using make to compile the project.

## Compiling Instructions

To compile the project:

- Open the project folder in Visual Studio Code and press F5. This will run the entire compilation process and executes the binary generated. The tasks.json file contains two tasks: 
    1. Run premake5 with the gmake argument to generate a makefile for the project.
    2. Compile the Project using the make command. 
    3. Then, launch.json project simply launches the binary generated after compilation. 
    
    
[Make](https://gnuwin32.sourceforge.net/packages/make.htm) and [Premake5](https://premake.github.io/) are necessary to compile the project. You can try compiling with just Make, but if that does not work, running Premake first may be necessary. 

The C++ compiler and linker can be changed to use **g++** and **gdb** linker instead, by editing these files: premake.lua, tasks.json and launch.json.  

All libraries and include files are provided with the project.
