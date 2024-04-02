#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include "file.h"
#include "./../Utils/List.h"
#include "./../include/inc.h"
#include "./../poco/Student.h"
#include "./../poco/Course.h"
#include "./../poco/Score.h"
#include "./../poco/Prize.h"
#include "./../poco/Paper.h"
#include "./../poco/Project.h"
#include "./../Utils/Logger.h"

void initCWD() { // 初始化当前工作目录
    if (access("data", 0) == -1) { // 如果data文件夹不存在
        mkdir("data");
    }

    if (access("data/student.txt", 0) == -1) { // 如果student文件不存在
        FILE *fp = fopen("data/student.txt", "w");
        fclose(fp);
    }

    if (access("data/course.txt", 0) == -1) {
        FILE *fp = fopen("data/course.txt", "w");
        fclose(fp);
    }

    if (access("data/score.txt", 0) == -1) {
        FILE *fp = fopen("data/score.txt", "w");
        fclose(fp);
    }

    if (access("data/prize.txt", 0) == -1) {
        FILE *fp = fopen("data/prize.txt", "w");
        fclose(fp);
    }

    if (access("data/paper.txt", 0) == -1) {
        FILE *fp = fopen("data/paper.txt", "w");
        fclose(fp);
    }

    if (access("data/project.txt", 0) == -1) {
        FILE *fp = fopen("data/project.txt", "w");
        fclose(fp);
    }

    if (access("data/cnt.txt", 0) == -1) {
        FILE *fp = fopen("data/cnt.txt", "w");
        fclose(fp);
    }

    if (access("data/log.txt", 0) == -1) {
        FILE *fp = fopen("data/log.txt", "w");
        fclose(fp);
    }
}

void readCnt() { // 读取各项记录的下一个id
    FILE *fp = fopen("data/cnt.txt", "r");
    if (fp == NULL) {
        logger.warn("读取cnt文件失败");
        return;
    }
    fscanf(fp, "%d", &studentCnt);
    fscanf(fp, "%d", &courseCnt);
    fscanf(fp, "%d", &scoreCnt);
    fscanf(fp, "%d", &prizeCnt);
    fscanf(fp, "%d", &paperCnt);
    fscanf(fp, "%d", &projectCnt);
    fclose(fp);
}

void writeCnt() { // 写入各项记录的下一个id
    FILE *fp = fopen("data/cnt.txt", "w");
    if (fp == NULL) {
        logger.warn("写入cnt文件失败");
        return;
    }
    fprintf(fp, "%d\n", studentCnt);
    fprintf(fp, "%d\n", courseCnt);
    fprintf(fp, "%d\n", scoreCnt);
    fprintf(fp, "%d\n", prizeCnt);
    fprintf(fp, "%d\n", paperCnt);
    fprintf(fp, "%d\n", projectCnt);
    fclose(fp);
}

void readStudentList() {
    FILE *fp = fopen("data/student.txt", "r");
    if (fp == NULL) {
        logger.warn("读取student文件失败");
        return;
    }
    int c = 0;
    if (fscanf(fp, "%d", &c) == EOF) {
        logger.warn("读取student文件记录数失败");
        fclose(fp);
        return;
    }
    for (int i = 0; i < c; i++) {
        Student *stu = readStudent(fp);
        append(StudentList, stu);
    }
    fclose(fp);
}

void writeStudentList() {
    FILE *fp = fopen("data/student.txt", "w");
    if (fp == NULL) {
        logger.warn("写入student文件失败");
        return;
    }
    fprintf(fp, "%d\n", StudentList->size);
    for (int i = 0; i < StudentList->size; i++) {
        Student *stu = (Student *)get(StudentList, i);
        writeStudent(fp, stu);
    }
    fclose(fp);
}

void readCourseList() {
    FILE *fp = fopen("data/course.txt", "r");
    if (fp == NULL) {
        logger.warn("读取course文件失败");
        return;
    }
    int c = 0;
    if (fscanf(fp, "%d", &c) == EOF) {
        logger.warn("读取course文件记录数失败");
        fclose(fp);
        return;
    }
    for (int i = 0; i < c; i++) {
        Course *course = readCourse(fp);
        append(CourseList, course);
    }
    fclose(fp);
}

void writeCourseList() {
    FILE *fp = fopen("data/course.txt", "w");
    if (fp == NULL) {
        logger.warn("写入course文件失败");
        return;
    }
    fprintf(fp, "%d\n", CourseList->size);
    for (int i = 0; i < CourseList->size; i++) {
        Course *course = (Course *)get(CourseList, i);
        writeCourse(fp, course);
    }
    fclose(fp);
}

void readScoreList() {
    FILE *fp = fopen("data/score.txt", "r");
    if (fp == NULL) {
        logger.warn("读取score文件失败");
        return;
    }
    int c = 0;
    if (fscanf(fp, "%d", &c) == EOF) {
        logger.warn("读取score文件记录数失败");
        fclose(fp);
        return;
    }
    for (int i = 0; i < c; i++) {
        Score *score = readScore(fp);
        append(ScoreList, score);
    }
    fclose(fp);
}

void writeScoreList() {
    FILE *fp = fopen("data/score.txt", "w");
    if (fp == NULL) {
        logger.warn("写入score文件失败");
        return;
    }
    fprintf(fp, "%d\n", ScoreList->size);
    for (int i = 0; i < ScoreList->size; i++) {
        Score *score = (Score *)get(ScoreList, i);
        writeScore(fp, score);
    }
    fclose(fp);
}

void readPrizeList() {
    FILE *fp = fopen("data/prize.txt", "r");
    if (fp == NULL) {
        logger.warn("读取prize文件失败");
        return;
    }
    int c = 0;
    if (fscanf(fp, "%d", &c) == EOF) {
        fclose(fp);
        return;
    }
    for (int i = 0; i < c; i++) {
        Prize *prize = readPrize(fp);
        append(PrizeList, prize);
    }
    fclose(fp);
}

void writePrizeList() {
    FILE *fp = fopen("data/prize.txt", "w");
    if (fp == NULL) {
        logger.warn("写入prize文件失败");
        return;
    }
    fprintf(fp, "%d\n", PrizeList->size);
    for (int i = 0; i < PrizeList->size; i++) {
        Prize *prize = (Prize *)get(PrizeList, i);
        writePrize(fp, prize);
    }
    fclose(fp);
}

void readPaperList() {
    FILE *fp = fopen("data/paper.txt", "r");
    if (fp == NULL) {
        logger.warn("读取paper文件失败");
        return;
    }
    int c = 0;
    if (fscanf(fp, "%d", &c) == EOF) {
        logger.warn("读取paper文件记录数失败");
        fclose(fp);
        return;
    }
    for (int i = 0; i < c; i++) {
        Paper *paper = readPaper(fp);
        append(PaperList, paper);
    }
    fclose(fp);
}

void writePaperList() {
    FILE *fp = fopen("data/paper.txt", "w");
    if (fp == NULL) {
        logger.warn("写入paper文件失败");
        return;
    }
    fprintf(fp, "%d\n", PaperList->size);
    for (int i = 0; i < PaperList->size; i++) {
        Paper *paper = (Paper *)get(PaperList, i);
        writePaper(fp, paper);
    }
    fclose(fp);
}

void readProjectList() {
    FILE *fp = fopen("data/project.txt", "r");
    if (fp == NULL) {
        logger.warn("读取project文件失败");
        return;
    }
    int c = 0;
    if (fscanf(fp, "%d", &c) == EOF) {
        logger.warn("读取project文件记录数失败");
        fclose(fp);
        return;
    }
    for (int i = 0; i < c; i++) {
        Project *project = readProject(fp);
        append(ProjectList, project);
    }
    fclose(fp);
}

void writeProjectList() {
    FILE *fp = fopen("data/project.txt", "w");
    if (fp == NULL) {
        logger.warn("写入project文件失败");
        return;
    }
    fprintf(fp, "%d\n", ProjectList->size);
    for (int i = 0; i < ProjectList->size; i++) {
        Project *project = (Project *)get(ProjectList, i);
        writeProject(fp, project);
    }
    fclose(fp);
}

void readAdminPassword() {
    if (access("data/adminPassword.txt", 0) == -1) {
        return;
    }
    FILE *fp = fopen("data/adminPassword.txt", "r");
    if (fp == NULL) {
        logger.warn("读取adminPassword文件失败");
        return;
    }
    char *password = (char *)malloc(DEFAULT_BUFFER_SIZE);
    password[0] = '\0';
    fscanf(fp, "%s", password);
    if (strlen(password) > 0) {
        AdminPassword = password;
    } else {
        free(password);
    }
}