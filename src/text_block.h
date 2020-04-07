#ifndef TEXT_BLOCK_H
#define TEXT_BLOCK_H
#include <string>
#include "asm8051_lex.h"


class T_HEX_TEXT_BLOCK
{
public:
    T_HEX_TEXT_BLOCK();

    int set_src_text(std::string src, int line_no);
    int set_address();
    std::string get_hex();


    static std::vector<T_HEX_TEXT_BLOCK> src_to_blocks(std::string src);

public:
    std::string m_source;//当前行的源代码
    int m_line_no;///当前行号

    unsigned long m_address;
    std::string m_hex_text;
    //int m_need_refresh;//对于含有label的，可能需要第二遍更新偏移地址

    int m_current_line_oscillator_period;


    std::vector<asm_token> m_tokens;

};



#endif // TEXT_BLOCK_H
