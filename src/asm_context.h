#ifndef ASM_CONTEXT_H
#define ASM_CONTEXT_H


#include <vector>
#include <string>
#include <map>
#include "text_block.h"

#define DEBUG_ALL 1


typedef int(* CODE_GEN_FUNC_PTR) (struct TAG_T_ASM_CONTEXT_tag *mCtx);


typedef struct TAG_T_ASM_CONTEXT_tag
{

    /// 0---成功生成代码； 1---需要二遍生成代码(例如label需要二次定位地址)； 2-其他错误

    ///当前行号--改名为： m_current_line_cnt
    int m_current_line_no;

    unsigned long m_current_address;///当前代码地址

    ///当前一行要处理的字符串
    T_HEX_TEXT_BLOCK m_current_block;

    //代码段，每次追加,每行一个block
    std::vector<T_HEX_TEXT_BLOCK> m_text_block;

    ///所有的命令，和对应的代码生成函数
    std::map<std::string, CODE_GEN_FUNC_PTR> m_line_key_word_ptr;

    ///记录每个label的地址
    std::map<std::string, unsigned long> m_label_address;

    ///记录每个需要更新label地址的位置
    std::vector<int> m_text_block_need_refresh_index;

}T_ASM_CONTEXT;




int asm8051_context_init(T_ASM_CONTEXT *mCtx);
int split_words(std::string mOneLine, std::vector<std::string> &mWords);


#endif // ASM_CONTEXT_H
