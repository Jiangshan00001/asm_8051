ORG 00H;
JB 020H, C_5H;		0H	20 20 02 
SJMP C_8H;		3H	80 03 
C_5H:
LJMP C_83H;		5H	02 00 83 
C_8H:
ORG 083H;
C_83H:
INC R4;		83H	0C 
RET ;		84H	22 
