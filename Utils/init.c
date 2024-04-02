#include <windows.h>
#include "./../include/inc.h"
#include "init.h"
#include "./../file/file.h"
#include "./../Utils/Logger.h"
const int DEFAULT_BUFFER_SIZE = 64;

// 全局变量的定义
int isModified = 0;
int permission = 0;
List *const StudentList;
List *const CourseList;
List *const ScoreList;
List *const PrizeList;
List *const PaperList;
List *const ProjectList;
int studentCnt;
int courseCnt;
int scoreCnt;
int prizeCnt;
int paperCnt;
int projectCnt;
const char AdminUsername[] = "admin";
char *AdminPassword = "admin";
int nowLoginUsername;
Logger logger;

void init() {
//    system("chcp 65001>nul");
    logger = createLogger();
    logger.info("初始化开始");
    *(List**)&StudentList = createList();
    *(List**)&CourseList = createList();
    *(List**)&ScoreList = createList();
    *(List**)&PrizeList = createList();
    *(List**)&PaperList = createList();
    *(List**)&ProjectList = createList();

    permission = 0;

    initCWD(); // 初始化当前工作目录

    readCnt();
    readStudentList();
    readCourseList();
    readScoreList();
    readPrizeList();
    readPaperList();
    readProjectList();
    readAdminPassword();
    logger.info("初始化完成");
}