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

set (SOURCES_STD std_enum_ns.cpp std_factory_ns.cpp std_header_ns.cpp std_implementation_ns.cpp)
set (HEADERS_STD std_enum_ns.hpp std_factory_ns.hpp std_header_ns.hpp std_implementation_ns.hpp)


#
# extra targets
#

add_files_to_parent (SOURCES FILES ${SOURCES_STD})
add_files_to_parent (HEADERS FILES ${HEADERS_STD})
