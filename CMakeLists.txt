cmake_minimum_required(VERSION 3.16)

project(Vendors)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_BUILD_TYPE Debug)

add_executable(main.out main.cpp)

target_include_directories(main.out PRIVATE "." "include" $ENV{CADMIUM})

target_compile_options(main.out PUBLIC -std=gnu++2b)

