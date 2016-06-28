cmake_minimum_required(VERSION 3.3)
project(TA_CoE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES TA_CoE.cpp src/Data.cpp src/Data.h src/Debug.h src/UDP_server.cpp src/UDP_server.h)
include_directories(src)

include_directories(lib/stanford-cpp-library/StanfordCPPLib)
add_subdirectory(lib)

add_executable(TA_CoE ${SOURCE_FILES})
target_link_libraries(TA_CoE StanfordCPPLib)