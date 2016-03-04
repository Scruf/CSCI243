cmake_minimum_required(VERSION 3.3)
project(WildFire)

set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")

set(SOURCE_FILES main.c)
add_executable(WildFire ${SOURCE_FILES})