#pragma once
#include "./../Utils/List.h"
#include "./../Poco/Student.h"
#include "./../Poco/Course.h"
#include "./../Poco/Paper.h"
#include "./../Poco/Project.h"

void insertObj(List *list, void *obj);

void deleteObjById(List *list, int id);

const void *getObjById(List *list, int id);

List* getStudentByName(char *name);

Student *getStudentByStuId(int stuId);

List *getCourseByName(char *name);

List *getPrizeByName(char *name);

List *getPaperByTitle(char *title);

List *getProjectByName(char *name);