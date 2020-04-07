#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



private slots:
    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionASM_HEX_triggered();

    void on_actionHEX_ASM_triggered();

    void on_actionGenCode_triggered();

    void on_actionGenDisCode_triggered();

    void on_actionGenTestAsm_triggered();

private:
    Ui::MainWindow *ui;
    void csv_gen();
    void csv_summary_load(std::string summary_file_name, std::vector<std::string> &m_code_table_header, std::vector<std::vector<std::string> > &m_code_table);
    void csv_dist_load(std::string file_ar_name, std::vector<std::string> &m_code_table_header2, std::vector<std::vector<std::string> > &m_code_table2);



    void load_asm_cmd_list(std::vector<std::string> &m_cmd_list);
    void load_asm_m2_inst_list(std::vector<std::string> &header2, std::vector<std::vector<std::string> > &cmd_list2);
    void load_asm_m3_inst_list(std::vector<std::string> &header3, std::vector<std::vector<std::string> > &cmd_list3);


    void csv_save(std::vector<std::string> &header2, std::vector<std::vector<std::string> > &cmd_list2, std::string file_name);
    void save_list_to_file(std::vector<std::string> m_cmd_list, std::string file_name);
    std::string generate_one_cmd_code(std::vector<std::vector<std::string> > cmd_list2, std::string mcmd, int indent_space);
    std::string get_cmd_comment(std::vector<std::string> header2, std::vector<std::vector<std::string> > cmd_list2, std::string mcmd, int indent_space);
    std::string generate_calc_code(std::string byte_formual, std::vector<std::string> except_tokens, std::vector<std::string> tokens_var);

    void hex_code_asm_table_gen();

};

#endif // MAINWINDOW_H
