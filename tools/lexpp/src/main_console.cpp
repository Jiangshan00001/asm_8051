#include <iostream>
#include <assert.h>
#include "main_console.h"
#include "lex_file_io.h"
#include "lex_file_template.h"

#ifndef QT_WID

int main(int argc, char *argv[])
#else
int main222(int argc, char *argv[])
#endif
{

    if(argc<5)
       {
           std::cout<<"prog -t <test/lex> in_lex.yy_file output_file_name  [namespace] debug ";
           std::cout<<"\n";
           exit(0);
       }

       lex_file_io m_file;

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

           m_file.out_lex(out_file_name, 0);
       }
       else if(type2=="lex")
       {

           m_file.out_lex(out_file_name, 1);
       }

       return 0;

    return 0;
}
