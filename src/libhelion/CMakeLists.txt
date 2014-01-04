# File: /CMakeLists:
# Author(s): P. Kilgore (ThyLordRoot)
# Since: 1/4/2014

# Collect source files

FILE(GLOB LIBHELION_SRC "*.cpp")

add_library(helion-core STATIC ${LIBHELION_SRC})