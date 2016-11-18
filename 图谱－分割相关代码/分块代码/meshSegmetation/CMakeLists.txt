# This is the root ITK CMakeLists file.
cmake_minimum_required(VERSION 2.4)
if(COMMAND CMAKE_POLICY)
  cmake_policy(SET CMP0003 NEW)
endif()


# This project is designed to be built outside the Insight source tree.
project(HelloWorld)

# Find ITK.
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})



add_executable( main meshSeg.cpp itkCommandLineArgumentParser.cpp
				DCELVertex.cpp DCELHalfEdge.cpp DCELFace.cpp DCELMesh.cpp 
	            Vector.cpp HalfEdgeList.cpp DCELTools.cpp utils.cpp) 

target_link_libraries(main ${ITK_LIBRARIES})
