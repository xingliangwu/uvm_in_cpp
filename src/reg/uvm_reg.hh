#ifndef UVM_REG
#define UVM_REG

#include "uvm_reg_field.hh"
#include <vector>

class uvm_reg : public uvm_object{
    public:
        uvm_reg(std::string name = "uvm_reg") : uvm_object(name){};
        uvm_reg_data_t  get();
        void            set(uvm_reg_data_t value);
        void            add_field(uvm_reg_field * field);

        // Function: reset
        //
        // Reset the desired/mirrored value for this register.
        //
        // Sets the desired and mirror value of the fields in this register
        // to the reset value for the specified reset ~kind~.
        // See <uvm_reg_field.reset()> for more details.
        //
        // Also resets the semaphore that prevents concurrent access
        // to the register.
        // This semaphore must be explicitly reset if a thread accessing
        // this register array was killed in before the access
        // was completed
        //
        virtual void reset(std::string kind);
    private:
        uvm_reg_data_t              m_value;
        std::vector<uvm_reg_field*> m_fields;
    friend class uvm_reg_field;
};

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
        this->m_reset = reset;

    if (size > m_max_size)
        m_max_size = size;
}

void uvm_reg::reset(std::string kind = "HARD"){
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
#endif // REGISTER
