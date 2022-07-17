add_library(uvm_pkg SHARED
    uvm_pkg.cc
    uvm_pkg.hh
)

target_include_directories(uvm_pkg
                           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
                           )

add_subdirectory(${PROJECT_SOURCE_DIR}/src/base)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/reg)
