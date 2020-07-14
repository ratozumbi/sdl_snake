# This cmake file should be the same as this command
# g++ -I /usr/include/SDL2 ./include/*.h ./src/*.cpp -lSDL2 -lSDL2_image -std=c++11 -o game_file_name
cmake_minimum_required(VERSION 3.12)
# uncomment these lines if not using clion on windows
#set(CMAKE_C_COMPILER "C:/Program Files (x86)/Microsoft Visual Studio/2017/Community/VC/Tools/MSVC/14.16.27023/bin/Hostx86/x86/cl.exe")
#set(CMAKE_CXX_COMPILER "C:/Program Files (x86)/Microsoft Visual Studio/2017/Community/VC/Tools/MSVC/14.16.27023/bin/Hostx86/x86/cl.exe")
#set(CMAKE_MAKE_PROGRAM "C:/Program Files (x86)/Microsoft Visual Studio/2017/Community/VC/Tools/MSVC/14.16.27023/bin/Hostx86/x86/nmake.exe")
#set(CMAKE_C_COMPILER_WORKS TRUE)
#set(CMAKE_CXX_COMPILER_WORKS TRUE)
project(enjoiado)
message("Cmake running on directory ${CMAKE_CURRENT_LIST_DIR} SDL2 folder should be here")
set(CMAKE_CXX_STANDARD 14)


# set(SDL2_INCLUDE_DIR /usr/include/SDL2)
set(SDL2_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/SDL2/include")
# set(SDL2_LIBRARY /usr/lib/x86_64-linux-gnu/libSDL2-2.0.so)
set(SDL2_LIBRARY "${CMAKE_CURRENT_LIST_DIR}/SDL2/x86/SDL2.lib")
set(SDL2_MAIN_LIBRARY "${CMAKE_CURRENT_LIST_DIR}/SDL2/x86/SDL2main.lib")
set(SDL2_TEST_LIBRARY "${CMAKE_CURRENT_LIST_DIR}/SDL2/x86/SDL2test.lib")
# set(SDL2_IMAGE /usr/lib/x86_64-linux-gnu/libSDL2_image-2.0.so.0)
set(SDL2_IMAGE "${CMAKE_CURRENT_LIST_DIR}/SDL2/x86/SDL2_image.lib")

file(GLOB game_source
        "include/*.h"
        "src/*.cpp"
        )

add_executable(enjoiado ${game_source})
include_directories(SYSTEM)
target_include_directories(enjoiado PUBLIC ${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} INCLUDE_DIRECTORIES)
target_link_libraries(enjoiado  ${SDL2_LIBRARY} ${SDL2_MAIN_LIBRARY} ${SDL2_TEST_LIBRARY} ${SDL2_IMAGE})