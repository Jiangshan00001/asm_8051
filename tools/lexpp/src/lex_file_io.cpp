#include <iostream>
#include "trim.h"
#include <fstream>
#include <sstream>
#include "lex_file_io.h"
#include "lex_file_template.h"

lex_file_io::lex_file_io()
{
    m_debug = 0;
}

int lex_file_io::out_lex(std::string out_file_name, int is_with_code)
{
    std::ofstream fout;
    fout.open(out_file_name.c_str());

    lex_file_template m_temp;


    fout<<m_lex_part1<<"\n";
    if(is_with_code)
    {
        fout<<m_temp.get_first_part(m_name_space, "ASM");
    }
    fout<<m_lex_part2<<"\n";

    if(is_with_code)
    {
        fout<<m_temp.get_second_part(m_name_space, "ASM");
    }

    fout.close();
    return 0;

}

int lex_file_io::set_name_space(std::string inamespace)
{
    m_name_space = inamespace;
    return 0;
}

int lex_file_io::read(std::string file_name)
{
    std::ifstream fin(file_name);


    std::stringstream p1;
    std::stringstream p2;

    int is_p2=0;
    std::string one_line;
    while(std::getline(fin, one_line))
    {
        trim(one_line);

        if(one_line=="%%")
        {
            is_p2=1;
            continue;
        }
        if(!is_p2)
        {
            p1<<one_line<<"\n";
        }
        else
        {
            p2<<one_line<<"\n";
        }
    }
    m_lex_part1 = p1.str();
    m_lex_part2 = p2.str();

    return 0;

}
