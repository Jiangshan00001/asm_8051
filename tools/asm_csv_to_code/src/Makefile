SRCS= csv_io.cpp main_console.cpp replace.cpp  trim.cpp split.cpp  csv_to_csv.cpp csv_to_dis.cpp csv_to_asmc.cpp csv_to_genasm.cpp

BUILD_DIR=../../../build/asm_csv_to_code

CXX=g++
INCS=  -I./  
CXX_FLAGS= 


OBJS_FILE = $(SRCS:%.cpp=%.o)
OBJS=$(addprefix $(BUILD_DIR)/,  $(OBJS_FILE))
BUILD_PATHTMP=$(dir $(abspath $(OBJS))) 
#BUILD_PATH=$(sort $(BUILD_PATHTMP))
BUILD_PATH=$(BUILD_DIR)

PROG=$(BUILD_DIR)/../asm_csv_to_code.exe

all: $(BUILD_PATH)  $(PROG)
	echo "finish!"
	
$(BUILD_PATH):
	mkdir -p $(BUILD_PATH)	
	
	
$(BUILD_DIR)/%.o:%.cpp
	$(CXX) $(INCS) $(CXX_FLAGS) -c $< -o $@
	
$(PROG): $(OBJS)
	$(CXX) -static -g $^  -o $@	
	
	
clean:
	rm -rf $(BUILD_DIR)
	
.PHONY: all clean  $(BUILD_PATH)	