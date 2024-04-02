#pragma once
#include "./../Utils/List.h"
#include "./../Utils/utils.h"
/*
 * 重要全局变量的声明
 */
extern const int DEFAULT_BUFFER_SIZE;

extern List * const StudentList;

extern List * const CourseList;

extern List * const ScoreList;

extern List * const PrizeList;

extern List * const PaperList;

extern List * const ProjectList;

extern int isModified;

extern int studentCnt;

extern int courseCnt;

extern int scoreCnt;

extern int prizeCnt;

extern int paperCnt;

extern int projectCnt;

extern int permission; // 权限等级， 0为未登录，1为学生，2为管理员

extern const char AdminUsername[];

extern char *AdminPassword;

extern int nowLoginUsername;