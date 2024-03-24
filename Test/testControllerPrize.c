#include <stdio.h>
#include <stdlib.h>
#include "./../include/inc.h"
#include "./../Service/Service.h"
#include "./../Controller/Controller.h"

extern void testControllerPrize() {
    printf("Test Controller Prize start\n");

    while (1) {
        int op = inputInt("1. Insert\n2. Delete\n3. Update\n4. Get\n5. Save\n");
        switch (op) {
            case 1: {
                InsertPrize();
                break;
            }
            case 2: {
                DeletePrize();
                break;
            }
            case 3: {
                UpdatePrize();
                break;
            }
            case 4: {
                GetPrize();
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

    printf("Test Controller Prize end\n");

}