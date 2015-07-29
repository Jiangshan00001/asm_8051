#ifndef MAIN_H
#define MAIN_H
#include <string>
#include <map>
#include <vector>
#include <iostream>
#define DEBUG_ALL 1

/// 0---成功生成代码； 1---需要二遍生成代码(例如label需要二次定位地址)； 2-其他错误
typedef int(* CODE_GEN_FUNC_PTR) (struct TAG_T_ASM_CONTEXT *mCtx);

typedef struct TAG_T_HEX_TEXT_BLOCK
{
	std::string m_source;//当前行的源代码
	int m_line_no;///当前行号

	unsigned long m_address;
	std::string m_hex_text;
	//int m_need_refresh;//对于含有label的，可能需要第二遍更新偏移地址

}T_HEX_TEXT_BLOCK;

typedef struct TAG_T_ASM_CONTEXT
{
	///当前行号
	int m_current_line_no;
	///当前一行要处理的字符串
	std::string m_current_one_line;
	std::string m_current_line_out;	
	std::vector<std::string> m_current_line_words;///当前行的所有单词

	unsigned long m_current_address;///当前代码地址


	//代码段，每次追加,每行一个block
	std::vector<T_HEX_TEXT_BLOCK> m_text_block;

	///所有的命令，和对应的代码生成函数
	std::map<std::string, CODE_GEN_FUNC_PTR> m_line_key_word_ptr;

	///记录每个label的地址
	std::map<std::string, unsigned long> m_label_address;

	///记录每个需要更新label地址的位置
	std::vector<int> m_text_block_need_refresh_index;

}T_ASM_CONTEXT;



#endif


