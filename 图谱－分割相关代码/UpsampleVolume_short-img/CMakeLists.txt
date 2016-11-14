
cmake_minimum_required(VERSION 2.8)

project(UpsampleVolume)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})
 

add_executable(main UpsampleVolume_short.cpp)
 
target_link_libraries(main ${ITK_LIBRARIES})


