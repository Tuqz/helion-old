# File: /src/libhelion/CMakeLists.txt
# Author(s): P. Kilgore (ThyLordRoot)
# Since: 1/4/2014

# Collect source files
FILE(GLOB LIBHELION_SRC "*.cpp")

# Now compile into a static library (todo: should we also build a shared library?)
add_library(helion-core STATIC ${LIBHELION_SRC})