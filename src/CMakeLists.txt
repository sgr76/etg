#
# extra CMake macros
#

list (APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
find_package (Clang COMPONENTS clangTooling clangBasic clangASTMatchers clangAST clangFrontend LLVMSupport clangDriver clangFormat clangLex clangRewrite clangToolingCore LLVMOption LLVMCore LLVMMC clangEdit clangParse clangSema clangSerialization LLVMBitReader LLVMProfileData LLVMMCParser clangAnalysis REQUIRED)


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
target_link_libraries (etg ${CLANG_LIBS} ${CLANG_LIBS} pthread dl z ncurses)


#
# install
#

get_filename_component (LLVM_BIN_DIR ${LLVM_CONFIG_EXECUTABLE} DIRECTORY CACHE)

install (TARGETS etg DESTINATION ${LLVM_BIN_DIR})

