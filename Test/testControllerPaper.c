#include <stdio.h>
#include <stdlib.h>
#include "./../include/inc.h"
#include "./../Service/Service.h"
#include "./../Controller/Controller.h"

extern void testControllerPaper(){
    printf("Testing ControllerPaper...\n");

    while(1){
        int op = inputInt("1. Insert\n2. Delete\n3. Update\n4. Get\n5. Save\n");
        switch(op){
            case 1:{
                InsertPaper();
                break;
            }
            case 2:{
                DeletePaper();
                break;
            }
            case 3:{
                UpdatePaper();
                break;
            }
            case 4:{
                GetPaper();
                break;
            }
            case 5:{
                saveAll();
                break;
            }
            default:{
                printf("Invalid input\n");
                break;
            }
        }
    }
}