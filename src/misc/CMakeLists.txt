aux_source_directory(cpp_lib  CPP_SRCS)
aux_source_directory(json_lib  JSON_SRCS)
aux_source_directory(util  UTIL_SRCS)

include_directories(cpp_lib)
include_directories(json_lib)
include_directories(util)
include_directories(C:/MinGW/msys/1.0/include/)



add_library(misc ${CPP_SRCS} ${JSON_SRCS} ${UTIL_SRCS} )
