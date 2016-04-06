#ifndef MAP_H
#define MAP_H

typedef struct Map_Item Map_Item;

struct Map_Item {
	Map_Item *prev;
	Map_Item *next;
	
	const char *key;
	int val;
};

typedef struct {
	Map_Item *head;
	void (*add_item)(const char *key, int val);
	void (*rem_item)(const char *key);
	Map_Item *(*find)(const char *key);
} Map;

void add_item(const char *key, int val);
void rem_item(const char *key);
Map_Item *find(const char *key);

Map create_map();
void destroy_map(Map map);

#endif // MAP_H
