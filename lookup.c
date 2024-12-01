#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#define MAX_QUERY_LEN 100
#define MIN_TABLE_SIZE 3
#define DEFAULT_TABLE_SIZE 1873
#define QUERY_SUCCESS_FORMAT "found sale id=%s, purchased_item=%s, cost=%.5f\n"
#define QUERY_FAILURE_FORMAT "could not find sale with id=%s\n"
#define USAGE_STRING "%s [-s threshold] [-t table_size] <filename>\n"

int main(int argc, char **argv) {
	int s_flag = 0;
	int threshold;
	size_t table_size = DEFAULT_TABLE_SIZE;
	// TODO: parse opts with getopt and initialize these variables
	// (see strtoul for parsing unsigned long)
	int c;
	while ((c = getopt(argc, argv, "s:t:")) != -1) {
		switch (c) {
			case 's':
				s_flag = 1;
				threshold = atoi(optarg);
				break;
			case 't':
				table_size = atoi(optarg);
				break;
			default:
	// handle any bad inputs (missing filename or invalid option flag
	// by printing out the USAGE_STRING to stderr and exiting with failure:
				fprintf(stderr, USAGE_STRING, argv[0]);
				return EXIT_FAILURE;
		}
	}

	if(table_size < MIN_TABLE_SIZE) {
		table_size = MIN_TABLE_SIZE;
	}

	// TODO: initialze htable
	// using calloc so all buckets are initialized to NULL
	Node **htable = NULL;
	htable = (Node**)calloc(table_size, sizeof(Node*));
	if (htable == NULL) {
		return EXIT_FAILURE;
	}

	// TODO: get filename and call load_table;
	if(optind >= argc) {
		fprintf(stderr, USAGE_STRING, argv[0]);
		return EXIT_FAILURE;
	}
	char *filename = argv[optind];

	if (load_table(htable, table_size, filename) == false) {
		fprintf(stderr, "error in load_table\n");
		delete_table(htable, table_size);
		return EXIT_FAILURE;
	}

	char query[MAX_QUERY_LEN + 1];
	char *end;
	int success = 0;
	// read one line at a time from stdin, do a lookup for that id
	
	while (fgets(query, MAX_QUERY_LEN + 1, stdin) == query) {
		// replace the \n, if it exists (for hashing)
		if ((end = strchr(query, '\n'))) *end = '\0'; // don't change this line

		// TODO: read a line from stdin and perform a lookup
		// if the sale is found, print its contents to stdout
		// using QUERY_SUCCESS_FORMAT
		Node *item = node_lookup(*(htable+(hash(query)%table_size)),query);
		if(item != NULL) {
			printf(QUERY_SUCCESS_FORMAT, (*item).id, (*item).purchased_item, (*item).cost);
			success += 1;
		}
		// if the sale is not found, print a message to **stdout**
		// using QUERY_FAILURE_FORMAT
		else {
			printf(QUERY_FAILURE_FORMAT, query);
		}
		// keep track of the number of successful queries
	}
	printf("%d successful queries\n", success);

	// if -s called then print stats
	if (s_flag == 1) {
		print_info(htable, table_size, threshold);
	}

	// free all allocated memory associated with the table
	// using delete_table()
	delete_table(htable, table_size);

	return EXIT_SUCCESS;

}
