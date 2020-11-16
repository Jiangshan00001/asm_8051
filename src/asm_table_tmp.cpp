#include "asm_table.h"
asm_to_hex_table g_asm_table[]={
{"ADD", "A,Rn", "Add register to Accumulator", 1, 12, "ARITHMETIC OPERATIONS", "0x28+$2", "", "", "TOKEN_ACC", "TOKEN_RN", "", "" },
{"ADD", "A,direct", "Add direct byte to Accumulator", 2, 12, "ARITHMETIC OPERATIONS", "0x25", "$2 ", "", "TOKEN_ACC", "TOKEN_NUM", "", "" },
{"ADD", "A,@Ri", "Add indirect RAM to Accumulator", 1, 12, "ARITHMETIC OPERATIONS", "0x26+$2", "", "", "TOKEN_ACC", "TOKEN_AT_RI", "", "" },
{"ADD", "A,#data", "Add immediate data to Accumulator", 2, 12, "ARITHMETIC OPERATIONS", "0x24", "$2 ", "", "TOKEN_ACC", "TOKEN_J_DATA", "", "" },
{"ADDC", "A,Rn", "Add register to Accumulator with Carry", 1, 12, "ARITHMETIC OPERATIONS", "0x38+$2", "", "", "TOKEN_ACC", "TOKEN_RN", "", "" },
{"ADDC", "A,direct", "Add direct byte to Accumulator with Carry", 2, 12, "ARITHMETIC OPERATIONS", "0x35", "$2 ", "", "TOKEN_ACC", "TOKEN_NUM", "", "" },
{"ADDC", "A,@Ri", "Add indirect RAM to Accumulator with Carry", 1, 12, "ARITHMETIC OPERATIONS", "0x36+$2", "", "", "TOKEN_ACC", "TOKEN_AT_RI", "", "" },
{"ADDC", "A,#data", "Add immediate data to Acc with Carry", 2, 12, "ARITHMETIC OPERATIONS", "0x34", "$2 ", "", "TOKEN_ACC", "TOKEN_J_DATA", "", "" },
{"SUBB", "A,Rn", "Subtract Register from Acc with borrow", 1, 12, "ARITHMETIC OPERATIONS", "0x98+$2", "", "", "TOKEN_ACC", "TOKEN_RN", "", "" },
{"SUBB", "A,direct", "Subtract direct byte from Acc with borrow", 2, 12, "ARITHMETIC OPERATIONS", "0x95", "$2 ", "", "TOKEN_ACC", "TOKEN_NUM", "", "" },
{"SUBB", "A,@Ri", "Subtract indirect RAM from ACC with borrow", 1, 12, "ARITHMETIC OPERATIONS", "0x96+$2", "", "", "TOKEN_ACC", "TOKEN_AT_RI", "", "" },
{"SUBB", "A,#data", "Subtract immediate data from Acc with borrow", 2, 12, "ARITHMETIC OPERATIONS", "0x94", "$2 ", "", "TOKEN_ACC", "TOKEN_J_DATA", "", "" },
{"INC", "A", "Increment Accumulator", 1, 12, "ARITHMETIC OPERATIONS", "0x04", "", "", "TOKEN_ACC", "", "", "" },
{"INC", "Rn", "Increment register", 1, 12, "ARITHMETIC OPERATIONS", "0x08+$1", "", "", "TOKEN_RN", "", "", "" },
{"INC", "direct", "Increment direct byte", 2, 12, "ARITHMETIC OPERATIONS", "0x05", "$1 ", "", "TOKEN_NUM", "", "", "" },
{"INC", "@Ri", "Increment direct RAM", 1, 12, "ARITHMETIC OPERATIONS", "0x06+$1", "", "", "TOKEN_AT_RI", "", "", "" },
{"DEC", "A", "Decrement Accumulator", 1, 12, "ARITHMETIC OPERATIONS", "0x14", "", "", "TOKEN_ACC", "", "", "" },
{"DEC", "Rn", "Decrement Register", 1, 12, "ARITHMETIC OPERATIONS", "0x18+$1", "", "", "TOKEN_RN", "", "", "" },
{"DEC", "direct", "Decrement direct byte", 2, 12, "ARITHMETIC OPERATIONS", "0x15", "$1 ", "", "TOKEN_NUM", "", "", "" },
{"DEC", "@Ri", "Decrement indirect RAM", 1, 12, "ARITHMETIC OPERATIONS", "0x16+$1", "", "", "TOKEN_AT_RI", "", "", "" },
{"INC", "DPTR", "Increment Data Pointer", 1, 24, "ARITHMETIC OPERATIONS", "0xA3", "", "", "TOKEN_DPTR", "", "", "" },
{"MUL", "AB", "Multiply A & B", 1, 48, "ARITHMETIC OPERATIONS", "0xA4", "", "", "TOKEN_AB", "", "", "" },
{"DIV", "AB", "Divide A by B", 1, 48, "ARITHMETIC OPERATIONS", "0x84", "", "", "TOKEN_AB", "", "", "" },
{"DA", "A", "Decimal Adjust Accumulator", 1, 12, "ARITHMETIC OPERATIONS", "0xD4", "", "", "TOKEN_ACC", "", "", "" },
{"CLR", "C", "Clear Carry", 1, 12, "BOOLEAN VARIABLE MANIPULATION", "0xC3", "", "", "TOKEN_C", "", "", "" },
{"CLR", "bit", "Clear direct bit", 2, 12, "BOOLEAN VARIABLE MANIPULATION", "0xC2", "$1 ", "", "TOKEN_NUM", "", "", "" },
{"SETB", "C", "Set Carry", 1, 12, "BOOLEAN VARIABLE MANIPULATION", "0xD3", "", "", "TOKEN_C", "", "", "" },
{"SETB", "bit", "Set direct bit", 2, 12, "BOOLEAN VARIABLE MANIPULATION", "0xD2", "$1 ", "", "TOKEN_NUM", "", "", "" },
{"CPL", "C", "Complement Carry", 1, 12, "BOOLEAN VARIABLE MANIPULATION", "0xB3", "", "", "TOKEN_C", "", "", "" },
{"CPL", "bit", "Complement direct bit", 2, 12, "BOOLEAN VARIABLE MANIPULATION", "0xB2", "$1 ", "", "TOKEN_NUM", "", "", "" },
{"ANL", "C,bit", "AND direct bit to CARRY", 2, 24, "BOOLEAN VARIABLE MANIPULATION", "0x82", "$2 ", "", "TOKEN_C", "TOKEN_NUM", "", "" },
{"ANL", "C,/bit", "AND complement of direct bit to Carry", 2, 24, "BOOLEAN VARIABLE MANIPULATION", "0xB0", "$2 ", "", "TOKEN_C", "TOKEN_DIV_NUM", "", "" },
{"ORL", "C,bit", "OR direct bit to Carry", 2, 24, "BOOLEAN VARIABLE MANIPULATION", "0x72", "$2 ", "", "TOKEN_C", "TOKEN_NUM", "", "" },
{"ORL", "C,/bit", "OR complement of direct bit to Carry", 2, 24, "BOOLEAN VARIABLE MANIPULATION", "0xA0", "$2 ", "", "TOKEN_C", "TOKEN_DIV_NUM", "", "" },
{"MOV", "C,bit", "Move direct bit to Carry", 2, 12, "BOOLEAN VARIABLE MANIPULATION", "0xA2", "$2 ", "", "TOKEN_C", "TOKEN_NUM", "", "" },
{"MOV", "bit,C", "Move Carry to direct bit", 2, 24, "BOOLEAN VARIABLE MANIPULATION", "0x92", "$1 ", "", "TOKEN_NUM", "TOKEN_C", "", "" },
{"JC", "rel", "Jump if Carry is set", 2, 24, "BOOLEAN VARIABLE MANIPULATION", "0x40", "$1 ", "", "TOKEN_KEYWORD", "", "", "" },
{"JNC", "rel", "Jump if Carry not set", 2, 24, "BOOLEAN VARIABLE MANIPULATION", "0x50", "$1 ", "", "TOKEN_KEYWORD", "", "", "" },
{"JB", "bit,rel", "Jump if direct Bit is set", 3, 24, "BOOLEAN VARIABLE MANIPULATION", "0x20", "$1 ", "$2", "TOKEN_NUM", "TOKEN_KEYWORD", "", "" },
{"JNB", "bit,rel", "Jump if direct Bit is Not set", 3, 24, "BOOLEAN VARIABLE MANIPULATION", "0x30", "$1 ", "$2", "TOKEN_NUM", "TOKEN_KEYWORD", "", "" },
{"JBC", "bit,rel", "Jump if direct Bit is set & clear bit", 3, 24, "BOOLEAN VARIABLE MANIPULATION", "0x10", "$1 ", "$2", "TOKEN_NUM", "TOKEN_KEYWORD", "", "" },
{"MOV", "A,Rn", "Move register to Accumulator", 1, 12, "DATA TRANSFER", "0xe8+$2", "", "", "TOKEN_ACC", "TOKEN_RN", "", "" },
{"MOV", "A,direct", "Move direct byte to Accumulator", 2, 12, "DATA TRANSFER", "0xe5", "$2 ", "", "TOKEN_ACC", "TOKEN_NUM", "", "" },
{"MOV", "A,@Ri", "Move indirect RAM to Accumulator", 1, 12, "DATA TRANSFER", "0xe6+$2", "", "", "TOKEN_ACC", "TOKEN_AT_RI", "", "" },
{"MOV", "A,#data", "Move immediate data to Accumulator", 2, 12, "DATA TRANSFER", "0x74", "$2 ", "", "TOKEN_ACC", "TOKEN_J_DATA", "", "" },
{"MOV", "Rn,A", "Move Accumulator to register", 1, 12, "DATA TRANSFER", "0xF8+$1", "", "", "TOKEN_RN", "TOKEN_ACC", "", "" },
{"MOV", "Rn,direct", "Move direct byte to register", 2, 24, "DATA TRANSFER", "0xA8+$1", "$2 ", "", "TOKEN_RN", "TOKEN_NUM", "", "" },
{"MOV", "Rn,#data", "Move immediate data to register", 2, 12, "DATA TRANSFER", "0x78+$1", "$2 ", "", "TOKEN_RN", "TOKEN_J_DATA", "", "" },
{"MOV", "direct,A", "Move Accumulator to direct byte", 2, 12, "DATA TRANSFER", "0xF5", "$1 ", "", "TOKEN_NUM", "TOKEN_ACC", "", "" },
{"MOV", "direct,Rn", "Move register to direct byte", 2, 24, "DATA TRANSFER", "0x88+$2", "$1 ", "", "TOKEN_NUM", "TOKEN_RN", "", "" },
{"MOV", "direct,direct", "Move direct byte to direct", 3, 24, "DATA TRANSFER", "0x85", "$2 ", "$1", "TOKEN_NUM", "TOKEN_NUM", "", "" },
{"MOV", "direct,@Ri", "Move indirect RAM to direct byte", 2, 24, "DATA TRANSFER", "0x86+$2", "$1 ", "", "TOKEN_NUM", "TOKEN_AT_RI", "", "" },
{"MOV", "direct,#data", "Move immediate data to direct byte", 3, 24, "DATA TRANSFER", "0x75", "$1 ", "$2", "TOKEN_NUM", "TOKEN_J_DATA", "", "" },
{"MOV", "@Ri,A", "Move Accumulator to indirect RAM", 1, 12, "DATA TRANSFER", "0xF6+$1", "", "", "TOKEN_AT_RI", "TOKEN_ACC", "", "" },
{"MOV", "@Ri,direct", "Move direct byte to indirect RAM", 2, 24, "DATA TRANSFER", "0xA6+$1", "$2 ", "", "TOKEN_AT_RI", "TOKEN_NUM", "", "" },
{"MOV", "@Ri,#data", "Move immediate data to indirect RAM", 2, 12, "DATA TRANSFER", "0x76+$1", "$2 ", "", "TOKEN_AT_RI", "TOKEN_J_DATA", "", "" },
{"MOV", "DPTR,#data16", "Load Data Pointer with a 16-bit constant", 3, 24, "DATA TRANSFER", "0x90", "($2 &0xff00)>>8", "($2 &0xff)", "TOKEN_DPTR", "TOKEN_J_DATA", "", "" },
{"MOVC", "A,@A+DPTR", "Move Code byte relative to DPTR to Acc", 1, 24, "DATA TRANSFER", "0x93", "", "", "TOKEN_ACC", "TOKEN_AT_A_PLUS_DPTR", "", "" },
{"MOVC", "A,@A+PC", "Move Code byte relative to PC to Acc", 1, 24, "DATA TRANSFER", "0x83", "", "", "TOKEN_ACC", "TOKEN_AT_A_PLUS_PC", "", "" },
{"MOVX", "A,@Ri", "Move External RAM (8- bit addr) to Acc", 1, 24, "DATA TRANSFER", "0xe2+$2", "", "", "TOKEN_ACC", "TOKEN_AT_RI", "", "" },
{"MOVX", "A,@DPTR", "Move Exernal RAM (16- bit addr) to Acc", 1, 24, "DATA TRANSFER", "0xe0", "", "", "TOKEN_ACC", "TOKEN_AT_DPTR", "", "" },
{"MOVX", "@Ri,A", "Move Acc to External RAM (8-bit addr)", 1, 24, "DATA TRANSFER", "0xf2+$1", "", "", "TOKEN_AT_RI", "TOKEN_ACC", "", "" },
{"MOVX", "@DPTR,A", "Move Acc to External RAM (16-bit addr)", 1, 24, "DATA TRANSFER", "0xf0", "", "", "TOKEN_AT_DPTR", "TOKEN_ACC", "", "" },
{"PUSH", "direct", "Push direct byte onto stack", 2, 24, "DATA TRANSFER", "0xC0", "$1 ", "", "TOKEN_NUM", "", "", "" },
{"POP", "direct", "Pop direct byte from stack", 2, 24, "DATA TRANSFER", "0xD0", "$1 ", "", "TOKEN_NUM", "", "", "" },
{"XCH", "A,Rn", "Exchange register with Accumulator", 1, 12, "DATA TRANSFER", "0xC8+$2", "", "", "TOKEN_ACC", "TOKEN_RN", "", "" },
{"XCH", "A,direct", "Exchange direct byte with Accumulator", 2, 12, "DATA TRANSFER", "0xC5", "$2 ", "", "TOKEN_ACC", "TOKEN_NUM", "", "" },
{"XCH", "A,@Ri", "Exchange indirect RAM with Accumulator", 1, 12, "DATA TRANSFER", "0xC6+$2", "", "", "TOKEN_ACC", "TOKEN_AT_RI", "", "" },
{"XCHD", "A,@Ri", "Exchange low-order Digit indirect RAM with Acc", 1, 12, "DATA TRANSFER", "0xD6+$2", "", "", "TOKEN_ACC", "TOKEN_AT_RI", "", "" },
{"ANL", "A,Rn", "AND Register to Accumulator", 1, 12, "LOGICAL OPERATIONS", "0x58+$2", "", "", "TOKEN_ACC", "TOKEN_RN", "", "" },
{"ANL", "A,direct", "AND direct byte to Accumulator", 2, 12, "LOGICAL OPERATIONS", "0x55", "$2 ", "", "TOKEN_ACC", "TOKEN_NUM", "", "" },
{"ANL", "A,@Ri", "AND indirect RAM to Accumulator", 1, 12, "LOGICAL OPERATIONS", "0x56+$2", "", "", "TOKEN_ACC", "TOKEN_AT_RI", "", "" },
{"ANL", "A,#data", "AND immediate data to Accumulator", 2, 12, "LOGICAL OPERATIONS", "0x54", "$2 ", "", "TOKEN_ACC", "TOKEN_J_DATA", "", "" },
{"ANL", "direct,A", "AND Accumulator to direct byte", 2, 12, "LOGICAL OPERATIONS", "0x52", "$1 ", "", "TOKEN_NUM", "TOKEN_ACC", "", "" },
{"ANL", "direct,#data", "AND immediate data to direct byte", 3, 24, "LOGICAL OPERATIONS", "0x53", "$1 ", "$2", "TOKEN_NUM", "TOKEN_J_DATA", "", "" },
{"ORL", "A,Rn", "OR register to Accumulator", 1, 12, "LOGICAL OPERATIONS", "0x48+$2", "", "", "TOKEN_ACC", "TOKEN_RN", "", "" },
{"ORL", "A,direct", "OR direct byte to Accumulator", 2, 12, "LOGICAL OPERATIONS", "0x45", "$2 ", "", "TOKEN_ACC", "TOKEN_NUM", "", "" },
{"ORL", "A,@Ri", "OR indirect RAM to Accumulator", 1, 12, "LOGICAL OPERATIONS", "0x46+$2", "", "", "TOKEN_ACC", "TOKEN_AT_RI", "", "" },
{"ORL", "A,#data", "OR immediate data to Accumulator", 2, 12, "LOGICAL OPERATIONS", "0x44", "$2 ", "", "TOKEN_ACC", "TOKEN_J_DATA", "", "" },
{"ORL", "direct,A", "OR Accumulator to direct byte", 2, 12, "LOGICAL OPERATIONS", "0x42", "$1 ", "", "TOKEN_NUM", "TOKEN_ACC", "", "" },
{"ORL", "direct,#data", "OR immediate data to direct byte", 3, 24, "LOGICAL OPERATIONS", "0x43", "$1 ", "$2", "TOKEN_NUM", "TOKEN_J_DATA", "", "" },
{"XRL", "A,Rn", "Exclusive-OR register to Accumulator", 1, 12, "LOGICAL OPERATIONS", "0x68+$2", "", "", "TOKEN_ACC", "TOKEN_RN", "", "" },
{"XRL", "A,direct", "Exclusive-OR direct byte to Accumulator", 2, 12, "LOGICAL OPERATIONS", "0x65", "$2 ", "", "TOKEN_ACC", "TOKEN_NUM", "", "" },
{"XRL", "A,@Ri", "Exclusive-OR indirect RAM to Accumulator", 1, 12, "LOGICAL OPERATIONS", "0x66+$2", "", "", "TOKEN_ACC", "TOKEN_AT_RI", "", "" },
{"XRL", "A,#data", "Exclusive-OR immediate data to Accumulator", 2, 12, "LOGICAL OPERATIONS", "0x64", "$2 ", "", "TOKEN_ACC", "TOKEN_J_DATA", "", "" },
{"XRL", "direct,A", "Exclusive-OR Accumulator to direct byte", 2, 12, "LOGICAL OPERATIONS", "0x62", "$1 ", "", "TOKEN_NUM", "TOKEN_ACC", "", "" },
{"XRL", "direct,#data", "Exclusive-OR immediate data to direct byte", 3, 24, "LOGICAL OPERATIONS", "0x63", "$1 ", "$2", "TOKEN_NUM", "TOKEN_J_DATA", "", "" },
{"CLR", "A", "Clear Accumulator", 1, 12, "LOGICAL OPERATIONS", "0xE4", "", "", "TOKEN_ACC", "", "", "" },
{"CPL", "A", "Complement Accumulator", 1, 12, "LOGICAL OPERATIONS", "0xF4", "", "", "TOKEN_ACC", "", "", "" },
{"RL", "A", "Rotate Accumulator Left", 1, 12, "LOGICAL OPERATIONS", "0x23", "", "", "TOKEN_ACC", "", "", "" },
{"RLC", "A", "Rotate Accumulator Left through the Carry", 1, 12, "LOGICAL OPERATIONS", "0x33", "", "", "TOKEN_ACC", "", "", "" },
{"RR", "A", "Rotate Accumulator Right", 1, 12, "LOGICAL OPERATIONS", "0x03", "", "", "TOKEN_ACC", "", "", "" },
{"RRC", "A", "Rotate Accumulator Right through the Carry", 1, 12, "LOGICAL OPERATIONS", "0x13", "", "", "TOKEN_ACC", "", "", "" },
{"SWAP", "A", "Swap nibbles within the Accumulator", 1, 12, "LOGICAL OPERATIONS", "0xC4", "", "", "TOKEN_ACC", "", "", "" },
{"ACALL", "addr11", "Absolute Subroutine Call", 2, 24, "PROGRAM BRANCHING", "(($1&0x700)>>3)+0x11", "($1&0xff)", "", "TOKEN_KEYWORD", "", "", "" },
{"LCALL", "addr16", "Long Subroutine Call", 3, 24, "PROGRAM BRANCHING", "0x12", "($1 &0xff00)>>8", "($1 &0xff)", "TOKEN_KEYWORD", "", "", "" },
{"RET", "", "Return from Subroutine", 1, 24, "PROGRAM BRANCHING", "0x22", "", "", "", "", "", "" },
{"RETI", "", "Return from interrupt", 1, 24, "PROGRAM BRANCHING", "0x32", "", "", "", "", "", "" },
{"AJMP", "addr11", "Absolute Jump", 2, 24, "PROGRAM BRANCHING", "(($1&0x700)>>3)+1", "$1&0xff", "", "TOKEN_KEYWORD", "", "", "" },
{"LJMP", "addr16", "Long Jump", 3, 24, "PROGRAM BRANCHING", "0x02", "($1 &0xff00)>>8", "($1 &0xff)", "TOKEN_KEYWORD", "", "", "" },
{"SJMP", "rel", "Short Jump (relative addr)", 2, 24, "PROGRAM BRANCHING", "0x80", "$1 ", "", "TOKEN_KEYWORD", "", "", "" },
{"JMP", "@A+DPTR", "Jump indirect relative to the DPTR", 1, 24, "PROGRAM BRANCHING", "0x73", "", "", "TOKEN_AT_A_PLUS_DPTR", "", "", "" },
{"JZ", "rel", "Jump if Accumulator is Zero", 2, 24, "PROGRAM BRANCHING", "0x60", "$1 ", "", "TOKEN_KEYWORD", "", "", "" },
{"JNZ", "rel", "Jump if Accumulator is Not Zero", 2, 24, "PROGRAM BRANCHING", "0x70", "$1 ", "", "TOKEN_KEYWORD", "", "", "" },
{"CJNE", "A,direct,rel", "Compare direct byte to Acc and Jump if Not Equal", 3, 24, "PROGRAM BRANCHING", "0xB5", "$2 ", "$3", "TOKEN_ACC", "TOKEN_NUM", "TOKEN_KEYWORD", "" },
{"CJNE", "A,#data,rel", "Compare immediate to Acc and Jump if Not Equal", 3, 24, "PROGRAM BRANCHING", "0xB4", "$2 ", "$3", "TOKEN_ACC", "TOKEN_J_DATA", "TOKEN_KEYWORD", "" },
{"CJNE", "Rn,#data,rel", "Compare immediate to register and Jump if Not Equal", 3, 24, "PROGRAM BRANCHING", "0xB8+$1", "$2 ", "$3", "TOKEN_RN", "TOKEN_J_DATA", "TOKEN_KEYWORD", "" },
{"CJNE", "@Ri,#data,rel", "Compare immediate to indirect and Jump if Not Equal", 3, 24, "PROGRAM BRANCHING", "0xB6+$1", "$2 ", "$3", "TOKEN_AT_RI", "TOKEN_J_DATA", "TOKEN_KEYWORD", "" },
{"DJNZ", "Rn,rel", "Decrement register and Jump if Not Zero", 2, 24, "PROGRAM BRANCHING", "0xD8+$1", "$2 ", "", "TOKEN_RN", "TOKEN_KEYWORD", "", "" },
{"DJNZ", "direct,rel", "Decrement direct byte and Jump if Not Zero", 3, 24, "PROGRAM BRANCHING", "0xD5", "$1 ", "$2", "TOKEN_NUM", "TOKEN_KEYWORD", "", "" },
{"NOP", "", "No Operation", 1, 12, "PROGRAM BRANCHING", "0x00", "", "", "", "", "", "" },
{"JMP", "rel", "Short Jump (relative addr)", 2, 24, "PROGRAM BRANCHING", "0x80", "$1 ", "", "TOKEN_KEYWORD", "", "", "" },
{"CALL", "addr11", "Absolute Subroutine Call", 2, 24, "PROGRAM BRANCHING", "(($1&0x700)>>3)+0x11", "($1&0xff)", "", "TOKEN_KEYWORD", "", "", "" },
{"SIMTRAP", "direct,direct", "A5 test A if not zero", 3, 12, "TEST", "0xA5", "$1 ", "$2", "TOKEN_NUM", "TOKEN_NUM", "", "" }

};
hex_code_asm_table g_hex_table[]={
{0x0,1,"NOP","",-1,"","",""},
{0x1,2,"AJMP","abs code addr",1,"(((($0>>5)<<8)+($1&0xff))&0x7ff)","",""},
{0x2,3,"LJMP","abs code addr",1,"((($1<<8) + ($2&0xff))&0xffff)","",""},
{0x3,1,"RR","A",-1,"","",""},
{0x4,1,"INC","A",-1,"","",""},
{0x5,2,"INC","data addr",1,"(($1)&0xff)","",""},
{0x6,1,"INC","@R0",-1,"","",""},
{0x7,1,"INC","@R1",-1,"","",""},
{0x8,1,"INC","R0",-1,"","",""},
{0x9,1,"INC","R1",-1,"","",""},
{0x0A,1,"INC","R2",-1,"","",""},
{0x0B,1,"INC","R3",-1,"","",""},
{0x0C,1,"INC","R4",-1,"","",""},
{0x0D,1,"INC","R5",-1,"","",""},
{0x0E,1,"INC","R6",-1,"","",""},
{0x0F,1,"INC","R7",-1,"","",""},
{0x10,3,"JBC","bit addr,rel code addr",2,"(($1)&0xff)","(($2)&0xff)",""},
{0x11,2,"ACALL","abs code addr",1,"((($1&0xff) + (($0&0xe0)<<3))&0x7ff)","",""},
{0x12,3,"LCALL","abs code addr",1,"((($1<<8) + ($2&0xff))&0xffff)","",""},
{0x13,1,"RRC","A",-1,"","",""},
{0x14,1,"DEC","A",-1,"","",""},
{0x15,2,"DEC","data addr",1,"(($1)&0xff)","",""},
{0x16,1,"DEC","@R0",-1,"","",""},
{0x17,1,"DEC","@R1",-1,"","",""},
{0x18,1,"DEC","R0",-1,"","",""},
{0x19,1,"DEC","R1",-1,"","",""},
{0x1A,1,"DEC","R2",-1,"","",""},
{0x1B,1,"DEC","R3",-1,"","",""},
{0x1C,1,"DEC","R4",-1,"","",""},
{0x1D,1,"DEC","R5",-1,"","",""},
{0x1E,1,"DEC","R6",-1,"","",""},
{0x1F,1,"DEC","R7",-1,"","",""},
{0x20,3,"JB","bit addr,rel code addr",2,"(($1+0)&0xff)","(($2)&0xff)",""},
{0x21,2,"AJMP","abs code addr",1,"(((($0>>5)<<8)+($1&0xff))&0x7ff)","",""},
{0x22,1,"RET","",-1,"","",""},
{0x23,1,"RL","A",-1,"","",""},
{0x24,2,"ADD","A,#data",2,"","(($1+0)&0xff)",""},
{0x25,2,"ADD","A,data addr",2,"","(($1+0)&0xff)",""},
{0x26,1,"ADD","A,@R0",-1,"","",""},
{0x27,1,"ADD","A,@R1",-1,"","",""},
{0x28,1,"ADD","A,R0",-1,"","",""},
{0x29,1,"ADD","A,R1",-1,"","",""},
{0x2A,1,"ADD","A,R2",-1,"","",""},
{0x2B,1,"ADD","A,R3",-1,"","",""},
{0x2C,1,"ADD","A,R4",-1,"","",""},
{0x2D,1,"ADD","A,R5",-1,"","",""},
{0x2E,1,"ADD","A,R6",-1,"","",""},
{0x2F,1,"ADD","A,R7",-1,"","",""},
{0x30,3,"JNB","bit addr,rel code addr",2,"(($1)&0xff)","(($2)&0xff)",""},
{0x31,2,"ACALL","abs code addr",1,"((($1&0xff) + (($0&0xe0)<<3))&0x7ff)","",""},
{0x32,1,"RETI","",-1,"","",""},
{0x33,1,"RLC","A",-1,"","",""},
{0x34,2,"ADDC","A,#data",2,"","(($1)&0xff)",""},
{0x35,2,"ADDC","A,data addr",2,"","(($1)&0xff)",""},
{0x36,1,"ADDC","A,@R0",-1,"","",""},
{0x37,1,"ADDC","A,@R1",-1,"","",""},
{0x38,1,"ADDC","A,R0",-1,"","",""},
{0x39,1,"ADDC","A,R1",-1,"","",""},
{0x3A,1,"ADDC","A,R2",-1,"","",""},
{0x3B,1,"ADDC","A,R3",-1,"","",""},
{0x3C,1,"ADDC","A,R4",-1,"","",""},
{0x3D,1,"ADDC","A,R5",-1,"","",""},
{0x3E,1,"ADDC","A,R6",-1,"","",""},
{0x3F,1,"ADDC","A,R7",-1,"","",""},
{0x40,2,"JC","rel code addr",1,"(($1)&0xff)","",""},
{0x41,2,"AJMP","abs code addr",1,"(((($0>>5)<<8)+($1&0xff))&0x7ff)","",""},
{0x42,2,"ORL","data addr,A",2,"(($1)&0xff)","",""},
{0x43,3,"ORL","data addr,#data",2,"(($1)&0xff)","(($2)&0xff)",""},
{0x44,2,"ORL","A,#data",2,"","(($1)&0xff)",""},
{0x45,2,"ORL","A,data addr",2,"","(($1)&0xff)",""},
{0x46,1,"ORL","A,@R0",-1,"","",""},
{0x47,1,"ORL","A,@R1",-1,"","",""},
{0x48,1,"ORL","A,R0",-1,"","",""},
{0x49,1,"ORL","A,R1",-1,"","",""},
{0x4A,1,"ORL","A,R2",-1,"","",""},
{0x4B,1,"ORL","A,R3",-1,"","",""},
{0x4C,1,"ORL","A,R4",-1,"","",""},
{0x4D,1,"ORL","A,R5",-1,"","",""},
{0x4E,1,"ORL","A,R6",-1,"","",""},
{0x4F,1,"ORL","A,R7",-1,"","",""},
{0x50,2,"JNC","rel code addr",1,"(($1)&0xff)","",""},
{0x51,2,"ACALL","abs code addr",1,"((($1&0xff) + (($0&0xe0)<<3))&0x7ff)","",""},
{0x52,2,"ANL","data addr,A",2,"(($1)&0xff)","",""},
{0x53,3,"ANL","data addr,#data",2,"(($1)&0xff)","(($2)&0xff)",""},
{0x54,2,"ANL","A,#data",2,"","(($1)&0xff)",""},
{0x55,2,"ANL","A,data addr",2,"","(($1)&0xff)",""},
{0x56,1,"ANL","A,@R0",-1,"","",""},
{0x57,1,"ANL","A,@R1",-1,"","",""},
{0x58,1,"ANL","A,R0",-1,"","",""},
{0x59,1,"ANL","A,R1",-1,"","",""},
{0x5A,1,"ANL","A,R2",-1,"","",""},
{0x5B,1,"ANL","A,R3",-1,"","",""},
{0x5C,1,"ANL","A,R4",-1,"","",""},
{0x5D,1,"ANL","A,R5",-1,"","",""},
{0x5E,1,"ANL","A,R6",-1,"","",""},
{0x5F,1,"ANL","A,R7",-1,"","",""},
{0x60,2,"JZ","rel code addr",1,"(($1)&0xff)","",""},
{0x61,2,"AJMP","abs code addr",1,"(((($0>>5)<<8)+($1&0xff))&0x7ff)","",""},
{0x62,2,"XRL","data addr,A",2,"(($1)&0xff)","",""},
{0x63,3,"XRL","data addr,#data",2,"(($1)&0xff)","(($2)&0xff)",""},
{0x64,2,"XRL","A,#data",2,"","(($1)&0xff)",""},
{0x65,2,"XRL","A,data addr",2,"","(($1)&0xff)",""},
{0x66,1,"XRL","A,@R0",-1,"","",""},
{0x67,1,"XRL","A,@R1",-1,"","",""},
{0x68,1,"XRL","A,R0",-1,"","",""},
{0x69,1,"XRL","A,R1",-1,"","",""},
{0x6A,1,"XRL","A,R2",-1,"","",""},
{0x6B,1,"XRL","A,R3",-1,"","",""},
{0x6C,1,"XRL","A,R4",-1,"","",""},
{0x6D,1,"XRL","A,R5",-1,"","",""},
{0x6E,1,"XRL","A,R6",-1,"","",""},
{0x6F,1,"XRL","A,R7",-1,"","",""},
{0x70,2,"JNZ","rel code addr",1,"(($1)&0xff)","",""},
{0x71,2,"ACALL","abs code addr",1,"((($1&0xff) + (($0&0xe0)<<3))&0x7ff)","",""},
{0x72,2,"ORL","C,bit addr",2,"","(($1)&0xff)",""},
{0x73,1,"JMP","@A+DPTR",-1,"","",""},
{0x74,2,"MOV","A,#data",2,"","(($1)&0xff)",""},
{0x75,3,"MOV","data addr,#data",2,"(($1)&0xff)","(($2)&0xff)",""},
{0x76,2,"MOV","@R0,#data",2,"","(($1)&0xff)",""},
{0x77,2,"MOV","@R1,#data",2,"","(($1)&0xff)",""},
{0x78,2,"MOV","R0,#data",2,"","(($1)&0xff)",""},
{0x79,2,"MOV","R1,#data",2,"","(($1)&0xff)",""},
{0x7A,2,"MOV","R2,#data",2,"","(($1)&0xff)",""},
{0x7B,2,"MOV","R3,#data",2,"","(($1)&0xff)",""},
{0x7C,2,"MOV","R4,#data",2,"","(($1)&0xff)",""},
{0x7D,2,"MOV","R5,#data",2,"","(($1)&0xff)",""},
{0x7E,2,"MOV","R6,#data",2,"","(($1)&0xff)",""},
{0x7F,2,"MOV","R7,#data",2,"","(($1)&0xff)",""},
{0x80,2,"SJMP","rel code addr",1,"(($1)&0xff)","",""},
{0x81,2,"AJMP","abs code addr",1,"(((($0>>5)<<8)+($1&0xff))&0x7ff)","",""},
{0x82,2,"ANL","C,bit addr",2,"","(($1)&0xff)",""},
{0x83,1,"MOVC","A,@A+PC",-1,"","",""},
{0x84,1,"DIV","AB",-1,"","",""},
{0x85,3,"MOV","data addr,data addr",2,"(($2)&0xff)","(($1)&0xff)",""},
{0x86,2,"MOV","data addr,@R0",2,"(($1)&0xff)","",""},
{0x87,2,"MOV","data addr,@R1",2,"(($1)&0xff)","",""},
{0x88,2,"MOV","data addr,R0",2,"(($1)&0xff)","",""},
{0x89,2,"MOV","data addr,R1",2,"(($1)&0xff)","",""},
{0x8A,2,"MOV","data addr,R2",2,"(($1)&0xff)","",""},
{0x8B,2,"MOV","data addr,R3",2,"(($1)&0xff)","",""},
{0x8C,2,"MOV","data addr,R4",2,"(($1)&0xff)","",""},
{0x8D,2,"MOV","data addr,R5",2,"(($1)&0xff)","",""},
{0x8E,2,"MOV","data addr,R6",2,"(($1)&0xff)","",""},
{0x8F,2,"MOV","data addr,R7",2,"(($1)&0xff)","",""},
{0x90,3,"MOV","DPTR,#data",2,"","((($1<<8)+($2&0xff))&0xffff)",""},
{0x91,2,"ACALL","abs code addr",1,"((($1&0xff) + (($0&0xe0)<<3))&0x7ff)","",""},
{0x92,2,"MOV","bit addr,C",2,"(($1)&0xff)","",""},
{0x93,1,"MOVC","A,@A+DPTR",-1,"","",""},
{0x94,2,"SUBB","A,#data",2,"","(($1)&0xff)",""},
{0x95,2,"SUBB","A,data addr",2,"","(($1)&0xff)",""},
{0x96,1,"SUBB","A,@R0",-1,"","",""},
{0x97,1,"SUBB","A,@R1",-1,"","",""},
{0x98,1,"SUBB","A,R0",-1,"","",""},
{0x99,1,"SUBB","A,R1",-1,"","",""},
{0x9A,1,"SUBB","A,R2",-1,"","",""},
{0x9B,1,"SUBB","A,R3",-1,"","",""},
{0x9C,1,"SUBB","A,R4",-1,"","",""},
{0x9D,1,"SUBB","A,R5",-1,"","",""},
{0x9E,1,"SUBB","A,R6",-1,"","",""},
{0x9F,1,"SUBB","A,R7",-1,"","",""},
{0xA0,2,"ORL","C,/bit addr",2,"","(($1)&0xff)",""},
{0xA1,2,"AJMP","abs code addr",1,"(((($0>>5)<<8)+($1&0xff))&0x7ff)","",""},
{0xA2,2,"MOV","C,bit addr",2,"","(($1)&0xff)",""},
{0xA3,1,"INC","DPTR",-1,"","",""},
{0xA4,1,"MUL","AB",-1,"","",""},
{0xA5,3,"SIMTRAP","data addr,data addr",2,"(($1)&0xff)","(($2)&0xff)",""},
{0xA6,2,"MOV","@R0,data addr",2,"","(($1)&0xff)",""},
{0xA7,2,"MOV","@R1,data addr",2,"","(($1)&0xff)",""},
{0xA8,2,"MOV","R0,data addr",2,"","(($1)&0xff)",""},
{0xA9,2,"MOV","R1,data addr",2,"","(($1)&0xff)",""},
{0xAA,2,"MOV","R2,data addr",2,"","(($1)&0xff)",""},
{0xAB,2,"MOV","R3,data addr",2,"","(($1)&0xff)",""},
{0xAC,2,"MOV","R4,data addr",2,"","(($1)&0xff)",""},
{0xAD,2,"MOV","R5,data addr",2,"","(($1)&0xff)",""},
{0xAE,2,"MOV","R6,data addr",2,"","(($1)&0xff)",""},
{0xAF,2,"MOV","R7,data addr",2,"","(($1)&0xff)",""},
{0xB0,2,"ANL","C,/bit addr",2,"","(($1)&0xff)",""},
{0xB1,2,"ACALL","abs code addr",1,"((($1&0xff) + (($0&0xe0)<<3))&0x7ff)","",""},
{0xB2,2,"CPL","bit addr",1,"(($1)&0xff)","",""},
{0xB3,1,"CPL","C",-1,"","",""},
{0xB4,3,"CJNE","A,#data,rel code addr",3,"","(($1)&0xff)","(($2)&0xff)"},
{0xB5,3,"CJNE","A,data addr,rel code addr",3,"","(($1)&0xff)","(($2)&0xff)"},
{0xB6,3,"CJNE","@R0,#data,rel code addr",3,"","(($1)&0xff)","(($2)&0xff)"},
{0xB7,3,"CJNE","@R1,#data,rel code addr",3,"","(($1)&0xff)","(($2)&0xff)"},
{0xB8,3,"CJNE","R0,#data,rel code addr",3,"","(($1)&0xff)","(($2)&0xff)"},
{0xB9,3,"CJNE","R1,#data,rel code addr",3,"","(($1)&0xff)","(($2)&0xff)"},
{0xBA,3,"CJNE","R2,#data,rel code addr",3,"","(($1)&0xff)","(($2)&0xff)"},
{0xBB,3,"CJNE","R3,#data,rel code addr",3,"","(($1)&0xff)","(($2)&0xff)"},
{0xBC,3,"CJNE","R4,#data,rel code addr",3,"","(($1)&0xff)","(($2)&0xff)"},
{0xBD,3,"CJNE","R5,#data,rel code addr",3,"","(($1)&0xff)","(($2)&0xff)"},
{0xBE,3,"CJNE","R6,#data,rel code addr",3,"","(($1)&0xff)","(($2)&0xff)"},
{0xBF,3,"CJNE","R7,#data,rel code addr",3,"","(($1)&0xff)","(($2)&0xff)"},
{0xC0,2,"PUSH","data addr",1,"(($1)&0xff)","",""},
{0xC1,2,"AJMP","abs code addr",1,"(((($0>>5)<<8)+($1&0xff))&0x7ff)","",""},
{0xC2,2,"CLR","bit addr",1,"(($1)&0xff)","",""},
{0xC3,1,"CLR","C",-1,"","",""},
{0xC4,1,"SWAP","A",-1,"","",""},
{0xC5,2,"XCH","A,data addr",2,"","(($1)&0xff)",""},
{0xC6,1,"XCH","A,@R0",-1,"","",""},
{0xC7,1,"XCH","A,@R1",-1,"","",""},
{0xC8,1,"XCH","A,R0",-1,"","",""},
{0xC9,1,"XCH","A,R1",-1,"","",""},
{0xCA,1,"XCH","A,R2",-1,"","",""},
{0xCB,1,"XCH","A,R3",-1,"","",""},
{0xCC,1,"XCH","A,R4",-1,"","",""},
{0xCD,1,"XCH","A,R5",-1,"","",""},
{0xCE,1,"XCH","A,R6",-1,"","",""},
{0xCF,1,"XCH","A,R7",-1,"","",""},
{0xD0,2,"POP","data addr",1,"(($1)&0xff)","",""},
{0xD1,2,"ACALL","abs code addr",1,"((($1&0xff) + (($0&0xe0)<<3))&0x7ff)","",""},
{0xD2,2,"SETB","bit addr",1,"(($1)&0xff)","",""},
{0xD3,1,"SETB","C",-1,"","",""},
{0xD4,1,"DA","A",-1,"","",""},
{0xD5,3,"DJNZ","data addr,rel code addr",2,"(($1)&0xff)","(($2)&0xff)",""},
{0xD6,1,"XCHD","A,@R0",-1,"","",""},
{0xD7,1,"XCHD","A,@R1",-1,"","",""},
{0xD8,2,"DJNZ","R0,rel code addr",2,"","(($1)&0xff)",""},
{0xD9,2,"DJNZ","R1,rel code addr",2,"","(($1)&0xff)",""},
{0xDA,2,"DJNZ","R2,rel code addr",2,"","(($1)&0xff)",""},
{0xDB,2,"DJNZ","R3,rel code addr",2,"","(($1)&0xff)",""},
{0xDC,2,"DJNZ","R4,rel code addr",2,"","(($1)&0xff)",""},
{0xDD,2,"DJNZ","R5,rel code addr",2,"","(($1)&0xff)",""},
{0xDE,2,"DJNZ","R6,rel code addr",2,"","(($1)&0xff)",""},
{0xDF,2,"DJNZ","R7,rel code addr",2,"","(($1)&0xff)",""},
{0xE0,1,"MOVX","A,@DPTR",-1,"","",""},
{0xE1,2,"AJMP","abs code addr",1,"(((($0>>5)<<8)+($1&0xff))&0x7ff)","",""},
{0xE2,1,"MOVX","A,@R0",-1,"","",""},
{0xE3,1,"MOVX","A,@R1",-1,"","",""},
{0xE4,1,"CLR","A",-1,"","",""},
{0xE5,2,"MOV","A,data addr",2,"","(($1)&0xff)",""},
{0xE6,1,"MOV","A,@R0",-1,"","",""},
{0xE7,1,"MOV","A,@R1",-1,"","",""},
{0xE8,1,"MOV","A,R0",-1,"","",""},
{0xE9,1,"MOV","A,R1",-1,"","",""},
{0xEA,1,"MOV","A,R2",-1,"","",""},
{0xEB,1,"MOV","A,R3",-1,"","",""},
{0xEC,1,"MOV","A,R4",-1,"","",""},
{0xED,1,"MOV","A,R5",-1,"","",""},
{0xEE,1,"MOV","A,R6",-1,"","",""},
{0xEF,1,"MOV","A,R7",-1,"","",""},
{0xF0,1,"MOVX","@DPTR,A",-1,"","",""},
{0xF1,2,"ACALL","abs code addr",1,"((($1&0xff) + (($0&0xe0)<<3))&0x7ff)","",""},
{0xF2,1,"MOVX","@R0,A",-1,"","",""},
{0xF3,1,"MOVX","@R1,A",-1,"","",""},
{0xF4,1,"CPL","A",-1,"","",""},
{0xF5,2,"MOV","data addr,A",2,"(($1)&0xff)","",""},
{0xF6,1,"MOV","@R0,A",-1,"","",""},
{0xF7,1,"MOV","@R1,A",-1,"","",""},
{0xF8,1,"MOV","R0,A",-1,"","",""},
{0xF9,1,"MOV","R1,A",-1,"","",""},
{0xFA,1,"MOV","R2,A",-1,"","",""},
{0xFB,1,"MOV","R3,A",-1,"","",""},
{0xFC,1,"MOV","R4,A",-1,"","",""},
{0xFD,1,"MOV","R5,A",-1,"","",""},
{0xFE,1,"MOV","R6,A",-1,"","",""},
{0xFF,1,"MOV","R7,A",-1,"","",""},
};
int g_hex_table_size=sizeof(g_hex_table)/sizeof(g_hex_table[0]);
int g_asm_table_size = sizeof(g_asm_table)/sizeof(g_asm_table[0]);
