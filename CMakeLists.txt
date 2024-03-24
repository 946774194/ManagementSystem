cmake_minimum_required(VERSION 3.26)
project(ManagementSystem C)
set(CMAKE_C_STANDARD 11)

file(GLOB_RECURSE SRC_DIR_LIST
        "./Test/*.c" "./Test/*.h" "./Utils/*.c" "./Utils/*.h"
        "./poco/*.c" "./poco/*.h" "./Mapper/*.c" "./Mapper/*.h"
        "./include/*.h" "./Service/*.c" "./Service/*.h"
        "./Controller/*.c" "./Controller/*.h" "./file/*.c" "./file/*.h" )

add_executable(ManagementSystem ${SRC_DIR_LIST} main.c)

#-Wall
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fexec-charset=GBK")