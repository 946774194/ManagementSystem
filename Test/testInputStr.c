#include <stdio.h>
#include "./../Controller/Controller.h"

extern void testInputStr() {
    char *str = NULL;
    str = inputStr("Please input a string");
    printf("You input: %s\n", str);

    str = inputStrn("Please input a string with max length 10", 10);
    printf("You input: %s\n", str);

    str = inputOptionalStrn("Please input a string with max length 10", 10);
    printf("You input: %s\n", str);

    int i = inputInt("Please input an integer");
    printf("You input: %d\n", i);

    float f = inputFloat("Please input a float");
    printf("You input: %f\n", f);

}