#ifndef DEQUE_H
#define DEQUE_H

struct Deque;

struct Deque *deque_new(int elem_size);
void deque_free(struct Deque *deq);

void put_front(struct Deque *deq, void *elem);
void get_front(struct Deque *deq, void *elem);

void put_back(struct Deque *deq, void *elem);
void get_back(struct Deque *deq, void *elem);

int deque_size(const struct Deque *deq);
int deque_is_empty(const struct Deque *deq);

#endif
