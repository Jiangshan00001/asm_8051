
%token  TK_EXTERN  TK_CODE  TK_DATA  TK_BIT  TK_XDATA 
%token  TK_NUMBER  TK_PUBLIC  TK_SEGMENT  TK_EJECT  TK_XSEG 
%token  TK_RSEG  TK_AT  TK_CSEG  TK_DS  TK_DBIG 
%token  TK_EQU  TK_USING  TK_DB  TK_DW  EOL 
%token  TK_ACC  TK_C  TK_AB  TK_AT_DPTR  TK_DPTR 
%token  TK_AT_A_PLUS_PC  TK_AT_A_PLUS_DPTR  TK_AT_RI  TK_RN  I_CONSTANT 
%token  F_CONSTANT  STRING_LITERAL  TK_CMD  TK_MACRO  TK_KEYWORD 
%token  TK_DOLLAR  TK_NOT  TK_HIGH  TK_LOW  TK_SHL 
%token  TK_MOD  TK_SHIFT_LEFT  TK_SHIFT_RIGHT 
%token END 0 "end of file"




%start file
file
	: 
	|  prog_block 
	;
prog_block
	:  EOL 
	|  cmd_text_line 
	|  macro_text_line 
	|  label_text_line 
	|  prog_block  cmd_text_line 
	|  prog_block  macro_text_line 
	|  prog_block  label_text_line 
	|  prog_block  EOL 
	;
cmd_text_line
	:  TK_CMD  EOL 
	|  TK_CMD  opand  EOL 
	|  TK_CMD  opand  ','  opand  EOL 
	|  TK_CMD  opand  ','  opand  ','  opand  EOL 
	|  TK_CMD  opand  ','  opand  ','  opand  ','  opand  EOL 
	;
opand
	:  expr 
	|  '#'  expr 
	|  '/'  expr 
	|  '/'  expr  '.'  expr 
	|  expr  '.'  expr 
	|  TK_ACC 
	|  TK_C 
	|  TK_AB 
	|  TK_AT_DPTR 
	|  TK_DPTR 
	|  TK_AT_A_PLUS_PC 
	|  TK_AT_A_PLUS_DPTR 
	|  TK_AT_RI 
	|  TK_RN 
	;
expr_elem
	:  TK_KEYWORD 
	|  I_CONSTANT 
	|  STRING_LITERAL 
	|  TK_DOLLAR 
	|  '('  expr  ')' 
	;
not_expr
	:  expr_elem 
	|  TK_NOT  expr_elem 
	|  TK_HIGH  expr_elem 
	|  TK_LOW  expr_elem 
	|  expr_elem  TK_SHL  expr_elem 
	|  expr_elem  TK_MOD  expr_elem 
	|  expr_elem  '&'  expr_elem 
	|  expr_elem  TK_SHIFT_RIGHT  expr_elem 
	|  expr_elem  TK_SHIFT_LEFT  expr_elem 
	;
multi_expr
	:  not_expr 
	|  multi_expr  '*'  not_expr 
	|  multi_expr  '/'  not_expr 
	|  multi_expr  '%'  not_expr 
	;
additive_expr
	:  multi_expr 
	|  additive_expr  '+'  multi_expr 
	|  additive_expr  '-'  multi_expr 
	;
expr
	:  additive_expr 
	;
macro_text_line
	:  TK_MACRO  EOL 
	|  TK_MACRO  expr_elem  EOL 
	|  TK_MACRO  expr_elem  expr_elem  EOL 
	|  TK_KEYWORD  TK_MACRO  opand  EOL 
	|  db_list  EOL 
	;
db_list
	:  TK_DB  opand 
	|  db_list  ','  opand 
	|  db_list  opand 
	;
label_text_line
	:  TK_KEYWORD  ':' 
	;
