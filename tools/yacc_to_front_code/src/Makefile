SRCS= bison_file_io.cpp main_console.cpp split.cpp  replace.cpp yy_file_template.cpp

BUILD_DIR=../../../build/yacc_to_front_code

CXX=g++
INCS=  -I./  
CXX_FLAGS= 


OBJS_FILE = $(SRCS:%.cpp=%.o)
OBJS=$(addprefix $(BUILD_DIR)/,  $(OBJS_FILE))
BUILD_PATHTMP=$(dir $(abspath $(OBJS))) 
BUILD_PATH=$(sort $(BUILD_PATHTMP))

PROG=$(BUILD_DIR)/../yacc_to_front_code.exe

all: $(BUILD_PATH)  $(PROG)
	echo "finish!"
	
$(BUILD_PATH):
	mkdir -p $(BUILD_DIR)
	
	
$(BUILD_DIR)/%.o:%.cpp
	$(CXX) $(INCS) $(CXX_FLAGS) -c $< -o $@
	
$(PROG): $(OBJS)
	$(CXX) -static -g $^  -o $@	
	
	
clean:
	rm -rf $(BUILD_DIR)
	
.PHONY: all	 clean $(BUILD_PATH)