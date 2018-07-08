#include <stdlib.h>
#include <stdio.h>

#include "grade_util.h"

int main(void)
{
	int max_n=2;
	float *grades = load_grades(&max_n);
	int n=max_n-1;
	printf("Number of students is %d\n", n);

	float min = minimum_of(n, grades);
	printf("Minimum is %.2f\n", min);

	float max = maximum_of(n, grades);
	printf("Maximum is %.2f\n", max);

	float average = average_of(n, grades);
	printf("Average is %.2f\n", average);

	printf("Letter grades:\n");
	for (int i = 0; i < n; ++i) {
			char *letter_grade = letter_grade_for(grades[i], average);
			printf("%6.2f -> %s\n", grades[i], letter_grade);
	}
	free(grades);
	return EXIT_SUCCESS;
}


