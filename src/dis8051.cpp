#include "dis8051.h"
#include<set>
#include <iostream>

#include "hex_generator.h"
#include "asm_table.h"
#include "split.h"
#include "trim.h"

dis8051::dis8051()
{
    load_inst();
}

dis8051::~dis8051()
{

}

std::string dis8051::dis_one_inst(std::string mhex, hex_code_asm_table &inst_info)
{
    std::set<std::string> to_inst;
    to_inst.insert("code addr");
    to_inst.insert("data addr");
    to_inst.insert("bit addr");
    to_inst.insert("#data");
    to_inst.insert("/bit addr");


    std::vector<std::string> params = split(inst_info.params,",");
    std::vector<int>  params_need_fill;
    int need_fill_cnt=0;
    for(int i=0;i<params.size();++i)
    {
        params[i] = trim(params[i]);
        if(to_inst.find(params[i])!=to_inst.end())
        {
            need_fill_cnt++;
            params_need_fill.push_back(1);
        }
        else
        {
            params_need_fill.push_back(0);
        }
    }

    if(need_fill_cnt==0)
    {
       //do nothing
    }
    else if((need_fill_cnt==1)&&(mhex.size()==2))
    {
        for(int i=0;i<params.size();++i)
        {
            if(params_need_fill[i])
            {
                params[i] = ByteToStr(mhex[1]);
                break;
            }
        }
    }
    else if((need_fill_cnt==2)&&(mhex.size()==3))
    {
        int f1=1;
        for(int i=0;i<params.size();++i)
        {
            if(params_need_fill[i])
            {
                params[i] = ByteToStr(mhex[f1]);
                f1++;
            }
        }
    }
    else if((need_fill_cnt==1)&&(mhex.size()==3))
    {

        for(int i=0;i<params.size();++i)
        {
            if(params_need_fill[i])
            {
                params[i] = ByteToStr(mhex[1]) + ByteToStr(mhex[2]);
                break;
            }
        }
    }
    else {
        std::cout<<"dis_one_inst param fill error"<<std::endl;
        std::cout<<inst_info.cmd<<" "<< inst_info.params<<std::endl;
        std::cout<<"mhex len="<<mhex.size()<<std::endl;

    }



    std::stringstream ret_out;
    ret_out<<inst_info.cmd<<" ";
    for(int i=0;i<params.size();++i)
    {
        ret_out<<params[i];
        if(i!=params.size()-1)
        {
            ret_out<<",";
        }
    }

    return ret_out.str();
}

std::string dis8051::add_hex_str(std::string hex_format_str)
{
    std::stringstream ret_out;
    std::vector<hex_block> hex_blocks = hex_file_to_hex_data(hex_format_str);


    for(int i=0;i<hex_blocks.size();++i)
    {
        //hex_blocks[i].m_address;
        for(int j=0;j<hex_blocks[i].m_hex.size();)
        {   //每个byte
            unsigned char cbyte = hex_blocks[i].m_hex[j];
            hex_code_asm_table &inst_info =m_inst_dis[cbyte];
            unsigned int inst_byte_num = inst_info.m_byte_num;

            std::string mhex = hex_blocks[i].m_hex.substr(j, inst_byte_num);

            ret_out<<dis_one_inst(mhex, inst_info)<<";"<<ByteToStr(cbyte);
            j++;
            for(int k=0;k<inst_byte_num-1;++k)
            {
                ret_out<<ByteToStr(hex_blocks[i].m_hex[j]);
                j++;
            }
            ret_out<<"\r\n";
        }
    }
    return ret_out.str();
}

int dis8051::load_inst()
{
    for(int i=0;i<g_hex_table_size;++i)
    {
        m_inst_dis[g_hex_table[i].m_hex_code] = g_hex_table[i];
    }
}


