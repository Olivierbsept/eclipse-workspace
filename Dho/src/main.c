#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "node_common.h"

// Déclaration
void get_node(const char* label, Node self, Node o1, Node o2);

int main() {
	Node A = {1, 100, 5, update_node};
	Node B = {1, 100, 7, update_node};
	Node C = {3, 300, 10, update_node};

	pid_t pidA = fork();
	if (pidA == 0) {
		get_node("A", A, B, C);
		return 0;
	}

	pid_t pidB = fork();
	if (pidB == 0) {
		get_node("B", B, C, A);
		return 0;
	}

	pid_t pidC = fork();
	if (pidC == 0) {
		get_node("C", C, A, B);
		return 0;
	}

	// Le processus parent attend les 3
	wait(NULL);
	wait(NULL);
	wait(NULL);

	return 0;
}
