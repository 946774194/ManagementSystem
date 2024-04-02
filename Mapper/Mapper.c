#include <string.h>
#include "./../include/inc.h"
#include "./Mapper.h"
#include "./../Poco/Prize.h"

void insertObj(List *list, void *obj) {
    append(list, obj);
}

void deleteObjById(List *list, int id) { // 因为各个对象的id的偏移地址相同
    Node *node = list->head->next;
    for(int i = 0; node != list->head; i++) { // 遍历链表
        if(*(int *)node->obj == id) {
            delete(list, i);
            break;
        }
        node = node->next;
    }
}

const void *getObjById(List *list, int id) { // 因为各个对象的id的偏移地址相同
    Node *node = list->head->next;
    for(int i = 0; node != list->head; i++) {
        if(*(int *)node->obj == id) {
            return node->obj;
        }
        node = node->next;
    }
    return NULL;
}

List *getStudentByName(char *name) { // TODO: 可以使name的偏移地址也相同，优化重复代码
    List *result = createList();
    Node *node = StudentList->head->next;
    while (node != StudentList->head) {
        Student *stu = (Student *)node->obj;
        if (strcmp(stu->name, name) == 0) {
            append(result, stu);
        }
        node = node->next;
    }
    return result; // 返回结果链表，意味着可能有多个学生同名
}

Student *getStudentByStuId(int stuId) { // 通过学号获取学生
    Node *node = StudentList->head->next;
    while (node != StudentList->head) {
        Student *stu = (Student *)node->obj;
        if (stu->stuId == stuId) {
            return stu;
        }
        node = node->next;
    }
    return NULL;
}

List *getCourseByName(char *name) {
    List *result = createList();
    for (Node *node = CourseList->head->next; node != CourseList->head; node = node->next) {
        Course *course = (Course *)node->obj;
        if (strcmp(course->name, name) == 0) {
            append(result, course);
        }
    }
    return result;
}

List *getPrizeByName(char *name) {
    List *result = createList();
    for (Node *node = PrizeList->head->next; node != PrizeList->head; node = node->next) {
        Prize *prize = (Prize *)node->obj;
        if (strcmp(prize->name, name) == 0) {
            append(result, prize);
        }
    }
    return result;
}

List *getPaperByTitle(char *title) {
    List *result = createList();
    for (Node *node = PaperList->head->next; node != PaperList->head; node = node->next) {
        Paper *paper = (Paper *)node->obj;
        if (strcmp(paper->title, title) == 0) {
            append(result, paper);
        }
    }
    return result;
}

List *getProjectByName(char *name) {
    List *result = createList();
    for (Node *node = ProjectList->head->next; node != ProjectList->head; node = node->next) {
        Project *project = (Project *)node->obj;
        if (strcmp(project->name, name) == 0) {
            append(result, project);
        }
    }
    return result;
}