#ifndef CSV_TO_CSV_H
#define CSV_TO_CSV_H

#include <vector>
#include <set>
#include <string>

/// 转为
class csv_to_csv
{
public:
    csv_to_csv();
    int set_input_file(std::string dis_list_file, std::string asm_list_file);
    int write_cmd_list(std::string cmd_list_file);
    int write_type_list(std::string type_list_file);

    std::set<std::string> m_cmd_list1;
    std::set<std::string> m_cmd_list2;
    std::set<std::string> m_param_type_list1;
    std::set<std::string> m_param_type_list2;

    int m_debug;
};

#endif // CSV_TO_CSV_H
