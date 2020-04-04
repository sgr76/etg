#
# extra CMake macros
#

list (APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

#find_package (ProjectMacros)


#
# extra options for kdevelop
#

include_directories (${CMAKE_SOURCE_DIR}/src)


#
# source files
#

set (SOURCES_QT5 qt5_enum_ns.cpp qt5_factory_ns.cpp qt5_header_ns.cpp qt5_implementation_ns.cpp)
set (HEADERS_QT5 qt5_enum_ns.hpp qt5_factory_ns.hpp qt5_header_ns.hpp qt5_implementation_ns.hpp)


#
# extra targets
#

add_files_to_parent (SOURCES FILES ${SOURCES_QT5})
add_files_to_parent (HEADERS FILES ${HEADERS_QT5})
