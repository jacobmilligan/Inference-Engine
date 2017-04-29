function(add_sources)
    get_property(is_defined GLOBAL PROPERTY SOURCE_LIST DEFINED)
    if (NOT is_defined)
        define_property(GLOBAL PROPERTY SOURCE_LIST
                BRIEF_DOCS "List of all source files"
                FULL_DOCS "List of all source files to be compiled into the executable or library")
    endif ()

    set(SRCS)
    foreach(s IN LISTS ARGN)
        if (NOT IS_ABSOLUTE "${s}")
            get_filename_component(s "${s}" ABSOLUTE)
        endif ()
        list(APPEND SRCS "${s}")
    endforeach()

    set_property(GLOBAL APPEND PROPERTY SOURCE_LIST "${SRCS}")
endfunction()