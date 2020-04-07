#include "csv_io.h"
#include "trim.h"
#include "split.h"
#include "replace.h"





static int split_count(std::string str, std::string token, std::string excep)
{
    std::string to_rep_str="";
    for(int i=0;i<excep.size();++i)
    {
        to_rep_str +="A";
    }

    str = replace(str, excep, to_rep_str);

    std::vector<std::string> vec1=split(str, token);
    return vec1.size();
}


csv_io::csv_io()
{


}

int csv_io::set_file_name(std::string file_name)
{
    m_file_name = file_name;

}

int csv_io::open_file()
{
    if(m_file.is_open())
    {
        m_file.close();
    }
    m_file.open(m_file_name.c_str());

}


std::vector<int> str_vec_size(std::vector<std::string> str1)
{
    std::vector<int> ret;
    for(int i=0;i<str1.size();++i)
    {
        ret.push_back(str1[i].size());
    }
    return ret;
}


std::vector<std::string> csv_io::parse_next_line(int *is_eof)
{
    std::vector<std::string> ret;
    std::string one_line;

    if(is_eof!=NULL)
    {
        *is_eof=0;
    }


    if((m_file.eof())||(!m_file.is_open()))
    {
        if (is_eof!=NULL)
        {
            *is_eof=1;
        }
        return ret;
    }


    std::getline(m_file, one_line);




    //m_file.is

    one_line = trim(one_line);
    if (one_line.size()==0)return ret;

    std::vector<std::string> quote_split_vec = split(one_line, m_quote);
    std::vector<std::string> delimiter_split_vec = split(one_line, m_delimiter);



    std::vector<int> delimiter_need_merge;
    int need_merge = 0;
    for(int i=0;i<delimiter_split_vec.size();++i)
    {
        ///delimiter_split_vec[i]
        int qut1 = split_count(delimiter_split_vec[i], m_quote, "\\\"");


        if ((qut1%2==1))
        {
            ///此处内部引号成对，所以正常，不需要和下一个合并
        }
        else if(qut1>0)
        {
            if (need_merge)
            {
                need_merge = 0;
            }
            else
            {
                need_merge = 1;
            }
        }

        delimiter_need_merge.push_back(need_merge);
    }


    ret.clear();
    ret.push_back(delimiter_split_vec[0]);
    for(int i=1;i<delimiter_split_vec.size();++i)
    {
        if(delimiter_need_merge[i-1])
        {
            std::string mlast = ret[ret.size()-1];
            mlast = mlast +m_delimiter+delimiter_split_vec[i];
            ret[ret.size()-1] = mlast;
        }
        else
        {
            ret.push_back(delimiter_split_vec[i]);
        }
    }
    return ret;
}

int csv_io::close_file()
{
    if(m_file.is_open())
    {
        m_file.close();
    }
}





