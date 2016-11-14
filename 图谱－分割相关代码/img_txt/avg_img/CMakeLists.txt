
cmake_minimum_required(VERSION 2.8)

project(SubsampleVolume)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})
 

add_executable(main AddImageFilter.cpp)
 
target_link_libraries(main ${ITK_LIBRARIES})


