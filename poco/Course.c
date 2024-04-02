#include <stdio.h>
#include <stdlib.h>
#include "Course.h"
#include "./../include/inc.h"

Course *createCourse() {
    Course *course = (Course *)malloc(sizeof(Course));
    course->id = 0;
    course->name = NULL;
    course->subject = NULL;
    course->teacher = NULL;
    course->term = NULL;
    course->isReq = 0;
    course->credit = 0;
    course->period = 0;
    return course;
}

char *courseToString(const Course *course) {
    char *str = (char *)malloc(512);
    sprintf(str, "id: %d\t课程名: %s\t专业: %s\t教师: %s\t学期: %s\t必修: %d\t学分: %.1f\t学时: %d\n",
            course->id, course->name, course->subject, course->teacher, course->term, course->isReq, course->credit, course->period);
    return str;
}

void showCourse(const Course *course) {
    char *str = courseToString(course);
    printf("%s\n", str);
    free(str);
}

void destroyCourseMembers(Course *course) {
    free(course->name);
    free(course->subject);
    free(course->teacher);
    free(course->term);
}

Course *readCourse(FILE *fp) {
    Course *course = createCourse();
    fscanf(fp, "%d\n", &course->id);
    course->name = inputStringFromFile(fp);
    course->subject = inputStringFromFile(fp);
    course->teacher = inputStringFromFile(fp);
    course->term = inputStringFromFile(fp);
    fscanf(fp, "%d\n", &course->isReq);
    fscanf(fp, "%f\n", &course->credit);
    fscanf(fp, "%d\n", &course->period);
    return course;
}

void writeCourse(FILE *fp, const Course *course) {
    fprintf(fp, "%d\n", course->id);
    fprintf(fp, "%s\n", course->name);
    fprintf(fp, "%s\n", course->subject);
    fprintf(fp, "%s\n", course->teacher);
    fprintf(fp, "%s\n", course->term);
    fprintf(fp, "%d\n", course->isReq);
    fprintf(fp, "%.1f\n", course->credit);
    fprintf(fp, "%d\n", course->period);
}