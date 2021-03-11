cmake_minimum_required(VERSION 3.10)

project(JPNN)

add_subdirectory(libs)

add_executable(john main.c)

target_link_libraries(john PUBLIC libs)

target_include_directories(john PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/libs")