#include "Paper.h"
#include <stdlib.h>
#include <string.h>
#include "./../include/inc.h"
#include "./../Utils/Pairif.h"
#include "./../poco/Student.h"
#include "../Mapper/Mapper.h"
#include "./../Utils/utils.h"

Paper *createPaper() {
    Paper *paper = (Paper *) malloc(sizeof(Paper));
    paper->id = 0;
    paper->title = NULL;
    paper->journalName = NULL;
    paper->publishDate = NULL;
    paper->level = NULL;
    paper->volume = NULL;
    paper->issue = NULL;
    paper->paperId = NULL;
    paper->page = NULL;
    paper->authors = createList();
    paper->corrAuthors = createList();
    paper->awards = createList();
    return paper;
}

char *paperToString(const Paper *paper) { // TODO: 重复代码
    char *str = (char *) malloc(512);
    char *authorsAndAwards = (char *) malloc(DEFAULT_BUFFER_SIZE);
    *authorsAndAwards = '\0';
    char *p = authorsAndAwards;
    for (int i = 0; i < paper->authors->size; i++) {
        Student *stu = (Student *) get(paper->authors, i);
        sprintf(p, "%d %s", i + 1, stu->name);
        p += strlen(p);

        if (getObjById(paper->awards, stu->id) != NULL) {
            sprintf(p, " +%.2f", getF((Pairif *) getObjById(paper->awards, stu->id)));
            p += strlen(p);
        }
        if (i != paper->authors->size - 1) {
            sprintf(p, ", ");
            p += strlen(p);
        }
    }
    char *corrAuthorsAndAwards = (char *) malloc(DEFAULT_BUFFER_SIZE);
    *corrAuthorsAndAwards = '\0';
    p = corrAuthorsAndAwards;
    for (int i = 0; i < paper->corrAuthors->size; i++) {
        Student *stu = (Student *) get(paper->corrAuthors, i);
        sprintf(p, "%d %s", i + 1, stu->name);
        p += strlen(p);

        if (getObjById(paper->awards, stu->id) != NULL) {
            sprintf(p, " +%.2f", getF((Pairif *) getObjById(paper->awards, stu->id)));
            p += strlen(p);
        }
        if (i != paper->corrAuthors->size - 1) {
            sprintf(p, ", ");
            p += strlen(p);
        }
    }
    sprintf(str, "id: %d\t论文标题: %s\t期刊名/会议名: %s\t发表日期: %s\t论文级别: %s\t卷: %s\t"
                 "期: %s\t论文号: %s\t页: %s\n作者: %s\n通讯作者: %s\n",
            paper->id, paper->title, paper->journalName, paper->publishDate, paper->level,
            orElse(paper->volume, ""), orElse(paper->issue, ""), orElse(paper->paperId, ""),
            orElse(paper->page, ""), authorsAndAwards, corrAuthorsAndAwards);
    free(authorsAndAwards);
    free(corrAuthorsAndAwards);
    return str;
}

void showPaper(const Paper *paper) {
    char *str = paperToString(paper);
    printf("%s", str);
    free(str);
}

void destroyPaperMembers(Paper *paper) {
    free(paper->title);
    free(paper->journalName);
    free(paper->publishDate);
    free(paper->level);
    if (paper->volume != NULL) {
        free(paper->volume);
    }
    if (paper->issue != NULL) {
        free(paper->issue);
    }
    if (paper->paperId != NULL) {
        free(paper->paperId);
    }
    if (paper->page != NULL) {
        free(paper->page);
    }
    for (Node *node = paper->authors->head->next; node != paper->authors->head; node = node->next) {
        Student *stu = (Student *) node->obj;
        free(stu->name);
        free(stu->scoreList);
        free(stu->paperList);
        free(stu->prizeList);
        free(stu->projectList);
        free(stu);
    }
    destroyList(paper->authors);
    for (Node *node = paper->corrAuthors->head->next; node != paper->corrAuthors->head; node = node->next) {
        Student *stu = (Student *) node->obj;
        free(stu->name);
        free(stu->scoreList);
        free(stu->paperList);
        free(stu->prizeList);
        free(stu->projectList);
        free(stu);
    }
    destroyList(paper->corrAuthors);
    destroyList(paper->awards);//TODO: free Pairif
}

Paper *readPaper(FILE *fp) {
    Paper *paper = createPaper();
    fscanf(fp, "%d", &paper->id);
    paper->title = (char *) malloc(DEFAULT_BUFFER_SIZE);
    fscanf(fp, "%s", paper->title);
    paper->journalName = (char *) malloc(DEFAULT_BUFFER_SIZE);
    fscanf(fp, "%s", paper->journalName);
    paper->publishDate = (char *) malloc(DEFAULT_BUFFER_SIZE);
    fscanf(fp, "%s", paper->publishDate);
    paper->level = (char *) malloc(DEFAULT_BUFFER_SIZE);
    fscanf(fp, "%s", paper->level);
    int len;
    fscanf(fp, "%d", &len);
    if(len > 0){
        paper->volume = (char *) malloc(len + 1);
        fscanf(fp, "%s", paper->volume);
    }
    fscanf(fp, "%d", &len);
    if(len > 0){
        paper->issue = (char *) malloc(len + 1);
        fscanf(fp, "%s", paper->issue);
    }
    fscanf(fp, "%d", &len);
    if(len > 0){
        paper->paperId = (char *) malloc(len + 1);
        fscanf(fp, "%s", paper->paperId);
    }
    fscanf(fp, "%d", &len);
    if(len > 0){
        paper->page = (char *) malloc(len + 1);
        fscanf(fp, "%s", paper->page);
    }
    int size;
    fscanf(fp, "%d", &size);
    for (int i = 0; i < size; i++) {
        Student *stu = createStudent();
        fscanf(fp, "%d", &stu->id);
        stu->name = (char *) malloc(DEFAULT_BUFFER_SIZE);
        fscanf(fp, "%s", stu->name);
        insertObj(paper->authors, stu);
    }
    fscanf(fp, "%d", &size);
    for (int i = 0; i < size; i++) {
        Student *stu = createStudent();
        fscanf(fp, "%d", &stu->id);
        stu->name = (char *) malloc(DEFAULT_BUFFER_SIZE);
        fscanf(fp, "%s", stu->name);
        insertObj(paper->corrAuthors, stu);
    }
    fscanf(fp, "%d", &size);
    for (int i = 0; i < size; i++) {
        Pairif *pairif = newPairif(0, 0);
        fscanf(fp, "%d", &pairif->i);
        fscanf(fp, "%f", &pairif->f);
        insertObj(paper->awards, pairif);
    }
    return paper;
}

void writePaper(FILE *fp, const Paper *paper) {
    fprintf(fp, "%d\n", paper->id);
    fprintf(fp, "%s\n", paper->title);
    fprintf(fp, "%s\n", paper->journalName);
    fprintf(fp, "%s\n", paper->publishDate);
    fprintf(fp, "%s\n", paper->level);
    int len;
    len = paper->volume == NULL ? 0 : strlen(paper->volume);
    fprintf(fp, "%d\n", len);
    if(len > 0){
        fprintf(fp, "%s\n", paper->volume);
    }
    len = paper->issue == NULL ? 0 : strlen(paper->issue);
    fprintf(fp, "%d\n", len);
    if(len > 0){
        fprintf(fp, "%s\n", paper->issue);
    }
    len = paper->paperId == NULL ? 0 : strlen(paper->paperId);
    fprintf(fp, "%d\n", len);
    if(len > 0){
        fprintf(fp, "%s\n", paper->paperId);
    }
    len = paper->page == NULL ? 0 : strlen(paper->page);
    fprintf(fp, "%d\n", len);
    if(len > 0){
        fprintf(fp, "%s\n", paper->page);
    }
    fprintf(fp, "%d\n", paper->authors->size);
    for (Node *node = paper->authors->head->next; node != paper->authors->head; node = node->next) {
        Student *stu = (Student *) node->obj;
        fprintf(fp, "%d\n", stu->id);
        fprintf(fp, "%s\n", stu->name);
    }
    fprintf(fp, "%d\n", paper->corrAuthors->size);
    for (Node *node = paper->corrAuthors->head->next; node != paper->corrAuthors->head; node = node->next) {
        Student *stu = (Student *) node->obj;
        fprintf(fp, "%d\n", stu->id);
        fprintf(fp, "%s\n", stu->name);
    }
    fprintf(fp, "%d\n", paper->awards->size);
    for (Node *node = paper->awards->head->next; node != paper->awards->head; node = node->next) {
        Pairif *pairif = (Pairif *) node->obj;
        fprintf(fp, "%d\n", pairif->i);
        fprintf(fp, "%.2f\n", pairif->f);
    }
}