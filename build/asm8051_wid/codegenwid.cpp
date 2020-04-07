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

    std::stringstream str_out;
    std::string mspace(indent_space, ' ');

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
            std::string param = cmd_list2[j][1];
            std::string hex_size = cmd_list2[j][3];
            std::string osci_period = cmd_list2[j][4];
            std::string byte0 = cmd_list2[j][6];
            std::string byte1 = cmd_list2[j][7];
            std::string byte2 = cmd_list2[j][8];


            std::vector<std::string> tokens = template_param_parse_str(param);
            std::vector<std::string> tokens_var = template_param_parse_str_var(param);

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
            str_out<<mspace<<"m_hex_text.resize("<<hex_size<<");\r\n";
            str_out<<mspace<<"m_current_line_oscillator_period="<<osci_period<<";\r\n";

            //此处添加注释,无法指令直接生成
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
    str_out<<"{\r\nT_ASM_CONTEXT* mp_ctx = (T_ASM_CONTEXT*)mCtx;\r\n"<<std::endl;
    for(int i=0;i<m_cmd_list.size();++i)
    {
        str_out<<"    mp_ctx->m_line_key_word_ptr[\""+m_cmd_list[i]  <<"\"] = &"<<m_cmd_list[i]<<"_CodeGen;\r\n";
    }
    str_out<<"\r\nreturn 0;\r\n}\r\n"<<std::endl;




#if 0
    std::cout<<str_out.str()<<std::endl;
#else

    std::ofstream m_file_out("../../../asm8051_v2/src/asm_keywords_tmp.cpp");
    std::string to_w = str_out.str();
    m_file_out.write(to_w.c_str(), to_w.size());
    m_file_out.close();
#endif
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





void CodeGenWid::on_actionAsmcsvTOcode_triggered()
{

    std::vector< std::vector<std::string> > m_code_table2;
    std::vector<std::string> m_code_table_header2;

    std::string file_ar_name;

    ///读取文件合并
    file_ar_name= "../../../asm8051_v2/doc/inst_v1_ar.csv";
    csv_dist_load(file_ar_name, m_code_table_header2, m_code_table2);
    file_ar_name = "../../../asm8051_v2/doc/inst_v1_bool.csv";
    csv_dist_load(file_ar_name, m_code_table_header2, m_code_table2);
    file_ar_name = "../../../asm8051_v2/doc/inst_v1_dt.csv";
    csv_dist_load(file_ar_name, m_code_table_header2, m_code_table2);
    file_ar_name = "../../../asm8051_v2/doc/inst_v1_lo.csv";
    csv_dist_load(file_ar_name, m_code_table_header2, m_code_table2);
    file_ar_name = "../../../asm8051_v2/doc/inst_v1_pb.csv";
    csv_dist_load(file_ar_name, m_code_table_header2, m_code_table2);


    //////////////////////////////////////////
    //////////////////////////////////////////
    //保存文件，用于手工修改添加公式
    csv_save(m_code_table_header2, m_code_table2, "../../../asm8051_v2/doc/m2.csv");
    //////////////////////////////////////////
    //////////////////////////////////////////

    ///manually add calc  and copy to m2_add_calc.csv
    m_code_table_header2.clear();
    m_code_table2.clear();
    load_asm_m2_inst_list(m_code_table_header2, m_code_table2, "../../../asm8051_v2/doc/m2_add_calc.csv");


    std::vector<std::string> m_cmd_list;
    /// 添加token的类型字符串，用于生成代码
    asm_inst_add_parse_token(m_code_table_header2, m_code_table2, m_cmd_list);

    ///生成代码
    gen_asm_keywords(m_code_table_header2,m_code_table2,m_cmd_list);

    std::string table1_str  = gen_tableA(m_code_table_header2, m_code_table2, m_cmd_list);
    std::string table2_str = gen_disa_table();

    std::string table12_size_str = "int g_hex_table_size=sizeof(g_hex_table)/sizeof(g_hex_table[0]);\r\nint g_asm_table_size = sizeof(g_asm_table)/sizeof(g_asm_table[0]);\r\n";

    std::ofstream f_out;
    f_out.open("../../../asm8051_v2/src/asm_table_tmp.cpp");
    f_out.write("#include \"asm_table.h\"\r\n", strlen("#include \"asm_table.h\"\r\n"));
    f_out.write(table1_str.c_str(), table1_str.size());
    f_out.write(table2_str.c_str(), table2_str.size());
    f_out.write(table12_size_str.c_str(), table12_size_str.size());
    f_out.close();



}

void CodeGenWid::load_asm_m3_inst_list(std::vector<std::string> &header3, std::vector<std::vector<std::string> > &cmd_list3)
{
    int is_eof  = 0;
    csv_io m_csv;
    m_csv.set_file_name("../../../asm8051_v2/doc/m3.csv");
    m_csv.m_delimiter="|";
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
        cmd_list3[i].resize(4);
        if(cmd_list3[i][0].size()==0)
        {
            continue;
        }


        str_out<<"{0x";
        str_out<<cmd_list3[i][0]<<",";
        str_out<<cmd_list3[i][1]<<",";

        no_quote=0;
        if(cmd_list3[i][2][0]!='"')
        {
            //没有引号
            no_quote=1;
        }
        if(no_quote)
        {
            str_out<<"\"";
        }
        str_out<<cmd_list3[i][2];
        if(no_quote)
        {
            str_out<<"\"";
        }
        str_out<<",";

        no_quote=0;
        if(cmd_list3[i][3][0]!='"')
        {
            //没有引号
            no_quote=1;
        }

        if(no_quote)
        {
            str_out<<"\"";
        }

        str_out<<cmd_list3[i][3];
        if(no_quote)
        {
            str_out<<"\"";
        }

        str_out<<"}";
        if(i!=cmd_list3.size()-1)
        {
            str_out<<",\r\n";
        }
    }

    str_out<<"};\r\n";

    return str_out.str();
}



void CodeGenWid::on_actionDiscsvTocode_triggered()
{

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



