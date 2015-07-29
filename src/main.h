#ifndef MAIN_H
#define MAIN_H
#include <string>
#include <map>
#include <vector>
#include <iostream>
#define DEBUG_ALL 1

/// 0---�ɹ����ɴ��룻 1---��Ҫ�������ɴ���(����label��Ҫ���ζ�λ��ַ)�� 2-��������
typedef int(* CODE_GEN_FUNC_PTR) (struct TAG_T_ASM_CONTEXT *mCtx);

typedef struct TAG_T_HEX_TEXT_BLOCK
{
	std::string m_source;//��ǰ�е�Դ����
	int m_line_no;///��ǰ�к�

	unsigned long m_address;
	std::string m_hex_text;
	//int m_need_refresh;//���ں���label�ģ�������Ҫ�ڶ������ƫ�Ƶ�ַ

}T_HEX_TEXT_BLOCK;

typedef struct TAG_T_ASM_CONTEXT
{
	///��ǰ�к�
	int m_current_line_no;
	///��ǰһ��Ҫ������ַ���
	std::string m_current_one_line;
	std::string m_current_line_out;	
	std::vector<std::string> m_current_line_words;///��ǰ�е����е���

	unsigned long m_current_address;///��ǰ�����ַ


	//����Σ�ÿ��׷��,ÿ��һ��block
	std::vector<T_HEX_TEXT_BLOCK> m_text_block;

	///���е�����Ͷ�Ӧ�Ĵ������ɺ���
	std::map<std::string, CODE_GEN_FUNC_PTR> m_line_key_word_ptr;

	///��¼ÿ��label�ĵ�ַ
	std::map<std::string, unsigned long> m_label_address;

	///��¼ÿ����Ҫ����label��ַ��λ��
	std::vector<int> m_text_block_need_refresh_index;

}T_ASM_CONTEXT;



#endif


