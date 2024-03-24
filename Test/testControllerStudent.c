#include <stdio.h>
#include "./../Service/Service.h"
#include "./../Controller/Controller.h"

extern void testControllerStudent(){
    printf("Test Controller Student start\n");

    while (1){
        int op = inputInt("1. Insert\n2. Delete\n3. Update\n4. Get\n5. Save\n");
        switch (op) {
            case 1: {
                InsertStudent();
                break;
            }
            case 2: {
                DeleteStudent();
                break;
            }
            case 3: {
                UpdateStudent();
                break;
            }
            case 4: {
                GetStudent();
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

    printf("Test Controller Student end\n");
}