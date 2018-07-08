#include "table.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct Table *new_table(int capacity)
{
        struct Table *table = malloc(sizeof(struct Table));
        table->capacity = capacity;
        table->next = NULL;
	table->prev = NULL;
        return table;
}

void free_table_list(struct Table *head)
{
        while (head != NULL) {
                struct Table *to_free = head;
	        head = head->next;
                free(to_free);
        }
}

void add_new_table(struct Table *head, int capacity)
{
        struct Table *table = new_table(capacity);
	if(head->next)	
	{
		head->next->prev = table;
		table->next = head->next;
	}
	head->next = table;
	table->prev = head;
}

struct Table *create_random()
{	
	srand(time(0));
	int r = (rand()%9)+2;
        struct Table *head = new_table(r);
	for(int i=0; i<19; i++)
	{
		r = (rand()%9)+2;
		add_new_table(head, r); 
	}
	return head;
}

void print_tables(struct Table *head)
{
        for(struct Table *t=head; t!=NULL; t=t->next)
                printf("%d ", t->capacity);
        printf("\n");
}

void exchange(struct Table *t1, struct Table *t2)
{
	int temp = t1->capacity;
	t1->capacity = t2->capacity;
	t2->capacity = temp;
}

void insertion_sort(struct Table *head)
{
        for (struct Table *i = head->next; i != NULL; i=i->next)
	{
                for (struct Table *j = i; j != head; j=j->prev)
                {
			if (j->capacity < j->prev->capacity)
                                exchange(j,j->prev);
		}
        }

}
