

enable_testing()
add_test( NAME test1 COMMAND mzasm8051 -dis -nd asm_test1.a51 asm_test1_tes.hex )

