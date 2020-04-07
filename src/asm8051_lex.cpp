#include "asm8051_lex.h"
#include<sstream>

#include <iostream>
#include <algorithm>
#include <ctype.h>
#include "asm_context.h"
#include "trim.h"
#include "split.h"

using namespace std;
// simple way in STL

unsigned long StrToHex(std::string mHexStr)
{
    unsigned long x;
    signed long val;

    std::stringstream ss;
    ss << std::hex << mHexStr;
    ss >> x;

    return x;
}

typedef int (*op_tmp) (int i);

/// [a-zA-Z0-9]
/// :
/// ,
/// 其他符号
int split_words(std::string mOneLine, std::vector<std::string> &mWords)
{
    //去除空格
    // trim
    trim1(mOneLine);
    // lower--->upper
    transform<std::basic_string<char>::iterator, std::basic_string<char>::iterator, op_tmp>(mOneLine.begin(), mOneLine.end(), mOneLine.begin(), toupper);

    mWords.clear();
    if(mOneLine.empty())return 0;

    //;区分，去掉注释
    std::vector<std::string> comment1 = split(mOneLine, ";");

    if(comment1.size()==0){return 0;}
    mOneLine = comment1[0];


    //查找是否有: 如果有，则前面是标签
    mWords = split(mOneLine, ":");
    if (mWords.size()>1)
    {
        //此行为标签
        mWords[0] = mWords[0]+":";
        mWords.resize(1);
        return mWords.size();
    }

    //通过第一个空格，找到指令
    mWords = split(mOneLine, " ");
    std::string cmd = mWords[0];

    ///去除指令后，都为参数，通过逗号区分
    mOneLine = mOneLine.substr(cmd.size());
    trim1(mOneLine);

    mWords = split(mOneLine, ",");
    mWords.insert(mWords.begin(), cmd);

    for(int i=0;i<mWords.size();++i)
    {
        mWords[i] = trim(mWords[i]);
    }

    return mWords.size();
}


#if 0
typedef int (*op_tmp) (int i);

/// [a-zA-Z0-9]
/// :
/// ,
/// 其他符号
int split_words(std::string mOneLine, std::vector<std::string> &mWords)
{
    //去除空格
    // trim
    trim1(mOneLine);
    // lower--->upper
    transform<std::basic_string<char>::iterator, std::basic_string<char>::iterator, op_tmp>(mOneLine.begin(), mOneLine.end(), mOneLine.begin(), toupper);

    mWords.clear();
    if(mOneLine.empty())return 0;

    const char *mTmpStrPtrStart = mOneLine.c_str();
    const char *mTmpStrPtr1 = mOneLine.c_str();
    const char *mTmpStrPtr2 = mOneLine.c_str();

    while((mTmpStrPtr2-mTmpStrPtrStart)!=mOneLine.size())
    {
        ///字母和数字连在一起作为一个单词，其他符号单独作为一个单词
        unsigned char mC = (*mTmpStrPtr2);
        if ( (( mC>='0')&&( mC<='9'))||
            (( mC>='a')&&( mC<='z'))||
            (( mC>='A')&&( mC<='Z'))
            )
        {
            mTmpStrPtr2++;
            continue;
        }
        else
        {
            if (mTmpStrPtr1!=mTmpStrPtr2)
            {
                std::string mCS;
                mCS.assign(mTmpStrPtr1, mTmpStrPtr2);
                mWords.push_back(mCS);
                mTmpStrPtr1 = mTmpStrPtr2;
            }

            if (mC!=' ')
            {
                unsigned char mCT[4]={0,0,0,0};
                mCT[0]=mC;
                mCT[1] = 0;
                mWords.push_back((char*)mCT);
            }

            mTmpStrPtr1 = ++mTmpStrPtr2;
            continue;
        }
    }

    if (mTmpStrPtr1!=mTmpStrPtr2)
    {
        std::string mCS;
        mCS.assign(mTmpStrPtr1, mTmpStrPtr2);
        mWords.push_back(mCS);
        mTmpStrPtr1 = mTmpStrPtr2;
    }

#if 1
    for(int i=0;i<mWords.size();i++)
    {
        cout<<"iWorld="<<i<<"."<<mWords[i].size()<<  " ["<<mWords[i]<<"]"<<endl;
    }

#endif

    return mWords.size();
}

#endif



asm_token param_parse(std::string str1)
{
    asm_token token1;
    token1.val_str = str1;

    std::map<std::string, int> m_keys;

    m_keys["A"] = TOKEN_ACC;
    m_keys["C"] = TOKEN_C;
    m_keys["AB"] = TOKEN_AB;
    m_keys["@DPTR"] = TOKEN_AT_DPTR;
    m_keys["DPTR"] = TOKEN_DPTR;
    m_keys["@A+PC"] = TOKEN_AT_A_PLUS_PC;
    m_keys["@A+DPTR"] = TOKEN_AT_A_PLUS_DPTR;
    m_keys["@R0"] = TOKEN_AT_RI;
    m_keys["@R1"] = TOKEN_AT_RI;
    m_keys["R0"] = TOKEN_RN;
    m_keys["R1"] = TOKEN_RN;
    m_keys["R2"] = TOKEN_RN;
    m_keys["R3"] = TOKEN_RN;
    m_keys["R4"] = TOKEN_RN;
    m_keys["R5"] = TOKEN_RN;
    m_keys["R6"] = TOKEN_RN;
    m_keys["R7"] = TOKEN_RN;




    if (m_keys.find(str1)!=m_keys.end())
    {
        token1.type = m_keys[str1];
        token1.num = 0;
        if(str1=="@R1")token1.num = 1;
        if(str1=="R1")token1.num = 1;
        if(str1=="R2")token1.num = 2;
        if(str1=="R3")token1.num = 3;
        if(str1=="R4")token1.num = 4;
        if(str1=="R5")token1.num = 5;
        if(str1=="R6")token1.num = 6;
        if(str1=="R7")token1.num = 7;
        return token1;
    }


    if(str1[0]=='#')
    {
        //立即数？
        token1.type = TOKEN_J_DATA;
        token1.num = StrToHex(str1.c_str()+1);//
        return token1;
    }

    if(str1[0]=='/')
    {
        //立即数？
        token1.type = TOKEN_DIV_NUM;
        token1.num = StrToHex(str1.c_str()+1);//
        return token1;
    }

    if( (str1[0]>='0' )&&(str1[0]<='9'))
    {
        token1.type = TOKEN_NUM;
        token1.num = StrToHex(str1);//
        return token1;
    }


    if(( (str1[0]>='a' )&&(str1[0]<='z'))||
            ( (str1[0]>='A' )&&(str1[0]<='Z'))
            )
    {
        if (str1[str1.size()-1]==':' )
        {
            token1.type = TOKEN_LABEL;
            token1.num = 0;//
            token1.val_str = token1.val_str.substr(0, token1.val_str.size()-1);
            return token1;

        }
        else
        {
            token1.type = TOKEN_KEYWORD;
            token1.num = 0;//
            return token1;
        }
    }

    std::cout<<"error: unkown key:"<<str1<<std::endl;
    token1.type = TOKEN_UNKNOWN;
    token1.num = 0;
    return token1;
}



std::vector<asm_token> asm_line_parse(void *ctx, std::string str1)
{
    std::vector<asm_token> tokens;
    std::vector<std::string> words;
    T_ASM_CONTEXT *mCtx = (T_ASM_CONTEXT*)ctx;

    int siz = split_words(str1, words);

    for(int i=0;i<words.size();++i)
    {
        asm_token token1;

        if(words[i].size()==0)continue;//0size. just skip

        token1.val_str = words[i];

        if(mCtx->m_line_key_word_ptr.find(words[i])!=mCtx->m_line_key_word_ptr.end())
        {
            //keyword
            token1.type=TOKEN_CMD;
            tokens.push_back(token1);
            continue;
        }
        token1= param_parse(words[i]);
        tokens.push_back(token1);
    }

    return tokens;
}



std::vector<std::string> template_param_parse_str(std::string str1)
{
    //"A,direct"
    //"A,Rn"
    std::vector<string> ret;

    str1 = trim1(str1,'\"');
    std::vector<std::string> params = split(str1, ",");


    for(int i=0;i<params.size();++i)
    {
        string token1;
        std::string param1=params[i];

        token1 = "";

        if(param1=="A")
        {
            token1 = "TOKEN_ACC";
        }
        else if(param1=="Rn")
        {
            token1="TOKEN_RN";
        }
        else if(param1=="direct")
        {
            token1 = "TOKEN_NUM";
        }
        else if(param1=="#data")
        {
            token1="TOKEN_J_DATA";
        }
        else if(param1=="#data16")
        {
            token1="TOKEN_J_DATA";
        }
        else if(param1=="@Ri")
        {
            token1 = "TOKEN_AT_RI";
        }
        else if(param1=="rel")
        {
            token1="TOKEN_KEYWORD";
        }
        else if(param1=="addr11")
        {
            token1 = "TOKEN_KEYWORD";
        }
        else if(param1=="addr16")
        {
            token1 = "TOKEN_KEYWORD";
        }
        else if(param1=="data16")
        {
            token1 = "TOKEN_KEYWORD";
        }
        else if(param1=="bit")
        {
            token1 = "TOKEN_NUM";
        }
        else if(param1=="/bit")
        {
            token1 = "TOKEN_DIV_NUM";
        }
        else if(param1=="@A+DPTR")
        {
            token1 = "TOKEN_AT_A_PLUS_DPTR";
        }
        else if(param1=="@A+PC")
        {
            token1 = "TOKEN_AT_A_PLUS_PC";
        }
        else if(param1=="DPTR")
        {
            token1 = "TOKEN_DPTR";
        }
        else if(param1=="@DPTR")
        {
            token1 = "TOKEN_AT_DPTR";
        }
        else if(param1=="AB")
        {
            token1 = "TOKEN_AB";
        }
        else if(param1=="C")
        {
            token1 = "TOKEN_C";
        }
        else if(param1=="code addr")
        {
            token1 = "TOKEN_KEYWORD";
        }
        else if(param1=="data addr")
        {
            token1 = "TOKEN_KEYWORD";

        }
        else if(param1=="bit addr")
        {
            token1 = "TOKEN_KEYWORD";
        }
        else
        {
            token1="TOKEN_UNKNOWN";
            std::cout<<"template_param_parse---unkown type:"<<param1<<std::endl;
        }
        ret.push_back(token1);
    }
    return ret;
}

std::vector<std::string> template_param_parse_str_var(std::string str1)
{
    //"A,direct"
    //"A,Rn"
    std::vector<string> ret;

    str1 = trim1(str1,'\"');
    std::vector<std::string> params = split(str1, ",");


    for(int i=0;i<params.size();++i)
    {
        string token1;
        std::string param1=params[i];

        token1 = "";

        if(param1=="A")
        {
            token1 = "num";
        }
        else if(param1=="Rn")
        {
            token1="num";
        }
        else if(param1=="direct")
        {
            token1 = "num";
        }
        else if(param1=="#data")
        {
            token1="num";
        }
        else if(param1=="#data16")
        {
            token1="num";
        }
        else if(param1=="@Ri")
        {
            token1 = "num";
        }
        else if(param1=="rel")
        {
            token1="rel";
        }
        else if(param1=="addr11")
        {
            token1 = "num";
        }
        else if(param1=="addr16")
        {
            token1 = "num";
        }
        else if(param1=="data16")
        {
            token1 = "num";
        }
        else if(param1=="bit")
        {
            token1 = "num";
        }
        else if(param1=="/bit")
        {
            token1 = "num";
        }
        else if(param1=="@A+DPTR")
        {
            token1 = "num";
        }
        else if(param1=="@A+PC")
        {
            token1 = "num";
        }
        else if(param1=="DPTR")
        {
            token1 = "num";
        }
        else if(param1=="@DPTR")
        {
            token1 = "num";
        }
        else if(param1=="AB")
        {
            token1 = "num";
        }
        else if(param1=="C")
        {
            token1 = "num";
        }
        else if(param1=="code addr")
        {
            token1 = "num";
        }
        else if(param1=="data addr")
        {
            token1 = "num";
        }
        else if(param1=="bit addr")
        {
            token1 = "num";
        }
        else
        {
            token1="TOKEN_UNKNOWN";
            std::cout<<"template_param_parse---unkown type:"<<param1<<std::endl;
        }
        ret.push_back(token1);
    }
    return ret;

}
