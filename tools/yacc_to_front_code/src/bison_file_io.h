#ifndef BISON_FILE_IO_H
#define BISON_FILE_IO_H
#include <string>
#include <vector>

///
/// \brief The bison_file_io class
///
class bison_file_io
{
public:
    bison_file_io();

public:
    ///
    /// \brief read 读取bison文件，内容放在m_tokens m_rules m_start 2个变量里
    /// \param file_name
    /// \return 0 正常
    ///
    int read(std::string file_name);

    int read_stream(std::istream &fin);

    int read_str(std::string file_content);

    ///
    /// \brief out_y 将读取的bison，生成yy输出
    /// \param file_name 输出文件名
    /// \param with_code 是否包含代码。
    /// \return
    ///
    int out_y(std::string file_name, int with_code);

    ///
    /// \brief out_ast_to_icode 生成yy对应ast的解码cpp框架文件
    /// \param file_name
    /// \return
    ///
    int out_ast_to_icode(std::string file_name);
    ///
    /// \brief out_ast_to_icode_h 生成yy对应ast的解码cpp框架文件的头文件
    /// \param file_name
    /// \return
    ///
    int out_ast_to_icode_h(std::string file_name);

    ///
    /// \brief out_ast_to_icode_func 生成yy对应ast的解码cpp框架文件中的各函数实体cpp
    /// \param file_name
    /// \return
    ///
    int out_ast_to_icode_func(std::string file_name);

    ///
    /// \brief out_token_tree 生成dot格式的ast树
    /// \param file_name
    /// \return
    ///
    int out_token_tree(std::string file_name);


    int set_name_space(std::string names){m_namespace=names;return 0;}

    ///输出2个列表，数字对应着字符串，用于程序调试输出语法树
    int out_debug_list(std::string file_name);

private:
    /// 终结符
    std::vector<std::string> m_tokens;


    std::vector<std::string> m_left;
    std::vector<std::string> m_right;

    /// 非终结符
    std::vector<std::string> m_types;

    ///语法规则。1个规则有多行，1行里有多列
    /// 规则存储格式：
    /// start :cmd1
    ///         | cmd2 cmd3
    ///     ;
    ///
    /// m_rules.size()=1
    /// m_rules[0][0][0]=="start";--第一个，保存规则名称，只有一个string
    /// m_rules[0][1][0]=="cmd1";---保存第一条规则
    /// m_rules[0][2][0]=="cmd2"; --保存第二条规则
    /// m_rules[0][2][1]=="cmd3";
    std::vector<std::vector< std::vector<std::string > > > m_rules;



    std::string m_start;
    //代码所在的命名空间名称。默认为example
    std::string m_namespace;


private:
    int generate_func1(std::string file_name);
    int generate_funci(std::string file_name, int start_rule_index, int end_rule_index);
    int generate_func_token(std::string file_name);

private:


    ///
    /// \brief add_one_rule 用于读取bison格式文件时，添加一个规则名称
    /// \param new_rule_name
    /// \return
    ///
    int add_one_rule(std::string new_rule_name);

    ///
    /// \brief add_one_rule_line 用于读取bison格式文件时，添加一个规则名称内的一行规则
    /// \param rule_name
    /// \param rule_str_list  [ : const '+' const]  第一个字符都是 ： 或者 |。 第一个字符会被省略
    /// \return
    ///
    int add_one_rule_line(std::string rule_name, std::vector<std::string> rule_str_list);


    int out_one_rule_line(std::ofstream &fout, std::vector<std::string> &one_line_rule, int rule_num, int line_num, int add_code);
    int add_y_code_one_line(std::ofstream &fout, std::vector<std::string> &one_line_rule, int rule_num, int line_num);


    int out_ast_to_icode_elem(std::ofstream &fout);
    int out_ast_to_icode_ast(std::ofstream &fout);

    int line_num_to_int(int rule_num, int line_num);
    std::string line_num_to_str(int rule_num, int line_num);
public:
    int m_debug;

    std::vector<std::string> m_func_sep_filename;
    std::vector<int> m_func_sep_file_rule_start;
    void comments_parse(std::string comments);

};

#endif // BISON_FILE_IO_H
