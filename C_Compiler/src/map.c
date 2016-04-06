#include "map.h"

void add_item(const char *key, int val) {

}

void rem_item(const char *key) {

}

Map_Item *find(const char *key) {

}

Map create_map() {
	Map m = { 0, &add_item, &rem_item, &find };
	return m;
}
