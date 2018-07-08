#ifndef SET_OF_INTS_H
#define SET_OF_INTS_H

struct SetOfInts;

struct SetOfInts *new_set_of_ints(int initial_size);
void free_set_of_ints(struct SetOfInts *si);

int size_of_set_of_ints(struct SetOfInts *si);
void add_to_set_of_ints(struct SetOfInts *si, int value);
void delete_from_set_of_ints(struct SetOfInts *si, int value);
void print_set_of_ints(struct SetOfInts *si);

int set_of_ints_find(struct SetOfInts *si, int value);
int hash_int(int n);
int hash_int2(int value);

#endif
