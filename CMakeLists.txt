cmake_minimum_required(VERSION 2.6)

project(ansh)

include_directories("include/")
include_directories("mpc/")

add_executable(ansh src/ansh.c mpc/mpc.c)
