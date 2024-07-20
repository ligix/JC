cmake_minimum_required(VERSION 3.28)
project(testing_elf_stuff C)

set(CMAKE_C_STANDARD 11)

add_executable(hello hello.c)
add_executable(read_elf read_elf.c)
