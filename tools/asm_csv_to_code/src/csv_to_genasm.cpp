#include "split.h"
#include "csv_io.h"
#include "csv_to_genasm.h"

csv_to_genasm::csv_to_genasm()
{
}

int csv_to_genasm::set_input_file(std::string asm_list_file, std::string operand_list_file)
{
    ///Mnemonic,Operands,Description,Byte,Oscillator Period,Class,BYTE0,BYTE1,BYTE2
    csv_io m_io;

    m_io.set_file_name(asm_list_file);
    m_io.open_file();
    m_asm_list_head = m_io.parse_next_line(NULL);
    m_asm_list = m_io.parse_file();

    for(int i=0;i<m_asm_list.size();++i)
    {
        if(m_asm_list[i].empty())
        {
            m_asm_list.erase(m_asm_list.begin()+i);
        }
    }


    for(int i=0;i<m_asm_list.size();++i)
    {
        m_cmd_list.insert(m_asm_list[i][0]);
    }





    csv_io m_io2;

    m_io2.set_file_name(operand_list_file);
    m_io2.open_file();
    std::vector<std::string> head2 = m_io2.parse_next_line(NULL);
    std::vector<std::vector<std::string> > opr1 = m_io2.parse_file();

    for(int i=0;i<opr1.size();++i)
    {
        if(opr1[i].size()<3)continue;
        std::string opr_name = opr1[i][0];
        std::string opr_type_name = opr1[i][1];
        std::string opr_type_asm_name = opr1[i][2];
        std::string type_mask = opr1[i][3];

        m_str_to_asm_token_type[opr_name] = opr_type_name;
        m_type_mask[opr_type_name] = type_mask;

        m_operand_type_list.insert(opr_type_name);

        std::vector<std::string> asm_possible_type=split(opr_type_asm_name,"/",1);
        m_ic_token_type_list.insert(asm_possible_type.begin(), asm_possible_type.end());
        m_asm_token_to_ic_token_type[opr_type_name] = asm_possible_type;
    }


    return 0;
}

int csv_to_genasm::output_asm_cpp(std::string output_file)
{

    return 0;
}

int csv_to_genasm::output_asm_h(std::string output_file)
{

    return 0;
}

int csv_to_genasm::set_namespace(std::string inamespace)
{
    m_namespace = inamespace;
    return 0;
}
