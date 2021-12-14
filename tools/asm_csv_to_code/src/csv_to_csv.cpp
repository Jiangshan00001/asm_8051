#include <iostream>
#include "replace.h"
#include "trim.h"
#include "split.h"
#include "csv_io.h"
#include "csv_to_csv.h"

csv_to_csv::csv_to_csv()
{
    m_debug = 1;
}

int csv_to_csv::set_input_file(std::string dis_list_file, std::string asm_list_file)
{
    ///Hex Code,Humber of Bytes,Mnemonic,Operands,param_count,param0,param1,param3
    csv_io m_io;

    m_io.set_file_name(dis_list_file);
    m_io.open_file();
    std::vector<std::string> header1 = m_io.parse_next_line(NULL);
    std::vector<std::vector<std::string> > dis_list = m_io.parse_file();

    // 生成cmd列表
    for(int i=0;i<dis_list.size();++i)
    {
        if (dis_list[i].size()==0)
        {
            std::cout<<"dis_list:line:"<<i<<". empty line skipped.\n";
            continue;
        }
        if(dis_list[i].size()<3)
        {
            if(m_debug)
            {
                std::cout<<"dis_list<3. line "<<i<<" skipped." <<(dis_list[i].size()>0?dis_list[i][0]:"empty") <<"\n";
            }

            continue;
        }
        m_cmd_list1.insert(dis_list[i][2]);
    }


    //生成命令列表
    for(int i=0;i<dis_list.size();++i)
    {
        if (dis_list[i].size()==0)
        {
            std::cout<<"dis_list:line:"<<i<<". empty line skipped.\n";
            continue;
        }
        if(dis_list[i].size()<4)
        {
            if(m_debug)
            {
                std::cout<<"dis_list<4. line:"<<i<<" skipped. "<< (dis_list[i].size()>0?dis_list[i][0]:"empty") <<"\n";
            }
            continue;
        }
        std::string param = dis_list[i][3];
        replace(param, "\"", "");
        std::vector<std::string> kk = split(param, ",",1);
        m_param_type_list1.insert(kk.begin(), kk.end());
    }


    ///Mnemonic,Operands,Description,Byte,Oscillator Period,Class,BYTE0,BYTE1,BYTE2
    csv_io m_io2;
    m_io2.set_file_name(asm_list_file);
    m_io2.open_file();
    std::vector<std::string> header2 = m_io2.parse_next_line(NULL);
    std::vector<std::vector<std::string> > asm_list = m_io2.parse_file();


    //生成汇编的命令列表
    for(int i=0;i<asm_list.size();++i)
    {
        if(asm_list[i].size()<1)
        {
            std::cout<<"asm_list line:"<< i<<". empty line skipped\n";
            continue;
        }

        m_cmd_list2.insert(asm_list[i][0]);
    }

    for(int i=0;i<asm_list.size();++i)
    {
        if(asm_list[i].size()<1)
        {
            std::cout<<"asm_list line:"<< i<<". empty line skipped\n";
            continue;
        }
        if(asm_list[i].size()<2)
        {
            std::cout<<"asm_list size error."<< i<<"\n";
            continue;
        }

        std::string param = asm_list[i][1];
        replace(param, "\"", "");
        std::vector<std::string> kk = split(param, ",",1);
        m_param_type_list1.insert(kk.begin(), kk.end());
    }

    return 0;
}

int csv_to_csv::write_cmd_list(std::string cmd_list_file)
{
    std::ofstream fin(cmd_list_file);

    fin<<"dis---\n";
    for(std::set<std::string>::iterator i=m_cmd_list1.begin();i!=m_cmd_list1.end();++i)
    {
        fin<< *i <<"\n";
    }
    fin<<"asm---\n";
    for(auto i=m_cmd_list2.begin();i!=m_cmd_list2.end();++i)
    {
        fin<<(*i)<<"\n";
    }

    fin.close();
    return 0;
}

int csv_to_csv::write_type_list(std::string type_list_file)
{
    std::ofstream fin(type_list_file);

    fin<<"dis---\n";

    for(auto i=m_param_type_list1.begin();i!=m_param_type_list1.end();++i)
    {
        fin<<(*i)<<"\n";
    }
    fin<<"asm---\n";

    for(auto i=m_param_type_list1.begin();i!=m_param_type_list1.end();++i)
    {
        fin<<(*i)<<"\n";
    }

    fin.close();
    return 0;
}





