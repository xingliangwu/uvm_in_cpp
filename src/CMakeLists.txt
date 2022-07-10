add_library(uvm_pkg SHARED
    uvm_pkg.cc
    uvm_pkg.hh
)

target_include_directories(uvm_pkg
                           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
                           )

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/base)
include_directories(${PROJECT_SOURCE_DIR}/reg)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")

#target_link_libraries(test PUBLIC uvm_pkg.so)
