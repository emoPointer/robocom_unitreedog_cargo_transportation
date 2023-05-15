cmake_minimum_required(VERSION 3.10)
project(ultraSound)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
#link_directories(lib)

add_executable(ultraSound main.cpp)
target_link_libraries(ultraSound libultraSound_SDK.so)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
