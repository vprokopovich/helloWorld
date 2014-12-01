cmake_minimum_required(VERSION 2.8)
project(fcgi)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

include_directories(../)
include_directories(../include/)

set(HEADERS
)
set(SOURCES
		fcgi_stdio.c
        fcgiapp.c
		fcgio.cpp
		os_unix.c
		#os_win32.c
)

SET(CMAKE_INSTALL_RPATH "${CMAKE_BINARY_DIR}/../products/lib")

#add_library(libfcgi STATIC ${SOURCES})
add_library(fcgi SHARED ${SOURCES})