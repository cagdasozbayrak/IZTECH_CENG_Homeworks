#ifndef ARRAY_H
#define ARRAY_H

struct Array;

struct Array *array_new(int elem_size);
void array_free(struct Array *arr);

int array_size(const struct Array *arr);
void array_resize(struct Array *arr, int new_size);

void array_set(struct Array *arr, int id, void *value);
void *array_get(const struct Array *arr, int id);
void array_push_back(struct Array *arr, void *value);

#endif
