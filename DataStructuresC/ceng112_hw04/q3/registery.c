#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N_LINES 100

struct Student{
	char *name;
	int id;
};

int cmp_int(const void *v0, const void *v1);
int cmp_char(const void *v0, const void *v1);

void print_list(struct Student *s, int n_lines);

int main()
{
	struct Student s[10];
	for(int i=0; i<10; i++)
	{
		s[i].name = malloc(30*sizeof(char));
		scanf("%d %s", &s[i].id, s[i].name);
	}
	qsort((void *)(&s[0]), 10, sizeof(struct Student), &cmp_int);
	printf("Ordered by student id:\n");
	print_list(s,10);
	qsort((void *)(&s[0]), 10, sizeof(struct Student), &cmp_char);
	printf("Ordered by name:\n");
	print_list(s,10);
	return 0;
}

int cmp_int(const void *v0, const void *v1)
{
        const struct Student *s0 = (const struct Student *)v0;
        const struct Student *s1 = (const struct Student *)v1;
        return s0->id - s1->id;
}

int cmp_char(const void *v0, const void *v1)
{
        const struct Student *s0 = (const struct Student *)v0;
        const struct Student *s1 = (const struct Student *)v1;
        return strcmp(s0->name,s1->name);
}

void print_list(struct Student *s, int n_lines)
{
	printf("Number\t Name\n");
	for(int i=0; i<n_lines; i++)
		printf("%d\t %s\n", s[i].id, s[i].name);
}
