cmake_minimum_required(VERSION 2.8)
project(TA_CoE)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    # require at least gcc 4.7
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.7)
        message(FATAL_ERROR "GCC version must be at least 4.7!")
    endif()
endif ()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES TA_CoE.cpp
        src/Data.cpp src/Data.h
        src/Telnet_server.cpp src/Telnet_server.h
        src/CoE_server.cpp src/CoE_server.h
        src/Utils.cpp src/Utils.h)

include_directories(src)

include_directories(lib/easyloggingpp/src)
include_directories(lib/stanford-cpp-library/StanfordCPPLib)
add_subdirectory(lib)

add_executable(TA_CoE ${SOURCE_FILES})
target_link_libraries(TA_CoE StanfordCPPLib pthread)