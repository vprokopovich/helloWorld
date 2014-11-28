cmake_minimum_required(VERSION 2.8)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../products/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../products/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../products/bin)

add_subdirectory(helloWorld)
add_subdirectory(stringToNumber)
add_subdirectory(threadPool)
add_subdirectory(typeList)
add_subdirectory(vectorUtility)
add_subdirectory(zadachka)