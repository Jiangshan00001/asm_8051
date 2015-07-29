#include <iostream>
#include <iosfwd>
#include <fstream>
#include <string>
#include <sstream>
#include "hex_generator.h"

std::string HByteToStr(const unsigned char mC)
{
	unsigned char mTmpStr[4]={0,0,0,0};
	///0--F
	if (mC<0xA)
	{
		mTmpStr[0] =(mC+'0');
	}
	else
	{
		mTmpStr[0] =(mC-10+'A');
	}
	return std::string((char*)mTmpStr);
}


std::string ByteToStr(const unsigned char mC)
{
	unsigned a = ((mC&0xf0)>>4);
	unsigned b = (mC&0x0f);

	return HByteToStr(a) + HByteToStr(b) ;	
}

//: 10 1234 00 021234513F2925102724123935143734  2A
//:1012440047413F5E5556575487520953784382812C
//:0E125400B081B534E6B443E3BE54E0B654DDD9
//:00000001FF

///格式说明 : 每一行前为":"
/// 1字节为数据个数"10"
/// 2字节为数据起始地址"1234"
/// 1字节为数据类型， 00---数据记录，01--文件结束记录
/// 1字节为 校验码


int hex_test(T_HEX_TEXT_BLOCK &mBlock, std::ofstream &file_out )
{
	
	unsigned long mAddressHead;
	unsigned long mAddress;
	
	mAddressHead = mAddress = mBlock.m_address;

	///everything done. flush all to file
	while((mAddress-mAddressHead<mBlock.m_hex_text.size()))
	{
		if ((mBlock.m_hex_text.size() - (mAddress-mAddressHead))>=0x10)
		{
			//写入0x10个字节
			file_out<<":";//起始字节
			file_out<<"10";//数据个数
			
			file_out<<ByteToStr((mAddress>>8)) ;
			file_out<<ByteToStr(mAddress);//地址
			file_out<<"00";//数据类型
			unsigned char mCheckByte = 0x10+((mAddress>>8)&0xff)+(mAddress&0xff);
			for (int j=0;j<0x10;j++)
			{
				file_out<<ByteToStr(mBlock.m_hex_text[mAddress-mAddressHead]);//数据类型
				mCheckByte += mBlock.m_hex_text[mAddress-mAddressHead];
				mAddress++;
			}
			mCheckByte = -mCheckByte;
			file_out<<ByteToStr(mCheckByte);
			file_out<<"\n";
		}
		else
		{
			//有多少字节，写多少字节
			int mBytesLeft = mBlock.m_hex_text.size() - (mAddress-mAddressHead);
			//写入mBytesLeft个字节
			file_out<<":";//起始字节
			file_out<<ByteToStr(mBytesLeft);//数据个数
			
			file_out<<ByteToStr((mAddress>>8)) ;
			file_out<<ByteToStr(mAddress);//地址
			file_out<<"00";//数据类型
			unsigned char mCheckByte = mBytesLeft+((mAddress>>8)&0xff)+(mAddress&0xff);
			for (int j=0;j<mBytesLeft;j++)
			{
				file_out<<ByteToStr(mBlock.m_hex_text[mAddress-mAddressHead]);//数据类型
				mCheckByte += mBlock.m_hex_text[mAddress-mAddressHead];
				mAddress++;
			}
			mCheckByte = (-mCheckByte);
			file_out<<ByteToStr(mCheckByte);
			file_out<<"\n";
		}
	}

	return 0;
}
int hex_generator(T_ASM_CONTEXT *mCtx, std::string file_name)
{
	if (mCtx->m_text_block.empty())
	{
		return 0;
	}
	
	
	std::ofstream file_out(file_name.c_str());


	std::vector<T_HEX_TEXT_BLOCK> text_block;

	//////////////////////////////////////////////////////////////////////////
	text_block = mCtx->m_text_block;//copy
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	/// skip
	for (int i1=0;i1<text_block.size();++i1)
	{
		if (text_block[i1].m_hex_text.empty())
		{
			// no code. skip it
			text_block.erase(text_block.begin()+i1);
			--i1;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	/// merge
	for (int i2=1;i2<text_block.size();++i2)
	{
		if (text_block[i2-1].m_address+text_block[i2-1].m_hex_text.size()== text_block[i2].m_address)
		{
			//merge
			text_block[i2-1].m_hex_text = text_block[i2-1].m_hex_text + text_block[i2].m_hex_text;
			text_block.erase(text_block.begin()+i2);
			--i2;
		}
	}


	//////////////////////////////////////////////////////////////////////////
	for (int i3=0;i3<text_block.size();++i3)
	{
		hex_test(text_block[i3], file_out);
	}

	//file end
	file_out<<":00000001FF"<<"\n";
	file_out.close();

	return 0;
}