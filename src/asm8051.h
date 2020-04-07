#ifndef ASM8051_H
#define ASM8051_H

#include <string>



///限制：标签为单独行
/// 转移地址必须使用标签，不能直接使用常数(可通过预处理实现)
class asm8051
{
public:
    asm8051();

    ~asm8051();

    int add_line(std::string one_line_text, int line_no=-1 );
    int add_src(std::string code_src);



    int compile();

    std::string generate_hex();



    int m_is_debug;

private:
    void *mp_context;



    int compile_first();
    int compile_update_label();
    int compile_second();

    std::string process_one_line(void *mCtx, int index, int first_time);

};

#endif // ASM8051_H
