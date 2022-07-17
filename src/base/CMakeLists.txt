add_library(uvm_base SHARED
    uvm_object.cc
    uvm_base.hh
)

set_target_properties(uvm_base PROPERTIES LINKER_LANGUAGE CXX)
