#ifndef MEMORY_H
#define MEMORY_H

#include "stdio.h"
#include "stdlib.h"
#include "map.h"

#define NUM_GLOBAL global_memory->num_values

Map *global_memory, *local_memory, *function_addresses;

void init_mem();
void deinit_mem();

int create_global_variable(const char *key, int addr);
int create_local_variable(const char *key, int offset);
int create_function(const char *key, int addr);

int get_global_addr(const char *key);
int get_local_offset(const char *key);
int get_function_addr(const char *key);

#endif // MEMORY_H
