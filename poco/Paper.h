/*
|属性|类型|必须|说明|
|-|-|-|-|
|id|int|是|自增、唯一|
|awards|List *|是|pairif的list，记录每个id的加分|
|authors|List *|是|按顺序包含所有作者的表，List中的节点存放Student对象,外校/教师的id，stuId为0|
|corrAuthors|List*|否|按顺序包含所有通讯作者的表，List中的节点存放Student对象,外校/教师的id，stuId为0|
|title|char *|是|论文名称|
|journalName|char *|是|期刊名称/会议名称|
|publishDate|char *|是|发表日期|
|level|char *|是|论文级别|
|volume|char *|否|卷|
|issue|char *|否|期|
|paperId|char *|否|论文号|
|page|char *|否|页|
 */

#pragma once
#include <stdio.h>
#include "./../Utils/List.h"

typedef struct {
    int id;
    char *title;
    char *journalName;
    char *publishDate;
    char *level;
    char *volume;
    char *issue;
    char *paperId;
    char *page;
    List *authors;
    List *corrAuthors;
    List *awards;
} Paper;

Paper *createPaper();

char *paperToString(const Paper *paper);

void showPaper(const Paper *paper);

void destroyPaperMembers(Paper *paper);

Paper *readPaper(FILE *fp);

void writePaper(FILE *fp, const Paper *paper);