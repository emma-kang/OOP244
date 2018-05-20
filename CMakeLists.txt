cmake_minimum_required(VERSION 3.6)
project(OOP244_final)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES ms5_tester.cpp Date.cpp ErrorState.cpp iProduct.h Perishable.cpp Product.cpp Allocator.cpp)
add_executable(OOP244_final ${SOURCE_FILES})