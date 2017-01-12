project("Algorithms")
cmake_minimum_required(VERSION 3.6)

# Everything is compiled with C++11
set(CMAKE_CXX_STANDARD 11)

include_directories("/usr/local/include")
link_directories("/usr/local/lib")

enable_testing()

add_subdirectory("source")

