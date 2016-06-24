#ifndef MEMORY_H
#define MEMORY_H

#include "stdio.h"
#include "stdlib.h"
#include "map.h"

#define NUM_GLOBAL global_memory->num_values

Map *global_memory, *local_memory, *function_addresses, *datatypes;

typedef struct {
	int size; // Units of 16 bits
	int addr;
	int type;
} Memory_Address;

void init_mem();
void deinit_mem();
void clear_mem();

Memory_Address *create_mem_addr(int size, int addr, int type);
void destroy_mem_addr(Memory_Address *mem_addr);

int create_global_variable(const char *key, Memory_Address *addr);
int create_local_variable(const char *key, Memory_Address *addr);
int create_function(const char *key, Memory_Address *addr);

Memory_Address *get_global_addr(const char *key);
Memory_Address *get_local_addr(const char *key);
Memory_Address *get_function_addr(const char *key);
int *get_datatype_by_key(const char *key);

#endif // MEMORY_H
