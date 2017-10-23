cmake_minimum_required(VERSION 3.8)
project(MyfirstClionProject)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES myArray.cpp linkedList.cpp arraySearch.cpp arraySort.cpp binaryTree.cpp myString.cpp myMath.cpp dp.cpp dfs.cpp stackAndQueue.cpp Singleton.cpp greedy.cpp)
add_executable(MyfirstClionProject ${SOURCE_FILES})