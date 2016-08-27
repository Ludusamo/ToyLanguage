#include "memory.h"

void init_mem() {
	global_memory = create_map();
	for (int i = 0; i < 255; i++)
		local_memory[i] = create_map();
	function_addresses = create_map();
	NUM_LOCAL = 0;
}

void deinit_mem() {
	destroy_map(global_memory);
	for (int i = 0; i < 255; i++)
		destroy_map(local_memory[i]);
	destroy_map(function_addresses);
}

void clear_mem() {
	rbt_destroy(global_memory->root);
	global_memory->root = 0;
	global_memory->num_values = 0;
	for (int i = 0; i < 255; i++) {
		rbt_destroy(local_memory[i]->root);
		local_memory[i]->root = 0;
		local_memory[i]->num_values = 0;
	}
	NUM_LOCAL = 0;
	rbt_destroy(function_addresses->root);
	function_addresses->root = 0;
	function_addresses->num_values = 0;
}

Memory_Address *create_mem_addr(int size, int addr, int type) {
	Memory_Address *mem_addr = malloc(sizeof(Memory_Address));
	mem_addr->size = size;
	mem_addr->addr = addr;
	mem_addr->type = type;
	return mem_addr;
}

Function *create_function(int addr, ASTNode *arg_list) {
	Function *func = malloc(sizeof(Function));
	func->addr = addr;
	func->arg_list = arg_list;
	return func;
}

void destroy_mem_addr(Memory_Address *mem_addr) {
	free(mem_addr);
	mem_addr = 0;
}

int create_global_variable(const char *key, Memory_Address *addr) {
	return rbt_insert(global_memory, key, addr);
}

int create_local_variable(const char *key, Memory_Address *addr, int depth) {
	NUM_LOCAL++;
	return rbt_insert(local_memory[depth - 1], key, addr);
}

int add_function(const char *key, Function *func) {
	return rbt_insert(function_addresses, key, func);
}

void exit_depth(int depth) {
	NUM_LOCAL -= local_memory[depth - 1]->num_values;
	rbt_destroy(local_memory[depth - 1]->root);
	local_memory[depth - 1]->root = 0;
	local_memory[depth - 1]->num_values = 0;
}

Memory_Address *get_global_addr(const char *key) {
	Map_Item *v = rbt_find(global_memory, key);
	if (v) return (Memory_Address*) v->data;
	return 0;
}

Memory_Address *get_local_addr(const char *key, int depth) {
	for (int i = depth - 1; i >= 0; i--) {
		Map_Item *v = rbt_find(local_memory[i], key);
		if (v) return (Memory_Address*) v->data;
	}
	return 0;
}

Function *get_function(const char *key) {
	Map_Item *f = rbt_find(function_addresses, key);
	if (f) return (Function*) f->data;
	else return 0;
}

int *get_datatype_by_key(const char *key) {
	Map_Item *d = rbt_find(datatypes, key);
	if (d) return (int*) d->data;
	else return 0;
}
