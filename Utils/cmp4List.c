#include <string.h>
#include "cmp4List.h"
#include "./../poco/Student.h"

const float EPS = 1e-6f;

int cmpStuIdAsc(const void *a, const void *b) {
    return ((Student *)a)->stuId - ((Student *)b)->stuId;
}

int cmpStuIdDesc(const void *a, const void *b) {
    return -cmpStuIdAsc(a, b);
}

int cmpStuNameAsc(const void *a, const void *b) {
    return strcmp(((Student *)a)->name, ((Student *)b)->name);
}

int cmpStuNameDesc(const void *a, const void *b) {
    return -cmpStuNameAsc(a, b);
}

int cmpStuGPAAsc(const void *a, const void *b) {
    if(((Student *)a)->gpa - ((Student *)b)->gpa > EPS) {
        return 1;
    } else if(((Student *)a)->gpa - ((Student *)b)->gpa < -EPS) {
        return -1;
    } else {
        return 0;
    }
}

int cmpStuGPADesc(const void *a, const void *b) {
    return -cmpStuGPAAsc(a, b);
}