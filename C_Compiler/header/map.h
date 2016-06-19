#ifndef MAP_H
#define MAP_H

#include "string_util.h"

typedef struct Map_Item Map_Item;

struct Map_Item {
	int red;
	const char *key;
	int data;
	struct Map_Item *link[2];
};

typedef struct {
	Map_Item *root;
	int num_values;
} Map;

Map *create_map();

void rbt_destroy(Map_Item *root);
void destroy_map(Map *map);

int is_red(Map_Item *item);
Map_Item *rbt_single(Map_Item *item, int dir);
Map_Item *rbt_double(Map_Item *item, int dir);
Map_Item *make_item(const char *key, int data);

Map_Item *rbt_insert_r(Map_Item *root, const char *key, int data);
int rbt_insert(Map *tree, const char *key, int data);
int rbt_remove(Map *tree, const char *key);
Map_Item *rbt_find(Map *tree, const char *key);

#endif // MAP_H
