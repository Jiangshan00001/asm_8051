#ifndef YY_FILE_TEMPLATE_H
#define YY_FILE_TEMPLATE_H
#include <string>


///
/// \brief The yy_file_template class
/// yyfile format:
/// first part
/// token_defines
/// second_part
/// syn_defines
/// third_part
///
/// %% is already included in parts
class yy_file_template
{
public:
    yy_file_template();
    std::string get_fist_part(std::string inamespace, std::string iparser_class_name);
    std::string get_second_part();
    std::string get_third_part(std::string inamespace, std::string iparser_class_name);



};

#endif // YY_FILE_TEMPLATE_H
