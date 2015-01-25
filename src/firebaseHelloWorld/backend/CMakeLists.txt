cmake_minimum_required(VERSION 2.8)
project(FirebaseHelloWorld)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

#set(HEADERS
#	ExampleBase.h
#)
set(SOURCES
	main.cpp
)
set(LIBRARIES
	curl
	jsoncpp
)

add_executable(firebaseHelloWorld ${HEADERS} ${SOURCES})

target_link_libraries(firebaseHelloWorld ${LIBRARIES})