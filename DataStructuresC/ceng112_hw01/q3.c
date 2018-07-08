#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <float.h>

#define MAX_N_STUDENTS 500
#define N_BINS 20
#define N_COLUMNS 80

int load_grades(float grades[], int max_n_students);
float minimum_of(int n, float x[]);
float maximum_of(int n, float x[]);
float average_of(int n, float x[]);
float normalize(float grade, float average);
char *letter_grade_for(float grade, float average);
void compute_histogram(int bins[], int n_students, float grades[]);

void draw_histogram(int bins[], int n_columns);
int maxNC(int bins[], int ncList[], float col_size);//Finds and returns maximum number of columns of the list
						    //Also creates list of nc
void initializeToZero(int arr[]);                     

int main(void)
{
        float grades[MAX_N_STUDENTS];
        int n = load_grades(grades, MAX_N_STUDENTS);

        int bins[N_BINS];
        compute_histogram(bins, n, grades);

        draw_histogram(bins, N_COLUMNS);

        return EXIT_SUCCESS;
}

int load_grades(float grades[], int max_n_students)
{
        int n = 0;
        while (n < max_n_students
               && scanf("%f\n", &grades[n]) == 1)
                n++;
        return n;
}

float minimum_of(int n, float x[])
{
        float min = FLT_MAX;
        for (int i = 0; i < n; ++i)
                if (x[i] < min)
                        min = x[i];
        return min;
}

float maximum_of(int n, float x[])
{
        float max = -FLT_MAX;
        for (int i = 0; i < n; ++i)
                if (x[i] > max)
                        max = x[i];
        return max;
}

float average_of(int n, float x[])
{
        float average = 0.0f;
        for (int i = 0; i < n; ++i)
                average += x[i];
        average /= n;

        return average;
}

float normalize(float grade, float average)
{
        float normalized = grade;
        if (average < 70.0f)
                normalized += 70.0f - average;
        if (normalized > 100.0f)
                normalized = 100.0f;
        return normalized;
}

char *letter_grade_for(float grade, float average)
{
        float normalized = normalize(grade, average);
        int letter_bin = round(normalized) / 5;
        char *letter_grade;
        switch (letter_bin) {
        case 20:
        case 19:
        case 18: letter_grade = "AA"; break;
        case 17: letter_grade = "BA"; break;
        case 16: letter_grade = "BB"; break;
        case 15: letter_grade = "CB"; break;
        case 14: letter_grade = "CC"; break;
        case 13: letter_grade = "DC"; break;
        case 12: letter_grade = "DD"; break;
        case 11: letter_grade = "FD"; break;
        default: letter_grade = "FF"; break;
        }

        return letter_grade;
}

void compute_histogram(int bins[], int n_students, float grades[])
{
        float min = minimum_of(n_students, grades);
        float max = maximum_of(n_students, grades);
        float range = max - min;
        float bin_size = range / N_BINS;

        for (int i = 0; i < N_BINS; ++i)
                bins[i] = 0;

        for (int i = 0; i < n_students; ++i) {
                int bin_id = (grades[i] - min) / bin_size;
                if (bin_id == N_BINS)
                        bin_id = N_BINS-1;
                bins[bin_id]++;
        }
}

void draw_histogram(int bins[], int n_columns)
{
        int max = 0, ncList[N_BINS];
        for (int i = 0; i < N_BINS; ++i)
                if (bins[i] > max)
                        max = bins[i];

        float col_size = max / (float)n_columns;
	int maximumNC=maxNC(bins, ncList, col_size);
	int countSpace[N_BINS];//Counts number of spaces that each column has
	initializeToZero(countSpace);
	printf("\n");
        for (int i = 0; i < maximumNC; ++i)
	{
		for(int k=0; k<N_BINS; k++)
		{
			if(maximumNC - ncList[k] > countSpace[k]) //If the column has lesser columns than the max value,
			{					  //it should print a space character.
				printf("   ");
				countSpace[k]++;
			}
			else
				printf("|| ");
		}
		printf("\n");
        }
}

int maxNC(int bins[], int ncList[], float col_size)
{	
	int max=0;

	for(int i=0; i<N_BINS; i++)
	{
		ncList[i] = bins[i] / col_size;
		if(ncList[i]>max)
			max=ncList[i];
	}

	return max;
}

void initializeToZero(int arr[])
{
	for(int i=0; i<N_BINS; i++)
		arr[i]=0;
}
