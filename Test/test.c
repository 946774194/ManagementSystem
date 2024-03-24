#include <stdio.h>

extern void testList();
extern void testMapper();
extern void testInputStr();
extern void testControllerStudent();
extern void testControllerCourse();
extern void testControllerScore();
extern void testControllerPrize();
extern void testControllerPaper();
extern void testControllerProject();
extern void testControllerCRUD();
extern void testLogin();

extern void testAll() {
    printf("Test start\n");
//    testList();
//    testMapper();
//    testInputStr();
//    testControllerStudent();
//    testControllerCourse();
//    testControllerScore();
//    testControllerPrize();
//    testControllerPaper();
//    testControllerProject();
//    testControllerCRUD();
    testLogin();
    printf("Test end\n");
}
