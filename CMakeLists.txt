cmake_minimum_required(VERSION 3.20)
project(prog_alap1_nhz C)

set(CMAKE_C_STANDARD 99)

add_executable(prog_alap1_nhz buszjaratok.c ido.c ido.h megallo.c megallo.h jarat.c jarat.h utvonal.c utvonal.h)
