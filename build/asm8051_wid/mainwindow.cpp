#include <iostream>
#include <sstream>
#include <set>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "csv_io.h"
#include "asm8051_lex.h"
#include "trim.h"
#include "replace.h"
#include "asm8051.h"
#include "dis8051.h"
#include "asm_table.h"
#include "asm_test_code_gen.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::csv_gen()
{
#if 0
    std::ofstream f_out;
    std::vector< std::vector<std::string> > m_code_table;
    std::vector<std::string> m_code_table_header;
    std::string summary_file_name =  "D:/tsdx/asm8051_v2/doc/inst_v1.csv";

    csv_summary_load(summary_file_name,m_code_table_header, m_code_table);




    //////////////////////////////////////////
    //////////////////////////////////////////
    csv_save(m_code_table_header,m_code_table, "D:/tsdx/asm8051_v2/doc/m3.csv");

    //////////////////////////////////////////
    //////////////////////////////////////////



//    std::vector< std::vector<std::string> > m_code_table2;
//    std::vector<std::string> m_code_table_header2;

//    std::string file_ar_name = "D:/tsdx/asm8051_v2/doc/inst_v1_ar.csv";

//    csv_dist_load(file_ar_name, m_code_table_header2, m_code_table2);
//    file_ar_name = "D:/tsdx/asm8051_v2/doc/inst_v1_bool.csv";
//    csv_dist_load(file_ar_name, m_code_table_header2, m_code_table2);
//    file_ar_name = "D:/tsdx/asm8051_v2/doc/inst_v1_dt.csv";
//    csv_dist_load(file_ar_name, m_code_table_header2, m_code_table2);
//    file_ar_name = "D:/tsdx/asm8051_v2/doc/inst_v1_lo.csv";
//    csv_dist_load(file_ar_name, m_code_table_header2, m_code_table2);
//    file_ar_name = "D:/tsdx/asm8051_v2/doc/inst_v1_pb.csv";
//    csv_dist_load(file_ar_name, m_code_table_header2, m_code_table2);



//    //////////////////////////////////////////
//    //////////////////////////////////////////

//    csv_save(m_code_table_header2,m_code_table2, "D:/tsdx/asm8051_v2/doc/m2.csv");
//    //////////////////////////////////////////
//    //////////////////////////////////////////


    std::set<std::string> m_cmd_set;
    std::vector<std::string> m_cmd_list;

    for(int i=0;i<m_code_table2.size();++i)
    {
        m_cmd_set.insert(m_code_table2[i][0]);
    }
    for (std::set<std::string>::iterator it = m_cmd_set.begin(); it != m_cmd_set.end(); ++it)
    {
          m_cmd_list.push_back( *it);
    }

    //////////////////////////////////////////
    //////////////////////////////////////////
    //write m1
    save_list_to_file(m_cmd_list, "D:/tsdx/asm8051_v2/doc/m1.csv");
    //////////////////////////////////////////
    //////////////////////////////////////////

#endif
}

void MainWindow::save_list_to_file(std::vector<std::string> m_cmd_list, std::string file_name)
{
    std::ofstream f_out;
    f_out.open(file_name.c_str());
    ///write data to csv
    ///
    for(int i=0;i<m_cmd_list.size();++i)
    {
      f_out<<m_cmd_list[i]<<std::endl;
    }
    f_out.close();
}




void MainWindow::on_actionOpen_triggered()
{

}

void MainWindow::on_actionSave_triggered()
{

}

void MainWindow::on_actionASM_HEX_triggered()
{
    asm8051 m_8051;
    m_8051.add_src(ui->plainTextEditASM->toPlainText().toStdString());
    m_8051.compile();
    std::string mout = m_8051.generate_hex();
    ui->plainTextEditHEX->setPlainText(QString::fromStdString(mout));
}

void MainWindow::on_actionHEX_ASM_triggered()
{
    dis8051 m_dis8051;
    std::string ret = m_dis8051.add_hex_str(ui->plainTextEditHEX->toPlainText().toStdString());
    ui->plainTextEditDISASM->setPlainText(QString::fromStdString(ret));
}


///TODO: 针对一行有多个语句，或者一行有的可能有标签的问题，添加预处理功能。
/// 限制为：一行只能有 一个语句，标签必修单独一行

void MainWindow::load_asm_cmd_list(std::vector<std::string>& m_cmd_list)
{
    std::ifstream m_file;
    std::string key_word;
    m_file.open("../../../asm8051_v2/doc/m1.csv");
    while(std::getline(m_file, key_word))
    {
        key_word = trim(key_word);
        m_cmd_list.push_back(key_word);
    }
    m_file.close();
}








void MainWindow::on_actionGenCode_triggered()
{
    //csv_gen();


    std::vector<std::string>  m_cmd_list;

    /////////////////////

    load_asm_cmd_list(m_cmd_list);
    /////////////////////

    std::vector<std::vector<std::string> > cmd_list2;
    std::vector<std::string> header2;
    /////////////////////

    //load_asm_m2_inst_list(header2, cmd_list2);

    /////////////////////

    /////////////////////
    /////////////////////
    ///对数据生成代码

}



void MainWindow::on_actionGenDisCode_triggered()
{



}



void MainWindow::on_actionGenTestAsm_triggered()
{
    asm_test_code_gen m_asm_gen;
    std::string a = m_asm_gen.test_code_gen1();
    ui->plainTextEditASM->setPlainText(QString::fromStdString(a));

}











