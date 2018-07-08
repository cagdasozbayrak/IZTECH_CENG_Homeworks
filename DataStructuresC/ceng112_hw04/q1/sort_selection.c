#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define N 10

int less(int i0, int i1) { return i0 < i1; }
void fill_random(int n, int *x);
void print_array(int n, const int *x);
int is_sorted(int n, int *x);
void exchange(int *x, int i, int j);

void selection_sort(int *x, int l, int r);

int main(int argc, char **argv)
{
        int x[N];
        fill_random(N, x);
        print_array(N, x);

        selection_sort(x, 0, N-1);
        print_array(N, x);

        if (is_sorted(N, x))
                printf("SORTED\n");
        else
                printf("NOT SORTED\n");

        return EXIT_SUCCESS;
}

void fill_random(int n, int *x)
{
        const int M = 1000;

        srand(time(0));

        for (int i = 0; i < n; ++i)
                x[i] = rand() % M;
}

void print_array(int n, const int *x)
{
        printf("[");
        for (int i = 0; i < n; ++i) {
                printf(" %3d", x[i]);
        }
        printf(" ]\n");
}

int is_sorted(int n, int *x)
{
        for (int i = 1; i < n; ++i)
                if (less(x[i], x[i-1]))
                        return 0;

        return 1;
}

void exchange(int *x, int i, int j)
{
        int t = x[i];
        x[i] = x[j];
        x[j] = t;
}


void selection_sort(int *x, int l, int r)
{
	if(l>=r)
		return;
	int min_id=l;
	for(int j=l+1; j<=r; j++)
		if(less(x[j], x[min_id]))
			min_id=j;
	exchange(x, min_id, l);
        fputs("  ", stdout);
        print_array(r-l+1, x+l);
	selection_sort(x, l+1, r);
}
