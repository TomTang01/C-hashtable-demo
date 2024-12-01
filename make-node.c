#include "node.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Node *make_node(Node *front, char *id, char *purchased_item, double cost) {
	// create a node, copy in the parameter fields
	// make sure that you do a deep copy
	char *cpid = malloc((strlen(id) + 1) * sizeof(char));
	if(cpid == NULL) {
		return NULL;
	}
	strcpy(cpid, id);
	char *cpitem = malloc((strlen(purchased_item) + 1) * sizeof(char));
	if(cpitem == NULL) {
		return NULL;
	}

	strcpy(cpitem, purchased_item);

	Node *nodeptr = malloc(sizeof(Node));
	nodeptr->id = cpid;
	nodeptr->purchased_item = cpitem;
	nodeptr->cost = cost;
	
	// link the new node into the chain
	nodeptr->next = front;

	if(nodeptr == NULL) {
		return NULL;
	}
	// return the new head of the chain if the function succeeded
	return nodeptr;
}
