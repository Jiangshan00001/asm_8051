find_package(BISON)
find_package(FLEX)

include_directories(C:/MinGW/msys/1.0/include/)
include_directories(.)
include_directories(../lex_yacc_adapt)
include_directories(../context)
include_directories(./ly)
include_directories(${CMAKE_CURRENT_BINARY_DIR})




BISON_TARGET(MyParser ly/parser.yy ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.h)
FLEX_TARGET(MyScanner ly/scanner.ll  ${CMAKE_CURRENT_BINARY_DIR}/scanner.cpp)
ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)

add_library(lex_yacc ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp ${CMAKE_CURRENT_BINARY_DIR}/scanner.cpp )
