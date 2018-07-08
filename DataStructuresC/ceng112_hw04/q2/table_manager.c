#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "table.h"

int main(int argc, char **argv)
{
        struct Table *head = create_random();
	printf("List of the tables: \n");
	print_tables(head);
	insertion_sort(head);
	printf("Sorted list of the tables: \n");
	print_tables(head);
	free_table_list(head);
	return 0;
}
