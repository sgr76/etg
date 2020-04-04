#
# extra CMake macros
#


#
# options
#

set (ETG_INCLUDE_DIR "../../include" CACHE PATH "path to etg.hpp")
set (ETG_EXECUTABLE "etg" CACHE FILEPATH "etg program executable")

set (CMAKE_INCLUDE_CURRENT_DIR ON)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -ggdb -O2")
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

    add_custom_command (OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${PARAM_PREFIX}_etg.cpp ${CMAKE_CURRENT_BINARY_DIR}/${PARAM_PREFIX}_etg.hpp COMMAND ${ETG_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/${PARAM_PREFIX}_enum.hpp -o ${PARAM_PREFIX}_etg.cpp -H ${PARAM_PREFIX}_etg.hpp -i ${PARAM_PREFIX}_enum.hpp --generator=std --use-namespcaes -- -I${ETG_INCLUDE_DIR} -std=c++11 DEPENDS ${PARAM_PREFIX}_enum.hpp)

    add_executable (ns_${PARAM_NAME} ${PARAM_PREFIX}_main.cpp ${PARAM_PREFIX}_etg.cpp)
    add_test (NAME test_ns_${PARAM_NAME} COMMAND ns_${PARAM_NAME} WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
    
    list (APPEND UNCRUSTIFY_FILES ${PARAM_PREFIX}_main.cpp ${PARAM_PREFIX}_enum.hpp)
endmacro ()


#
# tests
#

# test_definition (NAME std_debug            PREFIX debug)
# test_definition (NAME std_long_debug       PREFIX long_debug)
# test_definition (NAME std_cast             PREFIX cast)
# test_definition (NAME std_token            PREFIX token)
# test_definition (NAME std_translation      PREFIX translation)
# test_definition (NAME std_iterator         PREFIX iterator)
test_definition (NAME std_full             PREFIX full)
# test_definition (NAME std_casei            PREFIX casei)
# test_definition (NAME std_excptdef         PREFIX excptdef)

# test_definition (NAME std_c_debug          PREFIX c_debug)
# test_definition (NAME std_c_long_debug     PREFIX c_long_debug)
# test_definition (NAME std_c_cast           PREFIX c_cast)
# test_definition (NAME std_c_token          PREFIX c_token)
# test_definition (NAME std_c_translation    PREFIX c_translation)
# test_definition (NAME std_c_iterator       PREFIX c_iterator)
test_definition (NAME std_c_full           PREFIX c_full)
# test_definition (NAME std_c_casei          PREFIX c_casei)
# test_definition (NAME std_c_excptdef       PREFIX c_excptdef)

# test_definition (NAME std_ns_debug         PREFIX ns_debug)
# test_definition (NAME std_ns_long_debug    PREFIX ns_long_debug)
# test_definition (NAME std_ns_cast          PREFIX ns_cast)
# test_definition (NAME std_ns_token         PREFIX ns_token)
# test_definition (NAME std_ns_translation   PREFIX ns_translation)
# test_definition (NAME std_ns_iterator      PREFIX ns_iterator)
test_definition (NAME std_ns_full          PREFIX ns_full)
# test_definition (NAME std_ns_casei         PREFIX ns_casei)
# test_definition (NAME std_ns_excptdef      PREFIX ns_excptdef)

# test_definition (NAME std_ns_c_debug       PREFIX ns_c_debug)
# test_definition (NAME std_ns_c_long_debug  PREFIX ns_c_long_debug)
# test_definition (NAME std_ns_c_cast        PREFIX ns_c_cast)
# test_definition (NAME std_ns_c_token       PREFIX ns_c_token)
# test_definition (NAME std_ns_c_translation PREFIX ns_c_translation)
# test_definition (NAME std_ns_c_iterator    PREFIX ns_c_iterator)
test_definition (NAME std_ns_c_full        PREFIX ns_c_full)
# test_definition (NAME std_ns_c_casei       PREFIX ns_c_casei)
# test_definition (NAME std_ns_c_excptdef    PREFIX ns_c_excptdef)

test_definition (NAME std_i_full             PREFIX i_full)
test_definition (NAME std_i_c_full           PREFIX i_c_full)
test_definition (NAME std_ns_i_full          PREFIX ns_i_full)
test_definition (NAME std_ns_i_c_full        PREFIX ns_i_c_full)


#
# extra targets
#

uncrustify (FILES ${UNCRUSTIFY_FILES} TARGET std_ns_tests)
