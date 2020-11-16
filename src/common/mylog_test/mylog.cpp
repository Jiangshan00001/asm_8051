#include <iostream>
#include <fstream>
#include "mylog.h"

namespace mylog {


MyLog cout;
MyLog cerr;
MyLog cdbg;
MyLog cwarn;

}


mylog::MyStreamBuf::MyStreamBuf()
{

}

mylog::MyStreamBuf::~MyStreamBuf()
{

}

int mylog::MyStreamBuf::overflow(int c)
{
    m_callback->foo(c);
    return 0;
}


mylog::MyLog::MyLog()
{
    ///FIXME ostream 代码，如果编译选项改为-O3 则出错！！！！
    /// 怀疑是代码错误
    m_stream_buf.m_callback = this;
    this->init(&m_stream_buf);
    is_c_cout = 1;
}

mylog::MyLog::~MyLog()
{


}

void mylog::MyLog::foo(char c)
{
    if(is_c_cout)
    {
        std::cout.put(c);
    }

    if(m_log_stream.is_open())
    {
        m_log_stream<<c;
        m_log_stream.flush();
    }

}

int mylog::MyLog::set_log_file(std::string file_name)
{
    if(file_name.size()>0)
    {
        m_log_file_name = file_name;
    }

    if(m_log_file_name.size()>0)
    close_log_file();
    m_log_stream.open(m_log_file_name.c_str(), std::ios_base::out| std::ios_base::app );
    return 0;
}

int mylog::MyLog::close_log_file()
{
    if(m_log_stream.is_open())
    {
        m_log_stream.close();
    }
    return 0;
}

int mylog::MyLog::set_cout_output(int is_out)
{
    is_c_cout = is_out;
}
