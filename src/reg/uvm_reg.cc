#ifndef UVM_REG_CC
#define UVM_REG_CC

#include "uvm_reg.hh"

uvm_reg_data_t uvm_reg::get() {
   // Concatenate the value of the individual fields
   // to form the register value
   m_value = 0;
   
   for (auto field: m_fields) {
      m_value |= field->get() << field->get_lsb_pos();
   }
   return m_value;
}

void uvm_reg::add_field(uvm_reg_field * field) {
    m_fields.push_back(field);
}

void uvm_reg::set(uvm_reg_data_t value) {
    m_value = value;
    for(auto f: m_fields){
      f->set((value >> f->get_lsb_pos()) &
                       ((1 << f->get_n_bits()) - 1));
    }
}

void uvm_reg_field::configure(uvm_reg * parent,
                            int unsigned size,
                            int unsigned lsb_pos,
                            uvm_reg_data_t reset,
                            bool has_reset) {
    m_size = size;
    m_lsb  = lsb_pos;
    parent->add_field(this);

    if (has_reset)
    {
        this->m_reset = reset;
        this->m_has_reset = has_reset;
    }

    if (size > m_max_size)
        m_max_size = size;
}

void uvm_reg::reset(std::string kind){
   for (auto field: m_fields) {
      field->reset();
   }
   // Put back a key in the semaphore if it is checked out
   // in case a thread was killed during an operation
   //void'(m_atomic.try_get(1));
   //m_atomic.put(1);
   //m_process = null;
   //Xset_busyX(0);
}

#endif
