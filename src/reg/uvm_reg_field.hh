#ifndef UVM_REG_FIELD
#define UVM_REG_FIELD

#include "base/uvm_object.hh"

using uvm_reg_data_t = unsigned long long;

class uvm_reg;

class uvm_reg_field : public uvm_object {
    private:
        uvm_reg_data_t                          m_value;

        int unsigned                            m_lsb;
        int unsigned                            m_size;
        //std::map<std::string, uvm_reg_data_t>   m_reset;
        uvm_reg_data_t                          m_reset;
        static int unsigned                     m_max_size;
        uvm_reg *                               m_parent;
    public:
        uvm_reg_field(std::string name = "uvm_reg_field") : uvm_object(name){};
        int unsigned get_lsb_pos() {return m_lsb;}
        int unsigned get_n_bits() {return m_size;}
        void configure(uvm_reg *     parent,
                      int unsigned   size,
                      int unsigned   lsb_pos,
                      //std::string    access,
                      //bool           volatile,
                      uvm_reg_data_t reset,
                      bool           has_reset);
                      //bool           is_rand,
                      //bool           individually_accessible); 

        //--------------
        // Group: Access
        //--------------


        // Function: set
        //
        // Set the desired value for this field
        //
        // It sets the desired value of the field to the specified ~value~
        // modified by the field access policy.
        // It does not actually set the value of the field in the design,
        // only the desired value in the abstraction class.
        // Use the <uvm_reg::update()> method to update the actual register
        // with the desired value or the <uvm_reg_field::write()> method
        // to actually write the field and update its mirrored value.
        //
        // The final desired value in the mirror is a function of the field access
        // policy and the set value, just like a normal physical write operation
        // to the corresponding bits in the hardware.
        // As such, this method (when eventually followed by a call to
        // <uvm_reg::update()>)
        // is a zero-time functional replacement for the <uvm_reg_field::write()>
        // method.
        // For example, the desired value of a read-only field is not modified
        // by this method and the desired value of a write-once field can only
        // be set if the field has not yet been
        // written to using a physical (for example, front-door) write operation.
        //
        // Use the <uvm_reg_field::predict()> to modify the mirrored value of
        // the field.
        //
        virtual void set(uvm_reg_data_t  value);
                         //std::string     fname = "",
                         //int             lineno = 0);

        // Function: get
        //
        // Return the desired value of the field
        //
        // It does not actually read the value
        // of the field in the design, only the desired value
        // in the abstraction class. Unless set to a different value
        // using the <uvm_reg_field::set()>, the desired value
        // and the mirrored value are identical.
        //
        // Use the <uvm_reg_field::read()> or <uvm_reg_field::peek()>
        // method to get the actual field value. 
        //
        // If the field is write-only, the desired/mirrored
        // value is the value last written and assumed
        // to reside in the bits implementing it.
        // Although a physical read operation would something different,
        // the returned value is the actual content.
        //
        virtual uvm_reg_data_t get() {return m_value;}

        // Function: reset
        //
        // Reset the desired/mirrored value for this field.
        //
        // It sets the desired and mirror value of the field
        // to the reset event specified by ~kind~.
        // If the field does not have a reset value specified for the
        // specified reset ~kind~ the field is unchanged.
        //
        // It does not actually reset the value of the field in the design,
        // only the value mirrored in the field abstraction class.
        //
        // Write-once fields can be modified after
        // a "HARD" reset operation.
        //
        virtual void reset() {m_value = m_reset;}
        friend class uvm_reg;

};


void uvm_reg_field::set(uvm_reg_data_t value) {
    m_value = value;
}

int unsigned uvm_reg_field::m_max_size = 0;

#endif // REGISTER
