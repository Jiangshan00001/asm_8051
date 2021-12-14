#ifndef CSV_TO_ASMC_H
#define CSV_TO_ASMC_H
#include <string>
#include <map>
#include <vector>
#include <set>
class csv_to_asmc
{
public:
    csv_to_asmc();
public:
    int set_input_file(std::string asm_list_file, std::string operand_list_file);

    int output_asm_cpp(std::string output_file);
    int output_asm_h(std::string output_file);
    int set_namespace(std::string inamespace);
private:
    std::string m_namespace;

    std::vector<std::string> m_asm_list_head;
    std::vector<std::vector<std::string> > m_asm_list;

    //字符串->asm_token A-->TOKEN_ACC
    std::map<std::string, std::string> m_str_to_asm_token_type;
    //asm_token->ic_token
    std::map<std::string, std::vector<std::string> > m_asm_token_to_ic_token_type;
    //每个类型的mask，例如TYPE_IMM16 的mask是0xffff
    std::map<std::string, std::string> m_type_mask;

    std::set<std::string> m_operand_type_list;
    std::set<std::string> m_ic_token_type_list;


    std::set<std::string> m_cmd_list;//有几个cmd，会生成几个函数

    std::string asm_to_bin_func();
    std::string get_cmd_func(std::string cmd);
    std::string get_cmd_func_name(std::string cmd);
    std::string vec_str_to_str(std::vector<std::string> vecs);

    std::string trim_quote_if_exist(std::string aa);

    std::string abs_to_rel_patch_func();

};

#endif // CSV_TO_ASMC_H
