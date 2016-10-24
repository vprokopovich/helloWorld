cmake_minimum_required(VERSION 2.8)
project(Measures)

#O0 O1 O2 O3 Og
#SET(OPTIMIZATION_FLAG "/O2")
add_definitions(-DOPTIMIZATION_FLAG="$ENV{OPTIMIZATION_FLAG}")

MESSAGE( STATUS "OPTIMIZATION_FLAG: " $ENV{OPTIMIZATION_FLAG} )

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_BUILD_ARCH 64)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 $ENV{OPTIMIZATION_FLAG}")

include_directories("../heap")

set(HEADERS
	#../heap/measurements.h
	logging.h
	ITest.h
	Test1prefixPostfix.h
	TestZCycleOptimizations.h
)
set(SOURCES
	main.cpp
	test1prefixPostfix.cpp
	TestZCycleOptimizations.cpp
)
set(LIBRARIES
)

add_executable(measures ${HEADERS} ${SOURCES})

# no libs at the moment
#target_link_libraries(measures ${LIBRARIES})
