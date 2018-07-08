#include <stdlib.h>
#include <stdio.h>

#include "grade_util.h"
#include "array.h"

int main(void)
{
	struct Array *grades = load_grades();
	int n=array_size(grades);
	printf("Number of students is %d\n", n);

        float min = minimum_of(grades);
        printf("Minimum is %.2f\n", min);

        float max = maximum_of(grades);
        printf("Maximum is %.2f\n", max);

        float average = average_of(grades);
        printf("Average is %.2f\n", average);

        printf("Letter grades:\n");
        for (int i = 0; i < n; ++i) {
			char *letter_grade = letter_grade_for(*((float*)(array_get(grades,i))), average);
			printf("%6.2f -> %s\n", *((float*)(array_get(grades,i))), letter_grade);
        }
	
	array_free(grades);
	return EXIT_SUCCESS;
}
