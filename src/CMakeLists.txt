#
# extra CMake macros
#

list (APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
find_package (Clang COMPONENTS LLVM clang-cpp REQUIRED)
find_library (LIB_PTHREAD pthread)
find_library (LIB_DL dl)
find_library (LIB_Z z)
find_library (LIB_NCURSES ncurses)
find_library (LIB_TINFO tinfo)

include_directories (${CLANG_INCLUDE_DIRS})
link_directories (${CLANG_LIBRARY_DIRS})


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
target_link_libraries (etg ${CLANG_LIBS} ${LIB_PTHREAD} ${LIB_DL} ${LIB_Z} ${LIB_NCURSES} ${LIB_TINFO})


#
# install
#

get_filename_component (LLVM_BIN_DIR ${LLVM_CONFIG_EXECUTABLE} DIRECTORY CACHE)

install (TARGETS etg DESTINATION ${LLVM_BIN_DIR})

