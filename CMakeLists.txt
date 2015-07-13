cmake_minimum_required(VERSION 3.0)

project(ansh)

#SET(CMAKE_C_COMPILER "/usr/bin/clang")
#SET(CMAKE_AR "/usr/bin/llvm-ar")
#SET(CMAKE_LINKER "/usr/bin/llvm-ld")
#SET(CMAKE_NM "/usr/bin/llvm-nm")
#SET(CMAKE_OBJDUMP "/usr/bin/llvm-objdump")
#SET(CMAKE_RANLIB "/usr/bin/llvm-ranlib")

SET(CMAKE_C_FLAGS "-Wall -Wextra -Werror -pedantic -std=c11 -D_GNU_SOURCE=1")
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/")
SET(CMAKE_EXPORT_COMPILE_COMMANDS 1)

include_directories("include/" "mpc/")
include_directories(SYSTEM "Octothorpe/include")

add_library(Octothorpe STATIC Octothorpe/src/octo/hash.c
    Octothorpe/src/octo/carry.c Octothorpe/src/octo/cll.c
    Octothorpe/src/octo/keygen.c Octothorpe/src/octo/loa.c)
target_include_directories(Octothorpe SYSTEM PUBLIC "Octothorpe/include")

add_executable(ansh src/ansh.c mpc/mpc.c)
target_link_libraries(ansh m Octothorpe)
