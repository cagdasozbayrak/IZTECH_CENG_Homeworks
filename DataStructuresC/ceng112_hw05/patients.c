#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <inttypes.h>

struct Patient
{
	int64_t national_id;
	int condition;
};

struct PQueue
{
        int n;
        int max_n;
        struct Patient *elements;
};

struct PQueue *pqueue_new(int max_n);
void pqueue_free(struct PQueue *pq);

void pqueue_insert(struct PQueue *pq, struct Patient item);
int64_t pqueue_delmin(struct PQueue *pq);
int pqueue_is_empty(const struct PQueue *pq);

int count_lines(FILE *fp);

int main(int argc, char **argv)
{
	FILE *fp = fopen("patients.txt", "r");
	struct Patient temp;
	if(fp==NULL)
		return -1;
	int n_lines=0;
	n_lines = count_lines(fp);
	rewind(fp);
	struct PQueue *pq = pqueue_new(n_lines);
	for(int i = 0; i < n_lines; i++)
	{
		fscanf(fp, "%011jd %d", &temp.national_id, &temp.condition);
		pqueue_insert(pq, temp);
		if((i+1)%3 == 0)
			printf("%011jd ", pqueue_delmin(pq));
			
	}

	while(!pqueue_is_empty(pq))
	{
		printf("%011jd ", pqueue_delmin(pq));
	}
	printf("\n");
	fclose(fp);
	pqueue_free(pq);
        return EXIT_SUCCESS;
}

int greater(struct Patient p0, struct Patient p1)
{
        return p0.condition > p1.condition;
}

void exchange(struct Patient *x, int i, int j)
{
        struct Patient t;
	
	t.national_id = x[i].national_id;
	t.condition = x[i].condition;

	x[i].national_id = x[j].national_id;
	x[i].condition = x[j].condition;
        
	x[j].national_id = t.national_id;
	x[j].condition = t.condition;
}

void downheap(struct Patient *x, int k, int n)
{
        int j;
        while (2*k <= n) {
                j = 2*k;
                if (j < n && greater(x[j], x[j+1]))
                        j++;
                if (!greater(x[k], x[j]))
                        break;
                exchange(x, j, k);
                k = j;
        }
}

void upheap(struct Patient *x, int k)
{
        while (k > 1 && greater(x[k/2], x[k])) {
                exchange(x, k, k/2);
                k = k/2;
        }
}

struct PQueue *pqueue_new(int max_n)
{
        struct PQueue *pq = malloc(sizeof(*pq));

        pq->max_n = max_n;
        pq->n = 0;
        pq->elements = malloc((max_n+1)*sizeof(struct Patient));

        return pq;
}

void pqueue_free(struct PQueue *pq)
{
        if (pq) {
                free(pq->elements);
                free(pq);
        }
}

void pqueue_insert(struct PQueue *pq, struct Patient item)
{
        pq->elements[++pq->n].national_id = item.national_id;
	pq->elements[pq->n].condition = item.condition;
        upheap(pq->elements, pq->n);
}

int64_t pqueue_delmin(struct PQueue *pq)
{
        exchange(pq->elements, 1, pq->n);
        downheap(pq->elements, 1, pq->n-1);
        return (pq->elements[pq->n--]).national_id;
}

int pqueue_is_empty(const struct PQueue *pq)
{
        return pq->n == 0;
}

int count_lines(FILE *fp)
{
	char temp[30];
	int i;
	if(fp)
	{
		for(i=0; fgets(temp, 30, fp) != NULL; i++)
			;
	}
	return i;
}
