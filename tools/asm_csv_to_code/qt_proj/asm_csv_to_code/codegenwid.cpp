#include "codegenwid.h"
#include "ui_codegenwid.h"
#include "asm8051_lex.h"
#include <iostream>
#include <sstream>
#include <set>
#include <QFileDialog>
#include "csv_io.h"
#include "asm8051_lex.h"
#include "trim.h"
#include "replace.h"
#include "asm8051.h"
#include "dis8051.h"
#include "asm_table.h"
#include "asm_test_code_gen.h"
#include "hex_generator.h"
#include "split.h"
#include "replace.h"
#include "trim.h"
#include "code_gen_param_parse.h"

///针对部分参数是字符串，需要在前面添加引号，如果已经有了，则不再添加
/// 例如如果字符串是MOV 则返回"MOV"
/// 如果字符串是 "MOV" 则返回 "MOV"
std::string quote_if_not(std::string str_to_quote)
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


CodeGenWid::CodeGenWid(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CodeGenWid)
{
    ui->setupUi(this);
}

CodeGenWid::~CodeGenWid()
{
    delete ui;
}



std::string CodeGenWid::generate_calc_code(std::string byte_formual, std::vector<std::string> except_tokens, std::vector<std::string> tokens_var)
{
    //INPUT std::vector<asm_token> &m_tokens
    //OUTPUT return str
    std::string mstr1 = byte_formual;
    for(int i=0;i<except_tokens.size();++i)
    {
        mstr1 = replace(mstr1, "$"+QString::number(i+1).toStdString(), "m_tokens["+ QString::number(i+1).toStdString() +"]."+tokens_var[i]);
    }

    if(mstr1.find("$")!=mstr1.npos)
    {
        int mm = 0;
        std::cout<<"formual error:"<<byte_formual<<std::endl;
    }
    return mstr1;
}


void CodeGenWid::asm_inst_add_parse_token(std::vector<std::string> &header2, std::vector<std::vector<std::string> > &cmd_list2, std::vector<std::string> &token_list)
{
    int old_size = header2.size();
    header2.push_back("PARAM_TOKEN0");
    header2.push_back("PARAM_TOKEN1");
    header2.push_back("PARAM_TOKEN2");
    header2.push_back("PARAM_TOKEN3");

    int new_size = header2.size();

    //csv_save(header2, cmd_list2, "test1.csv");

    std::set<std::string> cmd_key_set;



    for(int i=0;i<cmd_list2.size();++i)
    {
        cmd_key_set.insert(cmd_list2[i][0]);
        std::string param = cmd_list2[i][1];
        std::vector<std::string> tokens = template_param_parse_str(param);

        cmd_list2[i].resize(old_size);
        for(int j=0;j<tokens.size();++j)
        {
            cmd_list2[i].push_back(tokens[j]);
        }
    }


    for(std::set<std::string>::iterator it=cmd_key_set.begin();it!=cmd_key_set.end();++it)
    {
        token_list.push_back(*it);
    }


    //csv_save(header2, cmd_list2, "./inst_table_with_token.csv");

#if 0
    std::set<std::string> token_set;
    for(int i=0;i<cmd_list2.size();++i)
    {
        for(int j=old_size;j<cmd_list2[i].size();++j)
        {
            token_set.insert( cmd_list2[i][j]);
        }
    }

    for(std::set<std::string>::iterator it = token_set.begin();it!=token_set.end();++it)
    {
        token_list.push_back(*it);
    }
    //save_list_to_file(token_list, "./param_token.csv");
#endif
    return;

}

std::string CodeGenWid::gen_tableA(std::vector<std::string> &header2, std::vector<std::vector<std::string> > &cmd_list2, std::vector<std::string> m_cmd_list)
{
    std::stringstream ret_out;


    ret_out<<"asm_to_hex_table g_asm_table[]={\r\n";
    for(int i=0;i<cmd_list2.size();++i)
    {
        cmd_list2[i].resize(13);
        ret_out<<"{";
        ret_out<<"\""<<cmd_list2[i][0]<<"\", ";

        if((cmd_list2[i][1].size()==0)||(cmd_list2[i][1][0]!='"'))
        {
            ret_out<<"\"";
        }
        ret_out<<cmd_list2[i][1];
        if((cmd_list2[i][1].size()==0)||(cmd_list2[i][1][0]!='"'))
        {
            ret_out<<"\"";
        }
        ret_out<<", ";

        ret_out<<"\""<<cmd_list2[i][2]<<"\", ";
        ret_out<<cmd_list2[i][3]<<", ";
        ret_out<<cmd_list2[i][4]<<", ";
        ret_out<<"\""<<cmd_list2[i][5]<<"\", ";//class
        ret_out<<"\""<<cmd_list2[i][6]<<"\", ";//b0
        ret_out<<"\""<<cmd_list2[i][7]<<"\", ";//b1
        ret_out<<"\""<<cmd_list2[i][8]<<"\", ";//b2
        ret_out<<"\""<<cmd_list2[i][9]<<"\", ";//token0
        ret_out<<"\""<<cmd_list2[i][10]<<"\", ";//1
        ret_out<<"\""<<cmd_list2[i][11]<<"\", ";//2
        ret_out<<"\""<<cmd_list2[i][12]<<"\" ";//3


        ret_out<<"}";
        if(i!=cmd_list2.size()-1)
        {
        ret_out<<",";
        }
        ret_out<<"\r\n";
    }

    ret_out<<"\r\n};\r\n";

    return  ret_out.str();
}


std::string CodeGenWid::generate_one_cmd_code(std::vector<std::vector<std::string> > cmd_list2, std::string mcmd, int indent_space)
{
    ///生成1个命令的代码生成代码
    /// 命令为：mcmd

    std::stringstream str_out;
    std::string mspace(indent_space, ' ');
    std::map<std::string, std::string> cmd_parse_token_equal_check;///检查是否有参数相同的函数，如果有，则此处生成的代码无法解析到2个相同的函数


    str_out<<mspace<<"std::vector<asm_token> &m_tokens = mCtx->m_current_block.m_tokens;\r\n";
    str_out<<mspace<<"std::string &m_hex_text = mCtx->m_current_block.m_hex_text;\r\n";
    str_out<<mspace<<"int &m_current_line_oscillator_period = mCtx->m_current_block.m_current_line_oscillator_period;\r\n";


    ////////////////////////////////
    /// 此处生成代码
    ///


    for(int j=0;j<cmd_list2.size();++j)
    {
        if (cmd_list2[j].size()==0)continue;

        if(cmd_list2[j][0]==mcmd)
        {
            ///找到命令
            /// 0--cmd
            std::string param =         cmd_list2[j][1]; //1-param
                                                         //2-comment
            std::string hex_size =      cmd_list2[j][3]; //3-hex_size
            std::string osci_period =   cmd_list2[j][4]; //4-osci period//5-class text
            std::string byte0 =         cmd_list2[j][6]; //6-byte0
            std::string byte1 =         cmd_list2[j][7]; //7-byte1
            std::string byte2 =         cmd_list2[j][8]; //8-byte2
            //std::string cparam0 =       cmd_list2[j][9];
            //std::string cparam1 =       cmd_list2[j][10];
            //std::string cparam2 =       cmd_list2[j][11];



            std::cout<<"mcmd:"<<mcmd<<" generating\n";

            std::vector<std::string> tokens = template_param_parse_str(param);
            std::vector<std::string> tokens_var = template_param_parse_str_var(param);
            std::vector<std::string> tokens_var_range = template_param_parse_str_var_range(param);
            std::vector<int> token_is_8bit_sign = template_param_parse_str_var_range_8bit_sign(param);

            {///for token check
                std::stringstream tkstr;
                tkstr<<tokens.size();
                for(int k=0;k<tokens.size();k++)
                {
                    tkstr<<tokens[k];
                }
                std::string keys = tkstr.str();
                if(cmd_parse_token_equal_check.find(keys)!=cmd_parse_token_equal_check.end())
                {
                    std::cout<<"ERROR: key has already got. "<<cmd_parse_token_equal_check[keys]<< mcmd<<keys<<std::endl;
                }
                cmd_parse_token_equal_check[keys] = mcmd;
            }

            str_out<<mspace<<"if(m_tokens.size()=="<<tokens.size()+1<<")\r\n";
            str_out<<mspace<<"{\r\n";

            str_out<<mspace<<"if( ";
            if(tokens.size()==0)
            {
                str_out<<"1";
            }
            for(int k=0;k<tokens.size();k++)
            {
                str_out<<mspace<<"(m_tokens["<<k+1<<"].type=="<<tokens[k]<<")";
                if(k!=tokens.size()-1)
                {
                    str_out<<"&&\r\n";
                }
            }
            str_out<<" )\r\n";
            str_out<<mspace<<"{\r\n";


            str_out<<mspace<<"//set hex size & inst-circle\r\n";
            str_out<<mspace<<"m_hex_text.resize("<<hex_size<<");\r\n";
            str_out<<mspace<<"m_current_line_oscillator_period="<<osci_period<<";\r\n";


            //此处添加注释,指令生成
            /////////////////////////
            str_out<<mspace<<"//OUTPUT:m_hex_text\r\n";
            str_out<<mspace<<"//INPUT:m_tokens\r\n";

            str_out<<mspace<<"m_hex_text[0]=";
            str_out<<generate_calc_code(byte0, tokens, tokens_var)<<";\r\n";
            if (atoi(hex_size.c_str())>1)
            {
                str_out<<mspace<<"m_hex_text[1]=";
                str_out<<generate_calc_code(byte1, tokens, tokens_var)<<";\r\n";
            }
            if(atoi(hex_size.c_str())>2)
            {
                str_out<<mspace<<"m_hex_text[2]=";
                str_out<<generate_calc_code(byte2, tokens, tokens_var)<<";\r\n";
            }


            //参数范围检查，如果范围检查不通过，则返回2
            str_out<<mspace<<"//oprand range check\r\n";
            for(unsigned ick=0;ick<tokens_var_range.size();++ick)
            {
                if(tokens_var_range[ick].size()==0)
                {
                    str_out<<mspace<<"//"<< ick<<"--check ignore\n";
                }
                else
                {
                    str_out<<mspace<<"//"<< ick<<"--check\n";



                    //目标比较数值
                    str_out<<mspace<<"unsigned int tcmp"<<ick<<"="<<" m_tokens["+ QString::number(ick+1).toStdString() +"]."+tokens_var[ick]<<";\n";

                    //正数比较数值
                    str_out<<mspace<<"unsigned int cmp"<<ick << "0="<< tokens_var_range[ick] <<"& m_tokens["+ QString::number(ick+1).toStdString() +"]."+tokens_var[ick]<<";\n";

                    //负数比较数值
                    str_out<<mspace<<"unsigned int cmp"<<ick<<"1="<< tokens_var_range[ick]<<";\n";
                    str_out<<mspace<<"cmp"<<ick<<"1=~cmp"<<ick<<"1;\n";
                    str_out<<mspace<<"cmp"<<ick<<"1=cmp"<<ick<<"1|cmp"<<ick<<"0;\n";

                    //最高位
                    str_out<<mspace<<"unsigned int cmp"<<ick<<"2=("<< tokens_var_range[ick]  <<"^("<< tokens_var_range[ick]<<">>1)) & cmp"<< ick<<"0  ;\n";


                    if(token_is_8bit_sign[ick])
                    {
                        //有符号的8bit数据
                        str_out<<mspace<<"// 8bit sign check\n";
                        str_out<<mspace<<" if ( ("<<" m_tokens["+ QString::number(ick+1).toStdString() +"]."+tokens_var[ick] <<">0)&&("<< "cmp" <<ick<<"2"<<   ")){return 2;}\n" ;

                    }


                    str_out<<mspace<< "if( "<<" (tcmp"<<ick<<"!=cmp"<<ick<<"0)"<<
                                                "&&(!(cmp" <<ick<<"2&&("<<  "tcmp"<<ick<<"==cmp"<<ick<<"1)))"
                                       <<"){ return 2; }\n";
                }
            }



            str_out<<mspace<<"return 0;\r\n";

            /////////////////////////

            str_out<<mspace<<"}\r\n";//if
            str_out<<mspace<<"}\r\n";//if

            str_out<<mspace<<"\r\n";
        }
    }


    return str_out.str();

    ////////////////////////////////
}

std::string CodeGenWid::get_cmd_comment(std::vector<std::string> header2, std::vector<std::vector<std::string> > cmd_list2, std::string mcmd, int indent_space)
{

    std::string mspace(indent_space, ' ');
    std::stringstream str_out;
    ////////////////////////////////
    str_out<<mspace<<"//";
    for(int j=0;j<header2.size();j++)
    {
        str_out<<header2[j]<<"|\t";
    }
    str_out<<mspace<<"\r\n";

    for(int j=0;j<cmd_list2.size();++j)
    {
        if (cmd_list2[j].size()==0)continue;
        if(cmd_list2[j][0]==mcmd)
        {
            str_out<<mspace<<"//";
            for(int k=0;k<cmd_list2[j].size();++k)
            {
                str_out<<cmd_list2[j][k]<<"|\t";
            }
            str_out<<"\r\n";
        }
    }
    ////////////////////////////////

    return str_out.str();

}

void CodeGenWid::gen_asm_keywords(std::vector<std::string> &header2, std::vector<std::vector<std::string> > &cmd_list2, std::vector<std::string> m_cmd_list)
{

    std::stringstream str_out;

    str_out<<"#include \"asm_keywords.h\"\r\n#include \"asm_context.h\"\r\n\r\n";

    for(int i=0;i<m_cmd_list.size();++i)
    {
        str_out<<"int "<<m_cmd_list[i]<<"_CodeGen(T_ASM_CONTEXT *mCtx)\r\n{\r\n";
        str_out<<get_cmd_comment(header2, cmd_list2, m_cmd_list[i], 4);

        str_out<<generate_one_cmd_code(cmd_list2, m_cmd_list[i], 4)<<"\r\n";


        str_out<<"//unknown code\r\n";
        str_out<<"return -1;\r\n";
        str_out<<"}\r\n";///codegen function end
    }




    //function asm_install
    str_out<<"int asm8051_context_init(void *mCtx)"<<std::endl;
    str_out<<"{\r\n";
    str_out<<"// inst codegen func count:"<<m_cmd_list.size()<<"\r\n";
    str_out<<"T_ASM_CONTEXT* mp_ctx = (T_ASM_CONTEXT*)mCtx;\r\n"<<std::endl;
    for(int i=0;i<m_cmd_list.size();++i)
    {
        str_out<<"    mp_ctx->m_line_key_word_ptr[\""+m_cmd_list[i]  <<"\"] = &"<<m_cmd_list[i]<<"_CodeGen;\r\n";
    }
    str_out<<"\r\nreturn 0;\r\n}\r\n"<<std::endl;


    std::ofstream m_file_out("../../src/asm8051/src/asm_keywords_tmp.cpp");
    std::string to_w = str_out.str();
    m_file_out.write(to_w.c_str(), to_w.size());
    m_file_out.close();

}

void CodeGenWid::csv_dist_load(std::string file_ar_name, std::vector<std::string> &m_code_table_header2, std::vector< std::vector<std::string> > &m_code_table2)
{
    csv_io m_csv;
    int is_eof=0;

    m_csv.set_file_name(file_ar_name);
    m_csv.open_file();
    //ignore header
    std::vector<std::string> line_data = m_csv.parse_next_line(&is_eof);
    std::string mclass = line_data[0];
    m_code_table_header2.clear();
    m_code_table_header2.push_back("Mnemonic");
    m_code_table_header2.push_back("Operands");
    m_code_table_header2.push_back("Description");
    m_code_table_header2.push_back("Byte");
    m_code_table_header2.push_back("Oscillator Period");
    m_code_table_header2.push_back("Class");

    m_csv.parse_next_line(&is_eof);
    while(is_eof==0)
    {
        line_data =  m_csv.parse_next_line(&is_eof);
        if(line_data.size()<4)
        {
            for(int i=0;i<line_data.size();++i)
            {
               std::cout<<line_data[i]<<std::endl;
            }
            std::cout<<"empty line"<<std::endl;
            continue;
        }
        line_data.resize(5);
        line_data.push_back(mclass);//Class
        m_code_table2.push_back(line_data);
     }

     std::cout<<"inst size:"<<m_code_table2.size()<<std::endl;
}


void CodeGenWid::load_asm_m2_inst_list(std::vector<std::string> &header2, std::vector<std::vector<std::string> > &cmd_list2, std::string file_name)
{
    //

    int is_eof  = 0;
    int line_cnt = 0;
    csv_io m_csv;
    m_csv.set_file_name(file_name);
    m_csv.open_file();
    header2 = m_csv.parse_next_line(&is_eof);
    line_cnt++;

    std::cout<<header2[0]<<std::endl;
    while(is_eof==0)
    {
        std::vector<std::string> one_line = m_csv.parse_next_line(&is_eof);
        line_cnt++;
        if(one_line.size()==0)
        {
            std::cout<<"empty line:"<<line_cnt<<std::endl;
            continue;
        }
        cmd_list2.push_back(one_line);
        //std::cout<<one_line[0]<<std::endl;
    }
    m_csv.close_file();


    ///此处调试打印加载的文件

    std::cout<<"load_asm_m2_inst_list debug:\n";
    for(int i=0;i<header2.size();++i)
    {
        std::cout<<header2[i]<<"|";
    }
    std::cout<<"\n";
    for(int i=0;i<cmd_list2.size();++i)
    {
        std::cout<<cmd_list2[i].size()<<",";
        for(int j=0;j<cmd_list2[i].size();++j)
        {
            std::cout<<cmd_list2[i][j]<<"|";
        }
        std::cout<<"\n";
    }
}



void CodeGenWid::csv_save(std::vector<std::string> &header2, std::vector<std::vector<std::string> > &cmd_list2, std::string file_name)
{

    std::ofstream f_out;
    f_out.open(file_name.c_str());
    ///write data to csv
    ///
    for(int i=0;i<header2.size();++i)
    {
      f_out<<header2[i]<<"|";
    }
    f_out<<std::endl;


    for(int i=0;i<cmd_list2.size();++i)
    {
      for(int j=0;j<cmd_list2[i].size();j++)
      {
        f_out<<cmd_list2[i][j]<<"|";
      }
        f_out<<std::endl;
    }
    f_out.close();
}


#if 0
std::string diss_dis_one_inst_default(std::string mhex, hex_code_asm_table &inst_info)
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
#endif

std::string CodeGenWid::gen_dis_keywords(std::vector<std::string> &header3, std::vector<std::vector<std::string> > &cmd_list3)
{
    std::stringstream mstr1;

    for(int i=0;i<cmd_list3.size();++i)
    {
        cmd_list3[i].resize(8);
        if(cmd_list3[i][0].size()==0)
        {
            continue;
        }

        ///生成函数
        ///
        ///
        ///
        mstr1<<"std::string AA_"<<cmd_list3[i][0]<<"H(dis8051* dis, std::string mbin, unsigned curr_addr)\r\n{\r\n";
        mstr1<<"//" ;
        for(int j=0;j<8;++j)
        {
            mstr1<<cmd_list3[i][j]<<"|\t";
        }
        mstr1<<"\r\n" ;

        mstr1<<"std::stringstream mout;\r\n";
        mstr1<<"mout<<"<<quote_if_not( cmd_list3[i][2])<<"<<\" \""<<";\r\n";


        if (cmd_list3[i][4]!="-1")
        {
            ///此处对参数进行整理切分
            std::vector<std::string> params = split(cmd_list3[i][3],",");
            std::map<std::string, std::string> to_inst;
            //to_inst["code addr"]="dis->REL_CODE_ADDR_DIS";
            //2020.6.4 code addr 不知道是相对地址还是绝对地址。所以拆分为2种类型：
            /// abs rel .如果rel有8bit，有11bit，有16bit的，则可以再拆分为 rel code addr8, rel code addr11, rel code addr16
            to_inst["abs code addr"]="dis->ABS_CODE_ADDR_DIS";
            to_inst["rel code addr"]="dis->REL_CODE_ADDR_DIS";
            to_inst["data addr"]="dis->DATA_ADDR_DIS";
            to_inst["bit addr"]="dis->BIT_ADDR_DIS";
            to_inst["#data"]="dis->DATA_VALUE_DIS";
            to_inst["/bit addr"]="dis->MBIT_ADDR_DIS";

            ///patch for "A, B" --> "A B" after the split
            ///
            if(params.size()>1)
            {
                if(params[0].size()>0)
                {
                    if(params[0][0]=='\"')
                    {
                        params[0] = params[0].substr(1);
                    }
                }
                if(params[params.size()-1].size()>0)
                {
                    if(params[params.size()-1][params[params.size()-1].size()-1]=='\"')
                    {
                        params[params.size()-1] = params[params.size()-1].substr(0, params[params.size()-1].size()-1);
                    }
                }
            }


            for(int j=0;j<atoi(cmd_list3[i][4].c_str());++j)
            {
                ///每一个参数进行计算
                if(cmd_list3[i][5+j].size()==0)
                {
                    ///参数为字符串，直接从params中获取
                    mstr1<<"mout<<"<<quote_if_not(params[j])<<";\r\n";
                }
                else
                {
                    ///如果参数数公式，则是数值
                    std::string tmp = cmd_list3[i][5+j];
                    mstr1<<"unsigned val"<<j<<"="<<replace(replace(replace(tmp,"$0","mbin[0]"), "$1",  "mbin[1]"),"$2", "mbin[2]")   <<";\r\n";
                    mstr1<<"mout<<"<<to_inst[trim(params[j])]<<"(val" <<j<<", curr_addr, " << cmd_list3[i][1]<<");\r\n";
                    if (to_inst.find(trim(params[j]))==to_inst.end())
                    {
                        int mm = 0;
                        std::cout<<"find param warning: "<<trim(params[j])<<std::endl;
                    }
                }

                if(j!=atoi(cmd_list3[i][4].c_str())-1)
                {
                    mstr1<<"mout<<\", \"; \r\n";
                }
                else
                {
                    mstr1<<"mout<<\";\"; \r\n";
                }

            }



        }
        else
        {
            mstr1<<"mout<<"<<quote_if_not(cmd_list3[i][3])<<"<<\";\";\r\n";
        }
        mstr1<<"return mout.str();\r\n";


        mstr1<<"}\r\n";
    }


    /// 生成总函数
    mstr1<<"int load_dis_keywords(std::map<unsigned, DIS_FUNC_PTR> &keys)\r\n{\r\n";
    for(int i=0;i<cmd_list3.size();++i)
    {
        if(cmd_list3[i][0].size()==0)
        {
            continue;
        }
        mstr1<<"keys[0x"<<cmd_list3[i][0]<<"]="<<"&AA_"<<cmd_list3[i][0]  <<"H;\r\n";
    }
    mstr1<<"return 0;\r\n}\r\n";


    return mstr1.str();
}





void CodeGenWid::on_actionAsmcsvTOcode_triggered()
{

    std::vector< std::vector<std::string> > m_code_table2;
    std::vector<std::string> m_code_table_header2;

    std::string file_ar_name;

    ///读取文件合并
    file_ar_name= "../../src/asm8051/doc/inst_v1_ar.csv";
    csv_dist_load(file_ar_name, m_code_table_header2, m_code_table2);
    file_ar_name = "../../src/asm8051/doc/inst_v1_bool.csv";
    csv_dist_load(file_ar_name, m_code_table_header2, m_code_table2);
    file_ar_name = "../../src/asm8051/doc/inst_v1_dt.csv";
    csv_dist_load(file_ar_name, m_code_table_header2, m_code_table2);
    file_ar_name = "../../src/asm8051/doc/inst_v1_lo.csv";
    csv_dist_load(file_ar_name, m_code_table_header2, m_code_table2);
    file_ar_name = "../../src/asm8051/doc/inst_v1_pb.csv";
    csv_dist_load(file_ar_name, m_code_table_header2, m_code_table2);


    //////////////////////////////////////////
    /// 读取信息显示
    ///
    //////////////////////////////////////////

    std::cout<<m_code_table_header2.size()<<std::endl;
    std::cout<<m_code_table2.size()<<std::endl;

    //////////////////////////////////////////
    //////////////////////////////////////////
    //////////////////////////////////////////

    //////////////////////////////////////////
    //////////////////////////////////////////
    //保存文件，用于手工修改添加公式
    csv_save(m_code_table_header2, m_code_table2, "../../src/asm8051/doc/m2.csv");
    //////////////////////////////////////////
    //////////////////////////////////////////

    ///manually add calc  and copy to m2_add_calc.csv
    m_code_table_header2.clear();
    m_code_table2.clear();
    load_asm_m2_inst_list(m_code_table_header2, m_code_table2, "../../src/asm8051/doc/m2_add_calc.csv");


    std::vector<std::string> m_cmd_list;
    /// 添加token的类型字符串，用于生成代码
    asm_inst_add_parse_token(m_code_table_header2, m_code_table2, m_cmd_list);

    ///生成代码
    gen_asm_keywords(m_code_table_header2,m_code_table2,m_cmd_list);

    /// 生成asm_table 列表。
    std::string table1_str  = gen_tableA(m_code_table_header2, m_code_table2, m_cmd_list);
    std::string table2_str = gen_disa_table();

    std::string table12_size_str = "int g_hex_table_size=sizeof(g_hex_table)/sizeof(g_hex_table[0]);\r\nint g_asm_table_size = sizeof(g_asm_table)/sizeof(g_asm_table[0]);\r\n";

    std::ofstream f_out;
    f_out.open("../../src/asm8051/src/asm_table_tmp.cpp");
    f_out.write("#include \"asm_table.h\"\r\n", strlen("#include \"asm_table.h\"\r\n"));
    f_out.write(table1_str.c_str(), table1_str.size());
    f_out.write(table2_str.c_str(), table2_str.size());
    f_out.write(table12_size_str.c_str(), table12_size_str.size());
    f_out.close();



    ///==============
    /// 此处生成dis_keywords.cpp
    //std::ofstream f_out;
    f_out.open("../../src/asm8051/src/dis_keywords_tmp.cpp");
    char dis_k_includes[] = "#include \"dis_keywords.h\"\r\n#include <string>\r\n#include <sstream>\r\n#include \"dis8051.h\"\r\n";
    f_out.write(dis_k_includes, strlen(dis_k_includes));
    std::vector<std::string> header3;
    std::vector<std::vector<std::string> > cmd_list3;
    /////////////////////
    load_asm_m3_inst_list(header3, cmd_list3);
    std::string strdis1= gen_dis_keywords(header3, cmd_list3);
    f_out.write(strdis1.c_str(), strdis1.size());
    f_out.close();


}

void CodeGenWid::load_asm_m3_inst_list(std::vector<std::string> &header3, std::vector<std::vector<std::string> > &cmd_list3)
{
    int is_eof  = 0;
    csv_io m_csv;
    m_csv.set_file_name("../../src/asm8051/doc/m3.csv");
    m_csv.m_delimiter=",";
    m_csv.open_file();
    header3 = m_csv.parse_next_line(&is_eof);


    std::cout<<header3[0]<<std::endl;
    while(is_eof==0)
    {
        std::vector<std::string> one_line = m_csv.parse_next_line(&is_eof);
        cmd_list3.push_back(one_line);
    }
    m_csv.close_file();
}




std::string CodeGenWid::gen_disa_table()
{

    std::vector<std::string> header3;
    std::vector<std::vector<std::string> > cmd_list3;
    /////////////////////
    load_asm_m3_inst_list(header3, cmd_list3);

    std::stringstream str_out;

    str_out<<"hex_code_asm_table g_hex_table[]={\r\n";

    for(int i=0;i<cmd_list3.size();++i)
    {
        int no_quote=0;
        cmd_list3[i].resize(8);
        if(cmd_list3[i][0].size()==0)
        {
            continue;
        }


        // 指令号，指令字节数
        str_out<<"{0x";
        str_out<<cmd_list3[i][0]<<",";
        str_out<<cmd_list3[i][1]<<",";

        /// 指令名称
        str_out<<quote_if_not(cmd_list3[i][2]);
        str_out<<",";

        /// 指令参数注释

        str_out<<quote_if_not(cmd_list3[i][3]);
        str_out<<",";

        ///指令参数个数
        str_out<<cmd_list3[i][4]<<",";

        ///指令参数0
        str_out<<quote_if_not(cmd_list3[i][5])<<",";
        str_out<<quote_if_not(cmd_list3[i][6])<<",";
        str_out<<quote_if_not(cmd_list3[i][7]);

        str_out<<"}";
        if(i!=cmd_list3.size()-1)
        {
            str_out<<",\r\n";
        }
    }

    str_out<<"};\r\n";

    return str_out.str();
}

void CodeGenWid::on_actionOpenHex_triggered()
{
    QString file_name = QFileDialog::getOpenFileName();
    if(file_name.size()==0)
    {
        return ;
    }

    std::ifstream f_in;
    f_in.open(file_name.toStdString().c_str());
    std::string one_line;
    std::string file_all;
    while(std::getline(f_in, one_line))
    {
        file_all += one_line+"\n";
    }
    f_in.close();



    std::vector<hex_block> hex_data = hex_file_to_hex_data(file_all);
    std::string hex_file_out = hex_data_to_hex_file(hex_data);

    std::ofstream f_out;
    f_out.open((file_name.toStdString()+"_out.hex").c_str());
    f_out.write(hex_file_out.c_str(), hex_file_out.size());
    f_out.close();
}



