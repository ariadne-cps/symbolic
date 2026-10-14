add_library(SYMBOLIC_SRC OBJECT expression.cpp expression_set.cpp space.cpp)
target_include_directories(SYMBOLIC_SRC PRIVATE "${PROJECT_SOURCE_DIR}/include/symbolic")
