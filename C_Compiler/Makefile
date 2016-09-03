SRC_FILES = main.c src/map.c src/linked_list.c src/string_util.c src/tests.c src/unit_test.c src/file_io.c src/token.c src/statement.c src/lex.c src/parser.c src/ast.c src/semantic.c src/memory.c src/compiler.c src/error.c src/pda.c

CC = gcc
COMPILER_FLAGS = -std=c99
LINKER_FLAGS = -Iheader

OBJ_NAME = COMPILER

all : 
	$(CC) $(SRC_FILES) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
