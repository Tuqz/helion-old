# File: /CMakeLists.txt
# Author(s): P. Kilgore (ThyLordRoot)
# Since: 1/4/2014

# Set up project 
PROJECT(helion C CXX)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# A place for external contributions to go
FILE(MAKE_DIRECTORY external)
FILE(MAKE_DIRECTORY external/cmake/)
SET(CMAKE_MODULE_PATH "external/cmake/")

# Setup any local flags we need, like C++11 support
IF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	SET(CXX11_FLAG "-std=c++0x")
ELSEIF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	SET(CXX11_FLAG "-std=c++11")
ENDIF()

# No compliant compiler was found
IF(NOT CXX11_FLAG)
	MESSAGE(FATAL_ERROR "Helion requires C++11 support (found ${CMAKE_CXX_COMPILER_ID}-${CMAKE_CXX_COMPILER_VERSION}). Please use a compliant compiler.")
ELSE()
	ADD_DEFINITIONS(${CXX11_FLAG})
ENDIF()

# We need to find OpenGL
find_package(OpenGL REQUIRED)
IF (NOT OPENGL_FOUND)
	MESSAGE(FATAL_ERROR "OpenGL is required to build Helion.")
ELSEIF (NOT OPENGL_GLU_FOUND)
	MESSAGE(FATAL_ERROR "GLU is required to build Helion.")
ELSE()
	INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIRS})
ENDIF()

# See if we can find glfw
IF (NOT GLFW_FOUND)
	IF (NOT EXISTS "external/cmake/FindGLFW.cmake")
		# Download Pixar's handly finder script for GLFW3
		FILE(DOWNLOAD "https://raw.github.com/PixarAnimationStudios/OpenSubdiv/master/cmake/FindGLFW.cmake"
			"external/cmake/FindGLFW.cmake")
	ENDIF()
	
	# Make sure there's a fallback location	
	SET(GLFW_LOCATION "${PROJECT_SOURCE_DIR}/external/glfw")
	find_package(GLFW)
ENDIF()

# Must have GLFW
IF (NOT GLFW_FOUND)
	MESSAGE(FATAL_ERROR "GLFW is required to build Helion. Please extract the latest binary release into external/glfw")
ENDIF()

# Includes
SET(LIBHELION_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/src/libhelion/")
SET(LIBHELIOCENTRIC_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/src/libheliocentric/")
SET(DEFAULT_INCS ${OPENGL_INCLUDE_DIR} ${GLFW_INCLUDE_DIR} ${LIBHELION_INCLUDE_DIR} ${LIBHELIOCENTRIC_INCLUDE_DIR})

# libhelion MUST come first, since it has unresolved syms that break the linker
SET(DEFAULT_LIBS "helion-core" ${OPENGL_LIBRARIES} ${GLFW_LIBRARIES})
# libhelion must come first
ADD_SUBDIRECTORY(src/libhelion)

# Check to see if we are building tech demos
IF(BUILD_TECH_DEMOS)
	MESSAGE(STATUS "Tech demos will be included in this build.")
	ADD_SUBDIRECTORY(techdemos/planetarium)
	ADD_SUBDIRECTORY(techdemos/rocket_design)
	ADD_SUBDIRECTORY(techdemos/ship_flight)
	ADD_SUBDIRECTORY(techdemos/engine_test)
ENDIF()
