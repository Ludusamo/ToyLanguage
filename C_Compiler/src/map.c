#include "map.h"

Map *create_map() {
	Map *m = malloc(sizeof(Map));
	m->num_values = 0;
	return m;
}

void rbt_destroy(Map_Item *root) {
	if (!root) return;
	if (root->link[0]) rbt_destroy(root->link[0]);
	if (root->link[1]) rbt_destroy(root->link[1]);
	free(root);
	root = 0;
}

void destroy_map(Map *map) {
	if (map) {
		if (map->root) rbt_destroy(map->root);
		free(map);
		map = 0;
	}
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

Map_Item *make_item(const char *key, int data) {
	Map_Item *item = malloc(sizeof(Map_Item));
	item->red = 1;
	item->key = key;
	item->data = data;
	item->link[0] = 0;
	item->link[1] = 0;
	return item;
}

Map_Item *rbt_insert_r(Map_Item *root, const char *key, int data) {
	if (!root) {
		root = make_item(key, data);
	} else if (data != root->data) {
		int dir = str_lt(root->key, key);

		root->link[dir] = rbt_insert_r(root->link[dir], key, data);

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

int rbt_insert(Map *tree, const char *key, int data) {
	tree->root = rbt_insert_r(tree->root, key, data);
	tree->root->red = 0;
	tree->num_values++;
	return 1;
}

int rbt_remove(Map *tree, const char* key) {
	if (tree->root != NULL) {
		Map_Item head = { 0 }; /* False tree root */
		Map_Item *q, *p, *g; /* Helpers */
		Map_Item *f = NULL;  /* Found item */
		int dir = 1;
		/* Set up helpers */
		q = &head;
		g = p = NULL;
		q->link[1] = tree->root;

		/* Search and push a red down */
		while (q->link[dir] != NULL) {
			int last = dir;

			/* Update helpers */
			g = p, p = q;
			q = q->link[dir];
			dir = str_lt(q->key, key);

			/* Save found node */
			if (str_equal(q->key, key)) {
				f = q;
			}

			/* Push the red node down */
			if (!is_red(q) && !is_red(q->link[dir])) {
				if (is_red(q->link[!dir])) {
					p = p->link[last] = rbt_single(q, dir);
				} else if (!is_red(q->link[!dir])) {
					Map_Item *s = p->link[!last];

					if (s != NULL) {
						if (!is_red(s->link[!last]) && !is_red(s->link[last])) {
							/* Color flip */
							p->red = 0;
							s->red = 1;
							q->red = 1;
						} else {
							int dir2 = g->link[1] == p;

							if (is_red(s->link[last])) {
								g->link[dir2] = rbt_double(p, last);
							} else if (is_red(s->link[!last])) {
								g->link[dir2] = rbt_single(p, last);
							}

							/* Ensure correct coloring */
							q->red = g->link[dir2]->red = 1;
							g->link[dir2]->link[0]->red = 0;
							g->link[dir2]->link[1]->red = 0;
						}
					}
				}
			}
		}

		/* Replace and remove if found */
		if (f != NULL) {
			f->key = q->key;
			f->data = q->data;
			p->link[p->link[1] == q] = q->link[q->link[0] == NULL];
			free(q);
		}

		/* Update root and make it black */
		tree->root = head.link[1];

		if (tree->root != NULL) {
			tree->root->red = 0;
		}
	}
	tree->num_values--;
	return 1;
}

Map_Item *rbt_find(Map *tree, const char *key) {
	Map_Item *cur = tree->root;
	while (cur) {
		if (str_equal(cur->key, key)) return cur;
		int dir = str_lt(cur->key, key);
		cur = cur->link[dir];
	}
	return 0;
}
