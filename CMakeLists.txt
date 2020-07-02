# This cmake file should be the same as this command
# g++ -I /usr/include/SDL2 ./include/*.h ./src/*.cpp -lSDL2 -lSDL2_image -std=c++11 -o game_file_name
cmake_minimum_required(VERSION 3.16)
project(game)

set(CMAKE_CXX_STANDARD 14)

set(SDL2_INCLUDE_DIR /usr/include/SDL2)
set(SDL2_LIBRARY /usr/lib/x86_64-linux-gnu/libSDL2-2.0.so)
set(SDL2_IMAGE /usr/lib/x86_64-linux-gnu/libSDL2_image-2.0.so.0)

file(GLOB game_source
        "include/*.h"
        "src/*.cpp"
        )

add_executable(sdl_snake ${game_source})

target_include_directories(sdl_snake PUBLIC ${SDL2_INCLUDE_DIR} INCLUDE_DIRECTORIES)
target_link_libraries(sdl_snake ${SDL2_LIBRARY} ${SDL2_IMAGE})