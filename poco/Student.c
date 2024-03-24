#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./../include/inc.h"
#include "./../Poco/Student.h"

Student *createStudent(){
    Student *stu = (Student *)malloc(sizeof(Student)); // 由delete()free
    stu->id = 0;
    stu->stuId = 0;
    stu->pwd = NULL; // 可选
    stu->name = NULL;
    stu->subject = NULL;
    stu->scoreList = createList();
    stu->prizeList = createList();
    stu->paperList = createList();
    stu->projectList = createList();
    return stu;
}

char *studentToString(const Student *stu){
    char *str = (char *)malloc(512); // 由调用者free
    sprintf(str, "id: %d\n学号: %d\n姓名: %s\n专业: %s\n"
                 "成绩记录数: %d\n获奖记录数: %d\n论文记录数: %d\n项目记录数: %d\n",
            stu->id, stu->stuId, stu->name, stu->subject,
            stu->scoreList->size, stu->prizeList->size, stu->paperList->size, stu->projectList->size);
    return str;
}

void showStudent(const Student *stu){
    char *str = studentToString(stu);
    printf("%s\n", str);
    free(str);
}

void destroyStudentMembers(Student *stu){
    if(stu->pwd != NULL){
        free(stu->pwd);
    }
    free(stu->name);
    free(stu->subject);
    destroyList(stu->scoreList);// TODO: destroyIntList()
    destroyList(stu->prizeList);
    destroyList(stu->paperList);
    destroyList(stu->projectList);
}

Student *readStudent(FILE *fp){// 由destroyStudentMembers()free
    Student *stu = createStudent();
    fscanf(fp, "%d", &stu->id);
    fscanf(fp, "%d", &stu->stuId);
    int len;// TODO:
    fscanf(fp, "%d", &len);
    if(len > 0){
        stu->pwd = (char *)malloc(len + 1);
        fscanf(fp, "%s", stu->pwd);
    }
    stu->name = (char *)malloc(DEFAULT_BUFFER_SIZE);
    fscanf(fp, "%s", stu->name);
    stu->subject = (char *)malloc(DEFAULT_BUFFER_SIZE);
    fscanf(fp, "%s", stu->subject);
    int size;
    int *p = (int *)malloc(sizeof(int));
    fscanf(fp, "%d", &size);
    for (int i = 0; i < size; i++) {
        fscanf(fp, "%d", p);
        append(stu->scoreList, p);
        p = (int *)malloc(sizeof(int));
    }
    fscanf(fp, "%d", &size);
    for (int i = 0; i < size; i++) {
        fscanf(fp, "%d", p);
        append(stu->prizeList, p);
        p = (int *)malloc(sizeof(int));
    }
    fscanf(fp, "%d", &size);
    for (int i = 0; i < size; i++) {
        fscanf(fp, "%d", p);
        append(stu->paperList, p);
        p = (int *)malloc(sizeof(int));
    }
    fscanf(fp, "%d", &size);
    for (int i = 0; i < size; i++) {
        fscanf(fp, "%d", p);
        append(stu->projectList, p);
        p = (int *)malloc(sizeof(int));
    }
    return stu;
}

void writeStudent(FILE *fp, const Student *stu){
    fprintf(fp, "%d\n", stu->id);
    fprintf(fp, "%d\n", stu->stuId);
    if(stu->pwd != NULL){
        fprintf(fp, "%d\n", (int)strlen(stu->pwd));
        fprintf(fp, "%s\n", stu->pwd);
    }else{
        fprintf(fp, "0\n");
    }
    fprintf(fp, "%s\n", stu->name);
    fprintf(fp, "%s\n", stu->subject);
    fprintf(fp, "%d\n", stu->scoreList->size);
    for (Node *node = stu->scoreList->head->next; node != stu->scoreList->head; node = node->next) {
        fprintf(fp, "%d\n", *(int*)node->obj);
    }
    fprintf(fp, "%d\n", stu->prizeList->size);
    for (Node *node = stu->prizeList->head->next; node != stu->prizeList->head; node = node->next) {
        fprintf(fp, "%d\n", *(int*)node->obj);
    }
    fprintf(fp, "%d\n", stu->paperList->size);
    for (Node *node = stu->paperList->head->next; node != stu->paperList->head; node = node->next) {
        fprintf(fp, "%d\n", *(int*)node->obj);
    }
    fprintf(fp, "%d\n", stu->projectList->size);
    for (Node *node = stu->projectList->head->next; node != stu->projectList->head; node = node->next) {
        fprintf(fp, "%d\n", *(int*)node->obj);
    }
}