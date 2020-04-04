#
# extra CMake macros
#

list (APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")


#
# source files
#

set (SOURCES )
set (HEADERS etg.hpp etg_qt5.hpp etg_std.hpp)


#
# extra targets
#

uncrustify (FILES ${HEADERS} ${SOURCES} TARGET include)


#
# install
#

install (FILES ${HEADERS} DESTINATION include)

