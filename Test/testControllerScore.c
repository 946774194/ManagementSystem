#include <stdio.h>
#include <stdlib.h>
#include "./../include/inc.h"
#include "./../Service/Service.h"
#include "./../Controller/Controller.h"

extern void testControllerScore(){
    printf("Test Controller Score start\n");

    while (1){
        int op = inputInt("1. Insert\n2. Delete\n3. Update\n4. Get\n5. Save\n");
        switch (op) {
            case 1: {
                InsertScore();
                break;
            }
            case 2: {
                DeleteScore();
                break;
            }
            case 3: {
                UpdateScore();
                break;
            }
            case 4: {
                GetScore();
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

    printf("Test Controller Score end\n");
}