cmake_minimum_required(VERSION 4.1)
project(sistema_grafos C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

include_directories(.)

add_executable(sistema_grafos
        arvores_dags.c
        basico.c
        buscas.c
        dijkstra.c
        grafo.c
        grafo.h
        main.c
        prim.c
        topologica.c
)
