cmake_minimum_required(VERSION 3.22)
project(DA)

set(CMAKE_CXX_STANDARD 11)

add_executable(DA
        code/main.cpp code/Graph.cpp code/Supervisor.cpp
        code/Menu.cpp code/VertexEdge.cpp
        )
