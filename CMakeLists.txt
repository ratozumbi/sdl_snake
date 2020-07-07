# This cmake file should be the same as this command
# g++ -I /usr/include/SDL2 ./include/*.h ./src/*.cpp -lSDL2 -lSDL2_image -std=c++11 -o game_file_name
cmake_minimum_required(VERSION 3.12)
project(game)

set(CMAKE_CXX_STANDARD 14)
# set(SDL2_INCLUDE_DIR /usr/include/SDL2)
set(SDL2_INCLUDE_DIR "C:/dev/sdl_snake/SDL2/include")
# set(SDL2_LIBRARY /usr/lib/x86_64-linux-gnu/libSDL2-2.0.so)
set(SDL2_LIBRARY "C:/dev/sdl_snake/SDL2/x86/SDL2.lib")
set(SDL2_MAIN_LIBRARY "C:/dev/sdl_snake/SDL2/x86/SDL2main.lib")
set(SDL2_TEST_LIBRARY "C:/dev/sdl_snake/SDL2/x86/SDL2test.lib")
# set(SDL2_IMAGE /usr/lib/x86_64-linux-gnu/libSDL2_image-2.0.so.0)
set(SDL2_IMAGE "C:/dev/sdl_snake/SDL2/x86/SDL2_image.lib")

file(GLOB game_source
        "include/*.h"
        "src/*.cpp"
        )

add_executable(sdl_snake ${game_source} src/Pice.cpp include/Pice.h src/Board.cpp include/Board.h)

target_include_directories(sdl_snake PUBLIC ${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} INCLUDE_DIRECTORIES)
target_link_libraries(sdl_snake  ${SDL2_LIBRARY} ${SDL2_MAIN_LIBRARY} ${SDL2_TEST_LIBRARY} ${SDL2_IMAGE})