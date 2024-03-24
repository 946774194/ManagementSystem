#include <stdio.h>
#include <stdlib.h>
#include "./../include/inc.h"
#include "./../Service/Service.h"
#include "./../Controller/Controller.h"

extern void testControllerProject() {
    printf("Test Controller Project start\n");

    while (1) {
        int op = inputInt("1. Insert\n2. Delete\n3. Update\n4. Get\n5. Save\n");
        switch (op) {
            case 1: {
                InsertProject();
                break;
            }
            case 2: {
                DeleteProject();
                break;
            }
            case 3: {
                UpdateProject();
                break;
            }
            case 4: {
                GetProject();
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

    printf("Test Controller Project end\n");

}