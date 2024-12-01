#include "node.h"
#include <string.h>
#include <stdio.h>

Node *node_lookup(Node *front, const char *id) {
	// step through the chain pointed to by front
	// use function like strcmp to compare the id to the current node
	// if found return a pointer to the node, else return NULL
	Node *current = front;
	while (current != NULL) {
		if (strcmp(current->id, id) == 0) {
			return current;
		} else {
			current = current->next;
		}
	}
	return NULL;
}
