#include <stdio.h>
#include <stdlib.h>
#include "./../include/inc.h"
#include "./../Service/Service.h"
#include "./../Controller/Controller.h"

extern void testControllerCRUD() {
    printf("Test Controller CRUD start\n");

    while (1) {
        int op = inputInt("【1】新增\n【2】删除\n【3】更新\n【4】查询\n【5】统计\n【6】保存\n");
        switch (op) {
            case 1: {
                Insert();
                break;
            }
            case 2: {
                Delete();
                break;
            }
            case 3: {
                Update();
                break;
            }
            case 4: {
                Get();
                break;
            }
            case 5: {
                StatAnalyze();
                break;
            }
            case 6: {
                saveAll();
                break;
            }
            default: {
                break;
            }
        }
    }

    printf("Test Controller CRUD end\n");
}