#include "memory.h"

void init_mem() {
	global_memory = create_map();
	local_memory = create_map();
	function_addresses = create_map();
}

void deinit_mem() {
	destroy_map(global_memory);
	destroy_map(local_memory);
	destroy_map(function_addresses);
}

Memory_Address *create_mem_addr(int size, int addr, int type) {
	Memory_Address *mem_addr = malloc(sizeof(Memory_Address));
	mem_addr->size = size;
	mem_addr->addr = addr;
	mem_addr->type = type;
	return mem_addr;
}

void destroy_mem_addr(Memory_Address *mem_addr) {
	free(mem_addr);
	mem_addr = 0;
}

int create_global_variable(const char *key, Memory_Address *addr) {
	return rbt_insert(global_memory, key, addr);
}

int create_local_variable(const char *key, Memory_Address *addr) {
	return rbt_insert(local_memory, key, addr);
}

int create_function(const char *key, Memory_Address *addr) {
	return rbt_insert(function_addresses, key, addr);
}

Memory_Address *get_global_addr(const char *key) {
	Map_Item *v = rbt_find(global_memory, key);
	if (v) return (Memory_Address*) v->data;
	return 0;
}

Memory_Address *get_local_addr(const char *key) {
	Map_Item *v = rbt_find(local_memory, key);
	if (v) return (Memory_Address*) v->data;
	else return 0;

}

Memory_Address *get_function_addr(const char *key) {
	Map_Item *f = rbt_find(function_addresses, key);
	if (f) return (Memory_Address*) f->data;
	else return 0;
}
