# File: /CMakeLists:
# Author: P. Kilgore (ThyLordRoot)
# Since: 1/4/2014

# Set up project 
PROJECT(helion)

# Setup any local flags we need, like C++11 support
IF (CMAKE_COMPILER_CXX_IS_GNUCXX)
	ADD_DEFINITIONS("-std=c++0x")
ELSEIF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	ADD_DEFINITIONS("-std=c++11")
ELSE()
	ERROR("Helion requires C++11 support");
ENDIF()

