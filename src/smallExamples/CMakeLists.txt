cmake_minimum_required(VERSION 2.8)
project(SmallExamples)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

set(HEADERS
    ProgramGeneticHW.h
)
set(SOURCES
    ProgramGeneticHW.cpp
    main.cpp
)
set(LIBRARIES

)

add_executable(SmallExamples ${HEADERS} ${SOURCES})
#add_library(libThreadPool STATIC ${SOURCES})
target_link_libraries(SmallExamples ${LIBRARIES})