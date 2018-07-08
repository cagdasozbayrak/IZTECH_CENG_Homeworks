#ifndef TABLE_H
#define TABLE_H

struct Table {
        int capacity;
        struct Table *next;
        struct Table *prev;
};

struct Table *new_table(int capacity);
void free_table_list(struct Table *head);

void add_new_table(struct Table *head, int capacity);

struct Table *create_random();
void print_tables(struct Table *head);

void exchange(struct Table *t1, struct Table *t2);
void insertion_sort(struct Table *head);
#endif
