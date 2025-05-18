C_FLAGS = -Wall -std=c99 -Iraylib/include/ -Isrc/
LINK_FLAGS = -Lraylib/lib -lraylib -lwinmm -lopengl32 -lgdi32 -luser32 -lkernel32 -Xlinker /NODEFAULTLIB -lmsvcrt -lucrt -lmsvcprt -lvcruntime -lshell32

build/main.exe: src/main.c
	clang $(C_FLAGS) src/main.c -o build/main.exe $(LINK_FLAGS) 
