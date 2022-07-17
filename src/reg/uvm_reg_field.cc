#ifndef UVM_REG_FIELD_CC
#define UVM_REG_FIELD_CC

#include "uvm_reg_field.hh"

int unsigned uvm_reg_field::m_max_size = 0;

void uvm_reg_field::set(uvm_reg_data_t value) {
    m_value = value;
}

#endif
