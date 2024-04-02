#include <string.h>
#include "cmp4List.h"
#include "./../poco/Student.h"

const float EPS = 1e-6f;

int cmpStuIdAsc(const void *a, const void *b) { // 按学号升序
    return ((Student *)a)->stuId - ((Student *)b)->stuId;
}

int cmpStuIdDesc(const void *a, const void *b) { // 按学号降序
    return -cmpStuIdAsc(a, b);
}

int cmpStuNameAsc(const void *a, const void *b) { // 按姓名升序
    return strcmp(((Student *)a)->name, ((Student *)b)->name);
}

int cmpStuNameDesc(const void *a, const void *b) { // 按姓名降序
    return -cmpStuNameAsc(a, b);
}

int cmpStuGPAAsc(const void *a, const void *b) { // 按GPA升序
    if(((Student *)a)->gpa - ((Student *)b)->gpa > EPS) {
        return 1;
    } else if(((Student *)a)->gpa - ((Student *)b)->gpa < -EPS) {
        return -1;
    } else {
        return 0;
    }
}

int cmpStuGPADesc(const void *a, const void *b) { // 按GPA降序
    return -cmpStuGPAAsc(a, b);
}