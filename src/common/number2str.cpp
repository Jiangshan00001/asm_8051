#include "number2str.h"
#include <sstream>

std::string NumberToStr(long num)
{
    std::stringstream s;
    std::string ss;
    s<<std::hex<<num<<"H";
    return s.str();
}

