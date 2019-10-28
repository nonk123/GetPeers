cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(GetPeers CXX)

add_executable(getpeers "")
target_sources(getpeers PRIVATE
  main.cpp
  BencodeParser.cpp)
target_include_directories(getpeers PRIVATE
  .
  external/HTTPRequest/include
  external/cxxopts/include)
set_target_properties(getpeers PROPERTIES CXX_STANDARD 17)
