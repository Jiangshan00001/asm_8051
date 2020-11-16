#ifndef MYLOG_H
#define MYLOG_H


#include <iostream>
#include <fstream>

namespace mylog {


class MyStreamBuf: public std::streambuf
{
public:
    MyStreamBuf();
    ~MyStreamBuf();
protected:


    ///Basically just subclass the ostream and the streambuf objects,
    /// and construct the ostream with itself as the buffer.
    /// the virtual overflow() from std::streambuf will be called for every character sent to the stream.
    /// To fit your example i just made a foo() function and called it.
    ///
    virtual int overflow(int c);
public:
    class MyLog *m_callback;

};

class MyLog : public std::ostream
{
public:
    MyLog();
    ~MyLog();



protected:
    ///Basically just subclass the ostream and the streambuf objects,
    /// and construct the ostream with itself as the buffer.
    /// the virtual overflow() from std::streambuf will be called for every character sent to the stream.
    /// To fit your example i just made a foo() function and called it.
    ///
    //virtual int overflow(int c);
public:
    void foo(char c);
    int set_log_file(std::string file_name="");
    int close_log_file();
    int set_cout_output(int is_out);
private:
    std::string m_log_file_name;
    std::ofstream m_log_stream;
    int is_c_cout;
private:
    MyStreamBuf m_stream_buf;
};


extern  MyLog cout;
extern MyLog cerr;
extern MyLog cdbg;
extern MyLog cwarn;

}



#endif // MYLOG_H
