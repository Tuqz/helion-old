# File: /techdemos/planetarium/CMakeLists.txt
# Author(s): P. Kilgore (ThyLordRoot)
# Since: 1/4/2014

# Collect source files
FILE(GLOB RD_SRC "*.cpp")

# Now compile into a static library (todo: should we also build a shared library?)
include_directories(${DEFAULT_INCS})
add_executable(rocket_design ${RD_SRC})
target_link_libraries(rocket_design ${DEFAULT_LIBS})