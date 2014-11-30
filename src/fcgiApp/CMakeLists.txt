cmake_minimum_required(VERSION 2.8)
project(Trace)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall") #to turn on c++ 11 features
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--rpath -Wl,${CMAKE_LIBRARY_OUTPUT_DIRECTORY}") #to link with libfcgi

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

#foreach (LIBRARY ${LIBRARIES})
#    find_library("${LIBRARY}_FOUND" ${LIBRARY})
#    message(STATUS "Check the ${LIBRARY} is installed: " ${${LIBRARY}_FOUND})
#    if ( "${${LIBRARY}_FOUND}" STREQUAL "${LIBRARY}_FOUND-NOTFOUND" )
#        message(STATUS "Adding library sources")
#        add_subdirectory (../${LIBRARY} lib/${LIBRARY})
#    endif ()
#endforeach ()

IF(OS_LINUX)
   set(LIBRARIES ${LIBRARIES} pthread)
ENDIF(OS_LINUX)

add_executable(FastCGIApp ${SOURCES} ${HEADERS})
target_link_libraries(FastCGIApp ${LIBRARIES})