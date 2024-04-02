/*
|属性|类型|必须|说明|
|-|-|-|-|
|id|int|是|自增、唯一|
|stuId|int|是|学号，唯一|
|pwd|char *|否|密码，初始值为123456,只能在修改密码功能中改动|
|name|char *|是|姓名（学生可能重名）|
|subject|char *|是|专业|
|gpa|float|否|绩点，仅在刚计算时有效|
|prizeList|List *|是|这四个List的Obj存带有该学生的记录的id（int*）|
|paperList|List *|是|
|scoreList|List *|是|
|projectList|List *|是|
 */

#pragma once
#include <stdio.h>
#include "./../Utils/List.h"


typedef struct student{
    int id;
    int stuId;
    char* pwd;
    char* name;
    char* subject;
    float gpa;
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