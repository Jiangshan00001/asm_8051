cmake_minimum_required(VERSION 3.22)

#project name
project(asm8051)
#head file path
include_directories(api)
include_directories(.)
include_directories(misc misc/util)
include_directories(misc/util)
include_directories(lex_yacc)
include_directories(lex_yacc/ly)
include_directories(lex_yacc_adapt)
include_directories(context)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/../asm_table)
 
 
 
#patch for flexlexer.h
include_directories(C:/MinGW/msys/1.0/include/)
include_directories(..)
include_directories(/include/)


include_directories(${CMAKE_CURRENT_BINARY_DIR}/lex_yacc)


find_package(BISON)
find_package(FLEX)



set(CMAKE_VERBOSE_MAKEFILE OFF)
set(BUILD_SHARED_LIBS OFF)

#source directory

aux_source_directory(. SRC_LISTA)
aux_source_directory(api SRC_LISTB)
aux_source_directory(lex_yacc SRC_LISTC)
aux_source_directory(${CMAKE_CURRENT_BINARY_DIR}/lex_yacc SRC_LISTD)
aux_source_directory(context SRC_LISTE)
aux_source_directory(lex_yacc_adapt SRC_LISTF)
aux_source_directory(lex_yacc/ly SRC_LISTG)

# 添加子目录misc
add_subdirectory(misc)
add_subdirectory(lex_yacc)


#aux_source_directory(. SRC_LISTA)
#set(CMAKE_EXE_LINKER_FLAGS "-Wl,-Map=output.map" )
#static link 
if(MSVC)
add_compile_options(
	$<$<CONFIG:>:/MT>
	$<$<CONFIG:Debug>:/MTd>
	$<$<CONFIG:Release>:/MT>
)
else()
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -static")
endif()


add_executable(asm8051 ${SRC_LISTA} ${SRC_LISTB} ${SRC_LISTC}  ${SRC_LISTD} ${SRC_LISTE} ${SRC_LISTF} ${SRC_LISTG})
target_link_libraries(asm8051  misc)
target_link_libraries(asm8051  lex_yacc)
target_link_libraries(asm8051 asm_table)

install(TARGETS asm8051)


