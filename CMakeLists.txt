cmake_minimum_required(VERSION 3.16)
project(sdl_snake)

set(CMAKE_CXX_STANDARD 14)

set(SDL2_INCLUDE_DIR /usr/include/SDL2)
set(SDL2_LIBRARY /usr/lib/x86_64-linux-gnu/libSDL2-2.0.so)
#set(SDL_IMAGE /usr/lib/x86_64-linux-gnu/libSDL_image-1.2.so.0) #libSDL_image-1.2.so.0 (libc6,x86-64) => /usr/lib/x86_64-linux-gnu/libSDL_image-1.2.so.0
set(SDL2_IMAGE /usr/lib/x86_64-linux-gnu/libSDL2_image-2.0.so.0) #libSDL2_image-2.0.so.0 (libc6,x86-64) => /usr/lib/x86_64-linux-gnu/libSDL2_image-2.0.so.0

include_directories(AFTER /include)

## includes cmake/FindSDL2.cmake
#set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
#
#find_package(SDL2 REQUIRED)
#include_directories(${SDL2_INCLUDE_DIR})

#TODO: use file(GLOB to add headers and sources
add_executable(sdl_snake src/main.cpp include/GameObject.h src/GameObject.cpp src/Image.cpp include/Image.h src/Actor.cpp include/Actor.h include/main.h src/Arrow.cpp src/Arrow.h)

target_include_directories(sdl_snake PUBLIC ${SDL2_INCLUDE_DIR} INCLUDE_DIRECTORIES)
target_link_libraries(sdl_snake ${SDL2_LIBRARY} ${SDL2_IMAGE})