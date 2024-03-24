/*
|属性|类型|必须|说明|
|-|-|-|-|
|id|int|是|自增、唯一|
|stuId|int|是|学生学号|
|courseId|int|是|课程id|
|score|int|是|总成绩，[0,100]|
|point|float|是|绩点，如 4 或 3.7|
 */

#pragma once
#include <stdio.h>
#include "./../Utils/List.h"

typedef struct Score{
    int id;
    int stuId;
    int courseId;
    int score;
    float point;
} Score;

Score *createScore();

char *scoreToString(const Score *score);

void showScore(const Score *score);

Score *readScore(FILE *fp);

void writeScore(FILE *fp, const Score *score);

