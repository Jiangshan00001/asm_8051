#ifndef ASM8051_LEX_H
#define ASM8051_LEX_H

#include <vector>
#include <string>


enum ASM_TOKEN_TYPE
{
    TOKEN_CMD=1,
    TOKEN_AB=2,
    TOKEN_ACC=3,
    TOKEN_AT_A_PLUS_DPTR=4,
    TOKEN_AT_A_PLUS_PC=5,
    TOKEN_AT_DPTR=6,
    TOKEN_AT_RI=7,
    TOKEN_C=8,
    TOKEN_DIV_NUM=9,
    TOKEN_DPTR=10,
    TOKEN_KEYWORD=11,
    TOKEN_RN=12,
    TOKEN_J_DATA=13,
    TOKEN_NUM=14,
    TOKEN_LABEL = 15,
    TOKEN_UNKNOWN=200,
};

typedef struct asm_token
{
    int type;
    std::string val_str;
    int num;
    int rel;
}asm_token;

std::vector<asm_token> asm_line_parse(void *ctx, std::string str1);

asm_token param_parse(std::string str1);


//std::vector<asm_token> template_param_parse(std::string str1);

std::vector<std::string> template_param_parse_str(std::string str1);
std::vector<std::string> template_param_parse_str_var(std::string str1);


#endif // ASM8051_LEX_H
