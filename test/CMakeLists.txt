# Add uvm_reg_test
add_executable(uvm_reg_test uvm_reg_test.cc)
# Add include dir to reg
include_directories(${PROJECT_SOURCE_DIR}/src/reg)
# link with uvm_reg shared lib
target_link_libraries(uvm_reg_test uvm_reg)
# Add test to ctest
add_test(uvm_reg_reset_test_1 uvm_reg_test 1)
add_test(uvm_reg_reset_test_2 uvm_reg_test 20)
add_test(uvm_reg_reset_test_3 uvm_reg_test 1234)
# PASS condition
set_tests_properties(uvm_reg_reset_test_1
                    uvm_reg_reset_test_2
                    uvm_reg_reset_test_3
                    PROPERTIES PASS_REGULAR_EXPRESSION "PASSED")
