#
# extra CMake macros
#

find_package (Clang REQUIRED CONFIG)
find_program (CLANG_BINARY clang REQUIRED)

include_directories (${CLANG_INCLUDE_DIRS})


#
# source files
#

set (SOURCES enum.cpp factory.cpp file.cpp file_pool.cpp header.cpp implementation.cpp main.cpp scope.cpp scope_walker.cpp)
set (HEADERS enum.hpp factory.hpp file.hpp file_pool.hpp header.hpp implementation.hpp scope.hpp scope_walker.hpp)


#
# subdirectories
#

add_subdirectory (std)
add_subdirectory (std_ns)
add_subdirectory (qt5)
add_subdirectory (qt5_ns)


#
# extra targets
#

uncrustify (FILES ${HEADERS} ${SOURCES} TARGET etg)


#
# program
#

add_executable (etg ${SOURCES})
target_link_libraries (etg LLVM clang-cpp)


#
# install
#

get_filename_component (CLANG_BINARY_DIR ${CLANG_BINARY} DIRECTORY)

install (TARGETS etg DESTINATION ${CLANG_BINARY_DIR})
