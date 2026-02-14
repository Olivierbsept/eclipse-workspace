#include "node_common.h"
#include <stdio.h>

bool ids_equal(uint32_t mn1, uint16_t mt1, uint32_t mn2, uint16_t mt2) {
	return mn1 == mn2 && mt1 == mt2;
}

bool all_ids_equal(Node* n1, Node* n2, Node* n3) {
	return ids_equal(n1->id_mn, n1->id_mt, n2->id_mn, n2->id_mt) &&
	       ids_equal(n2->id_mn, n2->id_mt, n3->id_mn, n3->id_mt);
}

bool ids_two_equal(Node* o1, Node* o2, Node* self) {
	return ids_equal(o1->id_mn, o1->id_mt, o2->id_mn, o2->id_mt) &&
	       !ids_equal(self->id_mn, self->id_mt, o1->id_mn, o1->id_mt);
}

void copy_id(Node* dst, Node* src) {
	dst->id_mn = src->id_mn;
	dst->id_mt = src->id_mt;
}

uint32_t max(uint32_t a, uint32_t b, uint32_t c) {
	uint32_t m = a > b ? a : b;
	return m > c ? m : c;
}

uint32_t max_two(uint32_t a, uint32_t b) {
	return a > b ? a : b;
}

void update_node(Node* self, Node* other1, Node* other2) {
	if (all_ids_equal(self, other1, other2)) {
		self->horameter = max(self->horameter, other1->horameter, other2->horameter);
	} else if (ids_two_equal(other1, other2, self)) {
		copy_id(self, other1);
		self->horameter = max_two(other1->horameter, other2->horameter);
	}
}

void print_node(const char* label, Node* n) {
	printf("%s -> ID: [%u, %u], H: %u\n", label, n->id_mn, n->id_mt, n->horameter);
}
