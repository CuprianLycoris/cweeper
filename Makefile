C_FLAGS = -Wall -std=c99
LINK_FLAGS = 

build/main.exe: src/main.c
	clang $(C_FLAGS) src/main.c -o build/main.exe $(LINK_FLAGS) 
