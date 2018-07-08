#include "deque.h"

#include <stdlib.h>
#include <string.h>

struct Node {
        char *elem;
        struct Node *next;
};

static struct Node *new_node(void *elem, int elem_size)
{
        struct Node *n = malloc(sizeof(struct Node));
        n->elem = malloc(elem_size);
        memcpy(n->elem, elem, elem_size);
        n->next = NULL;

        return n;
}

static void free_node(struct Node *n)
{
        if (n != NULL) {
                free(n->elem);
                free(n);
        }
}

struct Deque
{
        int elem_size;
        struct Node *head;
        struct Node *tail;
        int n_elems;
};

struct Deque *deque_new(int elem_size)
{
        struct Deque *deq = malloc(sizeof(struct Deque));
        deq->elem_size = elem_size;
        deq->head = NULL;
        deq->tail = NULL;
        deq->n_elems = 0;
        return deq;
}

void deque_free(struct Deque *deq)
{
        if (deq != NULL) {
                while (deq->head != NULL) {
                        struct Node *to_del = deq->head;
                        deq->head = deq->head->next;
                        free_node(to_del);
                }
                free(deq);
        }
}

void put_back(struct Deque *deq, void *elem)
{
        struct Node *n = new_node(elem, deq->elem_size);

        if (deq->head == NULL) {
                deq->head = n;
                deq->tail = n;
        } else {
                deq->tail->next = n;
                deq->tail = n;
        }

        deq->n_elems++;
}

void put_front(struct Deque *deq, void *elem)
{
        struct Node *n = new_node(elem, deq->elem_size);

        if (deq->head == NULL) {
                deq->head = n;
                deq->tail = n;
        } else {
                n->next = deq->head;
		deq->head = n;
        }

        deq->n_elems++;
}

void get_front(struct Deque *deq, void *elem)
{
        memcpy(elem, deq->head->elem, deq->elem_size);
        struct Node *to_del = deq->head;
        deq->head = deq->head->next;

        free_node(to_del);
        deq->n_elems--;
}

void get_back(struct Deque *deq, void *elem)
{
        memcpy(elem, deq->tail->elem, deq->elem_size);
        struct Node *to_del = deq->tail;
	if(deq->n_elems == 1){
		deq->head=NULL;
		deq->tail=NULL;
	}
	else{
		struct Node *temp = deq->head;
		while(temp->next != deq->tail)
			temp = temp->next;
		deq->tail=temp;
		deq->tail->next=NULL;
	}
       	free_node(to_del);
        deq->n_elems--;
}

int deque_size(const struct Deque *deq)
{
        return deq->n_elems;
}

int deque_is_empty(const struct Deque *deq)
{
        return deq->n_elems == 0;
}
