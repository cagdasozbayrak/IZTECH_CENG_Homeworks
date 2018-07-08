#include "set_of_ints.h"

#include <stdlib.h>
#include <stdio.h>

#define RBT_BLACK 0
#define RBT_RED 1

struct SetOfInts {
        int *buckets;
        int n_buckets;
        int n_keys;
};

struct SetOfInts *new_set_of_ints(int initial_size)
{
        struct SetOfInts *si = malloc(sizeof(*si));
        if (si == NULL) {
                fprintf(stderr, "Out of memory!\n");
                exit(EXIT_FAILURE);
        }

        si->n_buckets = initial_size;
        si->buckets = malloc(initial_size*sizeof(struct SetOfInts));
        if (si->buckets == NULL) {
                fprintf(stderr, "Out of memory!\n");
                exit(EXIT_FAILURE);
        }
        for (int i = 0; i < si->n_buckets; ++i)
                si->buckets[i] = -1;

        si->n_keys = 0;

        return si;
}

void free_set_of_ints(struct SetOfInts *si)
{
        if (si)
        {
                free(si->buckets);
                free(si);
        }
}

int size_of_set_of_ints(struct SetOfInts *si)
{
        return si->n_keys;
}

void add_to_set_of_ints(struct SetOfInts *si, int value)
{
        int hash = hash_int(value);
        int bucket_id = abs(hash % si->n_buckets);

        while (si->buckets[bucket_id] != -1)
                if (++bucket_id >= si->n_buckets)
                        bucket_id = 0;

        si->buckets[bucket_id] = value;
        ++si->n_keys;
}

void delete_from_set_of_ints(struct SetOfInts *si, int value)
{
	if(set_of_ints_find(si, value) == -1)
	{
		printf("%d is not an element of the set.\n", value);
		return;
	}
	
	int hash = hash_int(value);
	int bucket_id = abs(hash % si->n_buckets);
	while(si->buckets[bucket_id] != -1)
	{
		if(si->buckets[bucket_id] == value)
		{
			si->buckets[bucket_id] = -1;
			si->n_keys--;
			return;
		}
		else if(++bucket_id >= si->n_buckets)
			bucket_id=0;
	}
}

void print_set_of_ints(struct SetOfInts *si)
{
        for (int i = 0; i < si->n_buckets; ++i)
                if (si->buckets[i] != -1)
                        printf("Bucket %d -> %d\n", i, si->buckets[i]);
}

int set_of_ints_find(struct SetOfInts *si, int value)
{
        int hash = hash_int(value);
        int bucket_id = abs(hash % si->n_buckets);

        while (si->buckets[bucket_id] != -1) {
                if (si->buckets[bucket_id] == value)
                        return si->buckets[bucket_id];
                else if (++bucket_id >= si->n_buckets)
                        bucket_id = 0;
        }

        return -1;
}

int hash_int(int n)
{
        return 31*n;
}
