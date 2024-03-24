/*
|属性|类型|必须|说明|
|-|-|-|-|
|id|int|是|自增、唯一|
|awards|List *|是|pairif的list，记录每个id的加分|
|name|char *|是|竞赛项目名称|
|org|char *|是|主办单位|
|isOrdered|int|是|是否有顺序，1有0无|
|authors|List *|是|按顺序包含所有作者的表，List中的节点存放Student对象,借用其id，name属性，id为-1表示非在库Student|
|level|char *|是|获奖等级|
|date|char *|是|获奖日期|
 */

#pragma once
#include <stdio.h>
#include "./../Utils/List.h"

typedef struct Prize{
    int id;
    char *name;
    char *org;
    char *level;
    char *date;
    int isOrdered;
    List *authors;
    List *awards;
} Prize;

Prize *createPrize();

char *prizeToString(const Prize *prize);

void showPrize(const Prize *prize);

void destroyPrizeMembers(Prize *prize);

Prize *readPrize(FILE *fp);

void writePrize(FILE *fp, const Prize *prize);