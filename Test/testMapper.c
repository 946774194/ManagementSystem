#include <stdio.h>
#include "./../include/inc.h"
#include "./../Mapper/Mapper.h"

extern void testMapper(){ // 测试数据层
    printf("Test Mapper start\n");
    Student *stu1 = createStudent();
    stu1->id = 1;
    stu1->stuId = 1001;
    stu1->name = "Tom";
    insertObj(StudentList, stu1);
    Student *stu2 = createStudent();
    stu2->id = 2;
    stu2->stuId = 1002;
    stu2->name = "Jerry";
    insertObj(StudentList, stu2);
    Student *stu3 = createStudent();
    stu3->id = 3;
    stu3->stuId = 1003;
    stu3->name = "Tom";
    insertObj(StudentList, stu3);


    const Student *stu = (Student*)getObjById(StudentList, 1);
    printf("stu->name: %s\n", stu->name);// stu->name: Tom

    const List *list = getStudentByName("Tom");
    Node *node = list->head->next;
    while (node != list->head) {
        Student *s = (Student *)node->obj;
        printf("stu->name: %s\n", s->name);// 2 Tom
        node = node->next;
    }

    stu = getStudentByStuId(1002);
    printf("stu->name: %s\n", stu->name);// stu->name: Jerry

    deleteObjById(StudentList, 1);
    printf("size: %d\n", StudentList->size);// size: 2
    stu = (Student*)get(StudentList, 0);
    printf("stu->name: %s\n", stu->name);// stu->name: Jerry
    printf("Test Mapper end\n");
}