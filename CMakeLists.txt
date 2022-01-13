cmake_minimum_required(VERSION 3.1) 
project(VideoWriter VERSION 1.0)            

# set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_BUILD_TYPE debug)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

set(CMAKE_CXX_COMPILER "/usr/bin/g++-10")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -O3 -Wno-write-strings")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath -Wl,$ORIGIN")
#opencv
find_package(OpenCV REQUIRED)

#main executable
add_executable(orderedWriter videoGenerator.cpp)
target_link_libraries(orderedWriter ${OpenCV_LIBS})
