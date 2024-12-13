# SDL CMake Template

This template simplifies the setup process for [sdl](https://github.com/libsdl-org/SDL) using CMake FetchContent. It automatically fetches and configures [sdl](https://github.com/libsdl-org/SDL) along with a few optional game development libraries. Fast and easy way to start your game dev journey with [sdl](https://github.com/libsdl-org/SDL) using this straightforward template.

### libraries supported

- [sdl](https://github.com/libsdl-org/SDL) - A simple and easy-to-use library to enjoy videogames programming.
- [ImGui](https://github.com/ocornut/imgui) - Dear ImGui: Bloat-free Graphical User interface for C++ with minimal dependencies.
- [LDtkLoader](https://github.com/Madour/LDtkLoader) - Used to load and help
  with drawing a map made with the awesome [LDtk](https://ldtk.io/).
- [box2d](https://github.com/erincatto/box2d) - Ubiquitous and easy to use 2D
  physics engine.
- [fmt](https://github.com/fmtlib/fmt) - Logging and string formatting library
  that makes your life much easier.
- [bullet3](https://github.com/bulletphysics/bullet3) - 3d physics engine.
- [reactphysics3d](https://github.com/DanielChappuis/ReactPhysics3D) - Open source C++ physics engine library in 3D. - Note Wasm not working
- [JoltPhysics](https://github.com/jrouwe/JoltPhysics) - A multi core friendly rigid body physics and collision detection library, written in C++, suitable for games and VR applications.
- [Physx 5](https://github.com/NVIDIA-Omniverse/PhysX) - NVIDIA PhysX SDK a high performance, real-time physics engine by NVIDIA.

### How to use this template

#### Prerequisites
- [cmake](https://cmake.org/)
- [mingw](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/8.1.0/threads-posix/seh/) or [Visual Studio](https://visualstudio.microsoft.com/) with [Desktop development with c++](https://learn.microsoft.com/en-us/cpp/build/vscpp-step-0-installation?view=msvc-170)
- [Emscripten](https://github.com/emscripten-core/emsdk) (for web build)


### Choosing What libraries to use
```bash
## In CmakeLists.txt edit the following at the top

## Toggle a library with ON or OFF

# library toggles
option(USE_SDL3 "Use SDL3" ON)
option(USE_SDL2 "Use SDL2" OFF)
option(USE_GLAD "Use Glad" OFF)
option(USE_IMGUI "Use ImGui" OFF)
option(USE_LDTKLOADER "Use LDtk Loader" OFF)
option(USE_FMT "Use fmt" OFF)
option(USE_BOX2D "Use Box2D" OFF)
option(USE_BULLET3 "Use Bullet Physics 3D" OFF)
option(USE_REACTPHYSICS3D "Use React Physics 3D" OFF)
option(USE_JOLTPHYSICS "Use Jolt Physics 3D" OFF)
option(USE_PHYSX "Use PhysX" OFF)

```

## Building for Desktop

```bash
## supported windows and linux

## Clone the repository
git clone https://github.com/BrettWilsonBDW/sdl-cmake.git

## Navigate to the project directory
cd sdl-cmake

## Create a build directory
mkdir build

## Navigate to the build directory
cd build

## Run CMake to configure the project
cmake -DCMAKE_BUILD_TYPE=Release ..

## Build the project
cmake --build . --config Release

## The executable is found in the build directory either in the root of the directory or in debug/release file if using msvc
```

## Building for the Web

```bash
## Ensure Emscripten is installed and configured:
## on windows
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk
./emsdk.bat install latest
./emsdk.bat activate latest --permanent

## add emsdk to path ex: C:\Program Files\emsdk

## on linux
cd /usr/local
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk
./emsdk install latest
./emsdk activate latest --permanent

## add emsdk to path

## Navigate to the project directory
cd sdl-cmake

## Change to tools dir
cd tools

## Run the build script for the web
.\build-sdl3-emcc.bat async
## or for sdl2
.\build-sdl3-emcc.bat async

## If emscripten_set_main_loop_arg is set up then just use:
.\build-sdl3-emcc.bat
## or for sdl2
.\build-sdl2-emcc.bat

## This gives much better performance in the web
## Example of how to use emscripten_set_main_loop_arg below

```
##### emscripten_set_main_loop_arg example

```c++
void ClassName::MainLoopHelper(void *userData)
{
    ClassName *className = static_cast<ClassName *>(userData);

    className->Draw(); // call your game functions here
}

// main loop
void ClassName::Run() // Run() is called from a ClassName instance in main
{
#if defined(PLATFORM_WEB)
    emscripten_set_main_loop_arg(MainLoopHelper, this, 0, 1);
#else
    while (!WindowShouldClose())
    {
        MainLoopHelper(this);
    }
#endif

// replace ClassName with the name of your class and function names with your functions
```