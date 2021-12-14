/// 2020.12.22 添加debug参数
/// 2020.12.16 添加 left right 的读写
/// 添加命名空间的支持
///


#include <fstream>
#include <iostream>
#include <algorithm>    // transform
#include <sstream>
#include <map>
#include <assert.h>
#include "bison_file_io.h"
#include "split.h"
#include "replace.h"
#include "yy_file_template.h"

///
/// \brief bison_file_io::bison_file_io
/// 读取bison文件，并生成带代码的bison文件
bison_file_io::bison_file_io()
{
    m_debug = 0;
    m_namespace = "example";
}



int bison_file_io::add_one_rule(std::string new_rule_name)
{
    std::vector< std::vector<std::string> > reta;
    std::vector<std::string> orule;
    orule.push_back(new_rule_name);
    reta.push_back(orule);
    m_rules.push_back(reta);
    return 0;
}

int bison_file_io::add_one_rule_line(std::string rule_name, std::vector<std::string> rule_str_list)
{


    std::vector<std::string> oline;
    oline.insert(oline.end(), rule_str_list.begin()+1, rule_str_list.end());
    if(m_debug)
    {
        std::cout<<"append one rule line:";
        for(unsigned i=0;i<oline.size();++i)
        {
            std::cout<< oline[i]<<",";
        }
        std::cout<<std::endl;
    }
    std::vector< std::vector<std::string > > &orule = m_rules[m_rules.size()-1];
    orule.push_back(oline);
    return 0;
}


int bison_file_io::read(std::string file_name)
{
    std::ifstream fin;
    fin.open(file_name.c_str());

    read_stream(fin);

    fin.close();
    return 0;
}

int bison_file_io::read_str(std::string file_content)
{
    std::stringstream istr(file_content);
    return read_stream(istr);

}

int bison_file_io::read_stream(std::istream &fin)
{

    int bnf_start=0;

    m_rules.clear();
    m_tokens.clear();


    int line_cnt = 0;
    std::string oneline;
    while(std::getline(fin, oneline))
    {
        line_cnt++;
        replace(oneline, "\t", " ");
        replace(oneline, "\r", " ");
        replace(oneline, "\n", " ");
        if(m_debug){std::cout<<"get line:"<<oneline<<std::endl;}

        std::vector<std::string> ret1 = split(oneline, " ", 1);


        if((ret1.size()>0)&&(ret1[0].size()>1))
        {
            ///添加多行注释的支持：只有从行开始就是注释才支持
            if((ret1[0][0]=='/')&&
                    (ret1[0][1]=='*'))
            {
                std::stringstream comments;


                //多行注释
                int find_end_flag = 0;

                while(!find_end_flag)
                {
                    for(int i=0;i<ret1.size();++i)
                    {
                        comments<<ret1[i]<<" ";

                        if(ret1[i].size()<2)
                        {
                            continue;
                        }
                        for(int j=0;j<ret1[i].size()-1;++j)
                        {
                            if((ret1[i][j]=='*')&&(ret1[i][j+1]=='/'))
                            {
                                //找到结束符
                                find_end_flag = 1;
                                ret1.erase(ret1.begin(), ret1.begin()+i+1);
                                break;
                            }
                        }
                        if(find_end_flag)break;
                    }
                    if(find_end_flag)break;
                    std::getline(fin, oneline);
                    line_cnt++;
                    replace(oneline, "\t", " ");
                    if(m_debug){std::cout<<"get comment line:"<<oneline<<std::endl;}

                    ret1 = split(oneline, " ", 1);
                }
                comments_parse(comments.str());
                comments.clear();
                comments.str("");



            }
        }


#if 1
        for(unsigned i=0;i<ret1.size();++i)
        {
            if(ret1[i]=="/*")
            {
                ///如果有注释，则注释后到整行行尾擦掉
                /// FIXME: 此处默认注释只能是单独行
                ret1.erase(ret1.begin()+i, ret1.end());
                break;
            }
        }
#endif

        if(ret1.size()==0)continue;


        if(ret1[0]=="%token")
        {
            for(unsigned i=1;i<ret1.size();++i)
            {
                if(ret1[i].size()==2)
                {
                    //token后面有注释，直接去除
                    if(ret1[i]=="/*")break;
                }
                if(ret1[i]=="END")
                {
                    ///FIXME
                    /// 因为没法解析token带数字的语法：
                    /// %token END 0 "end of file"
                    /// 所以，END直接略过。在token最后，都添加一个%token END 0 来暂时解决这个问题
                    /// 只支持END用数字定义
                    /// 只支持END单独一行
                    break;
                }
                m_tokens.push_back(ret1[i]);
            }
        }
        else if(ret1[0]=="%left")
        {
            for(unsigned i=1;i<ret1.size();++i)
            {
                m_left.push_back(ret1[i]);
            }
        }
        else if(ret1[0]=="%right")
        {
            for(unsigned i=1;i<ret1.size();++i)
            {
                m_right.push_back(ret1[i]);
            }
        }
        else if(ret1[0]=="%type")
        {
            for(unsigned i=1;i<ret1.size();++i)
            {
                m_types.push_back(ret1[i]);
            }
        }
        else if(ret1[0]=="%start")
        {
            m_start = ret1[1];
            continue;
        }
        else if(ret1[0]=="%%")
        {
            bnf_start++;
            continue;
        }
        else if((ret1[0]==":")||(ret1[0]=="|"))
        {
            add_one_rule_line("", ret1);
            continue;
        }
        else if(ret1[0]==";")
        {
            continue;
        }
        else
        {
            if(bnf_start==1)
            {

                if((ret1[0].size()>1)&&(ret1[0][ret1[0].size()-1]==':'))
                {
                    /// 规则名称和冒号 连接 了。
                    ///
                    ret1[0] = ret1[0].substr(0, ret1[0].size()-1);
                    ret1.insert(ret1.begin()+1,std::string(":"));
                }

                ///
                /// 2种情况： const:
                ///        或者 const: INTEGER
                /// 第一种情况，只需要添加规则名ret1[0]
                /// 第二种情况，添加规则，并添加一行的规则
                add_one_rule(ret1[0]);
                if( ret1.size()>1)
                {
                    assert((ret1[1]==":")||(ret1[1]=="|"));
                    ret1.erase(ret1.begin());
                    add_one_rule_line(ret1[0], ret1);
                }
            }
        }
    }

    return 0;
}


int bison_file_io::line_num_to_int(int rule_num, int line_num)
{
    return rule_num*256+line_num;
}

std::string bison_file_io::line_num_to_str(int rule_num, int line_num)
{
    std::string rule_name = this->m_rules[rule_num][0][0];
    std::transform(rule_name.begin(), rule_name.end(), rule_name.begin(), ::toupper);

    //ICODE AST NUMBER
    std::stringstream ret1;
    ret1<<"IAN_"<<rule_name<<"_"<<line_num;

    return ret1.str();
}

void bison_file_io::comments_parse(std::string comments)
{
    ///解析下面类型的注释：
    /* :SEP:start: */
    /// 生成对应的变量m_func_sep_filename m_func_sep_file_rule_start
    ///




    std::vector<std::string> sp2 = split(comments, " ", 1);

    for(int i=0;i<sp2.size();++i)
    {
        std::vector<std::string> sep_id = split(sp2[i], ":");
        if((sep_id.size()==4)&&
                (sep_id[0].size()==0)&&
                (sep_id[3].size()==0)&&
                (sep_id[1]=="SEP")&&
                (sep_id[2].size()>0)
                )
        {
            m_func_sep_filename.push_back(sep_id[2]);
            m_func_sep_file_rule_start.push_back(m_rules.size());
        }
    }


}

int bison_file_io::add_y_code_one_line(std::ofstream &fout, std::vector<std::string > &one_line_rule, int rule_num, int line_num)
{
    fout<<"\t{";
    if(one_line_rule.size()==1)
    {
        fout<<"\n\t\t$$=$1; \n";
        //fout<<"$$.m_tk_type.push_back("<<"\""<<this->m_rules[rule_num][0][0]<<"\""<<");\n";
        fout<<"\t\t$$.m_tk_type_int_list.push_back("<<line_num_to_str(rule_num,line_num)<<");\n";
    }
    else
    {
        fout<<"\n\t\t$$=gempty_token();\n";
        fout<<"\t\t$$.m_type=TOKEN_DEFS_TYPE_AST;\n";
        fout<<"\t\t$$.m_tk_type_int = "<<line_num_to_str(rule_num,line_num)<<";\n";
        fout<<"\t\t$$.m_tk_type_int_list.push_back("<<line_num_to_str(rule_num,line_num)<<");\n";
        //fout<<"\t\t$$.m_tk_type.push_back("<<"\""<<this->m_rules[rule_num][0][0]<<"\""<<");"<<"\n";
        for(unsigned i=0;i<one_line_rule.size();++i)
        {
            fout<<"\t\t"<<"$$.m_tk_elems.push_back(parser_ntoken($"<<i+1<<"));\n";
        }
    }
    ///如果是start标记，则调用系统context函数
    /// driver.calc.
    if(m_rules[rule_num][0][0]==m_start)
    {
        fout<<"\t\t"<<"driver.calc.parse_start_token($$);\n";
    }
    fout<<"\t\t}";



    return 0;
}

int bison_file_io::out_one_rule_line(std::ofstream &fout, std::vector<std::string > &one_line_rule, int rule_num, int line_num, int add_code)
{
    if(line_num==0)
    {
        //0行是规则名称
        fout<<one_line_rule[0]<<"\n";
        return 0;
    }
    else if(line_num==1)
    {   ///1行是第一个规则，使用:
        fout<<"\t: ";
    }
    else
    {
        fout<<"\t| ";
    }

    for(unsigned k=0;k<one_line_rule.size();++k)
    {
        fout<<" "<<one_line_rule[k]<<" ";
    }
    if(add_code)
    {
        add_y_code_one_line(fout, one_line_rule, rule_num, line_num);
    }

    fout<<"\n";

    return 0;
}



int bison_file_io::out_y(std::string file_name, int with_code)
{
    std::ofstream fout;
    fout.open(file_name.c_str());

    yy_file_template m_temp;

    if(with_code)
    {
        fout<< m_temp.get_fist_part(m_namespace, "Parser")<<"\n";
    }


    for(unsigned i=0;i<m_tokens.size();++i)
    {
        if((i%5==0)&&(i!=m_tokens.size()-1))
        {
            fout<<"\n%token ";
        }
        fout<<" "<<m_tokens[i]<<" ";
    }
    fout<<"\n%token END 0 \"end of file\"\n";
    fout<<"\n";


    for(unsigned i=0;i<m_left.size();++i)
    {
        if((i%5==0)&&(i!=m_left.size()-1))
        {
            fout<<"\n%left ";
        }
        fout<<" "<<m_left[i]<<" ";
    }
    fout<<"\n";



    for(unsigned i=0;i<m_right.size();++i)
    {
        if((i%5==0)&&(i!=m_right.size()-1))
        {
            fout<<"\n%right ";
        }
        fout<<" "<<m_right[i]<<" ";
    }
    fout<<"\n";

    for(unsigned i=0;i<m_types.size();++i)
    {
        if((i%5==0)&&(i!=m_types.size()-1))
        {
            fout<<"\n%type ";
        }
        fout<<" "<<m_types[i]<<" ";
    }
    fout<<"\n";




    fout<<"%start "<<m_start<<"\n";
    //fout<<"%%\n";
    if(with_code)
    {
        fout<< m_temp.get_second_part()<<"\n";
    }


    for( unsigned i=0;i<m_rules.size();++i)
    {
        std::vector< std::vector<std::string > >  &orule = m_rules[i];
        for(unsigned j=0;j<orule.size();++j)
        {
            out_one_rule_line(fout, orule[j], i, j, with_code);
        }
        fout<<"\t;\n";
    }

    if(with_code)
    {
        //fout<<"%%\n";
        fout<< m_temp.get_third_part(m_namespace, "Parser")<<"\n";
    }

    fout.close();

    return 0;
}



int bison_file_io::out_ast_to_icode_elem(std::ofstream &fout)
{
    int case_cnt=0;

    fout<<"icode * comp_context::ast_to_icode_elem(token_defs* tdefs, bool need_result_icode, icode *result_ic)\n{\n";
    //fout<<"icode *a = new_icode();\n a->m_type=ICODE_TYPE_BLOCK;\n";
    fout<<"switch(tdefs->m_token_type)\n";
    fout<<"{\n";
    for(unsigned i=0;i<this->m_tokens.size();++i)
    {
        case_cnt++;
        fout<<"case Parser::token::"<<m_tokens[i]<<":\n";
        fout<<"{\n";
        //fout<<"assert(0);/* not supported here*/\n";
        fout<<" icode *a= func_token_"<<m_tokens[i]<<"(this, tdefs, need_result_icode, result_ic);\n";
        fout<<"return a;\n";
        fout<<"}\nbreak;\n";
    }
    fout<<"\n}"<<"//switch end. case_cnt="<<case_cnt<<"\n";
    fout<<"assert(0);\n";
    fout<<"return NULL;//this is just for compiler waning. should never be here \n";
    fout<<"\n}\n";

    return 0;
}

int bison_file_io::out_ast_to_icode_ast(std::ofstream &fout)
{
    int case_cnt=0;
    fout<<"icode * comp_context::ast_to_icode_ast(token_defs* tdefs, bool need_result_icode, icode *result_ic)\n{\n";

    fout<<"int top_type=tdefs->m_tk_type_int;\n";
    fout<<"if(tdefs->m_tk_type_int_list.size()>0)\n{\n";
    fout<<"\ttop_type=tdefs->m_tk_type_int_list[tdefs->m_tk_type_int_list.size()-1];\n";
    fout<<"tdefs->m_tk_type_int_list.pop_back();\n";
    fout<<"\n}\n";


    fout<<"switch(top_type)\n";
    fout<<"{\n";

    for(unsigned i=0;i<this->m_rules.size();++i)
    {
        std::vector< std::vector<std::string > > &orule = this->m_rules[i];
        for(unsigned j=1;j<orule.size();++j)
        {
            std::vector<std::string > &one_line_rule = orule[j];
            if(one_line_rule.size()<1)
            {
                continue;
             }
            case_cnt++;
            fout<<"case "<<line_num_to_str(i,j)<<": "<<"//0x"  <<std::hex<< line_num_to_int(i, j) <<"-"<< orule[0][0]<<"->";
            for(unsigned k=0;k<one_line_rule.size();++k)
            {
                fout<<one_line_rule[k]<<" ";
            }
            fout<<"\n";

            fout<<"{\n";
            //fout<<"assert(0);/* not supported here*/\n";

            fout<<"\ticode *a= func_"<<line_num_to_str(i,j)<<"(this, tdefs, need_result_icode, result_ic);\n";
            fout<<"\treturn a;\n";

            fout<<"}\nbreak;\n";
        }
    }
    fout<<"\n}"<<"//switch end. case_cnt="<<case_cnt<<"\n";
    fout<<"assert(0);\n";
    fout<<"return NULL;//this is just for compiler waning. should never be here \n";
    fout<<"\n}\n";

    return 0;
}

int bison_file_io::out_ast_to_icode(std::string file_name)
{
    std::ofstream fout;
    fout.open(file_name.c_str());

    fout<<"#include <assert.h>\n";
    fout<<"#include \"comp_context.h\"\n";
    fout<<"#include \"parser.h\"\n";
    fout<<"#include \"token_defs.h\"\n";
    fout<<"#include \"icode.h\"\n";
    fout<<"#include \"str2number.h\"\n";
    fout<<"#include \"comp_context_gen_defs.h\"\n";
    fout<<"#include \"mylog.h\"\n";
    fout<<"#include \"replace.h\"\n";

    fout<<"using mylog::cerr;\n";
    fout<<"using mylog::cout;\n";


    if(m_namespace.size()>0)
    {
        fout<<"namespace "<<m_namespace<<"{\n\n";
    }


    out_ast_to_icode_elem(fout);
    out_ast_to_icode_ast(fout);

    fout<<"\nicode * comp_context::ast_to_icode(token_defs* tdefs, bool need_result_icode, icode *result_ic)\n{\n";
    fout<<"if(tdefs==NULL){assert(0); return new_icode();}\n";

    fout<<"if((tdefs->m_type==TOKEN_DEFS_TYPE_AST)||(tdefs->m_tk_type_int_list.size()>0))\n{\n";
    fout<<"return ast_to_icode_ast(tdefs, need_result_icode, result_ic);";
    fout<<"\n}\n";

    fout<<"else if(tdefs->m_type==TOKEN_DEFS_TYPE_ELEM)\n{\n";
    fout<<"return ast_to_icode_elem(tdefs, need_result_icode, result_ic);";
    fout<<"\n}\n";

    fout<<"else\n{\nassert(0);\n}\n";

    fout<<"return new_icode();\n";
    fout<<"\n}\n";



    if(m_namespace.size()>0)
    {
        fout<<"\n}//namespace "<<m_namespace<<"\n";
    }


    fout.close();

    return 0;
}

int bison_file_io::out_ast_to_icode_h(std::string file_name)
{
    std::ofstream fout;
    fout.open(file_name.c_str());

    fout<<"#ifndef AST_TO_ICODE_GEN_DEF_H\n";
    fout<<"#define AST_TO_ICODE_GEN_DEF_H\n";


    if(m_namespace.size()>0)
    {
        fout<<"namespace "<<m_namespace<<"{\n\n";
    }

    fout<<"enum E_AST_TO_ICODE_GEN_DEF{\n";

    int case_cnt=0;

    for(unsigned i=0;i<this->m_rules.size();++i)
    {
        std::vector< std::vector<std::string > > &orule = this->m_rules[i];
        for(unsigned j=1;j<orule.size();++j)
        {
            std::vector<std::string > &one_line_rule = orule[j];

            case_cnt++;
            fout<<line_num_to_str(i, j)  << "=0x"<<std::hex<<line_num_to_int(i,j)<<", "<<"//"<< orule[0][0]<<"->";
            for(unsigned k=0;k<one_line_rule.size();++k)
            {
                fout<<one_line_rule[k]<<" ";
            }
            fout<<"\n";
        }
    }

    fout<<"};\n\n";


    ///添加函数声明
    /// ast
    case_cnt=0;
    for(unsigned i=0;i<this->m_rules.size();++i)
    {
        std::vector< std::vector<std::string > > &orule = this->m_rules[i];
        for(unsigned j=1;j<orule.size();++j)
        {
            std::vector<std::string > &one_line_rule = orule[j];
            if(one_line_rule.size()<1)
            {
                continue;
            }
            case_cnt++;

            fout<<"icode *  func_"<<line_num_to_str(i,j)<<"(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);\n";
        }
    }
    fout<<"//ast func cout:"<<std::dec<<case_cnt<<"\n";

    case_cnt=0;
    for(unsigned i=0;i<this->m_tokens.size();++i)
    {
        case_cnt++;
        fout<<" icode *func_token_"<<m_tokens[i]<<"(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);\n";
    }

    fout<<"//elem func cout:"<<std::dec<<case_cnt<<"\n\n";


    if(m_namespace.size()>0)
    {
        fout<<"\n}//namespace "<<m_namespace<<"\n";
    }


    fout<<"#endif\n";

    fout.close();

    return 0;
}

int bison_file_io::out_ast_to_icode_func(std::string file_name)
{


    std::string file_name1;
    std::string file_name2;

    file_name1 = file_name;
    file_name2 = file_name+"_token.tmp";

    generate_func1(file_name1);
    generate_func_token(file_name2);
    return 0;
}

int bison_file_io::out_token_tree(std::string file_name)
{
    std::ofstream fout;
    fout.open(file_name.c_str());


    fout<<"digraph g1{\n";


    for(unsigned i=0;i<this->m_tokens.size();++i)
    {
        fout<<"\""<<this->m_tokens[i]<<"\""<<"[color=Red]\n";
    }

    for(unsigned i=0;i<this->m_rules.size();++i)
    {
        if(this->m_rules[i][0][0]==this->m_start)
        {
            fout<<"\""<<this->m_rules[i][0][0]<<"\""<<"[color=Blue]\n";
        }
        else
        {
            fout<<"\""<<this->m_rules[i][0][0]<<"\""<<"[color=Green]\n";
        }
    }


    std::map< std::string, std::map<std::string, int> > m_src_dst;

    for(unsigned i=0;i<this->m_rules.size();++i)
    {
        std::string target = this->m_rules[i][0][0];
        for(unsigned j=1;j<this->m_rules[i].size();++j)
        {
            for(unsigned k=0;k<this->m_rules[i][j].size();++k)
            {
                int minit_num;
                minit_num = m_src_dst[this->m_rules[i][j][k]][target];
                minit_num=minit_num+1;
                m_src_dst[this->m_rules[i][j][k]][target] = minit_num;
                //fout<<"\""<<this->m_rules[i][j][k]<<"\""<< "->"<<"\"" << target<<"\""<<"\n";
            }
        }
    }


    std::string undraw_str="()\",[];";
    for(auto it=m_src_dst.begin();it!=m_src_dst.end();++it)
    {
        std::string src = it->first;

        if((src.size()==3)&&src[0]=='\'')
        {
            continue;
        }


        for(auto it2=it->second.begin();it2!=it->second.end();++it2)
        {
            std::string dst = it2->first;
            int num = it2->second;
            fout<<"\"" <<src<<"\""<<"->" <<"\"" << dst<<"\""<<"[label="<<num <<"]\n";
        }
    }







    fout<<"}\n";

    return 0;
}

int bison_file_io::out_debug_list(std::string file_name)
{

    int case_cnt=0;

    std::ofstream fout(file_name);


    fout<<"std::vector<T_DEBUG_LIST> g_ast_debug_str={\n";
    for(unsigned i=0;i<this->m_rules.size();++i)
    {
        std::vector< std::vector<std::string > > &orule = this->m_rules[i];
        for(unsigned j=1;j<orule.size();++j)
        {
            std::vector<std::string > &one_line_rule = orule[j];

            case_cnt++;
            fout<<"{"<<line_num_to_str(i, j)  << ", \""<< orule[0][0]<<"->";
            for(unsigned k=0;k<one_line_rule.size();++k)
            {
                fout<<one_line_rule[k]<<" ";
            }
            fout<<"\" },\n";
        }
    }

    fout<<"};\n\n";


    fout<<"std::vector<T_DEBUG_LIST>g_elem_debug_str{\n";
    for(int i=0;i<m_tokens.size();++i)
    {
        fout<<"{Parser::token::"<<m_tokens[i]<<", \""<<m_tokens[i] <<"\""<<"},\n";
    }
    fout<<"};\n\n";



    fout.close();

    return 0;
}



int bison_file_io::generate_funci(std::string file_name, int start_rule_index, int end_rule_index)
{

    int case_cnt = 0;


    if(start_rule_index>this->m_rules.size())
    {
        return 0;
    }
    if((end_rule_index<0)||(end_rule_index>this->m_rules.size()))
    {
        end_rule_index=this->m_rules.size();
    }





    std::ofstream fout;
    fout.open(file_name.c_str());

    fout<<"#include <assert.h>\n";
    fout<<"#include \"icode.h\"\n";
    fout<<"#include \"comp_context.h\"\n";
    fout<<"#include \"token_defs.h\"\n";
    fout<<"#include \"comp_context_gen_defs.h\"\n";

    if(m_namespace.size()>0)
    {
        fout<<"namespace "<<m_namespace<<"{\n\n";
    }
    ///添加函数定义
    /// ast
    case_cnt=0;
    //this->m_rules.size()
    for(unsigned i=start_rule_index;i<end_rule_index;++i)
    {
        std::vector< std::vector<std::string > > &orule = this->m_rules[i];
        for(unsigned j=1;j<orule.size();++j)
        {
            std::vector<std::string > &one_line_rule = orule[j];
            if(one_line_rule.size()<1)
            {
                continue;
            }
            case_cnt++;

            fout<<"icode *  func_"<<line_num_to_str(i,j)<<"(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)\n";
            fout<<"{\n";

            ///添加当前表达式的注释
            fout<<"\t//0x"<<std::hex<<line_num_to_int(i, j)<<"-"<<   orule[0][0]<<"->";
            for(unsigned k=0;k<one_line_rule.size();++k)
            {
                fout<<one_line_rule[k]<<" ";
            }
            fout<<"\n";

            ///-------------------------------------
            fout<<"\t//parent:\n";
            for(int pi=0;pi<this->m_rules.size();++pi)
            {
                //if(pi==i)continue;
                std::vector< std::vector<std::string > > &prule = this->m_rules[pi];
                for(int pj=1;pj<prule.size();++pj)
                {
                    std::vector<std::string > &pone_line_rule = prule[pj];
                    for(int pk=0;pk<pone_line_rule.size();++pk)
                    {
                        if(pone_line_rule[pk]==orule[0][0])
                        {
                            //此处有匹配
                            fout<<"\t// "<<prule[0][0]<<"-->" ;
                            for(int kkk=0;kkk<pone_line_rule.size();++kkk)
                            {
                                fout<<" "<<pone_line_rule[kkk];
                            }
                            fout<<"\n";
                            break;
                        }
                    }
                }
            }
            ///-------------------------------------

            if(one_line_rule.size()==1)
            {
                //只有1个元素的，直接到下一个元素
                fout<<"return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);\n";
                fout<<"}\n";
                continue;
            }

            //);\n\t a->m_type= 2020.12.18 两行合并为1行
            fout<<"\ticode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);\n";

            for(unsigned k=0;k<one_line_rule.size();++k)
            {
                fout<<"\t//token_defs *"<<one_line_rule[k]<<"=tdefs->m_tk_elems["<< k<<"];\n" ;
            }

            for(unsigned k=0;k<one_line_rule.size();++k)
            {
                fout<<"\t//icode *"<<one_line_rule[k]<<"_ic=pcompi->ast_to_icode("<< one_line_rule[k] <<");\n" ;
            }

            for(unsigned k=0;k<one_line_rule.size();++k)
            {
                fout<<"\t//a->merge_icode("<<one_line_rule[k]<<"_ic);\n" ;
            }

            fout<<"\tassert(0);\n";

            fout<<"\treturn a;\n";
            fout<<"}\n";
        }
    }
    fout<<"//cnt="<<case_cnt<<"\n";

    if(m_namespace.size()>0)
    {
        fout<<"\n}//namespace "<<m_namespace<<"\n";
    }

    fout.close();
    return 0;

}



int bison_file_io::generate_func1(std::string file_name)
{
    size_t pos_last = file_name.find_last_of('.');

    if(m_func_sep_filename.size()==0)
    {
        generate_funci(file_name,0, -1);//single file
        return 0;
    }

    int i = 0;
    for(i=0;i<m_func_sep_filename.size()-1;++i)
    {

        //multi file
        generate_funci(file_name.substr(0, pos_last)+ m_func_sep_filename[i], m_func_sep_file_rule_start[i], m_func_sep_file_rule_start[i+1]);//file
    }
    generate_funci(file_name.substr(0, pos_last)+ m_func_sep_filename[i], m_func_sep_file_rule_start[i], -1);//file

    return 0;
}

int bison_file_io::generate_func_token(std::string file_name)
{

    int case_cnt = 0;
    std::ofstream fout;
    fout.open(file_name.c_str());


    fout<<"#include <assert.h>\n";
    fout<<"#include \"icode.h\"\n";
    fout<<"#include \"comp_context.h\"\n";
    fout<<"#include \"token_defs.h\"\n";
    fout<<"#include \"comp_context_gen_defs.h\"\n";



    if(m_namespace.size()>0)
    {
        fout<<"namespace "<<m_namespace<<"{\n\n";
    }



    case_cnt=0;
    for(unsigned i=0;i<this->m_tokens.size();++i)
    {
        case_cnt++;
        fout<<" icode *func_token_"<<m_tokens[i]<<"(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)\n";
        fout<<"{\n";
        fout<<"\t//"<<m_tokens[i]<<"\n";


        ///-------------------------------------
        fout<<"\t//parent:\n";
        for(int pi=0;pi<this->m_rules.size();++pi)
        {
            //if(pi==i)continue;
            std::vector< std::vector<std::string > > &prule = this->m_rules[pi];
            for(int pj=1;pj<prule.size();++pj)
            {
                std::vector<std::string > &pone_line_rule = prule[pj];
                for(int pk=0;pk<pone_line_rule.size();++pk)
                {
                    if(pone_line_rule[pk]==m_tokens[i])
                    {
                        //此处有匹配
                        fout<<"\t// "<<prule[0][0]<<"-->" ;
                        for(int kkk=0;kkk<pone_line_rule.size();++kkk)
                        {
                            fout<<" "<<pone_line_rule[kkk];
                        }
                        fout<<"\n";
                        break;
                    }
                }
            }
        }
        ///-------------------------------------


        //);\n\t a->m_type= 2020.12.18 2行合并为1行
        fout<<"\ticode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);\n";


        fout<<"\tassert(0);\n";

        fout<<"\treturn a;\n";
        fout<<"}\n";
    }


    if(m_namespace.size()>0)
    {
        fout<<"\n}//namespace "<<m_namespace<<"\n";
    }


    fout.close();
    return 0;

}


