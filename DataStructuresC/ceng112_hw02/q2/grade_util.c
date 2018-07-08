#include "grade_util.h"

#include <stdio.h>
#include <math.h>
#include <float.h>
#include <stdlib.h>

#include "array.h"

struct Array* load_grades()
{
	float temp;
        struct Array *grades = array_new(sizeof(float));
        if(grades == NULL)
	{
		printf("Out of memory!\n");
		return 0;
	}
	while (scanf("%f", &temp) != EOF)
		array_push_back(grades, &temp);
        return grades;
}

float minimum_of(struct Array *grades)
{
        float min = FLT_MAX;
	int n = array_size(grades);
        for (int i = 0; i < n; ++i)
                if (*((float*)(array_get(grades,i))) < min)
                        min = *((float*)(array_get(grades,i)));
        return min;
}

float maximum_of(struct Array *grades)
{
        float max = -FLT_MAX;
	int n = array_size(grades);
        for (int i = 0; i < n; ++i)
                if (*((float*)(array_get(grades,i))) > max)
                        max = *((float*)(array_get(grades,i)));
        return max;
}

float average_of(struct Array *grades)
{
        float average = 0.0f;
	int n = array_size(grades);
        for (int i = 0; i < n; ++i)
                average += *((float*)(array_get(grades,i)));
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
