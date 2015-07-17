SRC_FILES = main.c src/VirtualMachine.c src/Bytecode.c src/Debug.c

CC = gcc
COMPILER_FLAGS = -std=c99
LINKER_FLAGS = -Iheader

OBJ_NAME = lavm

all : 
	$(CC) $(SRC_FILES) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
