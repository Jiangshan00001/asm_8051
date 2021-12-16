

enable_testing()


function(asm_to_hex  ASM_FILE  HEX_FILE)
#STRING(REGEX REPLACE ".+/(.+)\\..*" "\\1" FILE_NAME1 ${ASM_FILE})
#STRING(REGEX REPLACE ".+/(.+)\\..*" "\\1" FILE_NAME2 ${HEX_FILE})
add_test( NAME test_asm_to_hex${ASM_FILE} COMMAND asm8051 -asm -d  ${ASM_FILE} ${HEX_FILE} )
endfunction()

function(hex_to_asm  HEX_FILE  ASM_FILE)
#STRING(REGEX REPLACE ".+/(.+)\\..*" "\\1" FILE_NAME1 ${HEX_FILE})
#STRING(REGEX REPLACE ".+/(.+)\\..*" "\\1" FILE_NAME2 ${ASM_FILE})
add_test( NAME test_hex_to_asm${HEX_FILE} COMMAND asm8051 -dis -nd  ${HEX_FILE} ${ASM_FILE} )
endfunction()


function(diff_asm  asm1  asm2)
#STRING(REGEX REPLACE ".+/(.+)\\..*" "\\1" FILE_NAME1 ${asm1})
#STRING(REGEX REPLACE ".+/(.+)\\..*" "\\1" FILE_NAME2 ${asm2})
add_test( NAME test_diff_asm${asm1} COMMAND diff  ${asm1} ${asm2} )
endfunction()

set(TEST_SRCS test_zhushi1.a51)
set(TEST_SRCS ${TEST_SRCS} test_jb_ext1.a51 test_jb_ext2.a51 test_jc_ext1.a51 test_jc_ext2.a51)
set(TEST_SRCS ${TEST_SRCS} test_sjmp_ext1.a51 test_sjmp_ext2.a51 test_sjmp_ext3.a51 test_sjmp_ext4.a51)
set(TEST_SRCS ${TEST_SRCS} test_predefined1.a51)
set(TEST_SRCS ${TEST_SRCS} test_sjmp1.a51 test_sjmp2.a51 test_equ_2.a51 )
set(TEST_SRCS ${TEST_SRCS} test_label_opr.a51)
set(TEST_SRCS ${TEST_SRCS} asm_test1.a51 asm_test2.a51  stc8a_test1.a51 stc8a_test2.a51 stc8a_test3.a51 stc8a_test4.a51  stc8a_test5.a51 stc8a_test6.a51 stc_paomadeng.a51 )
set(TEST_SRCS ${TEST_SRCS} stc_hc595.a51 )

foreach(MY_ASM  ${TEST_SRCS})
#set(MY_ASM ${var1})
string(REPLACE ".a51"  "_self.hex"  MY_HEX "${MY_ASM}")
string(REPLACE ".a51"  "_keil.hex"  KEIL_HEX "${MY_ASM}")
string(REPLACE ".a51"  "_keil.a51"  KEIL_ASM "${MY_ASM}")
string(REPLACE ".a51"  "_self.a51"  MY_ASMREG "${MY_ASM}")

asm_to_hex(${CMAKE_CURRENT_SOURCE_DIR}/${MY_ASM}  ${CMAKE_CURRENT_BINARY_DIR}/${MY_HEX} )
hex_to_asm(${CMAKE_CURRENT_SOURCE_DIR}/${KEIL_HEX}  ${CMAKE_CURRENT_BINARY_DIR}/${KEIL_ASM} )
hex_to_asm(${CMAKE_CURRENT_BINARY_DIR}/${MY_HEX}  ${CMAKE_CURRENT_BINARY_DIR}/${MY_ASMREG} )
diff_asm(${CMAKE_CURRENT_BINARY_DIR}/${MY_ASMREG}  ${CMAKE_CURRENT_BINARY_DIR}/${KEIL_ASM})

endforeach()




