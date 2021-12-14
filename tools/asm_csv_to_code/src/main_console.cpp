#include <string.h>
#include <stdio.h>
#include <iostream>

#include "main_console.h"
#include "csv_io.h"
#include "csv_to_csv.h"
#include "csv_to_dis.h"
#include "csv_to_asmc.h"
#include "csv_to_genasm.h"
static void usage()
{
    std::cout<<"prog -t <csv/dis/asm/class> dis_list.csv assemble_list.csv output1 output2 \n";
    std::cout<<"prog -t csv  dis_list.csv assemble_list.csv output_cmd_list.csv output_param_type_list.csv\n";
    std::cout<<"prog -t class  dis_list.csv assemble_list.csv param_type_list.csv output_class_file\n";
    std::cout<<"prog -t dis  dis_list.csv param_type_list.csv output_dis.cpp output_dis.h namespace\n";
    std::cout<<"prog -t asm  asm_list.csv param_type_list.csv output_asm.cpp output_asm.h namespace\n";
    std::cout<<"prog -t genasm  asm_list.csv param_type_list.csv output_asm.cpp output_asm.h namespace\n";

}

#ifndef QT_WID
int main(int argc, char *argv[])
#else
int main_qt_asm_csv_to_code(int argc, char *argv[])
#endif
{
    ///根据asm的csv文件，生成对应编译器的部分代码
    /// 1--dis列表：
    /// 每个指令的信息列表
    /// 每个指令的反汇编代码
    ///
    ///

    if(argc<4)
    {
        usage();
        return 0;
    }


    if(strcmp(argv[1],"-t")!=0)
    {
        usage();
        return 0;
    }

    if(strcmp(argv[2], "csv")==0)
    {
        if(argc!=7)
        {
            usage();
            return 0;
        }
        std::string dis_list_file = argv[3];
        std::string asm_list_file = argv[4];
        std::string output_cmd_list = argv[5];
        std::string output_type_list = argv[6];
        csv_to_csv m_csv;
        m_csv.set_input_file(dis_list_file,asm_list_file);
        m_csv.write_cmd_list(output_cmd_list);
        m_csv.write_type_list(output_type_list);
    }
    else if(strcmp(argv[2], "class")==0)
    {

    }
    else if(strcmp(argv[2], "dis")==0)
    {
        if(argc!=8)
        {
            usage();
            return 0;
        }
        std::string dis_list_file = argv[3];
        std::string operand_list_file = argv[4];
        std::string output_cpp_list = argv[5];
        std::string output_h_list = argv[6];
        std::string inamespace = argv[7];

        csv_to_dis m_dis;
        m_dis.set_input_file(dis_list_file, operand_list_file);
        m_dis.set_namespace(inamespace);
        m_dis.output_dis_cpp(output_cpp_list);
        m_dis.output_dis_h(output_h_list);
    }
    else if(strcmp(argv[2], "asm")==0)
    {
        if(argc!=8)
        {
            usage();
            return 0;
        }
        std::string asm_list_file = argv[3];
        std::string operand_list_file = argv[4];
        std::string output_cpp_list = argv[5];
        std::string output_h_list = argv[6];
        std::string inamespace = argv[7];

        csv_to_asmc m_asm;
        m_asm.set_input_file(asm_list_file, operand_list_file);
        m_asm.set_namespace(inamespace);
        m_asm.output_asm_cpp(output_cpp_list);
        m_asm.output_asm_h(output_h_list);
    }
    else if(strcmp(argv[2], "genasm")==0)
    {
        if(argc!=8)
        {
            usage();
            return 0;
        }
        std::string asm_list_file = argv[3];
        std::string operand_list_file = argv[4];
        std::string output_cpp_list = argv[5];
        std::string output_h_list = argv[6];
        std::string inamespace = argv[7];

        csv_to_genasm m_asm;
        m_asm.set_input_file(asm_list_file, operand_list_file);
        m_asm.set_namespace(inamespace);
        m_asm.output_asm_cpp(output_cpp_list);
        m_asm.output_asm_h(output_h_list);
    }
    return 0;
}

