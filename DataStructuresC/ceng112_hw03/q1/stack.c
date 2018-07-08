#include "stack.h"

#include <stdlib.h>
#include <string.h>

struct Node
{
	char *elem;
	struct Node *next;
};

struct Node *newNode(void *elem, int elem_size)
{
        struct Node *n = malloc(sizeof(struct Node));
        n->elem = malloc(elem_size);
        memcpy(n->elem, elem, elem_size);
        n->next = NULL;

        return n;
}

void freeNode(struct Node *n)
{
        if (n != NULL) {
                free(n->elem);
                free(n);
        }
}

struct Stack {
        int elem_size;
        struct Node *head;
        int n_elems;
};

struct Stack *stack_new(int elem_size)
{
        struct Stack *s = malloc(sizeof(struct Stack));
        s->elem_size = elem_size;
	s->head = NULL;
	s->n_elems = 0;
        return s;
}

void stack_free(struct Stack *s)
{
	if(s != NULL){
		while(s->head != NULL){
			struct Node *temp = s->head;
			s->head = s->head->next;
			freeNode(temp);
		}
		free(s);	
	}
}

void stack_push(struct Stack *s, void *elem)
{
        struct Node *n = newNode(elem, s->elem_size);
	n->next = s->head;
	s->head = n;
	s->n_elems++;
}

void stack_pop(struct Stack *s)
{
        if (!stack_is_empty(s)) {
		struct Node *temp = s->head;
                s->head = s->head->next;
		freeNode(temp);
        }
	s->n_elems--;
}

void *stack_peek(struct Stack *s)
{
        if (s->n_elems == 0)
                return NULL;
	return s->head->elem;
}

int stack_size(const struct Stack *s)
{
        return s->n_elems;
}

int stack_is_empty(const struct Stack *s)
{
        return s->n_elems == 0;
}

