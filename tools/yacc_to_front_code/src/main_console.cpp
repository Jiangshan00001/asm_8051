#include <string>
#include <iostream>
#include <assert.h>
#include "bison_file_io.h"



#ifndef QT_WID

int main(int argc, char *argv[])
#else
int main222(int argc, char *argv[])
#endif
{
    if(argc<5)
    {
        std::cout<<"prog -t <test/yy_with_code/cpp_switch/cpp_func/defh/dot/debug_list> in_parser.yy_file output_file_name  [namespace] debug ";
        std::cout<<"\n";
        exit(0);
    }

    bison_file_io m_file;

    std::string type1 = argv[1];
    std::string type2 = argv[2];
    std::string in_file_name = argv[3];
    std::string out_file_name = argv[4];

    std::string name_space = "";
    if(argc>5)
    {
        name_space = argv[5];
        m_file.set_name_space(name_space);
    }
    if(argc>6)
    {
        //debug
        m_file.m_debug = 1;
    }

    assert(type1=="-t");

    m_file.read(in_file_name);

    if(type2=="test")
    {

        m_file.out_y(out_file_name, 0);
    }
    else if(type2=="yy_with_code")
    {

        m_file.out_y(out_file_name, 1);
    }
    else if(type2=="cpp_switch")
    {
        m_file.out_ast_to_icode(out_file_name);
    }
    else if(type2=="cpp_func")
    {
        m_file.out_ast_to_icode_func(out_file_name);
    }
    else if(type2=="defh")
    {
        m_file.out_ast_to_icode_h(out_file_name);
    }
    else if(type2=="dot")
    {
        m_file.out_token_tree(out_file_name);
    }
    else if(type2=="debug_list")
    {
        m_file.out_debug_list(out_file_name);
    }
    return 0;
}
