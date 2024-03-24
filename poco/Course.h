/*
|属性|类型|必须|说明|
|-|-|-|-|
|id|int|是|自增、唯一|
|name|char *|是|课程名|
|subject|char *|是|专业|
|teacher|char *|是|教师|
|term|char *|是|学年学期， 如 2023上|
|isReq|int|是|1为必修，0为选修|
|credit|float|是|学分，如 4 或 3.5|
|period|int|是|学时|
 */

#pragma once
#include "./../Utils/List.h"
#include <stdio.h>

typedef struct Course{
    int id;
    char *name;
    char *subject;
    char *teacher;
    char *term;
    int isReq;
    float credit;
    int period;
} Course;

Course *createCourse();

char *courseToString(const Course *course);

void showCourse(const Course *course);

void destroyCourseMembers(Course *course);

Course *readCourse(FILE *fp);

void writeCourse(FILE *fp, const Course *course);