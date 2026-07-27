cmake_minimum_required(VERSION 4.1)
project(sistema_grafos C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(sistema_grafos
        arvores_dags.c
        basico.c
        buscas.c
        grafo.c
        grafo.h
        topologica.c
        prim.c)
