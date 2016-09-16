cmake_minimum_required(VERSION 3.6)
project(ioalg_project1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp InputStreamA.h InputStreamA.cpp OutputStreamA.h OutputStreamA.cpp OutputStreamB.cpp OutputStreamB.h)

add_executable(ioalg_project1 ${SOURCE_FILES})