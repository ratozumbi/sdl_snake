## **Build instructions windows x86:**
> **TOOLS**:
- IDE used CLion 2020.1.2
- Visual Studio Comunity 2017 (for MSVC compiler)
- cmake v3.16.5
- make system: nmake (MSVC x86, bundled with visual studio 2017)
- c/c++ compiler: cl (MSVC x86, bundled with visual studio 2017)
> **INSTRUCTIONS**:
1. Clone repository
2. Install Visual Studio Comunity 2017 with C++ extras

**Option 1:**

- Install CLion 2020.1.2
- Open the cmake project with clion
- make sure to set
File > Settings > Build,Execution > Toolchains
With Visual Studio on the first line (default)

**Option 2:**

- you can set on your PATH to point the default compilers to MSVC and, in the project folder,  run

```cmake.exe -DCMAKE_BUILD_TYPE=Debug -G "CodeBlocks - NMake Makefiles" C:\your\path\sdl_snake```

then build with

`cmake.exe --build C:\your\path\cmake-build-debug --target sdl_snake`

Not Optional:
- Copy dlls files to where you run your .exe


>MAC

I don't own a MAC to test, but you should probably
point SDL2 and SDL2Image librarys and headers for cmake to find.

> LINUX
- Use your package manager to install SDL2-dev and SDL2_image-dev
- Point the installation path in CMakeLists.txt  

The commented lines in cmake should work for Ubuntu/apt-get.

### **Troubleshooting:**
- Build errors:
``Error: could not load cache`` try to run cmake again or check if cmake-build-debug folder exists on the same folder CMakeLists.txt
- Linker errors: check cmake paths for SDL libs.
- Runtime does not start or keeps crashing: check if all DLLs from SDL2/dlls are copied to the exe folder.   