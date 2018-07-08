#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "queue.h"

#define NV 8

struct NeighborInfo {
        int id;
        struct NeighborInfo *next;
};

void add_edge(int adj_matrix[][NV], int v0, int v1);
void make_neighbors(int adj_matrix[][NV], int v0, int v1);

int find_neighbors(int adj_matrix[NV][NV], int v0, int neighbors[NV-1]);
void print_adjaceny_matrix(int adj_matrix[][NV], int nv);
void print_depth_first(int adj_matrix[NV][NV], int id, int *marks);
void print_breadth_first(int adj_matrix[NV][NV], int id, int *marks);

void initialize_adjacency_matrix(int adj_matrix[NV][NV]);

int main(int argc, char **argv)
{
        int adj_matrix[NV][NV];
        initialize_adjacency_matrix(adj_matrix);

        make_neighbors(adj_matrix, 0, 1);
        make_neighbors(adj_matrix, 0, 2);
        make_neighbors(adj_matrix, 0, 5);
        make_neighbors(adj_matrix, 0, 6);
        make_neighbors(adj_matrix, 0, 7);
        make_neighbors(adj_matrix, 1, 7);
        make_neighbors(adj_matrix, 2, 7);
        make_neighbors(adj_matrix, 3, 4);
        make_neighbors(adj_matrix, 3, 5);
        make_neighbors(adj_matrix, 4, 5);
        make_neighbors(adj_matrix, 4, 6);
        make_neighbors(adj_matrix, 4, 7);

        print_adjaceny_matrix(adj_matrix, NV);
        // marks for already visited nodes
        int marks[NV];

        // print starting from 0
        printf("Depth First from 0: ");
        memset(marks, 0, NV*sizeof(marks[0]));
        print_depth_first(adj_matrix, 0, marks);
        printf("\n");

        // print starting from 4
        printf("Depth First from 4: ");
        memset(marks, 0, NV*sizeof(marks[0]));
        print_depth_first(adj_matrix, 4, marks);
        printf("\n");

        // print starting from 0
        printf("Breadth First from 0: ");
        memset(marks, 0, NV*sizeof(marks[0]));
        print_breadth_first(adj_matrix, 0, marks);
        printf("\n");

        // print starting from 4
        printf("Breadth First from 4: ");
        memset(marks, 0, NV*sizeof(marks[0]));
        print_breadth_first(adj_matrix, 4, marks);
        printf("\n");

        return EXIT_SUCCESS;
}

void add_edge(int adj_matrix[][NV], int v0, int v1)
{
	adj_matrix[v0][v1] = 1;
}

void make_neighbors(int adj_matrix[][NV], int v0, int v1)
{
        add_edge(adj_matrix, v0, v1);
        add_edge(adj_matrix, v1, v0);
}

void print_adjaceny_matrix(int adj_matrix[][NV], int nv)
{
        printf("Adjacency Matrix:\n  ");
        for(int i=0; i<nv; i++)
        	printf("  %c", 'A'+i);
        printf("\n");
	for(int i=0; i<nv; i++)
	{
		printf("%c | ", 'A'+i);
		for(int j=0; j<nv; j++)
			if(j==nv-1)
				printf("%d ", adj_matrix[i][j]);
			else
				printf("%d  ", adj_matrix[i][j]);
		printf("|\n");
	}
}

int find_neighbors(int adj_matrix[NV][NV], int v0, int neighbors[NV-1])
{
	int j=0;
	for(int i=0; i<NV; i++)
		if(adj_matrix[v0][i] == 1)
			neighbors[j++]=i;
	neighbors[j]=-1;
	return j;
}

void print_depth_first(int adj_matrix[NV][NV], int id, int *marks)
{
        printf("%c ", 'A'+id);
        marks[id] = 1;
        int neighbors[NV-1];
	int n_neighbors = find_neighbors(adj_matrix, id, neighbors);
	for(int i=n_neighbors-1; i>=0; i--)
	{
		int n_id = neighbors[i];
		if(marks[n_id] != 1)
			print_depth_first(adj_matrix, n_id, marks);
	}
}

void print_breadth_first(int adj_matrix[NV][NV], int id, int *marks)
{
        struct Queue *q = queue_new(sizeof(int));
        queue_put(q, &id);

        while (!queue_is_empty(q))
	{
		int k;
                queue_get(q, &k);

                if (marks[k] != 1)
		{
			printf("%c ", 'A'+k);
                        marks[k] = 1;
			int neighbors[NV-1];
			int n_neighbors = find_neighbors(adj_matrix, k, neighbors);
			for(int i=n_neighbors-1; i>=0; i--)
			{
				int n_id = neighbors[i];
				if(marks[n_id] != 1)
				queue_put(q, &n_id);
			}
		}
	}
        queue_free(q);
}

void initialize_adjacency_matrix(int adj_matrix[NV][NV])
{
	for(int i=0; i<NV; i++)
		for(int j=0; j<NV; j++)
			adj_matrix[i][j]=0;
}

