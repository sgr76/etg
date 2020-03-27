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

set (SOURCES_QT5 qt5_enum.cpp qt5_factory.cpp qt5_header.cpp qt5_implementation.cpp)
set (HEADERS_QT5 qt5_enum.hpp qt5_factory.hpp qt5_header.hpp qt5_implementation.hpp)


#
# extra targets
#

add_files_to_parent (SOURCES FILES ${SOURCES_QT5})
add_files_to_parent (HEADERS FILES ${HEADERS_QT5})
