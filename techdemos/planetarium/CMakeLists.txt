# File: /techdemos/planetarium/CMakeLists.txt
# Author(s): P. Kilgore (ThyLordRoot)
# Since: 1/4/2014

# Collect source files
FILE(GLOB PLANETARIUM_SRC "*.cpp")

# Now compile into a static library (todo: should we also build a shared library?)
include_directories(${DEFAULT_INCS})
add_executable(planetarium ${PLANETARIUM_SRC})
target_link_libraries(planetarium ${DEFAULT_LIBS})