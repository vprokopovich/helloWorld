cmake_minimum_required(VERSION 2.8)
project(HelloWorld)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

find_package(Boost COMPONENTS program_options REQUIRED)
if(NOT Boost_FOUND)
    message(SEND_ERROR "Failed to find boost::program_options.")
    return()
else()
    include_directories(${Boost_INCLUDE_DIRS})
endif()

set(HEADERS
	ExampleBase.h
)
set(SOURCES
	ExampleOptional.h
	ExampleProgramOptions.h
	ExampleAny.h
	main.cpp
)
set(LIBRARIES
	${Boost_LIBRARIES}
)

add_executable(helloWorld ${HEADERS} ${SOURCES})

target_link_libraries(helloWorld ${LIBRARIES})