cmake_minimum_required(VERSION 3.22)

#project name
project(asm8051)


SET( CMAKE_VERBOSE_MAKEFILE on )
set(CMAKE_VERBOSE_MAKEFILE OFF)

#static link 
set(BUILD_SHARED_LIBS OFF)
if(MSVC)
add_compile_options(
	$<$<CONFIG:>:/MT>
	$<$<CONFIG:Debug>:/MTd>
	$<$<CONFIG:Release>:/MT>
)
else()
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -static")
endif()


add_subdirectory(tools)
add_subdirectory(asm_table)
add_subdirectory(src)

add_subdirectory(test)