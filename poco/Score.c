#include <stdio.h>
#include <stdlib.h>
#include "./../Service/Service.h"
#include "./Course.h"
#include "Score.h"

Score *createScore() {
    Score *score = (Score *)malloc(sizeof(Score));
    score->id = 0;
    score->stuId = 0;
    score->courseId = 0;
    score->score = 0;
    score->point = 0;
    return score;
}

char *scoreToString(const Score *score) {
    char *str = (char *)malloc(100 * sizeof(char));
    Course *course = getCourseById(score->courseId);
    sprintf(str, "id: %d\t学号: %d\t课程: %d\t课程名：%s\t必修: %s\t总成绩: %d\t绩点: %.1f\n",
            score->id, score->stuId, score->courseId, course->name, course->isReq == 1 ? "是" : "否", score->score, score->point);
    return str;
}

void showScore(const Score *score) {
    char *str = scoreToString(score);
    printf("%s\n", str);
    free(str);
}

Score *readScore(FILE *fp) {
    Score *score = createScore();
    fscanf(fp, "%d", &score->id);
    fscanf(fp, "%d", &score->stuId);
    fscanf(fp, "%d", &score->courseId);
    fscanf(fp, "%d", &score->score);
    fscanf(fp, "%f", &score->point);
    return score;
}

void writeScore(FILE *fp, const Score *score) {
    fprintf(fp, "%d\n", score->id);
    fprintf(fp, "%d\n", score->stuId);
    fprintf(fp, "%d\n", score->courseId);
    fprintf(fp, "%d\n", score->score);
    fprintf(fp, "%.1f\n", score->point);
}
