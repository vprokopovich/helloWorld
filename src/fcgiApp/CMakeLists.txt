cmake_minimum_required(VERSION 2.8)
project(Trace)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall") #to turn on c++ 11 features
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--rpath -Wl,${CMAKE_LIBRARY_OUTPUT_DIRECTORY}") #to link with libfcgi

include_directories(../../3rdparty/fcgi-2.4.1-SNAP-0311112127/include) #FastCGI library includes

set(HEADERS
#        CTrace.h
)
set(SOURCES
        main.cpp
)
set(LIBRARIES
		libThreadPool
		fcgi
)

IF(OS_LINUX)
   set(LIBRARIES ${LIBRARIES} pthread)
ENDIF(OS_LINUX)

add_executable(FastCGIApp ${SOURCES} ${HEADERS})
target_link_libraries(FastCGIApp ${LIBRARIES})