helion
======

A game where you build rockets and fly around the solar system.


Compiling from Source
=====================

Since 1/4/2014, efforts have been made to make Helion portable. Right now, you can build with LLVM or GCC, and you will need the following dependencies:

* Some OpenGL implementation
* libglu
* libglfw

You will also need to download Kitware's CMake build system (http://www.cmake.org). This will let you generate the files for your preferred build environment. If you want to use the default, simply issue the following command:

$ cmake .

Note that on Windows, multiple generators are available by default. Windows users might consider downloading Code::Blocks 13.12 or greater (http://www.codeblocks.org) and running the following command:

$ cmake . -G "CodeBlocks - MinGW Makefiles" -DCMAKE_CXX_COMPILER=gcc

Tech demos are built optionally if you supply "-DBUILD_TECH_DEMOS=true" to that command. Once you run this the first time, you just need to do "cmake ." to update the makefiles.