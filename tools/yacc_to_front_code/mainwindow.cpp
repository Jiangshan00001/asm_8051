#include "mainwindow.h"
#include <QFileDialog>
#include "ui_mainwindow.h"
#include "bison_file_io.h"

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



void MainWindow::on_actionOpen_triggered()
{
    //bison_file_io m_file;
    //m_file.read("D:/tsdx/compiler/editor8051/src/c8051/src/lex_yacc/ly/parser_no_code.yy");
    //m_file.out_y("D:/tsdx/compiler/editor8051/src/c8051/src/lex_yacc/ly/parser_no_code_out.yy", 0);
    //m_file.out_y("D:/tsdx/compiler/editor8051/src/c8051/src/lex_yacc/ly/parser_with_code_tmp.yy", 1);
    //m_file.out_ast_to_icode("D:/tsdx/compiler/editor8051/src/c8051/src/context/ast_to_icode_gen_tmp.cpp");
    //m_file.out_ast_to_icode_h("D:/tsdx/compiler/editor8051/src/c8051/src/context/ast_to_icode_gen_def_tmp.h");
    //m_file.out_ast_to_icode_func("D:/tsdx/compiler/editor8051/src/c8051/src/context/ast_to_icode_gen_def_tmp.cpp");
    //m_file.out_token_tree("D:/tsdx/compiler/editor8051/src/c8051/src/lex_yacc/ly/token_tree.dot");
    QString file_name = QFileDialog::getOpenFileName(this, "open yacc with no code file");

    if(file_name.size()>0)
    {
        bison_file_io m_file;
        m_file.m_debug = 1;
        m_file.read(file_name.toStdString());

    }

}

void MainWindow::on_actionFileTest_triggered()
{
    bison_file_io m_file;
    m_file.read_str(ui->plainTextEdit->toPlainText().toStdString());

}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}
