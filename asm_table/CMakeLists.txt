add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/cmd_list.txt ${CMAKE_CURRENT_BINARY_DIR}/operand_list.txt
                   COMMAND asm_csv_to_code -t csv ${CMAKE_CURRENT_SOURCE_DIR}/dis_list.csv  ${CMAKE_CURRENT_SOURCE_DIR}/asm_list.csv ${CMAKE_CURRENT_BINARY_DIR}/cmd_list.txt ${CMAKE_CURRENT_BINARY_DIR}/operand_list.txt
				   DEPENDS asm_csv_to_code)

add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/dis_funcs.cpp  ${CMAKE_CURRENT_BINARY_DIR}/dis_funcs.h
                   COMMAND asm_csv_to_code -t dis ${CMAKE_CURRENT_SOURCE_DIR}/dis_list.csv  ${CMAKE_CURRENT_SOURCE_DIR}/operand_list.csv ${CMAKE_CURRENT_BINARY_DIR}/dis_funcs.cpp ${CMAKE_CURRENT_BINARY_DIR}/dis_funcs.h NS_AMS8051HEX
				   DEPENDS asm_csv_to_code ./operand_list.csv)
				   
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/asm_funcs.cpp  ${CMAKE_CURRENT_BINARY_DIR}/asm_funcs.h
                   COMMAND asm_csv_to_code -t asm ${CMAKE_CURRENT_SOURCE_DIR}/asm_list.csv  ${CMAKE_CURRENT_SOURCE_DIR}/operand_list.csv ${CMAKE_CURRENT_BINARY_DIR}/asm_funcs.cpp ${CMAKE_CURRENT_BINARY_DIR}/asm_funcs.h NS_AMS8051HEX
				   DEPENDS asm_csv_to_code ./operand_list.csv ./asm_list.csv)

include_directories(../src)
include_directories(../src/context)
include_directories(../src/misc/util)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library(asm_table ${CMAKE_CURRENT_BINARY_DIR}/dis_funcs.cpp ${CMAKE_CURRENT_BINARY_DIR}/asm_funcs.cpp )