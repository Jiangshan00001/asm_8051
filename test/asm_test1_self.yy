file->prog_block 
prog_block->prog_block macro_text_line 
-
prog_block->prog_block EOL 
-
prog_block->prog_block EOL 
-
prog_block->prog_block EOL 
-
prog_block->prog_block EOL 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block label_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block label_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block label_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block cmd_text_line 
-
prog_block->prog_block label_text_line 
-
prog_block->prog_block EOL 
-
prog_block->macro_text_line 
macro_text_line->TK_MACRO expr_elem EOL 
-
TK_MACRO(org)
=
expr_elem->I_CONSTANT 
I_CONSTANT(1234H)
=
EOL(
)
=
EOL(
)
=
label_text_line->TK_KEYWORD ':' 
-
TK_KEYWORD(START)
=
(:)
=
cmd_text_line->TK_CMD opand EOL 
-
TK_CMD(LJMP)
=
opand->expr 
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->TK_KEYWORD 
TK_KEYWORD(START)
=
EOL(
)
=
cmd_text_line->TK_CMD opand EOL 
-
TK_CMD(ACALL)
=
opand->expr 
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->TK_KEYWORD 
TK_KEYWORD(TMP1)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(ADD)
=
opand->TK_ACC 
TK_ACC(A)
=
(,)
=
opand->TK_RN 
TK_RN(R1)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(ADD)
=
opand->TK_ACC 
TK_ACC(A)
=
(,)
=
opand->expr 
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->I_CONSTANT 
I_CONSTANT(10H)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(ADD)
=
opand->TK_ACC 
TK_ACC(A)
=
(,)
=
opand->TK_AT_RI 
TK_AT_RI(@R1)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(ADD)
=
opand->TK_ACC 
TK_ACC(A)
=
(,)
=
opand->'#' expr 
-
(#)
=
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->I_CONSTANT 
I_CONSTANT(12H)
=
EOL(
)
=
label_text_line->TK_KEYWORD ':' 
-
TK_KEYWORD(TMP1)
=
(:)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(ADDC)
=
opand->TK_ACC 
TK_ACC(A)
=
(,)
=
opand->TK_RN 
TK_RN(R1)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(ADDC)
=
opand->TK_ACC 
TK_ACC(A)
=
(,)
=
opand->expr 
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->I_CONSTANT 
I_CONSTANT(14H)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(ADDC)
=
opand->TK_ACC 
TK_ACC(A)
=
(,)
=
opand->TK_AT_RI 
TK_AT_RI(@R1)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(ADDC)
=
opand->TK_ACC 
TK_ACC(A)
=
(,)
=
opand->'#' expr 
-
(#)
=
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->I_CONSTANT 
I_CONSTANT(47H)
=
EOL(
)
=
cmd_text_line->TK_CMD opand EOL 
-
TK_CMD(AJMP)
=
opand->expr 
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->TK_KEYWORD 
TK_KEYWORD(TMP1)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(ANL)
=
opand->TK_ACC 
TK_ACC(A)
=
(,)
=
opand->TK_RN 
TK_RN(R6)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(ANL)
=
opand->TK_ACC 
TK_ACC(A)
=
(,)
=
opand->expr 
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->I_CONSTANT 
I_CONSTANT(56H)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(ANL)
=
opand->TK_ACC 
TK_ACC(A)
=
(,)
=
opand->TK_AT_RI 
TK_AT_RI(@R1)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(ANL)
=
opand->TK_ACC 
TK_ACC(A)
=
(,)
=
opand->'#' expr 
-
(#)
=
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->I_CONSTANT 
I_CONSTANT(87H)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(ANL)
=
opand->expr 
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->I_CONSTANT 
I_CONSTANT(09H)
=
(,)
=
opand->TK_ACC 
TK_ACC(A)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(ANL)
=
opand->expr 
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->I_CONSTANT 
I_CONSTANT(78H)
=
(,)
=
opand->'#' expr 
-
(#)
=
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->I_CONSTANT 
I_CONSTANT(43H)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(ANL)
=
opand->TK_C 
TK_C(C)
=
(,)
=
opand->expr 
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->I_CONSTANT 
I_CONSTANT(81H)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(ANL)
=
opand->TK_C 
TK_C(C)
=
(,)
=
opand->'/' expr 
-
(/)
=
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->I_CONSTANT 
I_CONSTANT(81H)
=
EOL(
)
=
label_text_line->TK_KEYWORD ':' 
-
TK_KEYWORD(TMP2)
=
(:)
=
cmd_text_line->TK_CMD opand ',' opand ',' opand EOL 
-
TK_CMD(CJNE)
=
opand->TK_ACC 
TK_ACC(A)
=
(,)
=
opand->expr 
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->I_CONSTANT 
I_CONSTANT(34H)
=
(,)
=
opand->expr 
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->TK_KEYWORD 
TK_KEYWORD(TMP2)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand ',' opand EOL 
-
TK_CMD(CJNE)
=
opand->TK_ACC 
TK_ACC(A)
=
(,)
=
opand->'#' expr 
-
(#)
=
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->I_CONSTANT 
I_CONSTANT(43H)
=
(,)
=
opand->expr 
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->TK_KEYWORD 
TK_KEYWORD(TMP1)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand ',' opand EOL 
-
TK_CMD(CJNE)
=
opand->TK_RN 
TK_RN(R6)
=
(,)
=
opand->'#' expr 
-
(#)
=
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->I_CONSTANT 
I_CONSTANT(54H)
=
(,)
=
opand->expr 
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->TK_KEYWORD 
TK_KEYWORD(TMP1)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand ',' opand EOL 
-
TK_CMD(CJNE)
=
opand->TK_AT_RI 
TK_AT_RI(@R0)
=
(,)
=
opand->'#' expr 
-
(#)
=
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->I_CONSTANT 
I_CONSTANT(54H)
=
(,)
=
opand->expr 
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->TK_KEYWORD 
TK_KEYWORD(TMP1)
=
EOL(
)
=
cmd_text_line->TK_CMD opand EOL 
-
TK_CMD(CLR)
=
opand->TK_ACC 
TK_ACC(A)
=
EOL(
)
=
cmd_text_line->TK_CMD opand EOL 
-
TK_CMD(CLR)
=
opand->TK_C 
TK_C(C)
=
EOL(
)
=
cmd_text_line->TK_CMD opand EOL 
-
TK_CMD(CLR)
=
opand->expr 
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->I_CONSTANT 
I_CONSTANT(82H)
=
EOL(
)
=
cmd_text_line->TK_CMD opand EOL 
-
TK_CMD(CPL)
=
opand->TK_ACC 
TK_ACC(A)
=
EOL(
)
=
cmd_text_line->TK_CMD opand EOL 
-
TK_CMD(CPL)
=
opand->TK_C 
TK_C(C)
=
EOL(
)
=
cmd_text_line->TK_CMD opand EOL 
-
TK_CMD(CPL)
=
opand->expr 
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->I_CONSTANT 
I_CONSTANT(82H)
=
EOL(
)
=
cmd_text_line->TK_CMD opand EOL 
-
TK_CMD(DA)
=
opand->TK_ACC 
TK_ACC(A)
=
EOL(
)
=
cmd_text_line->TK_CMD opand EOL 
-
TK_CMD(DEC)
=
opand->TK_ACC 
TK_ACC(A)
=
EOL(
)
=
cmd_text_line->TK_CMD opand EOL 
-
TK_CMD(DEC)
=
opand->TK_RN 
TK_RN(R4)
=
EOL(
)
=
cmd_text_line->TK_CMD opand EOL 
-
TK_CMD(DEC)
=
opand->expr 
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->I_CONSTANT 
I_CONSTANT(23H)
=
EOL(
)
=
cmd_text_line->TK_CMD opand EOL 
-
TK_CMD(DEC)
=
opand->TK_AT_RI 
TK_AT_RI(@R1)
=
EOL(
)
=
cmd_text_line->TK_CMD opand EOL 
-
TK_CMD(DIV)
=
opand->TK_AB 
TK_AB(AB)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(DJNZ)
=
opand->TK_RN 
TK_RN(R2)
=
(,)
=
opand->expr 
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->TK_KEYWORD 
TK_KEYWORD(TMP1)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(DJNZ)
=
opand->expr 
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->I_CONSTANT 
I_CONSTANT(43H)
=
(,)
=
opand->expr 
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->TK_KEYWORD 
TK_KEYWORD(TMP2)
=
EOL(
)
=
cmd_text_line->TK_CMD opand EOL 
-
TK_CMD(INC)
=
opand->TK_ACC 
TK_ACC(A)
=
EOL(
)
=
cmd_text_line->TK_CMD opand EOL 
-
TK_CMD(INC)
=
opand->TK_RN 
TK_RN(R3)
=
EOL(
)
=
cmd_text_line->TK_CMD opand EOL 
-
TK_CMD(INC)
=
opand->expr 
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->I_CONSTANT 
I_CONSTANT(56H)
=
EOL(
)
=
cmd_text_line->TK_CMD opand EOL 
-
TK_CMD(INC)
=
opand->TK_AT_RI 
TK_AT_RI(@R1)
=
EOL(
)
=
cmd_text_line->TK_CMD opand EOL 
-
TK_CMD(INC)
=
opand->TK_DPTR 
TK_DPTR(DPTR)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(JB)
=
opand->expr 
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->I_CONSTANT 
I_CONSTANT(34H)
=
(,)
=
opand->expr 
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->TK_KEYWORD 
TK_KEYWORD(TMP1)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(JBC)
=
opand->expr 
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->I_CONSTANT 
I_CONSTANT(32H)
=
(,)
=
opand->expr 
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->TK_KEYWORD 
TK_KEYWORD(TMP2)
=
EOL(
)
=
cmd_text_line->TK_CMD opand EOL 
-
TK_CMD(JC)
=
opand->expr 
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->TK_KEYWORD 
TK_KEYWORD(TMP1)
=
EOL(
)
=
cmd_text_line->TK_CMD opand EOL 
-
TK_CMD(JMP)
=
opand->TK_AT_A_PLUS_DPTR 
TK_AT_A_PLUS_DPTR(@A+DPTR)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(JNB)
=
opand->expr 
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->I_CONSTANT 
I_CONSTANT(34H)
=
(,)
=
opand->expr 
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->TK_KEYWORD 
TK_KEYWORD(TMP1)
=
EOL(
)
=
cmd_text_line->TK_CMD opand EOL 
-
TK_CMD(JNC)
=
opand->expr 
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->TK_KEYWORD 
TK_KEYWORD(TMP2)
=
EOL(
)
=
cmd_text_line->TK_CMD opand EOL 
-
TK_CMD(JNZ)
=
opand->expr 
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->TK_KEYWORD 
TK_KEYWORD(TMP1)
=
EOL(
)
=
cmd_text_line->TK_CMD opand EOL 
-
TK_CMD(JZ)
=
opand->expr 
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->TK_KEYWORD 
TK_KEYWORD(TMP2)
=
EOL(
)
=
cmd_text_line->TK_CMD opand EOL 
-
TK_CMD(LCALL)
=
opand->expr 
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->TK_KEYWORD 
TK_KEYWORD(TMP1)
=
EOL(
)
=
cmd_text_line->TK_CMD opand EOL 
-
TK_CMD(LJMP)
=
opand->expr 
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->TK_KEYWORD 
TK_KEYWORD(TMP2)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(MOV)
=
opand->TK_ACC 
TK_ACC(A)
=
(,)
=
opand->TK_RN 
TK_RN(R5)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(MOV)
=
opand->TK_ACC 
TK_ACC(A)
=
(,)
=
opand->expr 
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->I_CONSTANT 
I_CONSTANT(34H)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(MOV)
=
opand->TK_ACC 
TK_ACC(A)
=
(,)
=
opand->TK_AT_RI 
TK_AT_RI(@R0)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(MOV)
=
opand->TK_ACC 
TK_ACC(A)
=
(,)
=
opand->'#' expr 
-
(#)
=
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->I_CONSTANT 
I_CONSTANT(32H)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(MOV)
=
opand->TK_RN 
TK_RN(R5)
=
(,)
=
opand->TK_ACC 
TK_ACC(A)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(MOV)
=
opand->TK_RN 
TK_RN(R2)
=
(,)
=
opand->expr 
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->I_CONSTANT 
I_CONSTANT(34H)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(MOV)
=
opand->TK_RN 
TK_RN(R4)
=
(,)
=
opand->'#' expr 
-
(#)
=
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->I_CONSTANT 
I_CONSTANT(32H)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(MOV)
=
opand->expr 
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->I_CONSTANT 
I_CONSTANT(43H)
=
(,)
=
opand->TK_ACC 
TK_ACC(A)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(MOV)
=
opand->expr 
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->I_CONSTANT 
I_CONSTANT(32H)
=
(,)
=
opand->TK_RN 
TK_RN(R2)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(MOV)
=
opand->expr 
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->I_CONSTANT 
I_CONSTANT(32H)
=
(,)
=
opand->expr 
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->I_CONSTANT 
I_CONSTANT(54H)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(MOV)
=
opand->expr 
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->I_CONSTANT 
I_CONSTANT(32H)
=
(,)
=
opand->TK_AT_RI 
TK_AT_RI(@R1)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(MOV)
=
opand->expr 
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->I_CONSTANT 
I_CONSTANT(67H)
=
(,)
=
opand->'#' expr 
-
(#)
=
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->I_CONSTANT 
I_CONSTANT(32H)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(MOV)
=
opand->TK_AT_RI 
TK_AT_RI(@R1)
=
(,)
=
opand->TK_ACC 
TK_ACC(A)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(MOV)
=
opand->TK_AT_RI 
TK_AT_RI(@R0)
=
(,)
=
opand->expr 
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->I_CONSTANT 
I_CONSTANT(87H)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(MOV)
=
opand->TK_AT_RI 
TK_AT_RI(@R1)
=
(,)
=
opand->'#' expr 
-
(#)
=
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->I_CONSTANT 
I_CONSTANT(23H)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(MOV)
=
opand->TK_C 
TK_C(C)
=
(,)
=
opand->expr 
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->I_CONSTANT 
I_CONSTANT(82H)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(MOV)
=
opand->expr 
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->I_CONSTANT 
I_CONSTANT(83H)
=
(,)
=
opand->TK_C 
TK_C(C)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(MOV)
=
opand->TK_DPTR 
TK_DPTR(DPTR)
=
(,)
=
opand->'#' expr 
-
(#)
=
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->I_CONSTANT 
I_CONSTANT(1234H)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(MOVC)
=
opand->TK_ACC 
TK_ACC(A)
=
(,)
=
opand->TK_AT_A_PLUS_DPTR 
TK_AT_A_PLUS_DPTR(@A+DPTR)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(MOVC)
=
opand->TK_ACC 
TK_ACC(A)
=
(,)
=
opand->TK_AT_A_PLUS_PC 
TK_AT_A_PLUS_PC(@A+PC)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(MOVX)
=
opand->TK_ACC 
TK_ACC(A)
=
(,)
=
opand->TK_AT_RI 
TK_AT_RI(@R0)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(MOVX)
=
opand->TK_ACC 
TK_ACC(A)
=
(,)
=
opand->TK_AT_DPTR 
TK_AT_DPTR(@DPTR)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(MOVX)
=
opand->TK_AT_RI 
TK_AT_RI(@R1)
=
(,)
=
opand->TK_ACC 
TK_ACC(A)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(MOVX)
=
opand->TK_AT_DPTR 
TK_AT_DPTR(@DPTR)
=
(,)
=
opand->TK_ACC 
TK_ACC(A)
=
EOL(
)
=
cmd_text_line->TK_CMD opand EOL 
-
TK_CMD(MUL)
=
opand->TK_AB 
TK_AB(AB)
=
EOL(
)
=
cmd_text_line->TK_CMD EOL 
-
TK_CMD(NOP)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(ORL)
=
opand->TK_ACC 
TK_ACC(A)
=
(,)
=
opand->TK_RN 
TK_RN(R6)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(ORL)
=
opand->TK_ACC 
TK_ACC(A)
=
(,)
=
opand->expr 
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->I_CONSTANT 
I_CONSTANT(87H)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(ORL)
=
opand->TK_ACC 
TK_ACC(A)
=
(,)
=
opand->TK_AT_RI 
TK_AT_RI(@R0)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(ORL)
=
opand->TK_ACC 
TK_ACC(A)
=
(,)
=
opand->'#' expr 
-
(#)
=
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->I_CONSTANT 
I_CONSTANT(32H)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(ORL)
=
opand->expr 
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->I_CONSTANT 
I_CONSTANT(98H)
=
(,)
=
opand->TK_ACC 
TK_ACC(A)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(ORL)
=
opand->expr 
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->I_CONSTANT 
I_CONSTANT(43H)
=
(,)
=
opand->'#' expr 
-
(#)
=
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->I_CONSTANT 
I_CONSTANT(23H)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(ORL)
=
opand->TK_C 
TK_C(C)
=
(,)
=
opand->expr 
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->I_CONSTANT 
I_CONSTANT(98H)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(ORL)
=
opand->TK_C 
TK_C(C)
=
(,)
=
opand->'/' expr 
-
(/)
=
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->I_CONSTANT 
I_CONSTANT(23H)
=
EOL(
)
=
cmd_text_line->TK_CMD opand EOL 
-
TK_CMD(POP)
=
opand->expr 
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->I_CONSTANT 
I_CONSTANT(34H)
=
EOL(
)
=
cmd_text_line->TK_CMD opand EOL 
-
TK_CMD(PUSH)
=
opand->expr 
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->I_CONSTANT 
I_CONSTANT(34H)
=
EOL(
)
=
cmd_text_line->TK_CMD EOL 
-
TK_CMD(RET)
=
EOL(
)
=
cmd_text_line->TK_CMD EOL 
-
TK_CMD(RETI)
=
EOL(
)
=
label_text_line->TK_KEYWORD ':' 
-
TK_KEYWORD(TMP3)
=
(:)
=
cmd_text_line->TK_CMD opand EOL 
-
TK_CMD(RL)
=
opand->TK_ACC 
TK_ACC(A)
=
EOL(
)
=
cmd_text_line->TK_CMD opand EOL 
-
TK_CMD(RLC)
=
opand->TK_ACC 
TK_ACC(A)
=
EOL(
)
=
cmd_text_line->TK_CMD opand EOL 
-
TK_CMD(RR)
=
opand->TK_ACC 
TK_ACC(A)
=
EOL(
)
=
cmd_text_line->TK_CMD opand EOL 
-
TK_CMD(RRC)
=
opand->TK_ACC 
TK_ACC(A)
=
EOL(
)
=
cmd_text_line->TK_CMD opand EOL 
-
TK_CMD(SETB)
=
opand->expr 
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->I_CONSTANT 
I_CONSTANT(93H)
=
EOL(
)
=
cmd_text_line->TK_CMD opand EOL 
-
TK_CMD(SETB)
=
opand->TK_C 
TK_C(C)
=
EOL(
)
=
cmd_text_line->TK_CMD opand EOL 
-
TK_CMD(SJMP)
=
opand->expr 
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->TK_KEYWORD 
TK_KEYWORD(TMP3)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(SUBB)
=
opand->TK_ACC 
TK_ACC(A)
=
(,)
=
opand->TK_RN 
TK_RN(R5)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(SUBB)
=
opand->TK_ACC 
TK_ACC(A)
=
(,)
=
opand->expr 
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->I_CONSTANT 
I_CONSTANT(43H)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(SUBB)
=
opand->TK_ACC 
TK_ACC(A)
=
(,)
=
opand->TK_AT_RI 
TK_AT_RI(@R0)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(SUBB)
=
opand->TK_ACC 
TK_ACC(A)
=
(,)
=
opand->'#' expr 
-
(#)
=
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->I_CONSTANT 
I_CONSTANT(21H)
=
EOL(
)
=
cmd_text_line->TK_CMD opand EOL 
-
TK_CMD(SWAP)
=
opand->TK_ACC 
TK_ACC(A)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(XCH)
=
opand->TK_ACC 
TK_ACC(A)
=
(,)
=
opand->TK_RN 
TK_RN(R4)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(XCH)
=
opand->TK_ACC 
TK_ACC(A)
=
(,)
=
opand->expr 
expr->additive_expr 
additive_expr->multi_expr 
multi_expr->not_expr 
not_expr->expr_elem 
expr_elem->I_CONSTANT 
I_CONSTANT(12H)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(XCH)
=
opand->TK_ACC 
TK_ACC(A)
=
(,)
=
opand->TK_AT_RI 
TK_AT_RI(@R0)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(XCHD)
=
opand->TK_ACC 
TK_ACC(A)
=
(,)
=
opand->TK_AT_RI 
TK_AT_RI(@R1)
=
EOL(
)
=
cmd_text_line->TK_CMD opand ',' opand EOL 
-
TK_CMD(XRL)
=
opand->TK_ACC 
TK_ACC(A)
=
(,)
=
opand->TK_RN 
TK_RN(R2)
=
EOL(
)
=
EOL(
)
=
EOL(
)
=
EOL(
)
=
EOL(
)
=
macro_text_line->TK_MACRO EOL 
-
TK_MACRO(end)
=
EOL(
)
=