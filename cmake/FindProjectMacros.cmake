include(CMakeParseArguments)


#
# create a link to the source directory
#

macro (source_directory_link)

    execute_process (COMMAND echo "${CMAKE_CURRENT_SOURCE_DIR}" OUTPUT_FILE ${CMAKE_CURRENT_BINARY_DIR}/.kate-cmake-session)

endmacro ()

source_directory_link ()


#
# uncrustify
#

function (enabled_uncrustify)
    if (NOT TARGET uncrustify)
        add_custom_target (uncrustify)
    endif ()
endfunction ()
  
  
function (uncrustify)
    set (options )
    set (oneValueParams TARGET)
    set (multiValueParams FILES SUBDIRS)
  
    cmake_parse_arguments (PARAM "${options}" "${oneValueParams}" "${multiValueParams}" ${ARGN})

    set (UNCRUSTIFY_DIR ${CMAKE_BINARY_DIR}/.uncrustify/${PARAM_TARGET})
  
    # file (REMOVE_RECURSE "${UNCRUSTIFY_DIR}")
    file (MAKE_DIRECTORY "${UNCRUSTIFY_DIR}")
    
    foreach (input ${PARAM_SUBDIRS})
        file (MAKE_DIRECTORY "${UNCRUSTIFY_DIR}/${input}")
    endforeach ()
  
    set (FILE_LIST "")
  
    foreach (input ${PARAM_FILES})
        add_custom_command (OUTPUT "${UNCRUSTIFY_DIR}/${input}" COMMAND uncrustify -c ${CMAKE_SOURCE_DIR}/cfg/default.cfg --replace --no-backup ${CMAKE_CURRENT_SOURCE_DIR}/${input} COMMAND touch "${UNCRUSTIFY_DIR}/${input}" DEPENDS ${input})
        list (APPEND FILE_LIST "${UNCRUSTIFY_DIR}/${input}")
    endforeach ()
  
    add_custom_target (uncrustify_${PARAM_TARGET} DEPENDS ${FILE_LIST})
    add_dependencies (uncrustify uncrustify_${PARAM_TARGET})
    
endfunction ()


#
# add to parent directory file list
#

macro (add_files_to_parent DEST_LIST)
    set (options )
    set (oneValueParams )
    set (multiValueParams FILES)
  
    cmake_parse_arguments (PARAM "${options}" "${oneValueParams}" "${multiValueParams}" ${ARGN})
  
    string (REGEX REPLACE ".*/" "" DIR ${CMAKE_CURRENT_SOURCE_DIR})
 
    set(TMP_LIST ${${DEST_LIST}})

    foreach (input ${PARAM_FILES})
        list (APPEND TMP_LIST "${DIR}/${input}")
    endforeach ()
  
    set (${DEST_LIST} ${TMP_LIST} PARENT_SCOPE)
 
endmacro ()


#
# enum names function
#

function (enum_names)
    set (options )
    set (oneValueParams SOURCE OUTPUT TARGET)
    set (multiValueParams )
  
    cmake_parse_arguments (PARAM "${options}" "${oneValueParams}" "${multiValueParams}" ${ARGN})
  
    if (PARAM_SOURCE AND PARAM_OUTPUT AND PARAM_TARGET)
        add_custom_command (OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${PARAM_OUTPUT} COMMAND ${CMAKE_SOURCE_DIR}/tools/enumnames/enumnames.py ${CMAKE_CURRENT_SOURCE_DIR}/${PARAM_SOURCE} ${CMAKE_CURRENT_BINARY_DIR}/${PARAM_OUTPUT} DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${PARAM_SOURCE})
        add_custom_target (${PARAM_TARGET} DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${PARAM_OUTPUT})
    else ()
        message ("invalid call of enum_names")
    endif ()
endfunction ()
