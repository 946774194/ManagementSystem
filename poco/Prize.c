#include <stdlib.h>
#include <string.h>
#include "./../include/inc.h"
#include "./../Utils/Pairif.h"
#include "Prize.h"
#include "./../poco/Student.h"
#include "../Mapper/Mapper.h"

Prize *createPrize(){
    Prize *prize = (Prize *)malloc(sizeof(Prize));
    prize->name = NULL;
    prize->org = NULL;
    prize->level = NULL;
    prize->date = NULL;
    prize->isOrdered = 0;
    prize->authors = createList();
    prize->awards = createList();
    return prize;
}

char *prizeToString(const Prize *prize){
    char *str = (char *)malloc(512);
    char *authorsAndAwards = (char *)malloc(DEFAULT_BUFFER_SIZE);
    *authorsAndAwards = '\0';
    char *p = authorsAndAwards; // 作者和加分的字符串
    for (int i = 0; i < prize->authors->size; i++){
        Student *stu = (Student *)get(prize->authors, i);
        if(prize->isOrdered == 1) {
            sprintf(p, "%d ", i + 1); // 有序的话加上序号
            p += strlen(p);
        }
        sprintf(p, "%s", stu->name);
        p += strlen(p);
        if(getObjById(prize->awards, stu->id) != NULL){ // 如果有加分
            sprintf(p, " +%.2f", getF((Pairif *)getObjById(prize->awards, stu->id)));
            p += strlen(p);
        }
        if (i != prize->authors->size - 1){ // 不是最后一个作者
            sprintf(p, ", ");
            p += strlen(p);
        }
    }
    sprintf(str, "id: %d\t项目名称: %s\t主办单位: %s\t获奖等级: %s\t获奖日期: %s\n作者: %s\n", prize->id, prize->name, prize->org, prize->level, prize->date, authorsAndAwards);
    return str;
}

void showPrize(const Prize *prize){
    char *str = prizeToString(prize);
    printf("%s", str);
    free(str);
}

void destroyPrizeMembers(Prize *prize){
    free(prize->name);
    free(prize->org);
    free(prize->level);
    for (Node *node = prize->authors->head->next; node != prize->authors->head; node = node->next){
        Student *stu = (Student *)node->obj;
        free(stu->name);
        free(stu->scoreList);
        free(stu->paperList);
        free(stu->prizeList);
        free(stu->projectList);
        free(stu);
    }
    destroyList(prize->authors);
    destroyList(prize->awards);
}

Prize *readPrize(FILE *fp){
    Prize *prize = createPrize();
    fscanf(fp, "%d\n", &prize->id);
    prize->name = inputStringFromFile(fp);
    prize->org = inputStringFromFile(fp);
    prize->level = inputStringFromFile(fp);
    prize->date = inputStringFromFile(fp);
    fscanf(fp, "%d\n", &prize->isOrdered);
    int size;
    fscanf(fp, "%d\n", &size);
    for (int i = 0; i < size; i++){
        Student *stu = createStudent();
        fscanf(fp, "%d\n", &stu->id);
        stu->name = inputStringFromFile(fp);
        insertObj(prize->authors, stu);
    }
    fscanf(fp, "%d\n", &size);
    for (int i = 0; i < size; i++){
        Pairif *pairif = newPairif(0, 0);
        fscanf(fp, "%d\n", &pairif->i);
        fscanf(fp, "%f\n", &pairif->f);
        insertObj(prize->awards, pairif);
    }
    return prize;
}

void writePrize(FILE *fp, const Prize *prize){
    fprintf(fp, "%d\n", prize->id);
    fprintf(fp, "%s\n", prize->name);
    fprintf(fp, "%s\n", prize->org);
    fprintf(fp, "%s\n", prize->level);
    fprintf(fp, "%s\n", prize->date);
    fprintf(fp, "%d\n", prize->isOrdered);
    fprintf(fp, "%d\n", prize->authors->size);
    for (Node *node = prize->authors->head->next; node != prize->authors->head; node = node->next){
        Student *stu = (Student *)node->obj;
        fprintf(fp, "%d\n", stu->id);
        fprintf(fp, "%s\n", stu->name);
    }
    fprintf(fp, "%d\n", prize->awards->size);
    for (Node *node = prize->awards->head->next; node != prize->awards->head; node = node->next){
        Pairif *pairif = (Pairif *)node->obj;
        fprintf(fp, "%d\n", pairif->i);
        fprintf(fp, "%.2f\n", pairif->f);
    }
}