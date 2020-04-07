#include <sstream>
#include <assert.h>
#include <iostream>
#include "asm8051.h"
#include "asm_context.h"
#include "hex_generator.h"
#include "asm8051_lex.h"
#include "text_block.h"
#include "asm_keywords.h"
#include "trim.h"
#include "split.h"
using namespace std;

asm8051::asm8051()
{
    mp_context = new T_ASM_CONTEXT();

    asm8051_context_init(mp_context);

    m_is_debug = 1;
}

asm8051::~asm8051()
{
    delete (T_ASM_CONTEXT*)mp_context;
}

int asm8051::add_line(std::string one_line_text, int line_no)
{
    ///TODO: 行的随机插入不支持，只支持顺序插入
    assert(line_no==-1);
    T_ASM_CONTEXT &m_context = * (T_ASM_CONTEXT*)mp_context;


    if(trim(one_line_text).size()==0)
    {
        return 0;
    }


    line_no = m_context.m_current_line_no;

    if(one_line_text.find(":")!=one_line_text.npos)
    {
        //additional label block add
        std::string mtmp = trim(one_line_text);
        std::vector<std::string> mtmp2 = split(mtmp,":");

        T_HEX_TEXT_BLOCK mBlk;
        std::string label_str = mtmp2[0]+":";
        mBlk.set_src_text(label_str, line_no);
        mBlk.m_tokens = asm_line_parse(&m_context, mBlk.m_source);
        m_context.m_text_block.push_back(mBlk);

        //去除标签
        one_line_text = one_line_text.substr(label_str.size());
    }



    T_HEX_TEXT_BLOCK mBlk;
    mBlk.set_src_text(one_line_text, line_no);
    mBlk.m_tokens = asm_line_parse(&m_context, mBlk.m_source);
    m_context.m_text_block.push_back(mBlk);


    m_context.m_current_line_no++;

    if(m_is_debug)
    {
        std::cout<<"============"<<std::endl;
        std::cout<<"add line:"<<m_context.m_current_line_no<<":"<<one_line_text<<std::endl;
        for(int i=0;i<mBlk.m_tokens.size();++i)
        {
            std::cout<<mBlk.m_tokens[i].type<<"-"<<mBlk.m_tokens[i].val_str<<std::endl;
        }
        std::cout<<"============"<<std::endl;
    }

}

int asm8051::add_src(std::string code_src)
{
    T_ASM_CONTEXT &m_context = * (T_ASM_CONTEXT*)mp_context;

    std::stringstream m_file_in(code_src);

    ///读出一行
    std::string mOneLine;
    m_context.m_current_line_no = 0;

    while(getline(m_file_in, mOneLine))
    {
        add_line(mOneLine);
    }
}

int asm8051::compile()
{
    //确定地址
    compile_first();

    compile_update_label();

    compile_second();
}


std::string asm8051::generate_hex()
{

    std::string m_out = hex_generator_str((T_ASM_CONTEXT*)mp_context);

    return m_out;
}

int asm8051::compile_first()
{
    T_ASM_CONTEXT &m_context = * (T_ASM_CONTEXT*)mp_context;

    for (int k1=0;k1<m_context.m_text_block.size();++k1)
    {
#if DEBUG_ALL
        cout<<"====================================="<<endl;
        cout<<"process1 k="<<k1<<endl;
#endif
        process_one_line(&m_context, k1, 1);
    }
    return 0;
}

int asm8051::compile_update_label()
{
    //更新label到各指令中

    T_ASM_CONTEXT &m_context = * (T_ASM_CONTEXT*)mp_context;
    for(int i=0;i<m_context.m_text_block.size();++i)
    {
        for(int j=0;j<m_context.m_text_block[i].m_tokens.size();++j)
        {
            unsigned long addr = m_context.m_text_block[i].m_address;
            asm_token &ctoken = m_context.m_text_block[i].m_tokens[j];
            if (ctoken.type==TOKEN_KEYWORD)
            {
                if (m_context.m_label_address.find(ctoken.val_str)!=m_context.m_label_address.end())
                {
                    //找到，则更新num,rel
                    ctoken.num = m_context.m_label_address[ctoken.val_str];
                    ctoken.rel = ctoken.num- addr - m_context.m_text_block[i].m_hex_text.size();

                    m_context.m_text_block_need_refresh_index.push_back(i);
                }
            }
        }
    }
    return 0;
}

int asm8051::compile_second()
{
    T_ASM_CONTEXT &m_context = * (T_ASM_CONTEXT*)mp_context;

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
    return 0;
}

std::string asm8051::process_one_line(void *mCtx, int index, int first_time)
{
    T_ASM_CONTEXT &m_context = * (T_ASM_CONTEXT*)mp_context;

    m_context.m_current_block = m_context.m_text_block[index];

    std::vector<asm_token> &m_token = m_context.m_current_block.m_tokens;

    std::string cmd_world = m_context.m_current_block.m_tokens[0].val_str;


    //////////////////////////////////////////////////////////////////////////
    /// process org
    ///
    if(cmd_world=="ORG")
    {
        m_context.m_current_address = m_context.m_current_block.m_tokens[1].num;
        return "";
    }
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    /// process end
    ///
    if(cmd_world=="END")
    {

        return "";
    }
    //////////////////////////////////////////////////////////////////////////



    //////////////////////////////////////////////////////////////////////////
    /// process label
    if(m_token[0].type==TOKEN_LABEL)
    {
        ///处理label。添加label的地址标记. FIXME TODO 此处对于添加标签时，如果标签已经存在，则报标签重复错误
        if(first_time)
        {
            m_context.m_label_address[m_token[0].val_str] = m_context.m_current_address;
        }
        return "";
    }

    //////////////////////////////////////////////////////////////////////////



    std::map<std::string, CODE_GEN_FUNC_PTR>::iterator it =
            m_context.m_line_key_word_ptr.find(cmd_world);

    if (it== m_context.m_line_key_word_ptr.end())
    {
        //未找到命令？？？
        std::cout<<"cmd not found error!!!"<< cmd_world <<std::endl;
        return "";
    }

    int ret = (*it->second)(&m_context);
    if((ret!=0)&&(ret!=1))
    {
        cout<<"error: line:"<<index<<". "<< m_context.m_current_block.m_source <<endl;
    }

    m_context.m_text_block[index] = m_context.m_current_block;


    ///更新地址
    if (first_time)
    {
        m_context.m_text_block[index].m_address = m_context.m_current_address;
    }
    m_context.m_current_address+=m_context.m_current_block.m_hex_text.size();

    return "";
}



