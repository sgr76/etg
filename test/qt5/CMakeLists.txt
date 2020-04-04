#
# extra CMake macros
#

find_package (Qt5Core)
find_package (Qt5Widgets)
# find_package (Qt5LinguistTools)


#
# options
#

set (ETG_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include" CACHE PATH "path to etg.hpp")
set (ETG_EXECUTABLE "etg" CACHE FILEPATH "etg program executable")

set (CMAKE_INCLUDE_CURRENT_DIR ON)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -ggdb -O2 -DETG_QT5")
set (UNCRUSTIFY_FILES )

include_directories (${ETG_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})


#
# macro
#

macro (test_definition)
    set (options )
    set (oneValueParams NAME PREFIX)
    set (multiValueParams )
  
    cmake_parse_arguments (PARAM "${options}" "${oneValueParams}" "${multiValueParams}" ${ARGN})

    add_custom_command (OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${PARAM_PREFIX}_etg.cpp ${CMAKE_CURRENT_BINARY_DIR}/${PARAM_PREFIX}_etg.hpp COMMAND ${ETG_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/${PARAM_PREFIX}_enum.hpp -o ${PARAM_PREFIX}_etg.cpp -H ${PARAM_PREFIX}_etg.hpp -i ${PARAM_PREFIX}_enum.hpp --generator=qt5 -- -I${ETG_INCLUDE_DIR} -I${Qt5Core_INCLUDE_DIRS} -DETG_QT5 -std=c++11 DEPENDS ${PARAM_PREFIX}_enum.hpp)

    add_executable (${PARAM_NAME} ${PARAM_PREFIX}_main.cpp ${PARAM_PREFIX}_etg.cpp)
    target_link_libraries (${PARAM_NAME} Qt5::Core Qt5::Widgets)
    add_test (NAME test_${PARAM_NAME} COMMAND ${PARAM_NAME} WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
    
    list (APPEND UNCRUSTIFY_FILES ${PARAM_PREFIX}_main.cpp ${PARAM_PREFIX}_enum.hpp)
endmacro ()


#
# tests
#

# test_definition (NAME qt5_debug            PREFIX debug)
# test_definition (NAME qt5_long_debug       PREFIX long_debug)
# test_definition (NAME qt5_cast             PREFIX cast)
# test_definition (NAME qt5_token            PREFIX token)
# test_definition (NAME qt5_translation      PREFIX translation)
# test_definition (NAME qt5_iterator         PREFIX iterator)
test_definition (NAME qt5_full             PREFIX full)
# test_definition (NAME qt5_casei            PREFIX casei)
# test_definition (NAME qt5_excptdef         PREFIX excptdef)

# test_definition (NAME qt5_c_debug          PREFIX c_debug)
# test_definition (NAME qt5_c_long_debug     PREFIX c_long_debug)
# test_definition (NAME qt5_c_cast           PREFIX c_cast)
# test_definition (NAME qt5_c_token          PREFIX c_token)
# test_definition (NAME qt5_c_translation    PREFIX c_translation)
# test_definition (NAME qt5_c_iterator       PREFIX c_iterator)
test_definition (NAME qt5_c_full           PREFIX c_full)
# test_definition (NAME qt5_c_casei          PREFIX c_casei)
# test_definition (NAME qt5_c_excptdef       PREFIX c_excptdef)

# test_definition (NAME qt5_ns_debug         PREFIX ns_debug)
# test_definition (NAME qt5_ns_long_debug    PREFIX ns_long_debug)
# test_definition (NAME qt5_ns_cast          PREFIX ns_cast)
# test_definition (NAME qt5_ns_token         PREFIX ns_token)
# test_definition (NAME qt5_ns_translation   PREFIX ns_translation)
# test_definition (NAME qt5_ns_iterator      PREFIX ns_iterator)
test_definition (NAME qt5_ns_full          PREFIX ns_full)
# test_definition (NAME qt5_ns_casei         PREFIX ns_casei)
# test_definition (NAME qt5_ns_excptdef      PREFIX ns_excptdef)

# test_definition (NAME qt5_ns_c_debug       PREFIX ns_c_debug)
# test_definition (NAME qt5_ns_c_long_debug  PREFIX ns_c_long_debug)
# test_definition (NAME qt5_ns_c_cast        PREFIX ns_c_cast)
# test_definition (NAME qt5_ns_c_token       PREFIX ns_c_token)
# test_definition (NAME qt5_ns_c_translation PREFIX ns_c_translation)
# test_definition (NAME qt5_ns_c_iterator    PREFIX ns_c_iterator)
test_definition (NAME qt5_ns_c_full        PREFIX ns_c_full)
# test_definition (NAME qt5_ns_c_casei       PREFIX ns_c_casei)
# test_definition (NAME qt5_ns_c_excptdef    PREFIX ns_c_excptdef)

test_definition (NAME qt5_i_full             PREFIX i_full)
test_definition (NAME qt5_i_c_full           PREFIX i_c_full)
test_definition (NAME qt5_ns_i_full          PREFIX ns_i_full)
test_definition (NAME qt5_ns_i_c_full        PREFIX ns_i_c_full)


#
# extra targets
#

uncrustify (FILES ${UNCRUSTIFY_FILES} TARGET qt5_tests)
