cmake_minimum_required(VERSION 2.8)
project(Measures)

add_definitions(-DOPTIMIZATION_FLAG="$ENV{OPTIMIZATION_FLAG}")

MESSAGE( STATUS "OPTIMIZATION_FLAG: " $ENV{OPTIMIZATION_FLAG} )

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_BUILD_ARCH 64)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 $ENV{OPTIMIZATION_FLAG}")

# turning on SSE instructions explicitly for linux
if (UNIX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse2")
endif (UNIX)

include_directories("../heap")

set(HEADERS
	logging.h
	ITest.h
	Test1PrefixPostfix.h
	Test2TryCatch.h
	Test3SIMD.h
	Test4CycleOptimizations.h
	Test5BranchPrediction.h
	#TestZCycleOptimizations.h
)
set(SOURCES
	main.cpp
	Test1PrefixPostfix.cpp
	Test2TryCatch.cpp
	Test3SIMD.cpp
	Test4CycleOptimizations.cpp
	Test5BranchPrediction.cpp
	#TestZCycleOptimizations.cpp
)
set(LIBRARIES
)

add_executable(measures ${HEADERS} ${SOURCES})

# no libs at the moment
#target_link_libraries(measures ${LIBRARIES})

