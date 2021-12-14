#include <algorithm>
#include "split.h"
#include "trim.h"
#include "replace.h"
#include "csv_to_dis.h"
#include "csv_io.h"
csv_to_dis::csv_to_dis()
{
}

int csv_to_dis::set_input_file(std::string dis_list_file, std::string operand_list_file)
{
    ///Hex Code,Humber of Bytes,Mnemonic,Operands,param_count,param0,param1,param3
    csv_io m_io;

    m_io.set_file_name(dis_list_file);
    m_io.open_file();
    m_dis_list_head = m_io.parse_next_line(NULL);
    m_dis_list = m_io.parse_file();

    for(int i=0;i<m_dis_list.size();++i)
    {
        if(m_dis_list[i].empty())
        {
            m_dis_list.erase(m_dis_list.begin()+i);
        }
    }




    csv_io m_io2;

    m_io2.set_file_name(operand_list_file);
    m_io2.open_file();
    std::vector<std::string> head2 = m_io2.parse_next_line(NULL);
    std::vector<std::vector<std::string> > opr1 = m_io2.parse_file();

    for(int i=0;i<opr1.size();++i)
    {
        if(opr1[i].size()<2)continue;
        std::string opr_name = opr1[i][0];
        std::string opr_type_name = opr1[i][1];
        m_dist_operand_type[opr_name] = opr_type_name;
        m_operand_type_list.insert(opr_type_name);
    }


    return 0;
}

int csv_to_dis::output_dis_cpp(std::string output_file)
{
    #define ADD_CRLF_ASM_END 0
    std::ofstream fout(output_file);

    fout<<"#include \"to_asm.h\"\n";
    fout<<"#include \"dis_funcs.h\"\n";


    fout<<"namespace "<<m_namespace<<"{\n";
    for(int i=0;i<m_dis_list.size();++i)
    {
        if(m_dis_list[i].empty())continue;
        generate_func_decl(m_dis_list[i], fout);
        fout<<"\n{\n";
        ///function start
        ///
        ///

        fout<<"//" ;
        for(int j=0;j<8;++j)
        {
            fout<<m_dis_list[i][j]<<"|\t";
        }
        fout<<"\n" ;

        fout<<"mout<<"<<quote_if_not( m_dis_list[i][2])<<"<<\" \""<<";\n";

        if (m_dis_list[i][4]=="-1")
        {
#if ADD_CRLF_ASM_END
            fout<<"mout<<"<<quote_if_not(m_dis_list[i][3])<<"<<\";\\n\";\n";
#else
            fout<<"mout<<"<<quote_if_not(m_dis_list[i][3])<<"<<\";\";\n";
#endif
        }
        else
        {
            int param_int = atoi(m_dis_list[i][4].c_str());

            ///此处对参数进行整理切分
            std::vector<std::string> params = split(m_dis_list[i][3],",", 1);
            for(int i=0;i<params.size();++i)
            {
                params[i] = trim_quote_if_exist(params[i]);
            }


            for(int j=0;j<param_int;++j)
            {
                ///每一个参数进行计算
                if(m_dis_list[i][5+j].size()==0)
                {
                    ///参数为字符串，直接从params中获取
                    fout<<"mout<<"<<quote_if_not(params[j])<<";\n";
                }
                else
                {
                    ///如果参数数公式，则是数值
                    std::string tmp = m_dis_list[i][5+j];
                    replace(tmp,"$0","mbin[i_byte_offset]");
                    replace(tmp, "$1",  "mbin[i_byte_offset+1]");
                    replace(tmp, "$2", "mbin[i_byte_offset+2]");
                    fout<<"unsigned val"<<j<<"="<<tmp <<";\n";
                    fout<<"mout<<dis->type_to_str_"<<m_dist_operand_type[trim(params[j])]<<"(val" <<j<<", curr_addr, " << m_dis_list[i][1]<<");\n";
                    if (m_dist_operand_type.find(trim(params[j]))==m_dist_operand_type.end())
                    {
                        int mm = 0;
                        std::cout<<"find param warning: "<<trim(params[j])<<std::endl;
                    }
                }

                if(j!=param_int-1)
                {
                    /// 不是最后一个参数
                    fout<<"mout<<\", \"; \n";
                }
                else
                {
                    /// 最后一个参数
                    //
#if ADD_CRLF_ASM_END
                    fout<<"mout<<\";\\n\"; \n";

#else
                    fout<<"mout<<\";\"; \n";
#endif
                }
            }



        }


        /// function end
        fout<<"return 0;\n";
        fout<<"}\n\n";
    }

    fout<<"int load_dis_funcs(std::map<unsigned, DIS_FUNC_PTR> &keys)\n";
    fout<<"{\n";
    for(int i=0;i<m_dis_list.size();++i)
    {
        std::vector<std::string> &dist_1 = m_dis_list[i];
        fout<<"keys[0x"<<dist_1[0]<<"]=";
        generate_func_name(dist_1, fout);
        fout<<";\n";
    }
    fout<<"return 0;\n}\n";


    fout<<"int get_inst_byte_len(unsigned first_byte)\n";
    fout<<"{\n";
    fout<<"switch(first_byte)\n";
    fout<<"{\n";//switch start

    for(int i=0;i<m_dis_list.size();++i)
    {
        std::vector<std::string> &dist_1 = m_dis_list[i];
        fout<<"case 0x"<<dist_1[0]<<":";
        fout<<"return "<<dist_1[1]<<";\n";
    }

    fout<<"}\n";//switch end
    fout<<"return 0;\n}\n";


    fout<<"}//namespace end\n";

    fout.close();
    return 0;
}

int csv_to_dis::output_dis_h(std::string output_file)
{
    std::ofstream fout(output_file);

    std::string namespace_upper = m_namespace;
    std::transform(namespace_upper.begin(), namespace_upper.end(), namespace_upper.begin(), ::toupper);
    std::string def_guard =namespace_upper+"_DIS_FUNC_H";
    fout<<"#ifndef "<<def_guard<<"\n";
    fout<<"#define "<<def_guard<<"\n";
    fout<<"#include <map>\n";
    fout<<"namespace "<< m_namespace<<"{\n\n";
    fout<<"class to_asm;\n";

    fout<<"typedef enum E_TYPE_DIS_OPR{\n";
    for(auto i=m_operand_type_list.begin();i!=m_operand_type_list.end();++i)
    {
        fout<<*i<<",\n";
    }
    fout<<"} E_TYPE_DIS_OPR;\n";

    fout<<"typedef int (* DIS_FUNC_PTR) ( to_asm *dis, const std::string &mbin, int ibyte_offset, unsigned curr_addr, std::ostream &mout);\n";
    for(int i=0;i<m_dis_list.size();++i)
    {
        if(m_dis_list[i].empty())continue;
        generate_func_decl(m_dis_list[i], fout);
        fout<<";\n";
    }

    fout<<"int load_dis_funcs(std::map<unsigned, DIS_FUNC_PTR> &keys);\n";
    fout<<"int get_inst_byte_len(unsigned first_byte);\n";
    fout<<"}//namespace end\n";
    fout<<"#endif\n";

    return 0;

}

int csv_to_dis::set_namespace(std::string inamespace)
{
    m_namespace = inamespace;
    return 0;
}

int csv_to_dis::generate_func_decl(std::vector<std::string> &dist_1, std::ostream &stri)
{
    if(dist_1.size()==0)
    {
        stri<<"void null_func()";
        return 0;
    }

    stri<<"int ";
    generate_func_name(dist_1, stri);
    stri<<"(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)";
    return 0;
}

int csv_to_dis::generate_func_name(std::vector<std::string> &dist_1, std::ostream &stri)
{
    stri<<"AA_"<<dist_1[0]<<"H";
    return 0;
}

std::string csv_to_dis::quote_if_not(std::string str_to_quote)
{
    int add_start_quote=1;
    int add_end_quote=1;
    if(str_to_quote.size()==0)
    {
        return "\"\"";
    }



    if(str_to_quote[0]=='"')
    {
        //有引号
        add_start_quote = 0;
    }
    if(str_to_quote[str_to_quote.size()-1]=='"')
    {
        //有引号
        add_end_quote = 0;
    }



    return (add_start_quote? "\"" : "") + str_to_quote + (add_end_quote?"\"":"");
}

std::string csv_to_dis::trim_quote_if_exist(std::string aa)
{
    if(aa.empty())return "";
    if(aa[0]=='\"')
    {
        aa = aa.substr(1);
    }

    if(aa[aa.size()-1]=='\"')
    {
        aa=aa.substr(0, aa.size()-1);
    }

    return aa;
}
