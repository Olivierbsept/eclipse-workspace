#ifndef NODE_COMMON_H
#define NODE_COMMON_H

#include <stdint.h>
#include <stdbool.h>

// --- Structure Node ---
typedef struct Node {
	uint32_t id_mn;
	uint16_t id_mt;
	uint32_t horameter;
	void (*update)(struct Node*, struct Node*, struct Node*);
} Node;

// --- Fonctions déclarées ---
bool ids_equal(uint32_t mn1, uint16_t mt1, uint32_t mn2, uint16_t mt2);
bool all_ids_equal(Node* n1, Node* n2, Node* n3);
bool ids_two_equal(Node* o1, Node* o2, Node* self);
void copy_id(Node* dst, Node* src);

uint32_t max(uint32_t a, uint32_t b, uint32_t c);
uint32_t max_two(uint32_t a, uint32_t b);

void update_node(Node* self, Node* other1, Node* other2);
void print_node(const char* label, Node* n);

#endif // NODE_COMMON_H
