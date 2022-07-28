cmake_minimum_required (VERSION 3.2)

project (etg)
enable_testing ()


#
# extra CMake macros
#

list (APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

find_package (ProjectMacros)

enabled_uncrustify ()


#
# options
#

set (CMAKE_INCLUDE_CURRENT_DIR ON)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -ggdb -O2 ${LLVM_CFLAGS}")
option (ENABLE_TESTS "Enable tests" OFF)


#
# subdirectories
#

add_subdirectory (include)
add_subdirectory (src)

if (ENABLE_TESTS)
  add_subdirectory (test)
endif()


#
# install
#

install (FILES COPYING COPYING.LESSER DESTINATION share/doc/etg)
