# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ivan/src/meshSegmetation

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ivan/src/meshSegmetation/build

# Include any dependencies generated for this target.
include CMakeFiles/main.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main.dir/flags.make

CMakeFiles/main.dir/meshSeg.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/meshSeg.o: ../meshSeg.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ivan/src/meshSegmetation/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/main.dir/meshSeg.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/main.dir/meshSeg.o -c /home/ivan/src/meshSegmetation/meshSeg.cpp

CMakeFiles/main.dir/meshSeg.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/meshSeg.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ivan/src/meshSegmetation/meshSeg.cpp > CMakeFiles/main.dir/meshSeg.i

CMakeFiles/main.dir/meshSeg.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/meshSeg.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ivan/src/meshSegmetation/meshSeg.cpp -o CMakeFiles/main.dir/meshSeg.s

CMakeFiles/main.dir/meshSeg.o.requires:
.PHONY : CMakeFiles/main.dir/meshSeg.o.requires

CMakeFiles/main.dir/meshSeg.o.provides: CMakeFiles/main.dir/meshSeg.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/meshSeg.o.provides.build
.PHONY : CMakeFiles/main.dir/meshSeg.o.provides

CMakeFiles/main.dir/meshSeg.o.provides.build: CMakeFiles/main.dir/meshSeg.o

CMakeFiles/main.dir/itkCommandLineArgumentParser.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/itkCommandLineArgumentParser.o: ../itkCommandLineArgumentParser.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ivan/src/meshSegmetation/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/main.dir/itkCommandLineArgumentParser.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/main.dir/itkCommandLineArgumentParser.o -c /home/ivan/src/meshSegmetation/itkCommandLineArgumentParser.cpp

CMakeFiles/main.dir/itkCommandLineArgumentParser.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/itkCommandLineArgumentParser.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ivan/src/meshSegmetation/itkCommandLineArgumentParser.cpp > CMakeFiles/main.dir/itkCommandLineArgumentParser.i

CMakeFiles/main.dir/itkCommandLineArgumentParser.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/itkCommandLineArgumentParser.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ivan/src/meshSegmetation/itkCommandLineArgumentParser.cpp -o CMakeFiles/main.dir/itkCommandLineArgumentParser.s

CMakeFiles/main.dir/itkCommandLineArgumentParser.o.requires:
.PHONY : CMakeFiles/main.dir/itkCommandLineArgumentParser.o.requires

CMakeFiles/main.dir/itkCommandLineArgumentParser.o.provides: CMakeFiles/main.dir/itkCommandLineArgumentParser.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/itkCommandLineArgumentParser.o.provides.build
.PHONY : CMakeFiles/main.dir/itkCommandLineArgumentParser.o.provides

CMakeFiles/main.dir/itkCommandLineArgumentParser.o.provides.build: CMakeFiles/main.dir/itkCommandLineArgumentParser.o

CMakeFiles/main.dir/DCELVertex.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/DCELVertex.o: ../DCELVertex.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ivan/src/meshSegmetation/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/main.dir/DCELVertex.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/main.dir/DCELVertex.o -c /home/ivan/src/meshSegmetation/DCELVertex.cpp

CMakeFiles/main.dir/DCELVertex.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/DCELVertex.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ivan/src/meshSegmetation/DCELVertex.cpp > CMakeFiles/main.dir/DCELVertex.i

CMakeFiles/main.dir/DCELVertex.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/DCELVertex.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ivan/src/meshSegmetation/DCELVertex.cpp -o CMakeFiles/main.dir/DCELVertex.s

CMakeFiles/main.dir/DCELVertex.o.requires:
.PHONY : CMakeFiles/main.dir/DCELVertex.o.requires

CMakeFiles/main.dir/DCELVertex.o.provides: CMakeFiles/main.dir/DCELVertex.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/DCELVertex.o.provides.build
.PHONY : CMakeFiles/main.dir/DCELVertex.o.provides

CMakeFiles/main.dir/DCELVertex.o.provides.build: CMakeFiles/main.dir/DCELVertex.o

CMakeFiles/main.dir/DCELHalfEdge.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/DCELHalfEdge.o: ../DCELHalfEdge.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ivan/src/meshSegmetation/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/main.dir/DCELHalfEdge.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/main.dir/DCELHalfEdge.o -c /home/ivan/src/meshSegmetation/DCELHalfEdge.cpp

CMakeFiles/main.dir/DCELHalfEdge.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/DCELHalfEdge.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ivan/src/meshSegmetation/DCELHalfEdge.cpp > CMakeFiles/main.dir/DCELHalfEdge.i

CMakeFiles/main.dir/DCELHalfEdge.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/DCELHalfEdge.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ivan/src/meshSegmetation/DCELHalfEdge.cpp -o CMakeFiles/main.dir/DCELHalfEdge.s

CMakeFiles/main.dir/DCELHalfEdge.o.requires:
.PHONY : CMakeFiles/main.dir/DCELHalfEdge.o.requires

CMakeFiles/main.dir/DCELHalfEdge.o.provides: CMakeFiles/main.dir/DCELHalfEdge.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/DCELHalfEdge.o.provides.build
.PHONY : CMakeFiles/main.dir/DCELHalfEdge.o.provides

CMakeFiles/main.dir/DCELHalfEdge.o.provides.build: CMakeFiles/main.dir/DCELHalfEdge.o

CMakeFiles/main.dir/DCELFace.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/DCELFace.o: ../DCELFace.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ivan/src/meshSegmetation/build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/main.dir/DCELFace.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/main.dir/DCELFace.o -c /home/ivan/src/meshSegmetation/DCELFace.cpp

CMakeFiles/main.dir/DCELFace.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/DCELFace.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ivan/src/meshSegmetation/DCELFace.cpp > CMakeFiles/main.dir/DCELFace.i

CMakeFiles/main.dir/DCELFace.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/DCELFace.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ivan/src/meshSegmetation/DCELFace.cpp -o CMakeFiles/main.dir/DCELFace.s

CMakeFiles/main.dir/DCELFace.o.requires:
.PHONY : CMakeFiles/main.dir/DCELFace.o.requires

CMakeFiles/main.dir/DCELFace.o.provides: CMakeFiles/main.dir/DCELFace.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/DCELFace.o.provides.build
.PHONY : CMakeFiles/main.dir/DCELFace.o.provides

CMakeFiles/main.dir/DCELFace.o.provides.build: CMakeFiles/main.dir/DCELFace.o

CMakeFiles/main.dir/DCELMesh.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/DCELMesh.o: ../DCELMesh.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ivan/src/meshSegmetation/build/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/main.dir/DCELMesh.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/main.dir/DCELMesh.o -c /home/ivan/src/meshSegmetation/DCELMesh.cpp

CMakeFiles/main.dir/DCELMesh.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/DCELMesh.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ivan/src/meshSegmetation/DCELMesh.cpp > CMakeFiles/main.dir/DCELMesh.i

CMakeFiles/main.dir/DCELMesh.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/DCELMesh.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ivan/src/meshSegmetation/DCELMesh.cpp -o CMakeFiles/main.dir/DCELMesh.s

CMakeFiles/main.dir/DCELMesh.o.requires:
.PHONY : CMakeFiles/main.dir/DCELMesh.o.requires

CMakeFiles/main.dir/DCELMesh.o.provides: CMakeFiles/main.dir/DCELMesh.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/DCELMesh.o.provides.build
.PHONY : CMakeFiles/main.dir/DCELMesh.o.provides

CMakeFiles/main.dir/DCELMesh.o.provides.build: CMakeFiles/main.dir/DCELMesh.o

CMakeFiles/main.dir/Vector.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/Vector.o: ../Vector.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ivan/src/meshSegmetation/build/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/main.dir/Vector.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/main.dir/Vector.o -c /home/ivan/src/meshSegmetation/Vector.cpp

CMakeFiles/main.dir/Vector.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/Vector.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ivan/src/meshSegmetation/Vector.cpp > CMakeFiles/main.dir/Vector.i

CMakeFiles/main.dir/Vector.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/Vector.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ivan/src/meshSegmetation/Vector.cpp -o CMakeFiles/main.dir/Vector.s

CMakeFiles/main.dir/Vector.o.requires:
.PHONY : CMakeFiles/main.dir/Vector.o.requires

CMakeFiles/main.dir/Vector.o.provides: CMakeFiles/main.dir/Vector.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/Vector.o.provides.build
.PHONY : CMakeFiles/main.dir/Vector.o.provides

CMakeFiles/main.dir/Vector.o.provides.build: CMakeFiles/main.dir/Vector.o

CMakeFiles/main.dir/HalfEdgeList.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/HalfEdgeList.o: ../HalfEdgeList.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ivan/src/meshSegmetation/build/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/main.dir/HalfEdgeList.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/main.dir/HalfEdgeList.o -c /home/ivan/src/meshSegmetation/HalfEdgeList.cpp

CMakeFiles/main.dir/HalfEdgeList.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/HalfEdgeList.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ivan/src/meshSegmetation/HalfEdgeList.cpp > CMakeFiles/main.dir/HalfEdgeList.i

CMakeFiles/main.dir/HalfEdgeList.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/HalfEdgeList.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ivan/src/meshSegmetation/HalfEdgeList.cpp -o CMakeFiles/main.dir/HalfEdgeList.s

CMakeFiles/main.dir/HalfEdgeList.o.requires:
.PHONY : CMakeFiles/main.dir/HalfEdgeList.o.requires

CMakeFiles/main.dir/HalfEdgeList.o.provides: CMakeFiles/main.dir/HalfEdgeList.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/HalfEdgeList.o.provides.build
.PHONY : CMakeFiles/main.dir/HalfEdgeList.o.provides

CMakeFiles/main.dir/HalfEdgeList.o.provides.build: CMakeFiles/main.dir/HalfEdgeList.o

CMakeFiles/main.dir/DCELTools.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/DCELTools.o: ../DCELTools.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ivan/src/meshSegmetation/build/CMakeFiles $(CMAKE_PROGRESS_9)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/main.dir/DCELTools.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/main.dir/DCELTools.o -c /home/ivan/src/meshSegmetation/DCELTools.cpp

CMakeFiles/main.dir/DCELTools.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/DCELTools.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ivan/src/meshSegmetation/DCELTools.cpp > CMakeFiles/main.dir/DCELTools.i

CMakeFiles/main.dir/DCELTools.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/DCELTools.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ivan/src/meshSegmetation/DCELTools.cpp -o CMakeFiles/main.dir/DCELTools.s

CMakeFiles/main.dir/DCELTools.o.requires:
.PHONY : CMakeFiles/main.dir/DCELTools.o.requires

CMakeFiles/main.dir/DCELTools.o.provides: CMakeFiles/main.dir/DCELTools.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/DCELTools.o.provides.build
.PHONY : CMakeFiles/main.dir/DCELTools.o.provides

CMakeFiles/main.dir/DCELTools.o.provides.build: CMakeFiles/main.dir/DCELTools.o

CMakeFiles/main.dir/utils.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/utils.o: ../utils.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ivan/src/meshSegmetation/build/CMakeFiles $(CMAKE_PROGRESS_10)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/main.dir/utils.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/main.dir/utils.o -c /home/ivan/src/meshSegmetation/utils.cpp

CMakeFiles/main.dir/utils.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/utils.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ivan/src/meshSegmetation/utils.cpp > CMakeFiles/main.dir/utils.i

CMakeFiles/main.dir/utils.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/utils.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ivan/src/meshSegmetation/utils.cpp -o CMakeFiles/main.dir/utils.s

CMakeFiles/main.dir/utils.o.requires:
.PHONY : CMakeFiles/main.dir/utils.o.requires

CMakeFiles/main.dir/utils.o.provides: CMakeFiles/main.dir/utils.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/utils.o.provides.build
.PHONY : CMakeFiles/main.dir/utils.o.provides

CMakeFiles/main.dir/utils.o.provides.build: CMakeFiles/main.dir/utils.o

# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/meshSeg.o" \
"CMakeFiles/main.dir/itkCommandLineArgumentParser.o" \
"CMakeFiles/main.dir/DCELVertex.o" \
"CMakeFiles/main.dir/DCELHalfEdge.o" \
"CMakeFiles/main.dir/DCELFace.o" \
"CMakeFiles/main.dir/DCELMesh.o" \
"CMakeFiles/main.dir/Vector.o" \
"CMakeFiles/main.dir/HalfEdgeList.o" \
"CMakeFiles/main.dir/DCELTools.o" \
"CMakeFiles/main.dir/utils.o"

# External object files for target main
main_EXTERNAL_OBJECTS =

main: CMakeFiles/main.dir/meshSeg.o
main: CMakeFiles/main.dir/itkCommandLineArgumentParser.o
main: CMakeFiles/main.dir/DCELVertex.o
main: CMakeFiles/main.dir/DCELHalfEdge.o
main: CMakeFiles/main.dir/DCELFace.o
main: CMakeFiles/main.dir/DCELMesh.o
main: CMakeFiles/main.dir/Vector.o
main: CMakeFiles/main.dir/HalfEdgeList.o
main: CMakeFiles/main.dir/DCELTools.o
main: CMakeFiles/main.dir/utils.o
main: CMakeFiles/main.dir/build.make
main: /home/ivan/src/ITK-build452/lib/libitkdouble-conversion-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libitksys-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libitkvnl_algo-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libitkvnl-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libitkv3p_netlib-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKCommon-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libitkNetlibSlatec-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKStatistics-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKIOImageBase-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKMesh-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libitkzlib-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKMetaIO-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKSpatialObjects-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKPath-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKLabelMap-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKQuadEdgeMesh-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKOptimizers-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKPolynomials-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKBiasCorrection-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKBioCell-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKFFT-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKDICOMParser-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKEXPAT-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKIOXML-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKIOSpatialObjects-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKFEM-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libitkopenjpeg-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libitkgdcmDICT-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libitkgdcmMSFF-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKznz-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKniftiio-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKgiftiio-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libitkhdf5_cpp-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libitkhdf5-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKIOBMP-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKIOBioRad-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKIOCSV-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKIOGDCM-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKIOIPL-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKIOGE-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKIOGIPL-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKIOHDF5-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libitkjpeg-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKIOJPEG-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libitktiff-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKIOTIFF-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKIOLSM-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKIOMRC-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKIOMesh-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKIOMeta-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKIONIFTI-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKNrrdIO-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKIONRRD-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libitkpng-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKIOPNG-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKIOSiemens-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKIOStimulate-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKIOTransformBase-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKIOTransformHDF5-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKIOTransformInsightLegacy-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKIOTransformMatlab-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKIOVTK-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKKLMRegionGrowing-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKVTK-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKWatersheds-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKReview-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKVideoCore-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKVideoIO-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKVtkGlue-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKgiftiio-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKLabelMap-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKQuadEdgeMesh-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKBiasCorrection-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKPolynomials-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKBioCell-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKFFT-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKIOSpatialObjects-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKIOXML-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKFEM-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKOptimizers-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKIOBMP-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKIOBioRad-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKIOGDCM-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libitkgdcmMSFF-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libitkopenjpeg-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libitkgdcmDICT-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libitkgdcmIOD-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKEXPAT-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libitkgdcmDSED-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libitkgdcmCommon-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKIOGIPL-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKIOJPEG-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKIOTIFF-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libitktiff-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libitkjpeg-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKIOMeta-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKMetaIO-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKIONIFTI-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKniftiio-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKznz-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKIONRRD-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKNrrdIO-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKIOPNG-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libitkpng-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKIOSiemens-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKIOGE-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKIOIPL-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKIOStimulate-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKIOTransformHDF5-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libitkhdf5_cpp-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libitkhdf5-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libitkzlib-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKIOTransformInsightLegacy-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKIOTransformMatlab-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKIOTransformBase-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKIOVTK-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKKLMRegionGrowing-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKWatersheds-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKSpatialObjects-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKMesh-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKPath-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKStatistics-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libitkNetlibSlatec-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKIOImageBase-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKVideoCore-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKVTK-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKCommon-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libitkdouble-conversion-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libitksys-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libITKVNLInstantiation-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libitkvnl_algo-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libitkv3p_lsqr-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libitkvnl-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libitkvcl-4.5.so.1
main: /home/ivan/src/ITK-build452/lib/libitkv3p_netlib-4.5.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkImagingStatistics-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkFiltersProgrammable-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkRenderingLOD-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkIOVideo-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkFiltersTexture-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkRenderingFreeTypeOpenGL-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkFiltersSelection-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkWrappingTools-6.0.a
main: /home/ivan/src/VTK-build6/lib/libvtkIOImport-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkIOParallel-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkIONetCDF-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkIOExport-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkRenderingGL2PS-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkgl2ps-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkFiltersFlowPaths-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkIOMINC-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkNetCDF_cxx-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkIOSQL-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtksqlite-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkIOExodus-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkexoIIc-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkNetCDF-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkFiltersVerdict-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkverdict-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkRenderingHybridOpenGL-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkRenderingVolumeAMR-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkRenderingVolumeOpenGL-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkImagingMath-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkIOEnSight-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkIOAMR-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkhdf5_hl-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkhdf5-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkFiltersAMR-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkDomainsChemistry-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkFiltersGeneric-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkFiltersParallelImaging-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkFiltersParallel-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkParallelCore-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkFiltersHyperTree-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkIOPLY-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkViewsContext2D-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkInteractionImage-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkRenderingImage-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkImagingStencil-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkLocalExample-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkIOLSDyna-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkChartsCore-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkCommonColor-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkImagingMorphological-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkIOMovie-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkoggtheora-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkIOInfovis-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkIOLegacy-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtklibxml2-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkViewsGeovis-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkViewsInfovis-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkRenderingContext2D-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkFiltersImaging-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkRenderingLabel-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkGeovisCore-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkRenderingOpenGL-6.0.so.1
main: /usr/lib/i386-linux-gnu/libGLU.so
main: /usr/lib/libXNVCtrl.a
main: /usr/lib/i386-linux-gnu/libSM.so
main: /usr/lib/i386-linux-gnu/libICE.so
main: /usr/lib/i386-linux-gnu/libX11.so
main: /usr/lib/i386-linux-gnu/libXext.so
main: /usr/lib/i386-linux-gnu/libXt.so
main: /home/ivan/src/VTK-build6/lib/libvtkIOXML-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkIOGeometry-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkjsoncpp-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkInfovisLayout-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkInfovisCore-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkViewsCore-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkInteractionWidgets-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkFiltersHybrid-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkFiltersModeling-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkImagingGeneral-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkImagingSources-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkImagingHybrid-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkInteractionStyle-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkRenderingAnnotation-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkImagingColor-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkRenderingFreeType-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkftgl-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkfreetype-6.0.so.1
main: /usr/lib/i386-linux-gnu/libGL.so
main: /home/ivan/src/VTK-build6/lib/libvtkRenderingVolume-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkRenderingCore-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkFiltersExtraction-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkFiltersStatistics-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkImagingFourier-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkImagingCore-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkalglib-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkFiltersGeometry-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkFiltersSources-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkFiltersGeneral-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkFiltersCore-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkCommonComputationalGeometry-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkIOImage-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkDICOMParser-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkmetaio-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkpng-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtktiff-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkjpeg-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkIOXMLParser-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkIOCore-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkCommonExecutionModel-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkCommonDataModel-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkCommonSystem-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkCommonTransforms-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkCommonMisc-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkCommonMath-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkCommonCore-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtksys-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkzlib-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkexpat-6.0.so.1
main: /home/ivan/src/VTK-build6/lib/libvtkproj4-6.0.so.1
main: CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable main"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/main.dir/build: main
.PHONY : CMakeFiles/main.dir/build

CMakeFiles/main.dir/requires: CMakeFiles/main.dir/meshSeg.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/itkCommandLineArgumentParser.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/DCELVertex.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/DCELHalfEdge.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/DCELFace.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/DCELMesh.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/Vector.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/HalfEdgeList.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/DCELTools.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/utils.o.requires
.PHONY : CMakeFiles/main.dir/requires

CMakeFiles/main.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/main.dir/cmake_clean.cmake
.PHONY : CMakeFiles/main.dir/clean

CMakeFiles/main.dir/depend:
	cd /home/ivan/src/meshSegmetation/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ivan/src/meshSegmetation /home/ivan/src/meshSegmetation /home/ivan/src/meshSegmetation/build /home/ivan/src/meshSegmetation/build /home/ivan/src/meshSegmetation/build/CMakeFiles/main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/main.dir/depend

