Build instructions windows x86:

IDE used CLion 2020.1.2
Visual Studio Comunity 2017 (for MSVC compiler)
cmake v3.16.5
make system: nmake (MSVC x86, bundled with visual studio 2017)
c/c++ compiler: cl (MSVC x86, bundled with visual studio 2017)

-1)Clone repository to C:/dev

0) Install Visual Studio Comunity 2017

1)Option 1:

Install CLion 2020.1.2
Open the cmake project with clion
make sure to set
File > Settings > Build,Execution > Toolchains
With Visual Studio on the first line (default)

1)Option 2:
you can set on your PATH to point the default compilers to MSVC and run
cmake.exe --build C:\dev\sdl_snake\cmake-build-debug --target sdl_snake

2)Copy dlls files to where you run your .exe

3)Select START, not QUIT

I don't own a MAC to test, but you should probably
point SDL2 and SDL2Image librarys and headers for cmake to find
The commented lines works for LINUX

