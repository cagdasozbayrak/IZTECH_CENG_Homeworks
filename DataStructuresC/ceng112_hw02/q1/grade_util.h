#ifndef GRADE_UTIL_H
#define GRADE_UTIL_H

float* load_grades(int* max_n);
float minimum_of(int n, float x[]);
float maximum_of(int n, float x[]);
float average_of(int n, float x[]);
float normalize(float grade, float average);
char *letter_grade_for(float grade, float average);

#endif
