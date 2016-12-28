cmake_minimum_required(VERSION 2.8)
project(HelloOpenCV)

# Currently building OpenCV project only under Windows
if (MSVC)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


set(OPENCV_DIR A:/Workspace/3rdParty/opencv/install)   # not really a good idea to use absolute path. but now its OK

# TODO: remove this shit:
#include_directories(${OPENCV_DIR}/build/include)
#include_directories(${OPENCV_DIR}/include)
#link_directories(${OPENCV_DIR}/x86/vc14/lib/)
#link_directories(${OPENCV_DIR}/myBuild/lib/Debug/)
#link_directories(${OPENCV_DIR}/myBuild/install/x86/vc14/lib/)
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${OPENCV_DIR}/sources/cmake/")
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${OPENCV_DIR})
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules)

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${OPENCV_DIR})



#MESSAGE( STATUS "CMAKE_PREFIX_PATH:         " ${CMAKE_PREFIX_PATH} )

FIND_PACKAGE(OpenCV REQUIRED)

set(HEADERS
		example1.h
		example2.h
)
set(SOURCES
        main.cpp
		example1.cpp
		example2.cpp
)
set(LIBRARIES
        opencv_imgproc2413d.lib
        opencv_highgui2413d.lib
        opencv_objdetect2413d.lib
)

MESSAGE( STATUS "OPENCV_DIR:         " ${OPENCV_DIR} )
MESSAGE( STATUS "OpenCV_LIB_DIR_OPT:         " ${OpenCV_LIB_DIR_OPT} )

add_executable(helloOpenCV ${HEADERS} ${SOURCES})

TARGET_LINK_LIBRARIES(helloOpenCV ${OpenCV_LIBS})
#target_link_libraries(helloOpenCV ${OpenCV_LIBS} ${LIBRARIES})


MACRO (COPY_DLL trgt libname)
        ADD_CUSTOM_COMMAND (
        TARGET ${trgt}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND}
        ARGS -E copy "${OpenCV_LIB_DIR_OPT}/../bin/${libname}.dll" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE}"
    )
ENDMACRO (COPY_DLL)

COPY_DLL(helloOpenCV opencv_imgproc2413d)
COPY_DLL(helloOpenCV opencv_highgui2413d)
COPY_DLL(helloOpenCV opencv_objdetect2413d)
COPY_DLL(helloOpenCV opencv_core2413d)
COPY_DLL(helloOpenCV opencv_calib3d2413d)
COPY_DLL(helloOpenCV opencv_flann2413d)
COPY_DLL(helloOpenCV opencv_features2d2413d)


endif (MSVC)