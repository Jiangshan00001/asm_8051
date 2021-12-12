

all:
	make -C src BUILD_BASE=$(shell pwd)/build
	#make -C test
check:
	make -C test BUILD_BASE=$(shell pwd)/build
clean:
	make -C src BUILD_BASE=$(shell pwd)/build clean
	#make -C test clean
