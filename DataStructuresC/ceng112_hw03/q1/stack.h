#ifndef STACK_H
#define STACK_H

struct Stack;

struct Stack *stack_new(int elem_size);
void stack_free(struct Stack *s);

void stack_push(struct Stack *s, void *elem);
void stack_pop(struct Stack *s);
void *stack_peek(struct Stack *s);

int stack_size(const struct Stack *s);
int stack_is_empty(const struct Stack *s);

#endif
