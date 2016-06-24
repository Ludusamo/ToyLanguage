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

int create_global_variable(const char *key, int *addr) {
	return rbt_insert(global_memory, key, addr);
}

int create_local_variable(const char *key, int *offset) {
	return rbt_insert(local_memory, key, offset);
}

int create_function(const char *key, int *addr) {
	return rbt_insert(function_addresses, key, addr);
}

int get_global_addr(const char *key) {
	Map_Item *v = rbt_find(global_memory, key);
	if (v) return *(int*) v->data;
	return -1;
}

int get_local_offset(const char *key) {
	Map_Item *v = rbt_find(local_memory, key);
	if (v) return *(int*) v->data;
	else return -1;

}

int get_function_addr(const char *key) {
	Map_Item *f = rbt_find(function_addresses, key);
	if (f) return *(int*) f->data;
	else return -1;
}
