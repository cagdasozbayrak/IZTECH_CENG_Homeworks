#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "stack.h"

#define MAX_LINE 2048

enum TokenType {
        TT_ADD,
        TT_SUB,
        TT_MUL,
        TT_DIV,
        TT_NUMBER,
        TT_QUIT
};

struct Token {
        enum TokenType type;
        double value;
};

int process_line(char *line, struct Stack *s);
struct Token parse_token(const char *token_text);
void add(struct Stack *s);
void subtract(struct Stack *s);
void multiply(struct Stack *s);
void divide(struct Stack *s);

int main(int argc, char **argv)
{
        struct Stack *s = stack_new(sizeof(double));

        char line[MAX_LINE];
        printf("Reverse Polish Calculator. Type q to exit.\n");
        printf("> ");
        while (fgets(line, MAX_LINE, stdin) != NULL) {
                if (!process_line(line, s))
                        break;
                printf("> ");
        }

        printf("\n");
        stack_free(s);

        return EXIT_SUCCESS;
}

int process_line(char *line, struct Stack *s)
{
        char token_text[256];
        int n = 0;
        while (sscanf(line, "%s%n", token_text, &n) == 1) {
                line += n;

                struct Token t = parse_token(token_text);
                switch (t.type) {
                case TT_ADD: add(s); break;
                case TT_SUB: subtract(s); break;
                case TT_MUL: multiply(s); break;
                case TT_DIV: divide(s); break;
                case TT_NUMBER: stack_push(s, &t.value); break;
                case TT_QUIT: return 0;
                }
        }

        printf("Top of Stack = %lf\n", *(double *)stack_peek(s));
        return 1;
}

struct Token parse_token(const char *token_text)
{
        struct Token t;

        if (strcmp(token_text, "+") == 0) {
                t.type = TT_ADD;
        } else if (strcmp(token_text, "-") == 0) {
                t.type = TT_SUB;
        } else if (strcmp(token_text, "*") == 0) {
                t.type = TT_MUL;
        } else if (strcmp(token_text, "/") == 0) {
                t.type = TT_DIV;
        } else if (strcmp(token_text, "q") == 0) {
                t.type = TT_QUIT;
        } else {
                t.type = TT_NUMBER;
                char *endptr = NULL;
                t.value = strtod(token_text, &endptr);

                if (endptr == token_text) {
                        fprintf(stderr, "Invalid operation: %s\n", token_text);
                        exit(EXIT_FAILURE);
                }
        }

        return t;
}

void get_top_values(struct Stack *s, double *d0, double *d1)
{
        if (stack_size(s) < 2) {
                fprintf(stderr, "Stack does not contain two operands!\n");
                exit(EXIT_FAILURE);
        }

        double *top = stack_peek(s);
        memcpy(d1, top, sizeof(double));
        stack_pop(s);

        top = stack_peek(s);
        memcpy(d0, top, sizeof(double));
        stack_pop(s);
}

void add(struct Stack *s)
{
        double arg0, arg1;
        get_top_values(s, &arg0, &arg1);

        arg0 += arg1;
        stack_push(s, &arg0);
}

void subtract(struct Stack *s)
{
        double arg0, arg1;
        get_top_values(s, &arg0, &arg1);

        arg0 -= arg1;
        stack_push(s, &arg0);
}

void multiply(struct Stack *s)
{
        double arg0, arg1;
        get_top_values(s, &arg0, &arg1);

        arg0 *= arg1;
        stack_push(s, &arg0);
}

void divide(struct Stack *s)
{
        double arg0, arg1;
        get_top_values(s, &arg0, &arg1);

        arg0 /= arg1;
        stack_push(s, &arg0);
}

/* Local Variables: */
/* mode: c          */
/* compile-command: "make rpn-calc" */
/* End:             */
