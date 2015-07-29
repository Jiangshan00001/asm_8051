#include "asm8051_lex .h"
#include <iostream>
//#include <fstream>
#include <algorithm>


using namespace std;
// simple way in STL
void trim1(string& str)
{
	/// FIXME: TODO: 将TAB \R \N 等，都改为 空格 。便于后续处理
	{
		string::size_type pos1 = str.find_first_of('\t');
		while(pos1!=string::npos)
		{
			str[pos1] = ' ';
			pos1 = str.find_first_of('\t');
		}
		pos1 = str.find_first_of('\r');
		while(pos1!=string::npos)
		{
			str[pos1] = ' ';
			pos1 = str.find_first_of('\r');
		}
		pos1 = str.find_first_of('\n');
		while(pos1!=string::npos)
		{
			str[pos1] = ' ';
			pos1 = str.find_first_of('\n');
		}
	}

	string::size_type pos1 = str.find_first_not_of(' ');
	string::size_type pos2 = str.find_last_not_of(' ');
	str = str.substr(pos1 == string::npos ? 0 : pos1, 
	pos2 == string::npos ? str.length() - 1 : pos2 - pos1 + 1);
	
}


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
	transform(mOneLine.begin(), mOneLine.end(), mOneLine.begin(), toupper);
	
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

#if 0
	while(!mOneLine.empty())
	{
		string::size_type pos1 = mOneLine.find_first_of(' ');
		if (pos1==std::string::npos)
		{
			mWords.push_back(mOneLine);
			mOneLine="";
		}
		else
		{
			mWords.push_back(mOneLine.substr(0, pos1));
			mOneLine = mOneLine.substr(pos1+1, mOneLine.size()-1);
		}
	}
#endif
#if 1
	for(int i=0;i<mWords.size();i++)
	{
		cout<<"iWorld="<<i<<"."<<mWords[i].size()<<  " ["<<mWords[i]<<"]"<<endl;
	}
	
#endif
	
	return mWords.size();
}

