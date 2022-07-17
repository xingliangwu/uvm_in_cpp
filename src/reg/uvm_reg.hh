#ifndef UVM_REG_HH
#define UVM_REG_HH

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
        virtual void reset(std::string kind = "HARD");
    private:
        uvm_reg_data_t              m_value;
        std::vector<uvm_reg_field*> m_fields;
    friend class uvm_reg_field;
};

#endif // REGISTER
