#include <stdio.h>
#include <stdlib.h>
#include "./../Utils/List.h"

extern void testList() {
    printf("Test List start\n");
    List *list = createList();
    for (int i = 0; i < 10; i++) {
        int* p = (int *)malloc(sizeof(int));
        *p = i;
        append(list, p);
    }
    for (int i = 9; i >= 0; i--) {
        printf("%d ", *(int*)get(list, i));
    }
    printf("\n");
    delete(list, 5);
    for (int i = 0; i < 9; i++) {
        printf("%d ", *(int*)get(list, i));
    }
    printf("\n");
    printf("Test List end\n");
}