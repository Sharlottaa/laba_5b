cmake_minimum_required(VERSION 3.20)
project(CLionProjects C)

set(CMAKE_C_STANDARD 11)

add_executable(CLionProjects main.c)

add_subdirectory(libs)
target_link_libraries(CLionProjects data_structures)
target_link_libraries(CLionProjects algorithmis)
