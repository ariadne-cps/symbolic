find_library(ARIADNE_DRAWING_LIBRARY NAMES ariadne-symbolic)
find_path(ARIADNE_DRAWING_INCLUDE_DIR ariadne-symbolic.hpp
          PATH_SUFFIXES ariadne-symbolic)

find_package(Threads REQUIRED)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(AriadneSymbolic DEFAULT_MSG
    ARIADNE_DRAWING_LIBRARY
    ARIADNE_DRAWING_INCLUDE_DIR
)

if(AriadneSymbolic_FOUND)
    get_filename_component(ARIADNE_DRAWING_INCLUDE_PARENT_DIR
        "${ARIADNE_DRAWING_INCLUDE_DIR}" DIRECTORY)
    if(NOT TARGET AriadneSymbolic::ariadne-symbolic)
        add_library(AriadneSymbolic::ariadne-symbolic UNKNOWN IMPORTED)
        set_target_properties(AriadneSymbolic::ariadne-symbolic PROPERTIES
            IMPORTED_LOCATION "${ARIADNE_DRAWING_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES
                "${ARIADNE_DRAWING_INCLUDE_PARENT_DIR};${ARIADNE_DRAWING_INCLUDE_DIR}"
            INTERFACE_LINK_LIBRARIES "Threads::Threads"
        )
    endif()
endif()
