#pragma once
#include <stdio.h>
#include "./../Utils/List.h"


typedef struct student{
    int id;
    int stuId;
    char* pwd;
    char* name;
    char* subject;
    float gpa;// 仅在刚计算时有效
    List *prizeList;
    List *paperList;
    List *scoreList;
    List *projectList;
} Student;

Student *createStudent();

char *studentToString(const Student *stu);

void showStudent(const Student *stu);

void destroyStudentMembers(Student *stu);

Student *readStudent(FILE *fp);

void writeStudent(FILE *fp, const Student *stu);