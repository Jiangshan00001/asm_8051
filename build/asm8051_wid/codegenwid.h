#ifndef CODEGENWID_H
#define CODEGENWID_H

#include <QMainWindow>

#include <string>
#include <vector>

namespace Ui {
class CodeGenWid;
}

class CodeGenWid : public QMainWindow
{
    Q_OBJECT

public:
    explicit CodeGenWid(QWidget *parent = 0);
    ~CodeGenWid();

private slots:
    void on_actionAsmcsvTOcode_triggered();

    void on_actionDiscsvTocode_triggered();

    void on_actionOpenHex_triggered();

private:
    Ui::CodeGenWid *ui;
    void csv_dist_load(std::string file_ar_name, std::vector<std::string> &m_code_table_header2, std::vector<std::vector<std::string> > &m_code_table2);
    void load_asm_m2_inst_list(std::vector<std::string> &header2, std::vector<std::vector<std::string> > &cmd_list2, std::string file_name);
    void asm_inst_add_parse_token(std::vector<std::string> &header2, std::vector<std::vector<std::string> > &cmd_list2, std::vector<std::string> &token_list);


    std::string gen_tableA(std::vector<std::string> &header2, std::vector<std::vector<std::string> > &cmd_list2, std::vector<std::string> m_cmd_list);

    void gen_asm_keywords(std::vector<std::string> &header2, std::vector<std::vector<std::string> > &cmd_list2, std::vector<std::string> m_cmd_list);
    std::string get_cmd_comment(std::vector<std::string> header2, std::vector<std::vector<std::string> > cmd_list2, std::string mcmd, int indent_space);
    std::string generate_one_cmd_code(std::vector<std::vector<std::string> > cmd_list2, std::string mcmd, int indent_space);
    std::string generate_calc_code(std::string byte_formual, std::vector<std::string> except_tokens, std::vector<std::string> tokens_var);
    void csv_save(std::vector<std::string> &header2, std::vector<std::vector<std::string> > &cmd_list2, std::string file_name);



    std::string gen_disa_table();
    void load_asm_m3_inst_list(std::vector<std::string> &header3, std::vector<std::vector<std::string> > &cmd_list3);
};

#endif // CODEGENWID_H
