ORG 00H;
LJMP C_129H;		0H	02 01 29 
ORG 023H;
LJMP C_100H;		23H	02 01 00 
ORG 0100H;
C_100H:
JNB 099H, C_107H;		100H	30 99 04 
CLR 099H;		103H	C2 99 
CLR 00H;		105H	C2 00 
C_107H:
JNB 098H, C_10cH;		107H	30 98 02 
CLR 098H;		10aH	C2 98 
C_10cH:
RETI ;		10cH	32 
C_10dH:
MOV 098H, #050H;		10dH	75 98 50 
MOV 089H, #00H;		110H	75 89 00 
MOV 08bH, #0e8H;		113H	75 8B E8 
MOV 08dH, #0ffH;		116H	75 8D FF 
SETB 08eH;		119H	D2 8E 
MOV 08eH, #040H;		11bH	75 8E 40 
CLR 00H;		11eH	C2 00 
RET ;		120H	22 
C_121H:
JB 00H, C_121H;		121H	20 00 FD 
SETB 00H;		124H	D2 00 
MOV 099H, A;		126H	F5 99 
RET ;		128H	22 
C_129H:
MOV 081H, #03fH;		129H	75 81 3F 
LCALL C_10dH;		12cH	12 01 0D 
SETB 0acH;		12fH	D2 AC 
SETB 0afH;		131H	D2 AF 
MOV R0, #0efH;		133H	78 EF 
MOV A,@R0;		135H	E6 
LCALL C_121H;		136H	12 01 21 
INC R0;		139H	08 
MOV A,@R0;		13aH	E6 
LCALL C_121H;		13bH	12 01 21 
C_13eH:
SJMP C_13eH;		13eH	80 FE 
