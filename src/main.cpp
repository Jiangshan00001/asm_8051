#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cctype>
#include "main.h"
#include "asm_8051_keywords.h"
#include "asm8051_lex .h"
#include "hex_generator.h"

using namespace std;



std::string process_one_line(T_ASM_CONTEXT *mCtx, int index, int first_time)
{
	std::string cmd_world;
	
	mCtx->m_current_one_line = mCtx->m_text_block[index].m_source;
	mCtx->m_current_line_no = mCtx->m_text_block[index].m_line_no;
	if (!first_time)
	{
		mCtx->m_current_address = mCtx->m_text_block[index].m_address;
	}
#if DEBUG_ALL
	cout<<"line: "<<mCtx->m_current_one_line<<endl;
#endif

	if (index==16)
	{
		int mm = 0;
	}
	int world_count = split_words(mCtx->m_current_one_line, mCtx->m_current_line_words);
	if(world_count==0)return "";
	
	//////////////////////////////////////////////////////////////////////////
	/// process label
	if ((mCtx->m_current_line_words.size()>1)&&
		(mCtx->m_current_line_words[1][0]==':') )
	{
		cmd_world = mCtx->m_current_line_words[2];
		///处理label。添加label的地址标记. FIXME TODO 此处对于添加标签时，如果标签已经存在，则报标签重复错误
		if(first_time)
		{
			mCtx->m_label_address[mCtx->m_current_line_words[0]] = mCtx->m_current_address;
		}
		/// 将label去掉，便于后续的代码生成。只在worlds中去掉，在源代码中不变
		mCtx->m_current_line_words.erase(mCtx->m_current_line_words.begin());
		mCtx->m_current_line_words.erase(mCtx->m_current_line_words.begin());
	}
	else
	{
		cmd_world = mCtx->m_current_line_words[0];
	}
	//////////////////////////////////////////////////////////////////////////
	
	
	std::map<std::string, CODE_GEN_FUNC_PTR>::iterator it = 
		mCtx->m_line_key_word_ptr.find(cmd_world);
	
	if(it != mCtx->m_line_key_word_ptr.end())
	{
		cout<<"INFO:line="<<mCtx->m_current_line_no<<"." <<cmd_world<<endl;
		
		mCtx->m_current_line_out="";
		int ret = (*it->second)(mCtx);
		if((ret!=0)&&(ret!=1))
		{
			cout<<"error: line="<<mCtx->m_current_line_no<<"." <<mCtx->m_current_one_line<<endl;
		}
		if (mCtx->m_current_line_out.size()>0)
		{
			//成功生成代码
			if (ret)//need refresh
			{
				if (first_time)///FIXME 此处只有处理2遍，多了可能导致死循环
				{
					mCtx->m_text_block_need_refresh_index.push_back(index);
				}
				
			}
			mCtx->m_text_block[index].m_hex_text = mCtx->m_current_line_out;
			if (first_time)
			{
				mCtx->m_text_block[index].m_address = mCtx->m_current_address;
			}
			mCtx->m_current_address+=mCtx->m_current_line_out.size();
		}
		else
		{
			//zero size code. eg. ORG 1000H
		}
	}
	else
	{
		cout<<"error: line="<<mCtx->m_current_line_no<<"." <<mCtx->m_current_one_line<<endl;
	}
	
	
	return "";
}


int main(int argc, char *argv[])
{
	std::string m_file_name_in="asm_test/asm_test1.asm";
	std::string m_file_name_hex_out;

	T_ASM_CONTEXT m_context;
	ifstream m_file_in;

	//////////////////////////////////////////////////////////////////////////
	asm8051_context_init(&m_context);
	//////////////////////////////////////////////////////////////////////////
	/// 读入关键字

	//////////////////////////////////////////////////////////////////////////
	m_file_in.open(m_file_name_in.c_str());

	///读出一行
	std::string mOneLine;
	m_context.m_current_line_no = 0;

	while(getline(m_file_in, mOneLine))
	{
		T_HEX_TEXT_BLOCK mBlk;
		cout<<m_context.m_current_line_no<<". "<< mOneLine<<endl;
		mBlk.m_line_no = m_context.m_current_line_no;
		mBlk.m_source = mOneLine;
		mBlk.m_address = 0;
		m_context.m_text_block.push_back(mBlk);
		m_context.m_current_line_no++;	
	}
	m_file_in.close();
	//////////////////////////////////////////////////////////////////////////
	for (int k1=0;k1<m_context.m_text_block.size();++k1)
	{
#if DEBUG_ALL
		cout<<"====================================="<<endl;
		cout<<"process1 k="<<k1<<endl;
#endif
		process_one_line(&m_context, k1, 1);
	}


	//////////////////////////////////////////////////////////////////////////
	///第二遍处理需要重定位的代码
	//////////////////////////////////////////////////////////////////////////
	for (int k=0;k<m_context.m_text_block_need_refresh_index.size();++k)
	{
#if DEBUG_ALL
		cout<<"====================================="<<endl;
		cout<<"process2 k="<<k<<endl;
#endif
		process_one_line(&m_context, m_context.m_text_block_need_refresh_index[k], 0);
	}

	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	///将代码集合起来,生成hex文件
	//////////////////////////////////////////////////////////////////////////
    //m_context.m_text_block
#if DEBUG_ALL
	cout<<"hex output:"<<endl;

	for (int i=0;i<m_context.m_text_block.size();i++)
	{
		cout<<i<<". ";
		cout<<std::hex<<m_context.m_text_block[i].m_address<<". "<< endl;
		for (int j=0;j<m_context.m_text_block[i].m_hex_text.size();++j)
		{
			cout<<std::hex<<(unsigned int)m_context.m_text_block[i].m_hex_text[j]<<" ";
		}
		cout<<endl;
	}
#endif

	hex_generator(&m_context, "test.hex");
	//////////////////////////////////////////////////////////////////////////

	return 0;
}
