#ifndef CSV_IO_H
#define CSV_IO_H
#include <string>
#include <vector>
#include <iostream>
#include <fstream>


class csv_io
{
public:
    csv_io();
    ///解析打开的文件到文件尾，生成列表
    std::vector<std::vector<std::string> > parse_file(int remove_empty=0);

    int set_file_name(std::string file_name);
    int open_file();
    std::vector<std::string> parse_next_line(int *is_eof);
    int close_file();
public:
    std::string m_quote = "\"";
    std::string m_delimiter = ",";

private:
    std::string m_file_name;
    std::ifstream m_file;
    // Configurable attributes
    //Term m_terminator = Term::CRLF;
};

#endif // CSV_IO_H
