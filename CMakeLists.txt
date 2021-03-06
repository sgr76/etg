cmake_minimum_required (VERSION 3.2)

project (etg)
enable_testing ()


#
# extra CMake macros
#

list (APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

find_package (ProjectMacros)
# find_package (Clang COMPONENTS clangTooling clangBasic clangASTMatchers clangAST clangFrontend clangDriver clangFormat clangLex clangRewrite clangToolingCore LLVMOption LLVMCore LLVMMC clangEdit clangParse clangSema clangSerialization LLVMBitReader LLVMProfileData LLVMMCParser clangAnalysis QUIET)
# find_package (Clang COMPONENTS LLVMSupport REQUIRED)

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


#
# package
#

set (CPACK_PACKAGE_VERSION "0.9")
set (CPACK_PACKAGE_CONTACT "sgroth@gmx.de")
set (CPACK_PACKAGE_VENDOR "Sebastian Groth")
set (CPACK_PACKAGE_DESCRIPTION_SUMMARY "etg: c++ string table generator for enumerations")
set (CPACK_DEBIAN_PACKAGE_HOMEPAGE "http://")
set (CPACK_GENERATOR "DEB")
#set (CPACK_INSTALLED_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/package_extra_files .)
set (CPACK_DEBIAN_PACKAGE_DEPENDS "libclang1-3.8 (>= 1:3.8), libclang-common-3.8-dev (>=1:3.8)")
set (CPACK_PACKAGING_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})
# set (CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "postinst;${CMAKE_CURRENT_SOURCE_DIR}/prerm;${CMAKE_CURRENT_SOURCE_DIR}/postrm;${CMAKE_CURRENT_SOURCE_DIR}/conffiles")

include (CPack)

