#include "array.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INITIAL_CAPACITY 2

struct Array
{
        char *elems;
        int elem_size;
        int size;
        int capacity;
};

struct Array *array_new(int elem_size)
{
        struct Array *arr = malloc(sizeof(struct Array));
        if (arr == NULL) {
                fprintf(stderr, "Out of memory!\n");
                exit(EXIT_FAILURE);
        }

        arr->elem_size = elem_size;
        arr->size = 0;
        arr->capacity = INITIAL_CAPACITY;
        arr->elems = malloc(arr->capacity*arr->elem_size);

        return arr;
}

void array_free(struct Array *arr)
{
        if (arr != NULL) {
                free(arr->elems);
                free(arr);
        }
}

int array_size(const struct Array *arr)
{
        return arr->size;
}

void array_resize(struct Array *arr, int new_size)
{
        while (new_size > arr->capacity) {
                arr->capacity *= 2;
                arr->elems = realloc(arr->elems, arr->capacity*arr->elem_size);
                if (arr->elems == NULL) {
                        fprintf(stderr, "Out of memory!\n");
                        exit(EXIT_FAILURE);
                }
        }

        arr->size = new_size;
}

void array_set(struct Array *arr, int id, void *value)
{
        if (id >= array_size(arr))
                array_resize(arr, id+1);

        memcpy(arr->elems + id*arr->elem_size, value, arr->elem_size);
}

void *array_get(const struct Array *arr, int id)
{
        return arr->elems + id*arr->elem_size;
}

void array_push_back(struct Array *arr, void *value)
{
        array_set(arr, arr->size, value);
}
