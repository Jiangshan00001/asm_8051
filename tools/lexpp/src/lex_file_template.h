#ifndef LEX_FILE_TEMPLATE_H
#define LEX_FILE_TEMPLATE_H
#include <string>

class lex_file_template
{
public:
    lex_file_template();
    std::string get_first_part(std::string inamespace, std::string scanner_base_name_prefix);
    std::string get_second_part(std::string inamespace, std::string scanner_base_name_prefix);
};

#endif // LEX_FILE_TEMPLATE_H
