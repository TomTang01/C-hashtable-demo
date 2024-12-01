#include "node.h"
#include <stdlib.h>

void delete_table(Node **htable, size_t table_size) {
	// TODO: walk through the chains in table
	Node *current;
	Node *nextN;
	for(size_t i=0; i< table_size; i++) {
		current = *(htable+i);
		while(current != NULL) {
			// free all the memory associated to each node in each chain
			free((*current).id);
			free((*current).purchased_item);
			nextN = (*current).next;
			free(current);
			current = nextN;
		}
	}
	// TODO: free the entire table
	free(htable);
}
