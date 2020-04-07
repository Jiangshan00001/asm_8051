#ifndef DIS8051_H
#define DIS8051_H

#include <string>
#include<map>
#include "asm_table.h"

class dis8051
{
public:
    dis8051();
    ~dis8051();
public:
    std::string add_hex_str(std::string hex_format_str);


    std::map<unsigned int, hex_code_asm_table> m_inst_dis;

    int load_inst();

private:
    std::string dis_one_inst(std::string mhex, hex_code_asm_table &inst_info);
};

#endif // DIS8051_H

