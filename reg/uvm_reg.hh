#ifndef UVM_REG
#define UVM_REG

#include "uvm_reg_field.hh"
#include <vector>

class uvm_reg : public uvm_object{
    public:
        uvm_reg(std::string name = "uvm_reg") : uvm_object(name){};
        uvm_reg_data_t  get();
        void            set(uvm_reg_data_t value);
        void            add_field(uvm_reg_field field);
    private:
        uvm_reg_data_t              m_value;
        std::vector<uvm_reg_field>  m_fields;
};

uvm_reg_data_t uvm_reg::get() {
   // Concatenate the value of the individual fields
   // to form the register value
   m_value = 0;
   
   for (auto field: m_fields) {
      m_value |= field.get() << field.get_lsb_pos();
   }
   return m_value;
}

void uvm_reg::add_field(uvm_reg_field field) {
    m_fields.push_back(field);
}

void uvm_reg::set(uvm_reg_data_t value) {
    m_value = value;
    for(auto f: m_fields){
      f.set((value >> f.get_lsb_pos()) &
                       ((1 << f.get_n_bits()) - 1));
    }
}

void uvm_reg_field::configure(uvm_reg * parent,
                            int unsigned size,
                            int unsigned lsb_pos,
                            uvm_reg_data_t reset,
                            bool has_reset) {
    m_size = size;
    m_lsb  = lsb_pos;
    parent->add_field(*this);

    if (has_reset)
        m_reset = reset;

    if (size > m_max_size)
        m_max_size = size;
}

#endif // REGISTER
