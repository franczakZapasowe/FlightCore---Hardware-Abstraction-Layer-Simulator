cmake_minimum_required(VERSION 3.10)
project(FlightCore)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(${PROJECT_NAME} main.cpp
        pamiecIMU.cpp
        pamiecIMU.h)

target_compile_options(${PROJECT_NAME} PRIVATE
-Wall
-Wextra
-pedantic
-Werror)


