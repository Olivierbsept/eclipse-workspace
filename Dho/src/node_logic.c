#include <stdio.h>
#include "node_common.h"

void get_node(const char* label, Node self, Node o1, Node o2) {
	printf("NOEUD %s - AVANT / APRES SYNC :\n", label);
	print_node(label, &self);

	self.update(&self, &o1, &o2);

	//printf("NOEUD %s - APRÈS SYNC :\n", label);
	print_node(label, &self);
}
