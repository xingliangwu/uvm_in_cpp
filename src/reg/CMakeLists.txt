add_library(uvm_reg SHARED
    uvm_reg.cc
    uvm_reg_field.cc
    uvm_reg_model.hh
)

set_target_properties(uvm_reg PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(uvm_reg uvm_base)
