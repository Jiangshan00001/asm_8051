#ifndef LEX_FILE_IO_H
#define LEX_FILE_IO_H
#include <string>

class lex_file_io
{
public:
    lex_file_io();

    int out_lex(std::string out_file_name, int is_with_code);
    int set_name_space(std::string  inamespace);
    int read(std::string file_name);

    std::string m_name_space;

    std::string m_lex_part1;
    std::string m_lex_part2;
    int m_debug;

};

#endif // LEX_FILE_IO_H
