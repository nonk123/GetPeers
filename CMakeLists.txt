cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(GetPeers CXX)

add_executable(GetPeers main.cpp)
target_include_directories(GetPeers PRIVATE . external/HTTPRequest/include)
