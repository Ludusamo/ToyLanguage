#ifndef MEMORY_H
#define MEMORY_H

#include "stdio.h"
#include "stdlib.h"
#include "map.h"
#include "ast.h"

#define NUM_GLOBAL global_memory->num_values
#define NUM_FUNC function_addresses->num_values
#define MAX_DEPTH 255

Map *global_memory, *local_memory[MAX_DEPTH], *function_addresses, *datatypes;
int last_active_depth;

int NUM_LOCAL;

typedef struct {
	int size; // Units of 16 bits
	int addr;
	int type;
} Memory_Address;

typedef struct {
	int addr;
	ASTNode *arg_list;
	int return_type;
} Function;

void init_mem();
void deinit_mem();
void clear_mem();

Memory_Address *create_mem_addr(int size, int addr, int type);
Function *create_function(int addr, ASTNode *arg_list, int return_type);
void destroy_mem_addr(Memory_Address *mem_addr);

int create_global_variable(const char *key, Memory_Address *addr);
int create_local_variable(const char *key, Memory_Address *addr, int depth);
int add_function(const char *key, Function *function);

int descend_depth();
void exit_depth(int depth);
int is_depth_active(int depth);

Memory_Address *get_global_addr(const char *key);
Memory_Address *get_local_addr(const char *key, int depth);
Function *get_function(const char *key);
int *get_datatype_by_key(const char *key);

#endif // MEMORY_H
