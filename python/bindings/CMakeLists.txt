include_directories(${Python3_INCLUDE_DIRS})
get_target_property(PYTHON_COMMON_SOURCE_DIR pyariadne-python-common SOURCE_DIR)

add_library(pyariadne-symbolic-submodule-obj OBJECT symbolic_submodule.cpp)
target_include_directories(pyariadne-symbolic-submodule-obj PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${PYTHON_COMMON_SOURCE_DIR}/include"
    $<TARGET_PROPERTY:pyariadne-kernel,INTERFACE_INCLUDE_DIRECTORIES>
)
target_link_libraries(pyariadne-symbolic-submodule-obj PRIVATE pyariadne-python-common pybind11::module symbolic)
set_target_properties(pyariadne-symbolic-submodule-obj PROPERTIES POSITION_INDEPENDENT_CODE ON)

add_library(pyariadne-symbolic INTERFACE)
target_sources(pyariadne-symbolic INTERFACE $<TARGET_OBJECTS:pyariadne-symbolic-submodule-obj>)
target_include_directories(pyariadne-symbolic INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<TARGET_PROPERTY:pyariadne-kernel,INTERFACE_INCLUDE_DIRECTORIES>
)
target_link_libraries(pyariadne-symbolic INTERFACE pyariadne-kernel)

ariadne_add_python_module(NAME symbolic MODULE_SOURCE symbolic_module.cpp)
