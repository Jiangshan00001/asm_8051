#include "mainwindow.h"
#include <QApplication>
#include <set>
#include <string>
#include <asm_table.h>
#include <sstream>
#include <iostream>
#include "codegenwid.h"

void test_code_gen()
{
    //生成测试用的asm代码
    std::stringstream ret_out;
    ret_out<<"ORG 2000H\r\n";

    std::map<std::string, std::vector<std::string> > param_enum_list;


    std::set<std::string> m_token_strs;
    for(int i=0;i<g_asm_table_size;++i)
    {
        std::string cmd = g_asm_table[i].cmd;
        std::string params = g_asm_table[i].params;
        m_token_strs.insert(g_asm_table[i].m_token0);
        m_token_strs.insert(g_asm_table[i].m_token1);
        m_token_strs.insert(g_asm_table[i].m_token2);
        m_token_strs.insert(g_asm_table[i].m_token3);
    }

    std::set<std::string>::iterator it= m_token_strs.begin();
    for(;it!=m_token_strs.end();++it)
    {
        ret_out<<"{";
        ret_out<<"\""<<*it<<"\", ";
        ret_out<<"1"<<", ";
        ret_out<<"\"\" "<<", ";
        ret_out<<"\"\""<<", ";
        ret_out<<"\"\""<<", ";
        ret_out<<"\"\""<<", ";
        ret_out<<"\"\""<<", ";
        ret_out<<"},\r\n";
    }
    std::cout<<ret_out.str()<<std::endl;
}


int main(int argc, char *argv[])
{
    test_code_gen();
    QApplication a(argc, argv);
    MainWindow w;
    //CodeGenWid w;
    w.show();

    return a.exec();
}

