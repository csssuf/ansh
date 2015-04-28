cmake_minimum_required(VERSION 2.6)

project(ansh)

SET(CMAKE_C_FLAGS_INIT "-Wall -Wextra -Werror -pedantic -std=c11")
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/")

include_directories("include/")
include_directories("mpc/")

add_executable(ansh src/ansh.c mpc/mpc.c)
target_link_libraries(ansh m)
