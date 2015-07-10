SRC_FILES = main.c src/VirtualMachine.c src/Bytecode.c src/Debug.c

CC = g++
COMPILER_FLAGS = -w
LINKER_FLAGS = -Iheader

OBJ_NAME = lavm

all : 
	$(CC) $(SRC_FILES) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
