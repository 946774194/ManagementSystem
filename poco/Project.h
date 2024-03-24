/*
|属性|类型|必须|说明|
|-|-|-|-|
|id|int|是|自增、唯一|
|awards|List *|是|pairif的list，记录每个学生（id）的加分|
|authors|List *|是|按顺序包含所有作者的表，List中的节点存放Student对象|
|teacher|char *|是|指导教师姓名|
|name|char *|是|项目名称|
|code|char *|是|项目编号|
|startDate|char *|是|立项日期|
|endDate|char *|是|结项日期|

 */

#pragma once
#include <stdio.h>
#include "./../Utils/List.h"

typedef struct {
    int id;
    char *teacher;
    char *name;
    char *code;
    char *startDate;
    char *endDate;
    List *authors;
    List *awards;
} Project;

Project *createProject();

char *projectToString(const Project *project);

void showProject(const Project *project);

void destroyProjectMembers(Project *project);

Project *readProject(FILE *fp);

void writeProject(FILE *fp, const Project *project);