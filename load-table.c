#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 100
#define FILE_OPEN_ERR_MSG "error in load_table while opening file %s\n"
#define DUPLICATE_ID_MSG "load_table duplicate entry: %s\n"
#define INSERTION_ERROR_MSG "load_table could not create node for %s\n"

bool load_table(Node **htable, size_t table_size, const char *filename) {
	FILE *fp = NULL;
	// open the file and check that it was successful
	if ((fp = fopen(filename, "r")) == NULL) {
		fprintf(stderr, FILE_OPEN_ERR_MSG, filename);
		return false;
	}

	// loop through the file and read one line at a time using fgets
	// see manual page for fgets for information on parameters
	char *id;
	char *purchased_item;
	double cost;
	int hashid;
	char buf[MAX_LINE_LEN + 1]; // input buffer for fgets
	while ((fgets(buf, MAX_LINE_LEN + 1, fp)) == buf) {
		// TODO: for each line, use strtok to break it into columns
		id = strtok(buf, ",");
		purchased_item = strtok(NULL, ",");

		// (convert the third column to a double)
		cost = atof(strtok(NULL, ","));

		// get the corresponding chain for this entry
		hashid = hash(id) % (int)(table_size);

		// check that the node doesn't already exist in table
		if(node_lookup(*(htable+hashid),id) != NULL) {	
			fprintf(stderr, DUPLICATE_ID_MSG, id);
		} else {
			// add non-duplicate node to the front of its chain
			Node *newHead;
			if((newHead = make_node(*(htable+hashid), id, purchased_item, cost)) == NULL) {	
				fprintf(stderr, INSERTION_ERROR_MSG, id);
				return false;
			} else {
				*(htable+hashid) = newHead;
			}
		}
	}
	fclose(fp);
	return true;
}
