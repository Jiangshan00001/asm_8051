#include <ASSERT.H>
#include "main.h"
#include "asm_8051_keywords.h"
#include <sstream>

std::map<std::string, CODE_GEN_FUNC_PTR>  asm_8051_key_words;


#define ASSERT_8051(a, stra) assert(a)



unsigned long StrToHex(std::string mHexStr)
{
	unsigned long x;
	signed long val;
	
	std::stringstream ss;
	ss << std::hex << mHexStr;
	ss >> x;

	return x;
}

int LABEL_Check(T_ASM_CONTEXT *mCtx, std::string mLabel, unsigned long &mAddress)
{
	std::map<std::string, unsigned long>::iterator it;
	it = mCtx->m_label_address.find(mLabel);
	if (it!=mCtx->m_label_address.end())
	{
		///标签地址已找到
		unsigned long addr = it->second;
		mAddress = addr;
		return 0;
	}
	///没有标签，直接返回，标记为需要第二遍操作
	return -1;
}

int ACALL_CodeGen(T_ASM_CONTEXT *mCtx)
{
	///此函数，只支持标签调用，不支持绝对地址
	/// ACALL LABEL
	/// ACALL

	//(PC) ← (PC) + 2
	//	(SP) ← (SP) + 1
	//	((SP)) ← (PC7-0)
	//	(SP) ← (SP) + 1
	//	((SP)) ← (PC15-8)
	//(PC10-0) ← page address

	mCtx->m_current_line_out.resize(2);//指令长度
	//周期2
	mCtx->m_current_line_out[0] = 0x11;
	std::map<std::string, unsigned long>::iterator it;
	it = mCtx->m_label_address.find(mCtx->m_current_line_words[1]);
	if (it!=mCtx->m_label_address.end())
	{
		///标签地址已找到
		unsigned long addr = it->second;
		mCtx->m_current_line_out[1] = (addr&0xff);
		mCtx->m_current_line_out[0] |= ((addr>>3)&0xe0);
		return 0;
	}
	///没有标签，直接返回，标记为需要第二遍操作
	return 1;
}

int ADD_CodeGen(T_ASM_CONTEXT *mCtx)
{
	// ADD A,direct ---2
	// A<--A+direct

	// ADD A,#data ---2
	// A<--A+#data
	
	if (mCtx->m_current_line_words[3][0]=='R')	
	{
		// ADD A, Rn  ---1
		// A<--A+Rn
		mCtx->m_current_line_out.resize(1);//指令长度
		mCtx->m_current_line_out[0] = 0x28;
		mCtx->m_current_line_out[0] |= (0x7&StrToHex(mCtx->m_current_line_words[3].c_str()+1));
		return 0;
	}
	else if (mCtx->m_current_line_words[3][0]=='@')
	{
		/// FIXME TODO 如果Ri不是R0 R1,则应该报错
		// ADD A,@Ri ---1; R0 R1
		// A<--A+@Ri
		mCtx->m_current_line_out.resize(1);//指令长度
		mCtx->m_current_line_out[0] = 0x26;
		mCtx->m_current_line_out[0] |= (0x1&StrToHex(mCtx->m_current_line_words[4].c_str()+1));
		return 0;
	}
	else if (mCtx->m_current_line_words[3][0]=='#')
	{
		//ADD A,#data
		mCtx->m_current_line_out.resize(2);//指令长度
		mCtx->m_current_line_out[0] = 0x24;
		mCtx->m_current_line_out[1] = StrToHex(mCtx->m_current_line_words[4]);
		return 0;
	}
	else
	{
		//ADD A,direct
		mCtx->m_current_line_out.resize(2);//指令长度
		mCtx->m_current_line_out[0] = 0x25;
		mCtx->m_current_line_out[1] = StrToHex(mCtx->m_current_line_words[3]);
		return 0;
	}
}

int ADDC_CodeGen(T_ASM_CONTEXT *mCtx)
{
	// ADD A,direct ---2
	// A<--A+direct
	
	// ADD A,#data ---2
	// A<--A+#data
	
	if (mCtx->m_current_line_words[3][0]=='R')	
	{
		// ADD A, Rn  ---1
		// A<--A+Rn
		mCtx->m_current_line_out.resize(1);//指令长度
		mCtx->m_current_line_out[0] = 0x38;
		mCtx->m_current_line_out[0] |= (0x7&StrToHex(mCtx->m_current_line_words[3].c_str()+1));
		return 0;
	}
	else if (mCtx->m_current_line_words[3][0]=='@')
	{
		/// FIXME TODO 如果Ri不是R0 R1,则应该报错
		// ADD A,@Ri ---1; R0 R1
		// A<--A+@Ri
		mCtx->m_current_line_out.resize(1);//指令长度
		mCtx->m_current_line_out[0] = 0x36;
		mCtx->m_current_line_out[0] |= (0x1&StrToHex(mCtx->m_current_line_words[4].c_str()+1));
		return 0;
	}
	else if (mCtx->m_current_line_words[3][0]=='#')
	{
		//ADD A,#data
		mCtx->m_current_line_out.resize(2);//指令长度
		mCtx->m_current_line_out[0] = 0x34;
		mCtx->m_current_line_out[1] = StrToHex(mCtx->m_current_line_words[4]);
		return 0;
	}
	else
	{
		//ADD A,direct
		mCtx->m_current_line_out.resize(2);//指令长度
		mCtx->m_current_line_out[0] = 0x35;
		mCtx->m_current_line_out[1] = StrToHex(mCtx->m_current_line_words[3]);
		return 0;
	}
}

int AJMP_CodeGen(T_ASM_CONTEXT *mCtx)
{
	///此函数，只支持标签调用，不支持绝对地址
	// AJMP LABEL
	//AJMP
	//(PC) ← (PC) + 2
	//(PC10-0) ← page address
	
	
	mCtx->m_current_line_out.resize(2);//指令长度
	//周期2
	mCtx->m_current_line_out[0] = 0x01;
	unsigned long addr = 0;
	int ret = LABEL_Check(mCtx, mCtx->m_current_line_words[1], addr);
	if (ret==0)
	{
		///标签地址已找到
		mCtx->m_current_line_out[1] = (addr&0xff);
		mCtx->m_current_line_out[0] |= ((addr>>3)&0xe0);
		return 0;
	}

	///没有标签，直接返回，标记为需要第二遍操作
	return 1;
}

int ANL_CodeGen(T_ASM_CONTEXT *mCtx)
{
	//ANL A,Rn
	//ANL A,direct
	//ANL A,@Ri
	//ANL A,#data

	//ANL direct,A
	//ANL direct, #data

	//ANL C,bit
	//ANL C,/bit

	ASSERT_8051(mCtx->m_current_line_words.size()>=4, "ANL format error");
	
	if (mCtx->m_current_line_words[1]=="A")
	{
		if (mCtx->m_current_line_words[3][0]=='R')
		{
			//ANL A,Rn
			mCtx->m_current_line_out.resize(1);//指令长度
			mCtx->m_current_line_out[0] = 0x58;
			mCtx->m_current_line_out[0] |= (0x7&StrToHex(mCtx->m_current_line_words[3].c_str()+1));
			return 0;
		}
		else if (mCtx->m_current_line_words[3][0]=='@')
		{
			//ANL A,@Ri
			mCtx->m_current_line_out.resize(1);//指令长度
			mCtx->m_current_line_out[0] = 0x56;
			mCtx->m_current_line_out[0] |= (0x1&StrToHex(mCtx->m_current_line_words[4].c_str()+1));
			return 0;
		}
		else if (mCtx->m_current_line_words[3][0]=='#')
		{
			//ANL A,#data
			mCtx->m_current_line_out.resize(2);//指令长度
			mCtx->m_current_line_out[0] = 0x54;
			mCtx->m_current_line_out[1] = StrToHex(mCtx->m_current_line_words[4]);
			return 0;
		}
		else //FIXME TODO. 语法判断没有,判断direct是否合法
		{
			//ANL A,direct
			mCtx->m_current_line_out.resize(2);//指令长度
			mCtx->m_current_line_out[0] = 0x55;
			mCtx->m_current_line_out[1] = StrToHex(mCtx->m_current_line_words[3]);
			return 0;
		}
	}
	else if (mCtx->m_current_line_words[1]=="C")
	{

		//ANL C,/bit
		if (mCtx->m_current_line_words.size()==4)
		{
			//ANL C,bit
			mCtx->m_current_line_out.resize(2);//指令长度
			mCtx->m_current_line_out[0] = 0x82;
			mCtx->m_current_line_out[1] = StrToHex(mCtx->m_current_line_words[3]);
			return 0;
		}
		else if ((mCtx->m_current_line_words.size()==5)&&
			 (mCtx->m_current_line_words[3][0]=='/')
			 )
		{
			//ANL C,/bit
			mCtx->m_current_line_out.resize(2);//指令长度
			mCtx->m_current_line_out[0] = 0xB0;
			mCtx->m_current_line_out[1] = StrToHex(mCtx->m_current_line_words[4]);
			return 0;
		}
		else
		{
			ASSERT_8051(0,"ERROR");
		}
	}
	else if (mCtx->m_current_line_words[3]==std::string("A"))
	{
		//ANL direct,A
		mCtx->m_current_line_out.resize(2);//指令长度
		mCtx->m_current_line_out[0] = 0x52;
		mCtx->m_current_line_out[1] = StrToHex(mCtx->m_current_line_words[1]);
		return 0;

	}
	else if (mCtx->m_current_line_words[3]=="#")
	{
		//ANL direct, #data	
		mCtx->m_current_line_out.resize(3);//指令长度
		mCtx->m_current_line_out[0] = 0x53;
		mCtx->m_current_line_out[1] = StrToHex(mCtx->m_current_line_words[1]);
		mCtx->m_current_line_out[2] = StrToHex(mCtx->m_current_line_words[4]);
		return 0;
	}
	else
	{
		std::cout<<"["<<mCtx->m_current_line_words[3]<<"]"<<std::endl;
		ASSERT_8051(0,"ERROR");
	}
}

int CJNE_CodeGen(T_ASM_CONTEXT *mCtx)
{
	// compare and jump if not equal
	// CJNE A,direct,rel
	// CJNE A,#data,rel
	// CJNE Rn,#data,rel
	// CJNE @Ri,data,rel
	
	ASSERT_8051(mCtx->m_current_line_words.size()>=6, "CJNE format error");
	
	if (mCtx->m_current_line_words[1]=="A")
		{
			if (mCtx->m_current_line_words[3][0]=='#')
			{
				// CJNE A,#data,rel
				mCtx->m_current_line_out.resize(3);//指令长度
				mCtx->m_current_line_out[0] = 0xB4;
				mCtx->m_current_line_out[1] = StrToHex(mCtx->m_current_line_words[4].c_str());
				unsigned long mAbsAddr=0;
				int ret = LABEL_Check(mCtx, mCtx->m_current_line_words[6],mAbsAddr);
				if (ret==0)//找到标签
				{
					///当前指令长度为3，相对偏移从下一条指令为0
					 long mRelAddr = mAbsAddr - mCtx->m_current_address-3;
					mCtx->m_current_line_out[2] = mRelAddr;
					return 0;
				}
				return 1;
			}
			else //FIXME TODO. 语法判断没有,判断direct是否合法
			{
				// CJNE A,direct,rel
				mCtx->m_current_line_out.resize(3);//指令长度
				mCtx->m_current_line_out[0] = 0xB5;
				mCtx->m_current_line_out[1] = StrToHex(mCtx->m_current_line_words[3]);
				unsigned long mAbsAddr=0;
				int ret = LABEL_Check(mCtx, mCtx->m_current_line_words[5],mAbsAddr);
				if (ret==0)//找到标签
				{
					long mRelAddr = mAbsAddr - mCtx->m_current_address-3;
					mCtx->m_current_line_out[2] = mRelAddr;
					return 0;
				}
				return 1;
			}
		}
		else if (mCtx->m_current_line_words[1]=="@")
		{
			// CJNE @Ri,#data,rel
			mCtx->m_current_line_out.resize(3);//指令长度
			mCtx->m_current_line_out[0] = 0xB6;
			mCtx->m_current_line_out[0] |= (1&StrToHex(mCtx->m_current_line_words[2].c_str()+1));
			mCtx->m_current_line_out[1] = StrToHex(mCtx->m_current_line_words[5]);
			unsigned long mAbsAddr=0;
			int ret = LABEL_Check(mCtx, mCtx->m_current_line_words[7],mAbsAddr);
			if (ret==0)//找到标签
			{
				long mRelAddr = mAbsAddr - mCtx->m_current_address-3;
				mCtx->m_current_line_out[2] = mRelAddr;
				return 0;
			}
			return 1;
		}
		else if (mCtx->m_current_line_words[1][0]=='R')
		{
			// CJNE Rn,#data,rel
			mCtx->m_current_line_out.resize(3);//指令长度
			mCtx->m_current_line_out[0] = 0xB8;
			mCtx->m_current_line_out[0] |= (0x7 & StrToHex(mCtx->m_current_line_words[1].c_str()+1));
			mCtx->m_current_line_out[1] = StrToHex(mCtx->m_current_line_words[4]);
			unsigned long mAbsAddr=0;
			int ret = LABEL_Check(mCtx, mCtx->m_current_line_words[6],mAbsAddr);
			if (ret==0)//找到标签
			{
				long mRelAddr = mAbsAddr - mCtx->m_current_address-3;
				mCtx->m_current_line_out[2] = mRelAddr;
				return 0;
			}
			return 1;
		}
		else
		{
			ASSERT_8051(0,"ERROR");
		}
}

int CLR_CodeGen(T_ASM_CONTEXT *mCtx)
{
	if (mCtx->m_current_line_words[1]=="A")
	{
		// CLR A
		mCtx->m_current_line_out.resize(1);//指令长度
		mCtx->m_current_line_out[0] = 0xE4;
	}
	else if (mCtx->m_current_line_words[1]=="C")
	{
		// CLR C
		mCtx->m_current_line_out.resize(1);//指令长度
		mCtx->m_current_line_out[0] = 0xC3;
	}
	else
	{
		// CLR bit
		mCtx->m_current_line_out.resize(2);//指令长度
		mCtx->m_current_line_out[0] = 0xC2;
		mCtx->m_current_line_out[1] = StrToHex(mCtx->m_current_line_words[1]);
	}

	return 0;
}

int CPL_CodeGen(T_ASM_CONTEXT *mCtx)
{
	if (mCtx->m_current_line_words[1]=="A")
	{
		// CPL A
		mCtx->m_current_line_out.resize(1);//指令长度
		mCtx->m_current_line_out[0] = 0xF4;
	}
	else if (mCtx->m_current_line_words[1]=="C")
	{
		// CLR C
		mCtx->m_current_line_out.resize(1);//指令长度
		mCtx->m_current_line_out[0] = 0xB3;
	}
	else
	{
		// CLR bit
		mCtx->m_current_line_out.resize(2);//指令长度
		mCtx->m_current_line_out[0] = 0xB2;
		mCtx->m_current_line_out[1] = StrToHex(mCtx->m_current_line_words[1]);
	}
	
	return 0;
}

int DA_CodeGen(T_ASM_CONTEXT *mCtx)
{
	// DA A;
	mCtx->m_current_line_out.resize(1);//指令长度
	mCtx->m_current_line_out[0] = 0xD4;
	return 0;
}

int DEC_CodeGen(T_ASM_CONTEXT *mCtx)
{
	
	/// DEC A
	/// DEC Rn
	/// DEC direct
	/// DEC @Ri

	if (mCtx->m_current_line_words[1]=="A")	
	{
		// DEC A
		mCtx->m_current_line_out.resize(1);//指令长度
		mCtx->m_current_line_out[0] = 0x14;
		return 0;
	}
	else if (mCtx->m_current_line_words[1][0]=='R')
	{
		// DEC Rn
		mCtx->m_current_line_out.resize(1);//指令长度
		mCtx->m_current_line_out[0] = 0x18;
		mCtx->m_current_line_out[0] |= (0x7&StrToHex(mCtx->m_current_line_words[1].c_str()+1));
		return 0;
	}
	else if (mCtx->m_current_line_words[1]=="@")
	{
		//DEC @Ri
		mCtx->m_current_line_out.resize(1);//指令长度
		mCtx->m_current_line_out[0] = 0x16;
		mCtx->m_current_line_out[0] |= (1&StrToHex(mCtx->m_current_line_words[2].c_str()+1));
		return 0;
	}
	else
	{
		//DEC direct
		mCtx->m_current_line_out.resize(2);//指令长度
		mCtx->m_current_line_out[0] = 0x15;
		mCtx->m_current_line_out[1] = StrToHex(mCtx->m_current_line_words[1]);
		return 0;
	}
}



int DIV_CodeGen(T_ASM_CONTEXT *mCtx)
{

	/// DIV AB
	if (mCtx->m_current_line_words[1]=="AB")	
	{
		// DEC A
		mCtx->m_current_line_out.resize(1);//指令长度
		mCtx->m_current_line_out[0] = 0x84;
		return 0;
	}
	else
	{
		ASSERT_8051(0,"DIV AB");
		return 2;
	}
}


int DJNZ_CodeGen(T_ASM_CONTEXT *mCtx)
{
	// compare and jump if not equal
	// DJNZ direct,rel
	// DJNZ Rn,rel
	
	ASSERT_8051(mCtx->m_current_line_words.size()>=4, "DJNZ format error");
	
	if (mCtx->m_current_line_words[1][0]=='R')
	{
		// DJNZ Rn,rel
		mCtx->m_current_line_out.resize(2);//指令长度
		mCtx->m_current_line_out[0] = 0xD8;
		mCtx->m_current_line_out[0] |= (0x7 & StrToHex(mCtx->m_current_line_words[1].c_str()+1));
		//mCtx->m_current_line_out[1] = StrToHex(mCtx->m_current_line_words[3]);
		unsigned long mAbsAddr=0;
		int ret = LABEL_Check(mCtx, mCtx->m_current_line_words[3],mAbsAddr);
		if (ret==0)//找到标签
		{
			long mRelAddr = mAbsAddr - mCtx->m_current_address-2;
			mCtx->m_current_line_out[1] = mRelAddr;
			return 0;
		}
		return 1;
	}
	else
	{
		// DJNZ direct,rel
		mCtx->m_current_line_out.resize(3);//指令长度
		mCtx->m_current_line_out[0] = 0xD5;
		mCtx->m_current_line_out[1] = StrToHex(mCtx->m_current_line_words[1]);
		unsigned long mAbsAddr=0;
		int ret = LABEL_Check(mCtx, mCtx->m_current_line_words[3],mAbsAddr);
		if (ret==0)//找到标签
		{
			long mRelAddr = mAbsAddr - mCtx->m_current_address-3;
			mCtx->m_current_line_out[2] = mRelAddr;
			return 0;
		}
		return 1;
	}
}


int INC_CodeGen(T_ASM_CONTEXT *mCtx)
{
	
	/// INC A
	/// INC Rn
	/// INC direct
	/// INC @Ri
	/// INC DPTR
	
	if (mCtx->m_current_line_words[1]=="A")	
	{
		// INC A
		mCtx->m_current_line_out.resize(1);//指令长度
		mCtx->m_current_line_out[0] = 0x04;
		return 0;
	}
	else if (mCtx->m_current_line_words[1][0]=='R')
	{
		// INC Rn
		mCtx->m_current_line_out.resize(1);//指令长度
		mCtx->m_current_line_out[0] = 0x08;
		mCtx->m_current_line_out[0] |= (0x7&StrToHex(mCtx->m_current_line_words[1].c_str()+1));
		return 0;
	}
	else if (mCtx->m_current_line_words[1]=="@")
	{
		//INC @Ri
		mCtx->m_current_line_out.resize(1);//指令长度
		mCtx->m_current_line_out[0] = 0x06;
		mCtx->m_current_line_out[0] |= (1&StrToHex(mCtx->m_current_line_words[2].c_str()+1));
		return 0;
	}
	else if (mCtx->m_current_line_words[1]=="DPTR")
	{
		//INC DPTR
		mCtx->m_current_line_out.resize(1);//指令长度
		mCtx->m_current_line_out[0] = 0xA3;
		return 0;
	}
	else
	{
		//INC direct
		mCtx->m_current_line_out.resize(2);//指令长度
		mCtx->m_current_line_out[0] = 0x05;
		mCtx->m_current_line_out[1] = StrToHex(mCtx->m_current_line_words[1]);
		return 0;
	}
}

int JB_CodeGen(T_ASM_CONTEXT *mCtx)
{
	/// JB bit,rel
	mCtx->m_current_line_out.resize(3);//指令长度
	mCtx->m_current_line_out[0] = 0x20;
	mCtx->m_current_line_out[1] = StrToHex(mCtx->m_current_line_words[1].c_str());
	unsigned long mAbsAddr=0;
	int ret = LABEL_Check(mCtx, mCtx->m_current_line_words[3], mAbsAddr);
	if (ret==0)//找到标签
	{
		long mRelAddr = mAbsAddr - mCtx->m_current_address-3;
		mCtx->m_current_line_out[2] = mRelAddr;
		return 0;
	}
	return 1;
}


int JBC_CodeGen(T_ASM_CONTEXT *mCtx)
{
	/// JBC bit,rel
	mCtx->m_current_line_out.resize(3);//指令长度
	mCtx->m_current_line_out[0] = 0x10;
	mCtx->m_current_line_out[1] = StrToHex(mCtx->m_current_line_words[1].c_str());
	unsigned long mAbsAddr=0;
	int ret = LABEL_Check(mCtx, mCtx->m_current_line_words[3], mAbsAddr);
	if (ret==0)//找到标签
	{
		long mRelAddr = mAbsAddr - mCtx->m_current_address-3;
		mCtx->m_current_line_out[2] = mRelAddr;
		return 0;
	}
	return 1;
}


int JC_CodeGen(T_ASM_CONTEXT *mCtx)
{
	/// JC rel
	mCtx->m_current_line_out.resize(2);//指令长度
	mCtx->m_current_line_out[0] = 0x40;
	unsigned long mAbsAddr=0;
	int ret = LABEL_Check(mCtx, mCtx->m_current_line_words[1],mAbsAddr);
	if (ret==0)//找到标签
	{
		long mRelAddr = mAbsAddr - mCtx->m_current_address-2;
		mCtx->m_current_line_out[1] = mRelAddr;
		return 0;
	}
	return 1;
}


int JMP_CodeGen(T_ASM_CONTEXT *mCtx)
{
	/// JMP @A+DPTR
	mCtx->m_current_line_out.resize(1);//指令长度
	mCtx->m_current_line_out[0] = 0x73;
	return 0;
}


int JNB_CodeGen(T_ASM_CONTEXT *mCtx)
{
	/// JNB bit,rel
	mCtx->m_current_line_out.resize(3);//指令长度
	mCtx->m_current_line_out[0] = 0x30;
	mCtx->m_current_line_out[1] = StrToHex(mCtx->m_current_line_words[1].c_str());
	unsigned long mAbsAddr=0;
	int ret = LABEL_Check(mCtx, mCtx->m_current_line_words[3], mAbsAddr);
	if (ret==0)//找到标签
	{
		long mRelAddr = mAbsAddr - mCtx->m_current_address-3;
		mCtx->m_current_line_out[2] = mRelAddr;
		return 0;
	}
	return 1;
}

int JNC_CodeGen(T_ASM_CONTEXT *mCtx)
{
	/// JNC rel
	mCtx->m_current_line_out.resize(2);//指令长度
	mCtx->m_current_line_out[0] = 0x50;
	unsigned long mAbsAddr=0;
	int ret = LABEL_Check(mCtx, mCtx->m_current_line_words[1],mAbsAddr);
	if (ret==0)//找到标签
	{
		long mRelAddr = mAbsAddr - mCtx->m_current_address-2;
		mCtx->m_current_line_out[1] = mRelAddr;
		return 0;
	}
	return 1;
}


int JNZ_CodeGen(T_ASM_CONTEXT *mCtx)
{
	/// JNZ rel
	mCtx->m_current_line_out.resize(2);//指令长度
	mCtx->m_current_line_out[0] = 0x70;
	unsigned long mAbsAddr=0;
	int ret = LABEL_Check(mCtx, mCtx->m_current_line_words[1],mAbsAddr);
	if (ret==0)//找到标签
	{
		long mRelAddr = mAbsAddr - mCtx->m_current_address-2;
		mCtx->m_current_line_out[1] = mRelAddr;
		return 0;
	}
	return 1;
}

int JZ_CodeGen(T_ASM_CONTEXT *mCtx)
{
	/// JZ rel
	mCtx->m_current_line_out.resize(2);//指令长度
	mCtx->m_current_line_out[0] = 0x60;
	unsigned long mAbsAddr=0;
	int ret = LABEL_Check(mCtx, mCtx->m_current_line_words[1],mAbsAddr);
	if (ret==0)//找到标签
	{
		long mRelAddr = mAbsAddr - mCtx->m_current_address-2;
		mCtx->m_current_line_out[1] = mRelAddr;
		return 0;
	}
	return 1;
}

int LCALL_CodeGen(T_ASM_CONTEXT *mCtx)
{
	/// LCALL addr16_LABEL
	mCtx->m_current_line_out.resize(3);//指令长度
	//周期2
	mCtx->m_current_line_out[0] = 0x12;
	std::map<std::string, unsigned long>::iterator it;
	it = mCtx->m_label_address.find(mCtx->m_current_line_words[1]);
	if (it!=mCtx->m_label_address.end())
	{
		///标签地址已找到
		unsigned long addr = it->second;
		mCtx->m_current_line_out[2] = (addr&0xff);
		mCtx->m_current_line_out[1] = ((addr>>8)&0xff);
		return 0;
	}
	///没有标签，直接返回，标记为需要第二遍操作
	return 1;
}

int LJMP_CodeGen(T_ASM_CONTEXT *mCtx)
{
	//mCtx->m_current_line_worlds
	/// LJMP LABEL
	mCtx->m_current_line_out.resize(3);//指令长度
	//周期2
	mCtx->m_current_line_out[0] = 0x02;
	std::map<std::string, unsigned long>::iterator it;
	it = mCtx->m_label_address.find(mCtx->m_current_line_words[1]);
	if (it!=mCtx->m_label_address.end())
	{
		///标签地址已找到
		unsigned long addr = it->second;
		mCtx->m_current_line_out[1] = (addr>>8);
		mCtx->m_current_line_out[2] = (addr&0xff);
		return 0;
	}
	///没有标签，直接返回，标记为需要第二遍操作
	return 1;
}


int MOV_CodeGen(T_ASM_CONTEXT *mCtx)
{
	/// MOV A,Rn
	/// MOV A,direct
	/// MOV A,@Ri
	/// MOV A,#data

	/// MOV Rn,A
	/// MOV Rn,direct
	/// MOV Rn,#data


	/// MOV direct,A
	/// MOV direct,Rn
	/// MOV direct,@Ri
	/// MOV direct,#data
	/// MOV direct,direct
	
	/// MOV @Ri,A
	/// MOV @Ri,direct
	/// MOV @Ri,#data

	/// MOV C,bit
	/// MOV bit,C

	/// MOV DPTR,#data16

	ASSERT_8051(mCtx->m_current_line_words.size()>=4,"MOV error");

	if (mCtx->m_current_line_words[1]=="DPTR")
	{
		/// MOV DPTR,#data16
		mCtx->m_current_line_out.resize(3);//指令长度
		mCtx->m_current_line_out[0] = 0x90;
		mCtx->m_current_line_out[1] = (StrToHex(mCtx->m_current_line_words[4])>>8);
		mCtx->m_current_line_out[2] = (StrToHex(mCtx->m_current_line_words[4])&0xff);
		return 0;
	}
	else if (mCtx->m_current_line_words[1]=="A")
	{
		if (mCtx->m_current_line_words[3]=="@")
		{
			/// MOV A,@Ri
			mCtx->m_current_line_out.resize(1);//指令长度
			mCtx->m_current_line_out[0] = 0xE6;
			mCtx->m_current_line_out[0] |= (0x1&StrToHex(mCtx->m_current_line_words[4].c_str()+1));
			return 0;
		}
		else if (mCtx->m_current_line_words[3][0]=='R')
		{
			/// MOV A,Rn
			mCtx->m_current_line_out.resize(1);//指令长度
			mCtx->m_current_line_out[0] = 0xE8;
			mCtx->m_current_line_out[0] |= (0x7&StrToHex(mCtx->m_current_line_words[3].c_str()+1));
			return 0;
		}
		else if (mCtx->m_current_line_words[3]=="#")
		{
			/// MOV A,#data
			mCtx->m_current_line_out.resize(2);//指令长度
			mCtx->m_current_line_out[0] = 0x74;
			mCtx->m_current_line_out[1] = StrToHex(mCtx->m_current_line_words[4]);
			return 0;
		}
		else 
		{
			/// MOV A,direct
			mCtx->m_current_line_out.resize(2);//指令长度
			mCtx->m_current_line_out[0] = 0xE5;
			mCtx->m_current_line_out[1] = StrToHex(mCtx->m_current_line_words[3]);
			return 0;
		}
	}
	else if (mCtx->m_current_line_words[1][0]=='R')
	{
		if (mCtx->m_current_line_words[3]=="A")
		{

			/// MOV Rn,A
			mCtx->m_current_line_out.resize(1);//指令长度
			mCtx->m_current_line_out[0] = 0xf8;
			mCtx->m_current_line_out[0] |= (0x7&StrToHex(mCtx->m_current_line_words[1].c_str()+1));
			return 0;
		}
		else if (mCtx->m_current_line_words[3]=="#")
		{
			/// MOV Rn,#data
			mCtx->m_current_line_out.resize(2);//指令长度
			mCtx->m_current_line_out[0] = 0x78;
			mCtx->m_current_line_out[0] |= (0x7&StrToHex(mCtx->m_current_line_words[1].c_str()+1));
			mCtx->m_current_line_out[1] = StrToHex(mCtx->m_current_line_words[4]);
			return 0;
		}
		else
		{
			/// MOV Rn,direct
			mCtx->m_current_line_out.resize(2);//指令长度
			mCtx->m_current_line_out[0] = 0xA8;
			mCtx->m_current_line_out[0] |= (0x7&StrToHex(mCtx->m_current_line_words[1].c_str()+1));
			mCtx->m_current_line_out[1] = StrToHex(mCtx->m_current_line_words[3]);
			return 0;
		}
	}
	else if (mCtx->m_current_line_words[1]=="@")
	{
		if (mCtx->m_current_line_words[4]=="A")
		{
			/// MOV @Ri,A
			mCtx->m_current_line_out.resize(1);//指令长度
			mCtx->m_current_line_out[0] = 0xf6;
			mCtx->m_current_line_out[0] |= (0x1&StrToHex(mCtx->m_current_line_words[2].c_str()+1));
			return 0;
		}
		else if (mCtx->m_current_line_words[4]=="#")
		{
			/// MOV @Ri,#data
			mCtx->m_current_line_out.resize(2);//指令长度
			mCtx->m_current_line_out[0] = 0x76;
			mCtx->m_current_line_out[0] |= (0x1&StrToHex(mCtx->m_current_line_words[2].c_str()+1));
			mCtx->m_current_line_out[1] = StrToHex(mCtx->m_current_line_words[5]);
			return 0;
		}
		else
		{
			/// MOV @Ri,direct
			mCtx->m_current_line_out.resize(2);//指令长度
			mCtx->m_current_line_out[0] = 0xA6;
			mCtx->m_current_line_out[0] |= (0x1&StrToHex(mCtx->m_current_line_words[2].c_str()+1));
			mCtx->m_current_line_out[1] = StrToHex(mCtx->m_current_line_words[4]);
			return 0;
		}
	}
	else if (mCtx->m_current_line_words[1]=="C")
	{
		/// MOV C,bit
		mCtx->m_current_line_out.resize(2);//指令长度
		mCtx->m_current_line_out[0] = 0xA2;
		mCtx->m_current_line_out[1] = (StrToHex(mCtx->m_current_line_words[3]));
		return 0;
	}
	else if (mCtx->m_current_line_words[3]=="C")
	{
		/// MOV bit,C
		mCtx->m_current_line_out.resize(2);//指令长度
		mCtx->m_current_line_out[0] = 0x92;
		mCtx->m_current_line_out[1] = (StrToHex(mCtx->m_current_line_words[1]));
		return 0;
	}
	else if (mCtx->m_current_line_words[3]=="A")
	{
		/// MOV direct,A
		mCtx->m_current_line_out.resize(2);//指令长度
		mCtx->m_current_line_out[0] = 0xf5;
		mCtx->m_current_line_out[1] = (StrToHex(mCtx->m_current_line_words[1]));
		return 0;
	}
	else if (mCtx->m_current_line_words[3][0]=='R')
	{
		/// MOV direct,Rn
		mCtx->m_current_line_out.resize(2);//指令长度
		mCtx->m_current_line_out[0] = 0x88;
		mCtx->m_current_line_out[0] |= (0x7&StrToHex(mCtx->m_current_line_words[3].c_str()+1));
		mCtx->m_current_line_out[1] = (StrToHex(mCtx->m_current_line_words[1]));
		return 0;
	}	
	else if (mCtx->m_current_line_words[3][0]=='@')
	{
		/// MOV direct,@Ri
		mCtx->m_current_line_out.resize(2);//指令长度
		mCtx->m_current_line_out[0] = 0x86;
		mCtx->m_current_line_out[0] |= (0x1&StrToHex(mCtx->m_current_line_words[4].c_str()+1));
		mCtx->m_current_line_out[1] = (StrToHex(mCtx->m_current_line_words[1]));
		return 0;
	}
	else if (mCtx->m_current_line_words[3]=="#")
	{
		/// MOV direct,#data
		mCtx->m_current_line_out.resize(3);//指令长度
		mCtx->m_current_line_out[0] = 0x75;
		mCtx->m_current_line_out[1] =StrToHex(mCtx->m_current_line_words[1]);
		mCtx->m_current_line_out[2] = (StrToHex(mCtx->m_current_line_words[4]));
		return 0;
	}
	else
	{
		/// MOV direct,direct
		mCtx->m_current_line_out.resize(3);//指令长度
		mCtx->m_current_line_out[0] = 0x85;
		mCtx->m_current_line_out[1] =(StrToHex(mCtx->m_current_line_words[3]));
		mCtx->m_current_line_out[2] = StrToHex(mCtx->m_current_line_words[1]);
		return 0;
	}
	



	return 1;
}



int MOVC_CodeGen(T_ASM_CONTEXT *mCtx)
{
	/// MOVC A,@A+DPTR
	/// MOVC,A,@A+PC

	ASSERT_8051(mCtx->m_current_line_words.size()==7,"MOVC error");

	if (mCtx->m_current_line_words[6]=="DPTR")
	{
		mCtx->m_current_line_out.resize(1);//指令长度
		mCtx->m_current_line_out[0] = 0x93;
	}
	else if (mCtx->m_current_line_words[6]=="PC")
	{
		mCtx->m_current_line_out.resize(1);//指令长度
		mCtx->m_current_line_out[0] = 0x83;
	}

	ASSERT_8051(mCtx->m_current_line_words.size()==7,"MOVC error");

	return 0;
}


int MOVX_CodeGen(T_ASM_CONTEXT *mCtx)
{
	/// MOVX A,@Ri
	/// MOVX A,@DPTR
	/// MOVX @Ri,A
	/// MOVX @DPTR,A

	
	ASSERT_8051(mCtx->m_current_line_words.size()==5,"MOVX error");
	
	if (mCtx->m_current_line_words[1]=="A")
	{
		ASSERT_8051(mCtx->m_current_line_words[3]=="@","MOVX error");
		if (mCtx->m_current_line_words[4][0]=='R')
		{
			/// MOVX A,@Ri
			mCtx->m_current_line_out.resize(1);//指令长度
			mCtx->m_current_line_out[0] = 0xe2;
			mCtx->m_current_line_out[0] |= (0x1&StrToHex(mCtx->m_current_line_words[4].c_str()+1));
			return 0;
		}
		if (mCtx->m_current_line_words[4]=="DPTR")
		{
			/// MOVX A,@DPTR
			mCtx->m_current_line_out.resize(1);//指令长度
			mCtx->m_current_line_out[0] = 0xe0;
			return 0;
		}
		else
		{
			ASSERT_8051(0,"MOVX error");
		}
	}
	else if (mCtx->m_current_line_words[4]=="A")
	{
		ASSERT_8051(mCtx->m_current_line_words[1]=="@","MOVX error");
		if (mCtx->m_current_line_words[2][0]=='R')
		{
			/// MOVX @Ri,A
			mCtx->m_current_line_out.resize(1);//指令长度
			mCtx->m_current_line_out[0] = 0xf2;
			mCtx->m_current_line_out[0] |= (0x1&StrToHex(mCtx->m_current_line_words[2].c_str()+1));
			return 0;
		}
		if (mCtx->m_current_line_words[2]=="DPTR")
		{
			/// MOVX @DPTR,A
			mCtx->m_current_line_out.resize(1);//指令长度
			mCtx->m_current_line_out[0] = 0xf0;
			return 0;
		}
		else
		{
			ASSERT_8051(0,"MOVX error");
		}
	}
	
	return 0;
}



int MUL_CodeGen(T_ASM_CONTEXT *mCtx)
{
	
	/// MUL AB
	if (mCtx->m_current_line_words[1]=="AB")	
	{
		// MUL AB
		mCtx->m_current_line_out.resize(1);//指令长度
		mCtx->m_current_line_out[0] = 0xA4;
		return 0;
	}
	else
	{
		ASSERT_8051(0,"MUL AB");
		return 2;
	}
}


int NOP_CodeGen(T_ASM_CONTEXT *mCtx)
{
	mCtx->m_current_line_out.resize(1);//指令长度
	mCtx->m_current_line_out[0] = 0x00;
	return 0;
}

int ORL_CodeGen(T_ASM_CONTEXT *mCtx)
{
	/// ORL A,Rn
	/// ORL A,direct
	/// ORL A,@Ri
	/// ORL A,#data

	/// ORL direct,A
	/// ORL direct, #data
	/// ORL C,bit
	/// ORL C,/bit

	if (mCtx->m_current_line_words[1]=="A")
	{
		if (mCtx->m_current_line_words[3]=="#")
		{
			/// ORL A,#data
			mCtx->m_current_line_out.resize(2);//指令长度
			mCtx->m_current_line_out[0] = 0x44;
			mCtx->m_current_line_out[1] = StrToHex(mCtx->m_current_line_words[4]);
			return 0;
		}
		else if (mCtx->m_current_line_words[3]=="@")
		{
			/// ORL A,@Ri
			mCtx->m_current_line_out.resize(1);//指令长度
			mCtx->m_current_line_out[0] = 0x46;
			mCtx->m_current_line_out[0] |= (1&StrToHex(mCtx->m_current_line_words[4].c_str()+1));
			return 0;
			
		}
		else if (mCtx->m_current_line_words[3][0]=='R')
		{
			/// ORL A,Rn
			mCtx->m_current_line_out.resize(1);//指令长度
			mCtx->m_current_line_out[0] = 0x48;
			mCtx->m_current_line_out[0] |= (7&StrToHex(mCtx->m_current_line_words[3].c_str()+1));
			return 0;
		}
		else
		{
			/// ORL A,direct
			mCtx->m_current_line_out.resize(2);//指令长度
			mCtx->m_current_line_out[0] = 0x45;
			mCtx->m_current_line_out[1] = StrToHex(mCtx->m_current_line_words[3]);
			return 0;
		}
	}
	else if (mCtx->m_current_line_words[1]=="C")
	{
		if (mCtx->m_current_line_words[3]=="/")
		{
			/// ORL C,/bit
			mCtx->m_current_line_out.resize(2);//指令长度
			mCtx->m_current_line_out[0] = 0xa0;
			mCtx->m_current_line_out[1] = StrToHex(mCtx->m_current_line_words[4]);
			return 0;
		}
		else
		{
			/// ORL C,bit
			mCtx->m_current_line_out.resize(2);//指令长度
			mCtx->m_current_line_out[0] = 0x72;
			mCtx->m_current_line_out[1] = StrToHex(mCtx->m_current_line_words[3]);
			return 0;
		}
	}
	else if (mCtx->m_current_line_words[3]=="A")
	{
		/// ORL direct,A
		mCtx->m_current_line_out.resize(2);//指令长度
		mCtx->m_current_line_out[0] = 0x42;
		mCtx->m_current_line_out[1] = StrToHex(mCtx->m_current_line_words[1]);
		return 0;
	}
	else if (mCtx->m_current_line_words[3]=="#")
	{
		/// ORL direct, #data
		mCtx->m_current_line_out.resize(3);//指令长度
		mCtx->m_current_line_out[0] = 0x43;
		mCtx->m_current_line_out[1] = StrToHex(mCtx->m_current_line_words[1]);
		mCtx->m_current_line_out[2] = StrToHex(mCtx->m_current_line_words[4]);
		return 0;
	}


	ASSERT_8051(0,"ORL error");
	return -1;
}

int POP_CodeGen(T_ASM_CONTEXT *mCtx)
{
	/// POP direct
	mCtx->m_current_line_out.resize(2);//指令长度
	mCtx->m_current_line_out[0] = 0xd0;
	mCtx->m_current_line_out[1] = StrToHex(mCtx->m_current_line_words[1]);
	return 0;
}

int PUSH_CodeGen(T_ASM_CONTEXT *mCtx)
{
	/// PUSH direct
	mCtx->m_current_line_out.resize(2);//指令长度
	mCtx->m_current_line_out[0] = 0xC0;
	mCtx->m_current_line_out[1] = StrToHex(mCtx->m_current_line_words[1]);
	return 0;
}

int RET_CodeGen(T_ASM_CONTEXT *mCtx)
{
	/// RET
	mCtx->m_current_line_out.resize(1);//指令长度
	mCtx->m_current_line_out[0] = 0x22;
	return 0;
}

int RETI_CodeGen(T_ASM_CONTEXT *mCtx)
{
	/// RETI
	mCtx->m_current_line_out.resize(1);//指令长度
	mCtx->m_current_line_out[0] = 0x32;
	return 0;
}

int RL_CodeGen(T_ASM_CONTEXT *mCtx)
{
	/// RL A
	mCtx->m_current_line_out.resize(1);//指令长度
	mCtx->m_current_line_out[0] = 0x23;
	return 0;
}

int RLC_CodeGen(T_ASM_CONTEXT *mCtx)
{
	/// RLC A
	mCtx->m_current_line_out.resize(1);//指令长度
	mCtx->m_current_line_out[0] = 0x33;
	return 0;
}


int RR_CodeGen(T_ASM_CONTEXT *mCtx)
{
	/// RR A
	mCtx->m_current_line_out.resize(1);//指令长度
	mCtx->m_current_line_out[0] = 0x03;
	return 0;
}

int RRC_CodeGen(T_ASM_CONTEXT *mCtx)
{
	/// RRC A
	mCtx->m_current_line_out.resize(1);//指令长度
	mCtx->m_current_line_out[0] = 0x13;
	return 0;
}

int SETB_CodeGen(T_ASM_CONTEXT *mCtx)
{
	/// SETB C
	/// SETB bit
	if (mCtx->m_current_line_words[1]=="C")
	{
		/// SETB C
		mCtx->m_current_line_out.resize(1);//指令长度
		mCtx->m_current_line_out[0] = 0xD3;
		return 0;
	}
	else
	{
		/// SETB bit
		mCtx->m_current_line_out.resize(2);//指令长度
		mCtx->m_current_line_out[0] = 0xD2;
		mCtx->m_current_line_out[1] = StrToHex(mCtx->m_current_line_words[1]);;
		return 0;
	}

	return 0;
}

int SJMP_CodeGen(T_ASM_CONTEXT *mCtx)
{
	// compare and jump if not equal
	// SJMP rel

	ASSERT_8051(mCtx->m_current_line_words.size()==2, "SJMP format error");
	

	mCtx->m_current_line_out.resize(2);//指令长度
	mCtx->m_current_line_out[0] = 0x80;
	unsigned long mAbsAddr=0;
	int ret = LABEL_Check(mCtx, mCtx->m_current_line_words[1],mAbsAddr);
	if (ret==0)//找到标签
	{
		long mRelAddr = mAbsAddr - mCtx->m_current_address-2;
		mCtx->m_current_line_out[1] = mRelAddr;
		return 0;
	}
	return 1;
}



int SUBB_CodeGen(T_ASM_CONTEXT *mCtx)
{

	/// SUBB A,Rn
	/// SUBB A,direct
	/// SUBB A,@Ri
	/// SUBB A,#data

	
	if (mCtx->m_current_line_words[3][0]=='R')	
	{
		// SUBB A, Rn  ---1
		mCtx->m_current_line_out.resize(1);//指令长度
		mCtx->m_current_line_out[0] = 0x98;
		mCtx->m_current_line_out[0] |= (0x7&StrToHex(mCtx->m_current_line_words[3].c_str()+1));
		return 0;
	}
	else if (mCtx->m_current_line_words[3][0]=='@')
	{
		/// FIXME TODO 如果Ri不是R0 R1,则应该报错
		// SUBB A,@Ri ---1; R0 R1
		mCtx->m_current_line_out.resize(1);//指令长度
		mCtx->m_current_line_out[0] = 0x96;
		mCtx->m_current_line_out[0] |= (0x1&StrToHex(mCtx->m_current_line_words[4].c_str()+1));
		return 0;
	}
	else if (mCtx->m_current_line_words[3][0]=='#')
	{
		//USBB A,#data
		mCtx->m_current_line_out.resize(2);//指令长度
		mCtx->m_current_line_out[0] = 0x94;
		mCtx->m_current_line_out[1] = StrToHex(mCtx->m_current_line_words[4]);
		return 0;
	}
	else
	{
		//SUBB A,direct
		mCtx->m_current_line_out.resize(2);//指令长度
		mCtx->m_current_line_out[0] = 0x95;
		mCtx->m_current_line_out[1] = StrToHex(mCtx->m_current_line_words[3]);
		return 0;
	}
}



int SWAP_CodeGen(T_ASM_CONTEXT *mCtx)
{
	///SWAP A
	mCtx->m_current_line_out.resize(1);//指令长度
	mCtx->m_current_line_out[0] = 0xC4;
	return 0;
}



int XCH_CodeGen(T_ASM_CONTEXT *mCtx)
{
	
	/// XCH A,Rn
	/// XCH A,direct
	/// XCH A,@Ri
	
	if (mCtx->m_current_line_words[3][0]=='R')	
	{
		// XCH A, Rn  ---1
		mCtx->m_current_line_out.resize(1);//指令长度
		mCtx->m_current_line_out[0] = 0xC8;
		mCtx->m_current_line_out[0] |= (0x7&StrToHex(mCtx->m_current_line_words[3].c_str()+1));
		return 0;
	}
	else if (mCtx->m_current_line_words[3][0]=='@')
	{
		/// FIXME TODO 如果Ri不是R0 R1,则应该报错
		// XCH A,@Ri ---1; R0 R1
		mCtx->m_current_line_out.resize(1);//指令长度
		mCtx->m_current_line_out[0] = 0xC6;
		mCtx->m_current_line_out[0] |= (0x1&StrToHex(mCtx->m_current_line_words[4].c_str()+1));
		return 0;
	}
	else
	{
		//XCH A,direct
		mCtx->m_current_line_out.resize(2);//指令长度
		mCtx->m_current_line_out[0] = 0xC5;
		mCtx->m_current_line_out[1] = StrToHex(mCtx->m_current_line_words[3]);
		return 0;
	}
}

int XCHD_CodeGen(T_ASM_CONTEXT *mCtx)
{
	/// XCHD A,@Ri
	mCtx->m_current_line_out.resize(1);//指令长度
	mCtx->m_current_line_out[0] = 0xD6;
	mCtx->m_current_line_out[0] |= (1&StrToHex(mCtx->m_current_line_words[4].c_str()+1));
	return 0;
}


int XRL_CodeGen(T_ASM_CONTEXT *mCtx)
{
	/// XRL A,Rn
	mCtx->m_current_line_out.resize(1);//指令长度
	mCtx->m_current_line_out[0] = 0x68;
	mCtx->m_current_line_out[0] |= (7&StrToHex(mCtx->m_current_line_words[3].c_str()+1));
	return 0;
}

int END_CodeGen(T_ASM_CONTEXT *mCtx)
{
	
	
	return 0;
}

int ORG_CodeGen(T_ASM_CONTEXT *mCtx)
{
	//assert(mCtx->m_current_line_worlds.size()==2);
	if (mCtx->m_current_line_words.size()>1)
	{
		mCtx->m_current_address  = 
		StrToHex(mCtx->m_current_line_words[1]);
	}
	
	return 0;
}

int asm8051_context_init(T_ASM_CONTEXT *mCtx)
{
	//////////////////////////////////////////////////////////////////////////
	/// 已完成指令
	mCtx->m_line_key_word_ptr["ORG"] = ORG_CodeGen;

	mCtx->m_line_key_word_ptr["ACALL"] = ACALL_CodeGen;
	mCtx->m_line_key_word_ptr["ADD"] = ADD_CodeGen;
	mCtx->m_line_key_word_ptr["ADDC"] = ADDC_CodeGen;
	mCtx->m_line_key_word_ptr["AJMP"] = AJMP_CodeGen;
	mCtx->m_line_key_word_ptr["ANL"] = ANL_CodeGen;
	mCtx->m_line_key_word_ptr["CJNE"] = CJNE_CodeGen;
	mCtx->m_line_key_word_ptr["CLR"] = CLR_CodeGen;
	mCtx->m_line_key_word_ptr["CPL"] = CPL_CodeGen;	
	//////////////////////////////////////////////////////////////////////////
	//2015.7.22
	mCtx->m_line_key_word_ptr["DA"] = DA_CodeGen;
	mCtx->m_line_key_word_ptr["DEC"] = DEC_CodeGen;
	mCtx->m_line_key_word_ptr["DIV"] = DIV_CodeGen;
	mCtx->m_line_key_word_ptr["DJNZ"] = DJNZ_CodeGen;
	mCtx->m_line_key_word_ptr["INC"] = INC_CodeGen;
	mCtx->m_line_key_word_ptr["JB"] = JB_CodeGen;
	mCtx->m_line_key_word_ptr["JBC"] = JBC_CodeGen;
	mCtx->m_line_key_word_ptr["JC"] = JC_CodeGen;
	mCtx->m_line_key_word_ptr["JMP"] = JMP_CodeGen;
	
	mCtx->m_line_key_word_ptr["JNB"] = JNB_CodeGen;
	mCtx->m_line_key_word_ptr["JNC"] = JNC_CodeGen;
	mCtx->m_line_key_word_ptr["JNZ"] = JNZ_CodeGen;
	mCtx->m_line_key_word_ptr["JZ"] = JZ_CodeGen;
	mCtx->m_line_key_word_ptr["LCALL"] = LCALL_CodeGen;
	mCtx->m_line_key_word_ptr["LJMP"] = LJMP_CodeGen;
	mCtx->m_line_key_word_ptr["MOV"] = MOV_CodeGen;
	mCtx->m_line_key_word_ptr["MOVC"] = MOVC_CodeGen;
	mCtx->m_line_key_word_ptr["MOVX"] = MOVX_CodeGen;
	mCtx->m_line_key_word_ptr["MUL"] = MUL_CodeGen;
	mCtx->m_line_key_word_ptr["NOP"] = NOP_CodeGen;
	

	//////////////////////////////////////////////////////////////////////////
	//2015.7.23
	mCtx->m_line_key_word_ptr["ORL"] = ORL_CodeGen;
	mCtx->m_line_key_word_ptr["POP"] = POP_CodeGen;
	mCtx->m_line_key_word_ptr["PUSH"] = PUSH_CodeGen;
	mCtx->m_line_key_word_ptr["RET"] = RET_CodeGen;
	mCtx->m_line_key_word_ptr["RETI"] = RETI_CodeGen;
	mCtx->m_line_key_word_ptr["RL"] = RL_CodeGen;
	mCtx->m_line_key_word_ptr["RLC"] = RLC_CodeGen;
	mCtx->m_line_key_word_ptr["RR"] = RR_CodeGen;
	mCtx->m_line_key_word_ptr["RRC"] = RRC_CodeGen;
	mCtx->m_line_key_word_ptr["SETB"] = SETB_CodeGen;
	mCtx->m_line_key_word_ptr["SJMP"] = SJMP_CodeGen;
	mCtx->m_line_key_word_ptr["SUBB"] = SUBB_CodeGen;
	mCtx->m_line_key_word_ptr["SWAP"] = SWAP_CodeGen;
	mCtx->m_line_key_word_ptr["XCH"] = XCH_CodeGen;
	mCtx->m_line_key_word_ptr["XCHD"] = XCHD_CodeGen;
	mCtx->m_line_key_word_ptr["XRL"] = XRL_CodeGen;
	
		
		
	
	
			
					




	//////////////////////////////////////////////////////////////////////////

	mCtx->m_line_key_word_ptr["JMP"] = JMP_CodeGen;

	mCtx->m_line_key_word_ptr["END"] = END_CodeGen;
	mCtx->m_current_address = 0;
	return 0;
}
