// Simple test for uvm_reg in c++
#include "uvm_reg_model.hh"
#include <array>
#include <iostream>

using namespace std;

int main(int argc, char * argv[])
{
    int seed = 0;
    uvm_reg reg;
    std::vector<array<int, 4>> fields;
    uvm_reg_field reg_fields[20];
    unsigned int  reg_init_val[20];

    if(argc > 1)
        seed= int(*argv[1]);
    srand(seed);

    // Initial all fields to random values
    for(int i = 0; i <20 ;i++){
        reg_init_val[i] = random();
        reg_fields[i].set(reg_init_val[i]);
    }

    // Create random reset values
    int max_bit = sizeof(uvm_reg_data_t) * 8;
    int current_msb = 0;
    int field_count = 0;

    // Genrat random field count
    while (field_count == 0) {
        field_count = (rand() % max_bit);
    }

    // For all counts, create a set to random reset values.
    // size, lsb, reset, has_reset
    // lsb = last field's msb
    for(int i = 0; i < field_count; i++) {
        int field_size = rand() % 16;
        int reset_val = rand() % (1 << field_size);
        int resetable = rand() % 2;
        if ((field_size + current_msb) < max_bit) {
            fields.push_back({field_size, current_msb, reset_val, resetable});
            current_msb += field_size;
        }
    }

    // Config the register. And create expected value.
    int index = 0;
    uvm_reg_data_t expect_val = 0;
    for(auto i : fields) {
        bool reset = (i[3] == 1) ? true : false;
        reg_fields[index].configure(&reg, i[0], i[1], i[2], reset);

        // Calculat expected value.
        // Base on if the field can be reset, it take init value
        // or reset value
        uvm_reg_data_t field_val = reset ? i[2] : reg_init_val[index];
        field_val <<= i[1];
        expect_val |= field_val;
        index ++;
    }

    // UVM_REG reset test
    reg.reset();

    printf("REG RESET CHECK: reg value: %llx, expect value: %llx\n",
            reg.get(), expect_val);

    if( reg.get() == expect_val) {
        printf("REG RESET CHECK PASSED\n");
        return 0;
    } else {
        printf("REG RESET CHECK FAILED: reg value: %llx, expect value: %llx\n",
                reg.get(), expect_val);
    }
    return 1;
}
