#include <stdio.h>

#define MAX_N_LINES 1000

struct grade
{
	float grade1;
	float grade2;
	float grade3;
};

int readLines(struct grade grades[], int numberOfLines);
void calculateAverage(struct grade grades[], int numberOfLines);

int main()
{
	struct grade grades[MAX_N_LINES];
	int numberOfLines = readLines(grades, MAX_N_LINES);
	calculateAverage(grades, numberOfLines);
	return 0;
}

int readLines(struct grade grades[], int numberOfLines)//Reads notes line-by-line and returns the number of lines
{
	int i=0;
	for(i=0; i<numberOfLines
		&& scanf("%f%f%f\n", &grades[i].grade1, &grades[i].grade2, &grades[i].grade3) != EOF; i++)
		continue;
	return i;
}

void calculateAverage(struct grade grades[], int numberOfLines)
{
	float avg=0.0;
	for(int i=0; i<numberOfLines; i++)	
	{	
		avg=(grades[i].grade1*0.2+grades[i].grade2*0.4+grades[i].grade3*0.4);
		printf("%.2f \n", avg);
	}
}
