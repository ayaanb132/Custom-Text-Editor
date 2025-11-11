cmake_minimum_required(VERSION 3.10)
project(c_text_editor C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic")

add_executable(c_text_editor kilo.c)
