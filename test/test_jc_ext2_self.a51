ORG 00H;
JC C_4H;		0H	40 02 
SJMP C_7H;		2H	80 03 
C_4H:
LJMP C_82H;		4H	02 00 82 
C_7H:
ORG 082H;
C_82H:
INC R4;		82H	0C 
RET ;		83H	22 