cmake_minimum_required(VERSION 3.1) 
project(VideoWriter VERSION 1.0)            

#Change to you compiler path
set(CMAKE_CXX_COMPILER "/usr/bin/g++-10") 
#Select C++ preferred version C++14 works fine too
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -O3 -Wno-write-strings")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath -Wl,$ORIGIN")
#opencv
find_package(OpenCV REQUIRED)

#main executable
add_executable(orderedWriter videoGenerator.cpp)
target_link_libraries(orderedWriter ${OpenCV_LIBS})
