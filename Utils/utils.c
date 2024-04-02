#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "../include/inc.h"

char *orElse(char *str1, char *str2){
    return (str1)?str1:str2;
}

char *inputStringFromFile(FILE *fp){ // 从文件中读取一行字符串，包括空格
    char *str = (char *)malloc(DEFAULT_BUFFER_SIZE);
    fgets(str, DEFAULT_BUFFER_SIZE, fp);
    str[strlen(str) - 1] = '\0'; // 去掉换行符
    return str;
}

