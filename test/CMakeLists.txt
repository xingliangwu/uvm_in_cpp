add_executable(uvm_reg_test uvm_reg_test.cc)
target_link_libraries(uvm_reg_test uvm_pkg)
add_test(uvm_reg_test uvm_reg_test)
set_tests_properties(uvm_reg_test PROPERTIES PASS_REGULAR_EXPRESSION "PASSED")
