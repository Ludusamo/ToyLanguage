#include "map.h"

void add_item(const char *key, int val) {

}

void rem_item(const char *key) {

}

Map_Item *find(const char *key) {

}

Map create_map() {
	Map m = { 0 };
	return m;
}

int is_red(Map_Item *item) {
	return item && item->red;
}

Map_Item *rbt_single(Map_Item *item, int dir) {
	Map_Item *buf = item->link[!dir];

	item->link[!dir] = buf->link[dir];
	buf->link[dir] = item;

	item->red = 1; 
	buf->red = 0; 
	return buf;
}

Map_Item *rbt_double(Map_Item *item, int dir) {
	item->link[!dir] = rbt_single(item->link[!dir], !dir);

	return rbt_single(item, dir);
}

Map_Item *make_item(const char *key, int val) {
	return &(Map_Item) { 1, key, val };
}

Map_Item *jsw_insert_r(Map_Item *root, int data) {
	if (!root) {
		root = make_item("NULL", data);
	} else if (data != root->data) {
		int dir = root->data < data;

		root->link[dir] = jsw_insert_r(root->link[dir], data);

		if (is_red(root->link[dir])) {
			if (is_red(root->link[!dir])) {
				/* Case 1 */ 
				root->red = 1;
				root->link[0]->red = 0;
				root->link[1]->red = 0;
	    		} else {
				/* Cases 2 & 3 */
				if (is_red(root->link[dir]->link[dir])) {
					root = rbt_single(root, !dir);
				} else if (is_red(root->link[dir]->link[!dir])) {
					root = rbt_double(root, !dir);
				}
			}
		}
	}

	return root;
}

int jsw_insert(Map *tree, int data) {
	tree->root = jsw_insert_r(tree->root, data);
	tree->root->red = 0;

	return 1;
}
