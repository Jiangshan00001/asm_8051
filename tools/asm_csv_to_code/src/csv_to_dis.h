#ifndef CSV_TO_DIS_H
#define CSV_TO_DIS_H

#include <vector>
#include <string>
#include <map>
#include <set>
///
/// \brief The csv_to_dis class
/// csv转为反汇编需要的代码
class csv_to_dis
{
public:
    csv_to_dis();

public:
    int set_input_file(std::string dis_list_file, std::string operand_list_file);

    int output_dis_cpp(std::string output_file);
    int output_dis_h(std::string output_file);
    int set_namespace(std::string inamespace);

    std::string m_namespace;

    std::vector<std::string> m_dis_list_head;
    std::vector<std::vector<std::string> > m_dis_list;

    std::map<std::string, std::string> m_dist_operand_type;

    std::set<std::string> m_operand_type_list;

    int generate_func_decl(std::vector<std::string> &dist_1, std::ostream &stri);
    int generate_func_name(std::vector<std::string> &dist_1, std::ostream &stri);

    std::string quote_if_not(std::string str_to_quote);
    std::string trim_quote_if_exist(std::string aa);
};

#endif // CSV_TO_DIS_H
