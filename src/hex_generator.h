#ifndef hex_generator_h__
#define hex_generator_h__
#include <string>
#include <sstream>
#include <vector>
#include "asm_context.h"



typedef struct hex_block
{
    std::string m_hex;
    unsigned long m_address;
    unsigned char m_crc;
}hex_block;

/// 将字符串格式转为hex 文件格式的字符串
int hex_data_to_hex_file_format(unsigned long address, std::string hex_data, std::stringstream &file_out);
std::string hex_generator_str(T_ASM_CONTEXT *mCtx);


std::vector<hex_block> hex_file_to_hex_data(std::string hex_file_data);
std::string hex_data_to_hex_file(std::vector<hex_block> hex_data);

std::string ByteToStr(const unsigned char mC);
unsigned int StrToByte(std::string mC);


#endif // hex_generator_h__

