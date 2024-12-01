#include "node.h"
#include <limits.h>
#include <stdio.h>

#define TABLESIZE_MSG "Table size: %zu\n"
#define TOTAL_ENTRIES_MSG "Total entries: %lu\n"
#define LONGEST_MSG "Longest chain: %lu\n"
#define SHORTEST_MSG "Shortest chain: %lu\n"
#define THRESHOLD_MSG "Reached threshold: %lu\n"
#define EMPTY_MSG "Empty buckets: %lu\n"

void print_info(Node **htable, size_t table_size, unsigned long threshold) {
	// TODO: walk down the indices of the htable
	// iterate through each chain and update statistics
	// print out statistics at end
	//
	// NOTE: all your statistics variables should be of type
	// unsigned long
	//
	// NOTE: you may use ULONG_MAX if you want
	// (maximum value for unsigned long int)
	unsigned long total = 0;
	unsigned long longest = 0;
	unsigned long shortest = 0;
	unsigned long reached = 0;
	unsigned long empty = 0;
	unsigned long length = 0;
	Node *current;
	bool first_loop = true;
	for(size_t i=0; i<table_size; i++) {
		current = *(htable+i);
		while(current != NULL) {
			total += 1;
			length +=1;
			current = current->next;
		}
		if(length == 0) {
			empty += 1;
		}
		if(length >= threshold) {
			reached += 1;
		}
		if(length > longest) {
			longest = length;
		}
		if(first_loop) {
			shortest = longest;
			first_loop = false;
		}
		if(shortest > length) {
			shortest = length;
		}
		length = 0;
	}

	printf(TABLESIZE_MSG, table_size);
	printf(TOTAL_ENTRIES_MSG, total);
	printf(LONGEST_MSG, longest);
	printf(SHORTEST_MSG, shortest);
	printf(THRESHOLD_MSG, reached);
	printf(EMPTY_MSG, empty);
}
