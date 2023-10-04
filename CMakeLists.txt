cmake_minimum_required(VERSION 3.5)

project (nightlytool)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

set(SOURCES
    source/main.cpp
)

add_executable(nightlytool ${SOURCES})
target_include_directories(nightlytool PRIVATE 
    source
)
