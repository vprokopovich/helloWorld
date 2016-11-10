cmake_minimum_required(VERSION 2.8)

include(${CMAKE_SOURCE_DIR}/../buildconfig/detectOS.cmake)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../products/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../products/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../products/bin)

include_directories(trace)
#include_directories(threadPool)
#include_directories(../3rdparty/jsoncpp-src-0.5.0/include)
#include_directories(../3rdparty/fcgi-2.4.1-SNAP-0311112127/include) #FastCGI library includes

#add_subdirectory(../3rdparty/fcgi-2.4.1-SNAP-0311112127/libfcgi ./libfcgi)
#add_subdirectory(../3rdparty/jsoncpp-src-0.5.0 ./libjsoncpp)
#add_subdirectory(helloWorld)
#add_subdirectory(stringToNumber)
add_subdirectory(threadPool)
#add_subdirectory(typeList)
#add_subdirectory(vectorUtility)
#add_subdirectory(zadachka)
add_subdirectory(trace)
#add_subdirectory(fcgiApp)
#add_subdirectory(firebaseHelloWorld/backend)
#add_subdirectory(smallExamples)
add_subdirectory(heap)
add_subdirectory(helloOpenCV)
add_subdirectory(measures)