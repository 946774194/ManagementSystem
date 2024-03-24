#include <stdio.h>
#include <stdlib.h>
#include "./../include/inc.h"
#include "./../Service/Service.h"
#include "./../Controller/Controller.h"

extern void testControllerCourse(){
    printf("Test Controller Course start\n");

    while (1){
        int op = inputInt("1. Insert\n2. Delete\n3. Update\n4. Get\n5. Save\n");
        switch (op) {
            case 1: {
                InsertCourse();
                break;
            }
            case 2: {
                DeleteCourse();
                break;
            }
            case 3: {
                UpdateCourse();
                break;
            }
            case 4: {
                for (Node *node = CourseList->head->next; node != CourseList->head; node = node->next) {
                    Course *course = (Course *) node->obj;
                    showCourse(course);
                }
                system("pause");
                break;
            }
            case 5: {
                saveAll();
                break;
            }
            default: {
                printf("Invalid input\n");
                break;
            }
        }
    }

    printf("Test Controller Course end\n");
}