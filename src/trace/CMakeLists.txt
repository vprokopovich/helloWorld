cmake_minimum_required(VERSION 2.8)
project(Trace)

set(HEADERS
        CTrace.h
)
set(SOURCES
        CTrace.cpp
)

add_library(Trace STATIC ${SOURCES})
