#include <stdio.h>
#include "./../include/inc.h"
#include "./../Controller/Controller.h"

extern void testLogin() {
    printf("Test Login start\n");
    while(1){
        if (permission == 0) {
            login();
        }
        else {
            int op = inputInt("【1】注销\n【2】修改密码\n");
            switch (op) {
                case 1: {
                    logout();
                    break;
                }
                case 2: {
                    changePassword();
                    break;
                }
                default: {
                    break;
                }
            }
        }
    }


    printf("Test Login end\n");
}