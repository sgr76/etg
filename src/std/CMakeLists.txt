#
# extra CMake macros
#

list (APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")


#
# extra options for kdevelop
#

include_directories (${CMAKE_SOURCE_DIR}/src)


#
# source files
#

set (SOURCES_STD std_enum.cpp std_factory.cpp std_header.cpp std_implementation.cpp)
set (HEADERS_STD std_enum.hpp std_factory.hpp std_header.hpp std_implementation.hpp)


#
# extra targets
#

add_files_to_parent (SOURCES FILES ${SOURCES_STD})
add_files_to_parent (HEADERS FILES ${HEADERS_STD})
