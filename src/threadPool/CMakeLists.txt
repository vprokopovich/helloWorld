cmake_minimum_required(VERSION 2.8)
project(ThreadPool)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

set(HEADERS
		ThreadPool.h
        Worker.h
)
set(SOURCES
		main.cpp
        ThreadPool.cpp
		Worker.cpp
)

add_executable(ThreadPool ${HEADERS} ${SOURCES})