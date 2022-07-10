// Simple test for uvm_reg in c++
// TODO. Move this to google test
#include "uvm_pkg.hh"
#include "stdlib.h"

int main()
{
    // UVM_REG reset test
    uvm_reg reg;
    uvm_reg_field field1;
    uvm_reg_field field2;

    field1.configure(&reg, 4, 0, 1,   true);
    field2.configure(&reg, 4, 4, 0xf, true);

    reg.reset();

    uvm_reg_data_t expect_val = 0xf1;

    if( reg.get() == expect_val) {
        printf("REG RESET CHECK PASSED\n");
    } else {
        printf("REG RESET CHECK FAILED: reg value: %llx, expect value: %llx\n",
        reg.get(), expect_val);
    }
    return 1;
}
