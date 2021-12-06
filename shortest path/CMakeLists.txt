cmake_minimum_required(VERSION 3.20)
project(shortest_path)

set(CMAKE_CXX_STANDARD 23)

add_executable(shortest_path main.cpp read_lines.h read_lines.cpp graph.cpp graph.h dijkstra.cpp dijkstra.h)
