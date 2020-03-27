# Detect Clang libraries
#
# Defines the following variables:
#  CLANG_FOUND   
#  CLANG_INCLUDE_DIRS
#  CLANG_LIBRARY_DIRS 
#  CLANG_LIBCLANG_LIB 
#  CLANG_CLANGFRONTEND_LIB 
#  CLANG_CLANGDRIVER_LIB    
#  ...
#  CLANG_LIBS

if (Clang_FIND_REQUIRED)
    find_package (LLVM REQUIRED)
else ()
    find_package (LLVM)
endif ()

set (CLANG_FOUND FALSE)

if (LLVM_FOUND AND LLVM_LIBRARY_DIRS)
    find_library (CLANG_LIBCLANG_LIB NAMES clang HINTS ${LLVM_LIBRARY_DIRS})

    if (Clang_FIND_COMPONENTS )
        foreach (component ${Clang_FIND_COMPONENTS})
            string (TOUPPER ${component} _COMPONENT)
            find_library (CLANG_${_COMPONENT}_LIB NAMES ${component} HINTS ${LLVM_LIBRARY_DIRS})
            if (CLANG_${_COMPONENT}_LIB)
                set (CLANG_LIBS ${CLANG_LIBS} ${CLANG_${_COMPONENT}_LIB})
            else ()
                if (Clang_FIND_REQUIRED)
                    message (FATAL_ERROR "Could NOT find Clang library: ${component}")
                else ()
                    message (STATUS "Could not find Clang library: ${component}")
                endif ()
            endif ()
        endforeach (component)
    endif ()
endif()

if (CLANG_LIBS OR CLANG_LIBCLANG_LIB)
    set (CLANG_FOUND TRUE)
else()
    if (Clang_FIND_REQUIRED)
        message (FATAL_ERROR "Could NOT find Clang")
    else ()
        message (STATUS "Could not find Clang")
    endif ()
endif ()

if (CLANG_FOUND)
    set (CLANG_LIBRARY_DIRS ${LLVM_LIBRARY_DIRS})
    set (CLANG_INCLUDE_DIRS ${LLVM_INCLUDE_DIRS})
endif()
