#include <assert.h>
#include <vector>

#include <sstream>
#include <algorithm>
#include "csv_to_asmc.h"
#include "split.h"

#include "trim.h"
#include "replace.h"
#include "csv_io.h"


csv_to_asmc::csv_to_asmc()
{
}

int csv_to_asmc::set_input_file(std::string asm_list_file, std::string operand_list_file)
{
    ///Mnemonic,Operands,Description,Byte,Oscillator Period,Class,BYTE0,BYTE1,BYTE2
    csv_io m_io;

    m_io.set_file_name(asm_list_file);
    m_io.open_file();
    m_asm_list_head = m_io.parse_next_line(NULL);
    m_asm_list = m_io.parse_file();

    for(int i=0;i<m_asm_list.size();++i)
    {
        if(m_asm_list[i].empty())
        {
            m_asm_list.erase(m_asm_list.begin()+i);
        }
    }


    for(int i=0;i<m_asm_list.size();++i)
    {
        m_cmd_list.insert(m_asm_list[i][0]);
    }





    csv_io m_io2;

    m_io2.set_file_name(operand_list_file);
    m_io2.open_file();
    std::vector<std::string> head2 = m_io2.parse_next_line(NULL);
    std::vector<std::vector<std::string> > opr1 = m_io2.parse_file();

    for(int i=0;i<opr1.size();++i)
    {
        if(opr1[i].size()<3)continue;
        std::string opr_name = opr1[i][0];
        std::string opr_type_name = opr1[i][1];
        std::string opr_type_asm_name = opr1[i][2];
        std::string type_mask = opr1[i][3];

        m_str_to_asm_token_type[opr_name] = opr_type_name;
        m_type_mask[opr_type_name] = type_mask;

        m_operand_type_list.insert(opr_type_name);

        std::vector<std::string> asm_possible_type=split(opr_type_asm_name,"/",1);
        m_ic_token_type_list.insert(asm_possible_type.begin(), asm_possible_type.end());
        m_asm_token_to_ic_token_type[opr_type_name] = asm_possible_type;
    }


    return 0;
}

int csv_to_asmc::output_asm_cpp(std::string output_file)
{
    std::ofstream fout(output_file);

    fout<<"#include \"asm_to.h\"\n";
    fout<<"#include \"asm_funcs.h\"\n";
    fout<<"#include \"assert.h\"\n";
    fout<<"#include \"mylog.h\"\n";
    fout<<"using mylog::cerr;\n";


    fout<<"namespace "<< m_namespace<<"{\n\n";

    fout<<"//this enum may conflit with dis_funcs.h\n// so please do not include dis_funcs.h\n";
    fout<<"typedef enum E_TYPE_ASM_TOKEN_OPR{\n";
    for(auto i=m_operand_type_list.begin();i!=m_operand_type_list.end();++i)
    {
        fout<<*i<<",\n";
    }
    fout<<"} E_TYPE_ASM_TOKEN_OPR;\n";


    fout<<abs_to_rel_patch_func();

    for(auto i=m_cmd_list.begin();i!=m_cmd_list.end();++i)
    {
        std::string ccmd = *i;
        fout<<get_cmd_func(ccmd)<<"\n";
        fout<<"\n{\n";
        for(int j=0;j<m_asm_list.size();++j)
        {

            std::vector<std::string> & curr_asm_line = m_asm_list[j];
            if(curr_asm_line.empty())continue;
            if(curr_asm_line[0]!=ccmd)continue;
            fout<<"//"<< vec_str_to_str(curr_asm_line)<<"\n";
            std::vector<std::string> param_str = split(curr_asm_line[1], ",");
            for(int pi=0;pi<param_str.size();++pi) param_str[pi] = trim_quote_if_exist(param_str[pi]);

            fout<<"if(\n(opr_cnt==0x"<<std::hex<< param_str.size()<<")\n";
            if(param_str.size()>0)
            {
                for(int k=0;k<param_str.size();k++)
                {
                    fout<<"&&(";//parami start
                    std::vector<std::string> v = m_asm_token_to_ic_token_type[m_str_to_asm_token_type[param_str[k]] ];
                    if(v.size()==0)
                    {
                        std::cout<<"cmd:"<<ccmd <<". "<< "param:"<< param_str[k]<<"token zero error"<< "\n";
                        assert(0);
                    }
                    for(int vv=0;vv<v.size();++vv)
                    {
                        if(vv>0)fout<<"||";
                        fout<<"(opr_type"<<k+1<<"=="<<v[vv]<<")";
                    }
                    fout<<")\n";//parami end
                }
            }


            fout<<")\n";//if )end
            fout<<"{\n";// if in
            int byte_cnt = atoi(curr_asm_line[3].c_str());


            fout<<"int is_jmp_err = 0;\n";
            ///if进入，此处每一个参数，都根据具体含义，添加mask
            ///
            for(int k=0;k<param_str.size();++k)
            {

                if(m_str_to_asm_token_type[param_str[k]]=="TOKEN_REL")
                {
                    // here is a rel token patch
                    fout<<"is_jmp_err |= abs_to_rel(curr_addr+"<<byte_cnt  <<",opr_val"<<k+1<<");\n";
                }
                else if(m_str_to_asm_token_type[param_str[k]]=="TOKEN_ADDR11")
                {
                    //11bit addr
                    fout<<"if(((curr_addr+"<<byte_cnt<<")&0x0000f800)!="<<"(opr_val"<<k+1<<" &0x0000f800))\n";
                    fout<<"{is_jmp_err = 1;}\n";
                }

                {
                    fout<<"opr_val"<<k+1<<" &="<<m_type_mask[m_str_to_asm_token_type[param_str[k]]]<<";\n";
                }
            }



            /// 此处生成代码


            fout<<"ibin.resize("<<byte_cnt<<");\n";
            for(int k=0;k<byte_cnt;k++)
            {
                replace(curr_asm_line[6+k],"$1", "opr_val1");
                replace(curr_asm_line[6+k],"$2", "opr_val2");
                replace(curr_asm_line[6+k],"$3", "opr_val3");
                fout<<"ibin["<<k<< "] = "<<curr_asm_line[6+k]<<";\n";
            }

            fout<<"return is_jmp_err;\n";
            fout<<"}\n";// if end
        }


        fout<<"return -1;\n";
        fout<<"\n}\n";//func end
    }

    fout<<"typedef "<< "int (*ASM_FUNC_PTR)(const std::string cmd, int opr_cnt, "
                                 "int opr_type1, unsigned opr_val1, int opr_type2, unsigned opr_val2,"
                                 "int opr_type3, unsigned opr_val3, unsigned curr_addr, std::string &ibin);\n";
    ///全局变量
    fout<<"static std::map<std::string, ASM_FUNC_PTR> g_func_map {\n";
    for(auto i=m_cmd_list.begin();i!=m_cmd_list.end();++i)
    {
        fout<<"{\""<<*i<<"\","<<get_cmd_func_name(*i)<<"},\n";
    }
    fout<<"};\n";


    fout<<asm_to_bin_func();
    fout<<"\n{\n";// asm_to_bin_func start

    fout<<"ASM_FUNC_PTR ptr = g_func_map[cmd];\n";
    fout<<"assert(ptr!=NULL);\n";
    fout<<"return ptr(cmd,opr_cnt,opr_type1, opr_val1, opr_type2, opr_val2, opr_type3, opr_val3,curr_addr, ibin);\n";

    fout<<"\n}//asm_to_bin_func end\n";//asm_to_bin_func end


    fout<<"\n}//namespace end\n";//namespace end
    fout.close();
    return 0;
}

int csv_to_asmc::output_asm_h(std::string output_file)
{
    std::ofstream fout(output_file);

    std::string namespace_upper = m_namespace;
    std::transform(namespace_upper.begin(), namespace_upper.end(), namespace_upper.begin(), ::toupper);
    std::string def_guard =namespace_upper+"_ASM_FUNCS_H";
    fout<<"#ifndef "<<def_guard<<"\n";
    fout<<"#define "<<def_guard<<"\n";
    fout<<"#include <map>\n";
    fout<<"namespace "<< m_namespace<<"{\n\n";
    fout<<"class asm_to;\n";

    fout<<"typedef enum E_TYPE_IC_TOKEN_OPR{\n";
    for(auto i=m_ic_token_type_list.begin();i!=m_ic_token_type_list.end();++i)
    {
        fout<<*i<<",\n";
    }
    fout<<"} E_TYPE_IC_TOKEN_OPR;\n";

    fout<<asm_to_bin_func()<<";\n";

    fout<<"}//namespace end\n";
    fout<<"#endif\n";

    fout.close();
    return 0;
}

int csv_to_asmc::set_namespace(std::string inamespace)
{
    m_namespace = inamespace;
    return 0;
}

std::string csv_to_asmc::asm_to_bin_func()
{
    return "int get_asm_to_bin(const std::string cmd, int opr_cnt, "
           "int opr_type1, unsigned opr_val1, int opr_type2, unsigned opr_val2,"
           "int opr_type3, unsigned opr_val3, unsigned curr_addr,  std::string &ibin)";
}

std::string csv_to_asmc::get_cmd_func(std::string cmd)
{
    return "int "+get_cmd_func_name(cmd)+ "(const std::string cmd, int opr_cnt, "
                       "int opr_type1, unsigned opr_val1, int opr_type2, unsigned opr_val2,"
                       "int opr_type3, unsigned opr_val3, unsigned curr_addr, std::string &ibin)";
}

std::string csv_to_asmc::get_cmd_func_name(std::string cmd)
{
    return cmd+"_CodeGen";
}

std::string csv_to_asmc::vec_str_to_str(std::vector<std::string> vecs)
{
    std::stringstream istr;
    for(int i=0;i<vecs.size();++i)
    {
        istr<<vecs[i]<<" ";
    }
    return istr.str();
}

std::string csv_to_asmc::trim_quote_if_exist(std::string aa)
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

std::string csv_to_asmc::abs_to_rel_patch_func()
{
    return R"(
            /// 8bit signed data. -128 -> +127
            ///curr_addr=curr_addr+this_inst_len.
            /// curr_addr is the end of the inst addr
            int abs_to_rel(unsigned curr_addr, unsigned &abs_addr)
    {
        unsigned rel1 = 0;
        int is_jmp_err = 0;
        if(abs_addr>curr_addr)
        {
            rel1 = abs_addr - curr_addr;

            if(rel1>127)
            {
                is_jmp_err = 1;
                /**
                cerr<<"relative address jmp not reach error.\n";
                cerr<<"curr_addr+inst="<<std::hex<<curr_addr<<"H\n";
                cerr<<"abs_addr="<<std::hex<<abs_addr<<"H\n";
                cerr<<"jmp length="<<rel1<<"H\n";
                **/
            }
            abs_addr = rel1;
        }
        else if(abs_addr==curr_addr)
        {
            abs_addr = 0;
        }
        else
        {
            ///此处是<0的负数
            int kk = curr_addr-abs_addr;

            if(kk>128)
            {
                is_jmp_err = 1;
                /**
                cerr<<"relative address jmp not reach error.\n";
                cerr<<"curr_addr+inst="<<std::hex<<curr_addr<<"H\n";
                cerr<<"abs_addr="<<std::hex<<abs_addr<<"H\n";
                cerr<<"jmp length="<<kk<<"H\n";**/
            }

            abs_addr = (unsigned)((-kk)&0xff);

        }
        return is_jmp_err;
    }


            )";
}
