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

char *studentToString(const Student *stu){ // 生成字符串
    char *str = (char *)malloc(512);
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
    destroyList(stu->scoreList);
    destroyList(stu->prizeList);
    destroyList(stu->paperList);
    destroyList(stu->projectList);
}

Student *readStudent(FILE *fp){
    Student *stu = createStudent();
    fscanf(fp, "%d\n", &stu->id);
    fscanf(fp, "%d\n", &stu->stuId);
    int len;
    fscanf(fp, "%d\n", &len);
    if(len > 0){
        stu->pwd = inputStringFromFile(fp);
    }
    stu->name = stu->pwd = inputStringFromFile(fp);
    stu->subject = stu->pwd = inputStringFromFile(fp);
    int size;
    int *p = (int *)malloc(sizeof(int));
    fscanf(fp, "%d\n", &size); // 读取对象的记录数，下同
    for (int i = 0; i < size; i++) {
        fscanf(fp, "%d\n", p); // 读取一个对象的id，下同
        append(stu->scoreList, p);
        p = (int *)malloc(sizeof(int));
    }
    fscanf(fp, "%d\n", &size);
    for (int i = 0; i < size; i++) {
        fscanf(fp, "%d\n", p);
        append(stu->prizeList, p);
        p = (int *)malloc(sizeof(int));
    }
    fscanf(fp, "%d\n", &size);
    for (int i = 0; i < size; i++) {
        fscanf(fp, "%d\n", p);
        append(stu->paperList, p);
        p = (int *)malloc(sizeof(int));
    }
    fscanf(fp, "%d\n", &size);
    for (int i = 0; i < size; i++) {
        fscanf(fp, "%d\n", p);
        append(stu->projectList, p);
        p = (int *)malloc(sizeof(int));
    }
    return stu;
}

void writeStudent(FILE *fp, const Student *stu){
    fprintf(fp, "%d\n", stu->id);
    fprintf(fp, "%d\n", stu->stuId);
    if(stu->pwd != NULL){
        fprintf(fp, "%d\n", (int)strlen(stu->pwd)); // 写入可选字符串时先写入字符串长度
        fprintf(fp, "%s\n", stu->pwd);
    }else{
        fprintf(fp, "0\n");
    }
    fprintf(fp, "%s\n", stu->name);
    fprintf(fp, "%s\n", stu->subject);
    fprintf(fp, "%d\n", stu->scoreList->size);
    for (Node *node = stu->scoreList->head->next; node != stu->scoreList->head; node = node->next) {
        fprintf(fp, "%d\n", *(int*)node->obj); // 保存对象的id，下同
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