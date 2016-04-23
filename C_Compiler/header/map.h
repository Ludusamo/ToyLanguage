#ifndef MAP_H
#define MAP_H

typedef struct Map_Item Map_Item;

struct Map_Item {
	int red;
	const char *key;
	int data;
	struct Map_Item *link[2];
};

typedef struct {
	Map_Item *root;
} Map;

void add_item(const char *key, int val);
void rem_item(const char *key);
Map_Item *find(const char *key);

Map create_map();
void destroy_map(Map map);

int is_red(Map_Item *item);
Map_Item *rbt_single(Map_Item *item, int dir);
Map_Item *rbt_double(Map_Item *item, int dir);
Map_Item *make_item(const char *key, int val);

#endif // MAP_H
