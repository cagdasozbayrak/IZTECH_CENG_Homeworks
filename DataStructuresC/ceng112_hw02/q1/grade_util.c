#include "grade_util.h"

#include <stdio.h>
#include <math.h>
#include <float.h>
#include <stdlib.h>

float* load_grades(int* max_n)
{
        int n = 0;
	float *grades = malloc(*(max_n)*sizeof(float));
        if(grades == NULL)
	{
		printf("Out of memory!\n");
		return 0;
	}
	while (n < *(max_n) && scanf("%f\n", &grades[n]) == 1)
	{
		n++;
		if(n== *(max_n))
		{
			*(max_n)+=1;
			grades = realloc(grades, *(max_n)*sizeof(float));
			if(grades == NULL)
			{
				printf("Out of memory!\n");
				return 0;
			}
		}
	}
        return grades;
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
