#ifndef GRADE_UTIL_H
#define GRADE_UTIL_H

struct Array* load_grades();
float minimum_of(struct Array *grades);
float maximum_of(struct Array *grades);
float average_of(struct Array *grades);
float normalize(float grade, float average);
char *letter_grade_for(float grade, float average);

#endif
