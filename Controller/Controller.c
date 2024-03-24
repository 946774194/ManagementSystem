#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "./../include/inc.h"
#include "Controller.h"
#include "./../Service/Service.h"
#include "./../Mapper/Mapper.h"
#include "./../Utils/cmp4List.h"
#include "./../Utils/Pairif.h"
#include "./../Utils/Logger.h"

extern void showWelcomeScreen();

void clearInputBuffer() {
    int ch;
    while ((ch = getchar()) != EOF && ch != '\n');
}

char *inputOptionalStrn(char *prompt, int maxSize) {
    char *buffer = (char *) malloc(maxSize); // 由最终字符串接受者free
    if (buffer == NULL) return NULL;

    system("cls");
    printf("%s\n", prompt);
    char *res = fgets(buffer, maxSize, stdin);
    if (res == NULL) {
        free(buffer);
        return NULL;
    }

    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else {
        clearInputBuffer();
    }

    return buffer;
}

char *inputStrn(char *prompt, int maxSize) {
    char *res = NULL;
    do {
        res = inputOptionalStrn(prompt, maxSize);
    } while (!res || strlen(res) == 0);
    return res;
}

char *inputStr(char *prompt) {
    return inputStrn(prompt, DEFAULT_BUFFER_SIZE);
}

int inputInt(char *prompt) {
    char *str = NULL;
    do {
        str = inputStr(prompt);
    } while (!isdigit(*str));
    int res = strtol(str, NULL, 10);
    free(str);
    return res;
}

float inputFloat(char *prompt) {
    char *str = NULL;
    do {
        str = inputStr(prompt);
    } while (!isdigit(*str));
    float res = strtof(str, NULL);
    free(str);
    return res;
}

Student *inputStudent() {
    Student *stu = createStudent();
    stu->stuId = inputInt("请输入学号:");
    stu->pwd = NULL;
    stu->name = inputStr("请输入姓名:");
    stu->subject = inputStr("请输入专业:");
    return stu;
}

Course *inputCourse() {
    Course *course = createCourse();
    course->name = inputStr("请输入课程名:");
    course->subject = inputStr("请输入专业:");
    course->teacher = inputStr("请输入教师:");
    course->term = inputStr("请输入学年学期:");
    course->isReq = inputInt("是否必修(1/0):");
    course->credit = inputFloat("请输入学分:");
    course->period = inputInt("请输入学时:");
    return course;
}

Score *inputScore() {
    Score *score = createScore();
    score->stuId = inputInt("请输入学号:");
//    score->courseId = inputInt("请输入课程id:");
    score->score = inputInt("请输入总成绩:");
    score->point = inputFloat("请输入绩点:");
    return score;
}

Prize *inputPrize() {
    Prize *prize = createPrize();
    prize->name = inputStr("请输入奖项名:");
    prize->org = inputStr("请输入主办单位:");
    prize->level = inputStr("请输入奖项级别:");
    prize->date = inputStr("请输入获奖日期:");
    prize->isOrdered = inputInt("是否有序(1/0):");
    int num = inputInt("请输入作者数量:");
    for (int i = 0; i < num; i++) {
        Student *stu = createStudent();
        stu->name = inputStr("请输入作者名:");
        stu->id = -1;
        int isExist = inputInt("是否为在系统学生(1/0):");
        if (isExist == 1) {
            int stuId = inputInt("请输入学号:");
            Student *s = getStudentByStuId(stuId);
            if (s && getObjById(prize->authors, s->id)) {
                printf("学生已添加\n");
                system("pause");
                destroyStudentMembers(stu);
                free(stu);
                i--;
                continue;
            } else if (s && strcmp(s->name, stu->name) == 0) {
                stu->id = s->id;
            } else {
                printf("学生不存在\n");
                system("pause");
                destroyStudentMembers(stu);
                free(stu);
                i--;
                continue;
            }
            float award = inputFloat("请输入加分数");
            if (award > 0) {
                Pairif *pairif = newPairif(stu->id, award);
                insertObj(prize->awards, pairif);
            }
        }
        insertObj(prize->authors, stu);
    }
    return prize;
}

Paper *inputPaper() {
    Paper *paper = createPaper();
    paper->title = inputStr("请输入论文题目:");
    paper->journalName = inputStr("请输入期刊名:");
    paper->publishDate = inputStr("请输入发表日期:");
    paper->level = inputStr("请输入级别:");
    paper->volume = inputOptionalStrn("请输入卷号:", DEFAULT_BUFFER_SIZE);
    paper->issue = inputOptionalStrn("请输入期号:", DEFAULT_BUFFER_SIZE);
    paper->paperId = inputOptionalStrn("请输入论文号:", DEFAULT_BUFFER_SIZE);
    paper->page = inputOptionalStrn("请输入页码:", DEFAULT_BUFFER_SIZE);
    int num = inputInt("请输入作者数量:");
    for (int i = 0; i < num; i++) {
        Student *stu = createStudent();
        stu->name = inputStr("请输入作者名:");
        stu->id = -1;
        int isExist = inputInt("是否为在系统学生(1/0):");
        if (isExist == 1) {
            int stuId = inputInt("请输入学号:");
            Student *s = getStudentByStuId(stuId);
            if (s && (getObjById(paper->authors, s->id) ||
                      getObjById(paper->corrAuthors, s->id))) {
                printf("学生已添加\n");
                system("pause");
                destroyStudentMembers(stu);
                free(stu);
                i--;
                continue;
            } else if (s && strcmp(s->name, stu->name) == 0) {
                stu->id = s->id;
            } else {
                printf("学生不存在\n");
                system("pause");
                i--;
                continue;
            }
            float award = inputFloat("请输入加分数");
            if (award > 0) {
                Pairif *pairif = newPairif(stu->id, award);
                insertObj(paper->awards, pairif);
            }
        }
        insertObj(paper->authors, stu);
    }
    num = inputInt("请输入通讯作者数量:");
    for (int i = 0; i < num; i++) {
        Student *stu = createStudent();
        stu->name = inputStr("请输入通讯作者名:");
        stu->id = -1;
        int isExist = inputInt("是否为在系统学生(1/0):");
        if (isExist == 1) {
            int stuId = inputInt("请输入学号:");
            Student *s = getStudentByStuId(stuId);
            if (s && (getObjById(paper->corrAuthors, s->id) ||
                      getObjById(paper->authors, s->id))) {
                printf("学生已添加\n");
                system("pause");
                destroyStudentMembers(stu);
                free(stu);
                i--;
                continue;
            } else if (s && strcmp(s->name, stu->name) == 0) {
                stu->id = s->id;
            } else {
                printf("学生不存在\n");
                system("pause");
                destroyStudentMembers(stu);
                free(stu);
                i--;
                continue;
            }
            float award = inputFloat("请输入加分数");
            if (award > 0) {
                Pairif *pairif = newPairif(stu->id, award);
                insertObj(paper->awards, pairif);
            }
        }
        insertObj(paper->corrAuthors, stu);
    }
    return paper;
}

Project *inputProject() {
    Project *project = createProject();
    project->teacher = inputStr("请输入指导老师:");
    project->name = inputStr("请输入项目名:");
    project->code = inputStr("请输入项目编号:");
    project->startDate = inputStr("请输入开始日期:");
    project->endDate = inputStr("请输入结束日期:");
    int num = inputInt("请输入作者数量:");
    for (int i = 0; i < num; i++) {
        Student *stu = createStudent();
        stu->name = inputStr("请输入作者名:");
        stu->id = -1;
        int isExist = inputInt("是否为在系统学生(1/0):");
        if (isExist == 1) {
            int stuId = inputInt("请输入学号:");
            Student *s = getStudentByStuId(stuId);
            if (s && getObjById(project->authors, s->id)) {
                printf("学生已添加\n");
                system("pause");
                destroyStudentMembers(stu);
                free(stu);
                i--;
                continue;
            } else if (s && strcmp(s->name, stu->name) == 0) {
                stu->id = s->id;
            } else {
                printf("学生不存在\n");
                system("pause");
                destroyStudentMembers(stu);
                free(stu);
                i--;
                continue;
            }
            float award = inputFloat("请输入加分数");
            if (award > 0) {
                Pairif *pairif = newPairif(stu->id, award);
                insertObj(project->awards, pairif);
            }
        }
        insertObj(project->authors, stu);
    }
    return project;
}

void InsertStudent() {
    logger.info("开始增加学生");
    Student *stu = inputStudent();
    if (getStudentByStuId(stu->stuId)) {
        printf("学号已存在\n");
        logger.info("结束增加学生，学号已存在，stuId: %d", stu->stuId);
        system("pause");
        return;
    }
    insertStudent(stu);
    logger.info("结束增加学生");
}

void InsertStudentFromFile() {
    logger.info("开始从文件增加学生");
    char *filename = inputStr("请输入文件名:");
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("文件打开失败\n");
        logger.info("结束从文件增加学生，文件打开失败");
        system("pause");
        free(filename);
        return;
    }
    while (!feof(fp)) {
        Student *stu = createStudent();
        if (fscanf(fp, "%d", &stu->stuId) == EOF) {
            destroyStudentMembers(stu);
            free(stu);
            break;
        }
        stu->name = (char *) malloc(DEFAULT_BUFFER_SIZE);
        fscanf(fp, "%s", stu->name);
        stu->subject = (char *) malloc(DEFAULT_BUFFER_SIZE);
        fscanf(fp, "%s", stu->subject);

        insertStudent(stu);
    }
    fclose(fp);
    free(filename);
    logger.info("结束从文件增加学生");
}

void DeleteStudentById() {
    int stuId = inputInt("请输入学号:");
    const Student *stu = getStudentByStuId(stuId);
    if (stu == NULL) {
        printf("学号不存在\n");
        logger.info("结束删除学生，学号不存在，stuId: %d", stuId);
        system("pause");
        return;
    }
    deleteStudentById(stu->id);
}

void DeleteStudentByName() {
    char *name = inputStr("请输入姓名:");
    const List *list = getStudentByName(name);
    switch (list->size) {
        case 0:
            printf("姓名不存在\n");
            logger.info("结束删除学生，姓名不存在，name: %s", name);
            system("pause");
            break;
        case 1:
            deleteStudentById(((Student *) list->head->next->obj)->id);
            break;
        default: {
            char *prompt = malloc(512); // 函数内free
            sprintf(prompt, "找到多个学生：请输入学号：\n");
            char *p = prompt + strlen(prompt);
            for (Node *node = list->head->next; node != list->head; node = node->next, p += strlen(p)) {
                Student *stu = (Student *) node->obj;
                sprintf(p, "姓名：%s\t学号：%d\t专业：%s\n", stu->name, stu->stuId, stu->subject);
            }
            int stuId = inputInt(prompt);
            const Student *stu = getStudentByStuId(stuId);
            if (stu == NULL) {
                printf("学号不存在\n");
                logger.info("结束删除学生，学号不存在，stuId: %d", stuId);
                system("pause");
            } else {
                deleteStudentById(stu->id);
            }
            free(prompt);
            free(name);

        }
    }
}

void DeleteStudent() {
    logger.info("开始删除学生");
    int op = inputInt("【1】按学号删除\n【2】按姓名删除\n");
    if (op == 1) {
        DeleteStudentById();
    } else if (op == 2) {
        DeleteStudentByName();
    }
    logger.info("结束删除学生");
}

void UpdateStudentByStuId() {
    int stuId = inputInt("请输入学号:");
    const Student *stu = getStudentByStuId(stuId);
    if (stu == NULL) {
        printf("学号不存在\n");
        logger.info("结束修改学生，学号不存在，stuId: %d", stuId);
        system("pause");
        return;
    }
    Student *newStu = inputStudent();
    newStu->id = stu->id;
    updateStudent(newStu);
}

void UpdateStudentByName() {
    char *name = inputStr("请输入姓名:");
    List *list = getStudentByName(name);
    switch (list->size) {
        case 0:
            printf("姓名不存在\n");
            logger.info("结束修改学生，姓名不存在，name: %s", name);
            break;
        case 1: {
            Student *newStu = inputStudent();
            newStu->id = ((Student *) list->head->next->obj)->id;
            updateStudent(newStu);
            break;
        }
        default: {
            char *prompt = malloc(512); // 函数内free
            sprintf(prompt, "找到多个学生：请输入学号：\n");
            char *p = prompt + strlen(prompt);
            for (Node *node = list->head->next; node != list->head; node = node->next, p += strlen(p)) {
                Student *stu = (Student *) node->obj;
                sprintf(p, "姓名：%s\t学号：%d\t专业：%s\n", stu->name, stu->stuId, stu->subject);
            }
            int stuId = inputInt(prompt);
            const Student *stu = getStudentByStuId(stuId);
            if (stu == NULL) {
                printf("学号不存在\n");
                logger.info("结束修改学生，学号不存在，stuId: %d", stuId);
                return;
            }
            Student *newStu = inputStudent();
            newStu->id = stu->id;
            updateStudent(newStu);
            destroyList(list);
            free(prompt);
            free(name);
        }
    }
}

void UpdateStudent() {
    logger.info("开始修改学生");
    int op = inputInt("【1】按学号修改\n【2】按姓名修改\n");
    if (op == 1) {
        UpdateStudentByStuId();
    } else if (op == 2) {
        UpdateStudentByName();
    }
    logger.info("结束修改学生");
}

void GetStudentByStuId() {
    int stuId = inputInt("请输入学号:");
    const Student *stu = getStudentByStuId(stuId);
    if (stu == NULL) {
        printf("学号不存在\n");
        logger.info("结束查询学生，学号不存在，stuId: %d", stuId);
        return;
    }
    showStudent(stu);
    system("pause");
}

void GetStudentByName() {
    char *name = inputStr("请输入姓名:");
    List *list = getStudentByName(name);
    if (list->size == 0) {
        printf("姓名不存在\n");
        logger.info("结束查询学生，姓名不存在，name: %s", name);
        destroyList(list);
        return;
    }
    int op = inputInt("【1】学号升序\n【2】学号降序\n");
    switch (op) {
        case 1:
            sort(list, cmpStuIdAsc);
            break;
        case 2:
            sort(list, cmpStuIdDesc);
            break;
        default:
            sort(list, cmpStuIdAsc);
            return;
    }
    for (Node *node = list->head->next; node != list->head; node = node->next) {
        Student *stu = (Student *) node->obj;
        showStudent(stu);
    }
    system("pause");
    destroyList(list);
}

void GetStudent() {
    logger.info("开始查询学生");
    int op = inputInt("【1】按学号查询\n【2】按姓名查询\n");
    if (op == 1) {
        GetStudentByStuId();
    } else if (op == 2) {
        GetStudentByName();
    }
    logger.info("结束查询学生");
}

void InsertCourse() {
    logger.info("开始增加课程");
    Course *course = inputCourse();
    insertCourse(course);
    logger.info("结束增加课程");
}

void InsertCourseFromFile() {
    logger.info("开始从文件增加课程");
    char *filename = inputStr("请输入文件名:");
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("文件打开失败\n");
        system("pause");
        free(filename);
        return;
    }
    while (!feof(fp)) {
        Course *course = createCourse();
        course->name = (char *) malloc(DEFAULT_BUFFER_SIZE);
        if (fscanf(fp, "%s", course->name) == EOF) {
            free(course->name);
            free(course);
            break;
        }
        course->subject = (char *) malloc(DEFAULT_BUFFER_SIZE);
        fscanf(fp, "%s", course->subject);
        course->teacher = (char *) malloc(DEFAULT_BUFFER_SIZE);
        fscanf(fp, "%s", course->teacher);
        course->term = (char *) malloc(DEFAULT_BUFFER_SIZE);
        fscanf(fp, "%s", course->term);
        fscanf(fp, "%d", &course->isReq);
        fscanf(fp, "%f", &course->credit);
        fscanf(fp, "%d", &course->period);
        insertCourse(course);
    }
    fclose(fp);
    free(filename);
    logger.info("结束从文件增加课程");
}

void DeleteCourse() {
    logger.info("开始删除课程");
    for (Node *node = CourseList->head->next; node != CourseList->head; node = node->next) {
        Course *course = (Course *) node->obj;
        showCourse(course);
    }
    system("pause");
    int id = inputInt("请输入要删除的id:");
    if (getCourseById(id) == NULL) {
        printf("id不存在\n");
        logger.info("结束删除课程，id不存在，id: %d", id);
        system("pause");
        return;
    }
    deleteCourseById(id);
    logger.info("结束删除课程");
}

void UpdateCourse() {
    logger.info("开始修改课程");
    for (Node *node = CourseList->head->next; node != CourseList->head; node = node->next) {
        Course *course = (Course *) node->obj;
        showCourse(course);
    }
    system("pause");
    int id = inputInt("请输入要修改的id:");
    if (getCourseById(id) == NULL) {
        printf("id不存在\n");
        logger.info("结束修改课程，id不存在，id: %d", id);
        system("pause");
        return;
    }
    Course *course = inputCourse();
    course->id = id;
    updateCourse(course);
    logger.info("结束修改课程");
}

void GetCourse() {
    logger.info("开始查询课程");
    char *name = inputStr("请输入课程名:");
    List *list = getCourseByName(name);
    if (list->size == 0) {
        printf("课程名不存在\n");
        logger.info("结束查询课程，课程名不存在，name: %s", name);
        system("pause");
        return;
    }
    for (Node *node = list->head->next; node != list->head; node = node->next) {
        Course *course = (Course *) node->obj;
        showCourse(course);
    }
    system("pause");
    destroyList(list);
    free(name);
    logger.info("结束查询课程");
}

void InsertScore() {
    logger.info("开始增加成绩");
    char *courseName = inputStr("请输入课程名:");
    List *list = getCourseByName(courseName);
    int courseId;
    if (list->size == 0) {
        printf("课程名不存在\n");
        logger.info("结束增加成绩，课程名不存在，courseName: %s", courseName);
        system("pause");
        destroyList(list);
        free(courseName);
        return;
    } else if (list->size > 1) {
        printf("找到多个课程：\n");
        for (Node *node = list->head->next; node != list->head; node = node->next) {
            Course *course = (Course *) node->obj;
            showCourse(course);
        }
        system("pause");
        courseId = inputInt("请输入课程id:");
        if (getCourseById(courseId) == NULL) {
            printf("id不存在\n");
            logger.info("结束增加成绩，课程id不存在，id: %d", courseId);
            system("pause");
            destroyList(list);
            free(courseName);
            return;
        }
    } else {
        courseId = ((Course *) list->head->next->obj)->id;
    }
    Score *score = inputScore();
    score->courseId = courseId;
    Student *stu = getStudentByStuId(score->stuId);
    if (stu == NULL) {
        printf("学号不存在\n");
        logger.info("结束增加成绩，学号不存在，stuId: %d", score->stuId);
        system("pause");
        destroyList(list);
        free(courseName);
        return;
    }
    insertScore(score, stu->id);
    destroyList(list);
    free(courseName);
    logger.info("结束增加成绩");
}

void DeleteScore() {
    logger.info("开始删除成绩");
    int stuId = inputInt("请输入学号:");
    Student *stu = getStudentByStuId(stuId);
    if (stu == NULL) {
        printf("学号不存在\n");
        logger.info("结束删除成绩，学号不存在，stuId: %d", stuId);
        system("pause");
        return;
    }
    List *list = stu->scoreList;
    for (Node *node = list->head->next; node != list->head; node = node->next) {
        int *id = (int *) node->obj;
        Score *score = getScoreById(*id);
        showScore(score);
    }
    system("pause");
    int id = inputInt("请输入要删除的id:");
    if (getScoreById(id) == NULL) {
        printf("id不存在\n");
        logger.info("结束删除成绩，id不存在，id: %d", id);
        system("pause");
        return;
    }
    deleteScoreById(id);
    logger.info("结束删除成绩");
}

void UpdateScore() {
    logger.info("开始修改成绩");
    int stuId = inputInt("请输入学号:");
    Student *stu = getStudentByStuId(stuId);
    if (stu == NULL) {
        printf("学号不存在\n");
        logger.info("结束修改成绩，学号不存在，stuId: %d", stuId);
        system("pause");
        return;
    }
    List *list = stu->scoreList;
    for (Node *node = list->head->next; node != list->head; node = node->next) {
        int *id = (int *) node->obj;
        Score *score = getScoreById(*id);
        showScore(score);
    }
    system("pause");
    int id = inputInt("请输入要修改的id:");
    Score *score = getScoreById(id);
    if (score == NULL) {
        printf("id不存在\n");
        logger.info("结束修改成绩，id不存在，id: %d", id);
        system("pause");
        return;
    }
    Score *newScore = inputScore();
    newScore->id = score->id;
    updateScore(newScore);
    logger.info("结束修改成绩");
}

void GetScore() {
    logger.info("开始查询成绩");
    int stuId = inputInt("请输入学号:");
    Student *stu = getStudentByStuId(stuId);
    if (stu == NULL) {
        printf("学号不存在\n");
        logger.info("结束查询成绩，学号不存在，stuId: %d", stuId);
        system("pause");
        return;
    }
    List *list = stu->scoreList;
    for (Node *node = list->head->next; node != list->head; node = node->next) {
        int *id = (int *) node->obj;
        Score *score = getScoreById(*id);
        showScore(score);
    }
    system("pause");
    logger.info("结束查询成绩");
}

void InsertPrize() {
    logger.info("开始增加奖项");
    Prize *prize = inputPrize();
    insertPrize(prize);
    logger.info("结束增加奖项");
}

void DeletePrize() {
    logger.info("开始删除奖项");
    for (Node *node = PrizeList->head->next; node != PrizeList->head; node = node->next) {
        Prize *prize = (Prize *) node->obj;
        showPrize(prize);
    }
    system("pause");
    int id = inputInt("请输入要删除的id:");
    if (getPrizeById(id) == NULL) {
        printf("id不存在\n");
        logger.info("结束删除奖项，id不存在，id: %d", id);
        system("pause");
        return;
    }
    deletePrizeById(id);
    logger.info("结束删除奖项");
}

void UpdatePrize() {
    logger.info("开始修改奖项");
    for (Node *node = PrizeList->head->next; node != PrizeList->head; node = node->next) {
        Prize *prize = (Prize *) node->obj;
        showPrize(prize);
    }
    system("pause");
    int id = inputInt("请输入要修改的id:");
    if (getPrizeById(id) == NULL) {
        printf("id不存在\n");
        logger.info("结束修改奖项，id不存在，id: %d", id);
        system("pause");
        return;
    }
    Prize *prize = inputPrize();
    prize->id = id;
    updatePrize(prize);
    logger.info("结束修改奖项");
}

void GetPrize() {
    logger.info("开始查询奖项");
    int op = inputInt("【1】按学生学号查询\n【2】按奖项名查询\n");
    switch (op) {
        case 1: {
            int stuId = inputInt("请输入学号:");
            Student *stu = getStudentByStuId(stuId);
            if (stu == NULL) {
                printf("学号不存在\n");
                logger.info("结束查询奖项，学号不存在，stuId: %d", stuId);
                system("pause");
                return;
            }
            List *list = stu->prizeList;
            for (Node *node = list->head->next; node != list->head; node = node->next) {
                int *id = (int *) node->obj;
                Prize *prize = getPrizeById(*id);
                showPrize(prize);
            }
            system("pause");
            break;
        }
        case 2: {
            char *name = inputStr("请输入奖项名:");
            List *list = getPrizeByName(name);
            if (list->size == 0) {
                printf("奖项名不存在\n");
                logger.info("结束查询奖项，奖项名不存在，name: %s", name);
                system("pause");
                free(name);
                destroyList(list);
                return;
            }
            for (Node *node = list->head->next; node != list->head; node = node->next) {
                Prize *prize = (Prize *) node->obj;
                showPrize(prize);
            }
            system("pause");
            destroyList(list);
            free(name);
            break;
        }
        default:
            break;
    }
    logger.info("结束查询奖项");
}

void InsertPaper() {
    logger.info("开始增加论文");
    Paper *paper = inputPaper();
    insertPaper(paper);
    logger.info("结束增加论文");
}

void DeletePaper() {
    logger.info("开始删除论文");
    for (Node *node = PaperList->head->next; node != PaperList->head; node = node->next) {
        Paper *paper = (Paper *) node->obj;
        showPaper(paper);
    }
    system("pause");
    int id = inputInt("请输入要删除的id:");
    if (getPaperById(id) == NULL) {
        printf("id不存在\n");
        logger.info("结束删除论文，id不存在，id: %d", id);
        system("pause");
        return;
    }
    deletePaperById(id);
    logger.info("结束删除论文");
}

void UpdatePaper() {
    logger.info("开始修改论文");
    for (Node *node = PaperList->head->next; node != PaperList->head; node = node->next) {
        Paper *paper = (Paper *) node->obj;
        showPaper(paper);
    }
    system("pause");
    int id = inputInt("请输入要修改的id:");
    if (getPaperById(id) == NULL) {
        printf("id不存在\n");
        logger.info("结束修改论文，id不存在，id: %d", id);
        system("pause");
        return;
    }
    Paper *paper = inputPaper();
    paper->id = id;
    updatePaper(paper);
    logger.info("结束修改论文");
}

void GetPaper() {
    logger.info("开始查询论文");
    int op = inputInt("【1】按学生学号查询\n【2】按论文题目查询\n");
    switch (op) {
        case 1: {
            int stuId = inputInt("请输入学号:");
            Student *stu = getStudentByStuId(stuId);
            if (stu == NULL) {
                printf("学号不存在\n");
                logger.info("结束查询论文，学号不存在，stuId: %d", stuId);
                system("pause");
                return;
            }
            List *list = stu->paperList;
            for (Node *node = list->head->next; node != list->head; node = node->next) {
                int *id = (int *) node->obj;
                Paper *paper = getPaperById(*id);
                showPaper(paper);
            }
            system("pause");
            break;
        }
        case 2: {
            char *title = inputStr("请输入论文题目:");
            List *list = getPaperByTitle(title);
            if (list->size == 0) {
                printf("论文题目不存在\n");
                logger.info("结束查询论文，论文题目不存在，title: %s", title);
                system("pause");
                free(title);
                destroyList(list);
                return;
            }
            for (Node *node = list->head->next; node != list->head; node = node->next) {
                Paper *paper = (Paper *) node->obj;
                showPaper(paper);
            }
            system("pause");
            destroyList(list);
            free(title);
            break;
        }
        default:
            break;
    }
    logger.info("结束查询论文");
}

void InsertProject() {
    logger.info("开始增加项目");
    Project *project = inputProject();
    insertProject(project);
    logger.info("结束增加项目");
}

void DeleteProject() {
    logger.info("开始删除项目");
    for (Node *node = ProjectList->head->next; node != ProjectList->head; node = node->next) {
        Project *project = (Project *) node->obj;
        showProject(project);
    }
    system("pause");
    int id = inputInt("请输入要删除的id:");
    if (getProjectById(id) == NULL) {
        printf("id不存在\n");
        logger.info("结束删除项目，id不存在，id: %d", id);
        system("pause");
        return;
    }
    deleteProjectById(id);
    logger.info("结束删除项目");
}

void UpdateProject() {
    logger.info("开始修改项目");
    for (Node *node = ProjectList->head->next; node != ProjectList->head; node = node->next) {
        Project *project = (Project *) node->obj;
        showProject(project);
    }
    system("pause");
    int id = inputInt("请输入要修改的id:");
    if (getProjectById(id) == NULL) {
        printf("id不存在\n");
        logger.info("结束修改项目，id不存在，id: %d", id);
        system("pause");
        return;
    }
    Project *project = inputProject();
    project->id = id;
    updateProject(project);
    logger.info("结束修改项目");
}

void GetProject() {
    logger.info("开始查询项目");
    int op = inputInt("【1】按学生学号查询\n【2】按项目名查询\n");
    switch (op) {
        case 1: {
            int stuId = inputInt("请输入学号:");
            Student *stu = getStudentByStuId(stuId);
            if (stu == NULL) {
                printf("学号不存在\n");
                logger.info("结束查询项目，学号不存在，stuId: %d", stuId);
                system("pause");
                return;
            }
            List *list = stu->projectList;
            for (Node *node = list->head->next; node != list->head; node = node->next) {
                int *id = (int *) node->obj;
                Project *project = getProjectById(*id);
                showProject(project);
            }
            system("pause");
            break;
        }
        case 2: {
            char *name = inputStr("请输入项目名:");
            List *list = getProjectByName(name);
            if (list->size == 0) {
                printf("项目名不存在\n");
                logger.info("结束查询项目，项目名不存在，name: %s", name);
                system("pause");
                free(name);
                destroyList(list);
                return;
            }
            for (Node *node = list->head->next; node != list->head; node = node->next) {
                Project *project = (Project *) node->obj;
                showProject(project);
            }
            system("pause");
            destroyList(list);
            free(name);
            break;
        }
        default:
            break;
    }
    logger.info("结束查询项目");
}

void Insert() {
    int op = inputInt("【1】新增学生\n【2】新增课程\n【3】新增成绩\n【4】新增奖项\n"
                      "【5】新增论文\n【6】新增项目\n【7】从文件导入学生\n【8】从文件导入课程\n");
    switch (op) {
        case 1:
            InsertStudent();
            break;
        case 2:
            InsertCourse();
            break;
        case 3:
            InsertScore();
            break;
        case 4:
            InsertPrize();
            break;
        case 5:
            InsertPaper();
            break;
        case 6:
            InsertProject();
            break;
        case 7:
            InsertStudentFromFile();
            break;
        case 8:
            InsertCourseFromFile();
            break;
        default:
            break;
    }
}

void Delete() {
    int op = inputInt("【1】删除学生\n【2】删除课程\n【3】删除成绩\n【4】删除奖项\n【5】删除论文\n【6】删除项目\n");
    switch (op) {
        case 1:
            DeleteStudent();
            break;
        case 2:
            DeleteCourse();
            break;
        case 3:
            DeleteScore();
            break;
        case 4:
            DeletePrize();
            break;
        case 5:
            DeletePaper();
            break;
        case 6:
            DeleteProject();
            break;
        default:
            break;
    }
}

void Update() {
    int op = inputInt("【1】修改学生\n【2】修改课程\n【3】修改成绩\n【4】修改奖项\n【5】修改论文\n【6】修改项目\n");
    switch (op) {
        case 1:
            UpdateStudent();
            break;
        case 2:
            UpdateCourse();
            break;
        case 3:
            UpdateScore();
            break;
        case 4:
            UpdatePrize();
            break;
        case 5:
            UpdatePaper();
            break;
        case 6:
            UpdateProject();
            break;
        default:
            break;
    }
}

void Get() {
    int op = inputInt("【1】查询学生\n【2】查询课程\n【3】查询成绩\n【4】查询奖项\n【5】查询论文\n【6】查询项目\n");
    switch (op) {
        case 1:
            GetStudent();
            break;
        case 2:
            GetCourse();
            break;
        case 3:
            GetScore();
            break;
        case 4:
            GetPrize();
            break;
        case 5:
            GetPaper();
            break;
        case 6:
            GetProject();
            break;
        default:
            break;
    }
}

void StatAnalyze() {
    int op = inputInt("【1】计算单个学生GPA\n【2】计算所有学生GPA\n【3】统计一门课的成绩分布\n");
    switch (op) {
        case 1: {
            logger.info("开始计算单个学生GPA");
            int stuId = inputInt("请输入学号:");
            Student *stu = getStudentByStuId(stuId);
            if (stu == NULL) {
                printf("学号不存在\n");
                system("pause");
                return;
            }
            float gpa = calculateTotalGPA(stu);
            printf("GPA: %.4f\n", gpa);
            logger.info("结束计算单个学生GPA，stuId: %d, GPA: %.4f", stuId, gpa);
            system("pause");
            break;
        }
        case 2: {
            logger.info("开始计算所有学生GPA");
            List *list = calculateAllGPA();
            int op1 = inputInt("【1】升序\n【2】降序\n");
            switch (op1) {
                case 1:
                    sort(list, cmpStuGPAAsc);
                    break;
                case 2:
                    sort(list, cmpStuGPADesc);
                    break;
                default:
                    sort(list, cmpStuGPADesc);
                    break;
            }
            int i = 1;
            for (Node *node = list->head->next; node != list->head; node = node->next, i++) {
                Student *stu = (Student *) node->obj;

                printf("排名：%d\t学号：%d\t姓名：%s\tGPA: %.4f\n", i, stu->stuId, stu->name, stu->gpa);
            }
            system("pause");
            destroyList(list);
            logger.info("结束计算所有学生GPA");
            break;
        }
        case 3: {
            logger.info("开始统计一门课的成绩分布");
            char *courseName = inputStr("请输入课程名:");
            List *list = getCourseByName(courseName);
            if (list->size == 0) {
                printf("课程名不存在\n");
                system("pause");
                free(courseName);
                destroyList(list);
                return;
            }
            int courseId;
            if (list->size > 1) {
                printf("找到多个课程：\n");
                for (Node *node = list->head->next; node != list->head; node = node->next) {
                    Course *course = (Course *) node->obj;
                    showCourse(course);
                }
                system("pause");
                courseId = inputInt("请输入课程id:");
                if (getCourseById(courseId) == NULL) {
                    printf("id不存在\n");
                    system("pause");
                    destroyList(list);
                    free(courseName);
                    return;
                }
            } else {
                courseId = ((Course *) list->head->next->obj)->id;
            }
            analyzeCourseDistribution(courseId);
            logger.info("结束统计一门课的成绩分布");
        }
        default:
            break;

    }
}

void login() {
    char *username = inputStr("请输入用户名:");
    char *password = inputStr("请输入密码:");
    if (strcmp(username, AdminUsername) == 0 && strcmp(password, AdminPassword) == 0) {
        printf("登录成功\n");
        logger.info("管理员登录成功");
        system("pause");
        permission = 2;
        nowLoginUsername = 0;
        free(username);
        free(password);
        return;
    } else {
        Student *stu = getStudentByStuId(strtol(username, NULL, 10));
        if (stu) {
            if ((!stu->pwd && strcmp(password, "123456") == 0) ||
                (stu->pwd && strcmp(stu->pwd, password) == 0)) {
                printf("登录成功\n");
                logger.info("学生登录成功，stuId: %d", stu->stuId);
                system("pause");
                permission = 1;
                nowLoginUsername = stu->stuId;
                free(username);
                free(password);
                return;
            }
        }
        printf("登录失败\n");
        logger.info("登录失败，username: %s", username);
        system("pause");
        free(username);
        free(password);
    }
}

void logout() {
    printf("注销成功\n");
    logger.info("注销成功");
    system("pause");
    permission = 0;
}

void changePassword() {
    logger.info("开始修改密码");
    if (nowLoginUsername == 0) {
        printf("不可修改\n");
        logger.warn("管理员密码不可修改");
        system("pause");
    } else {
        Student *stu = getStudentByStuId(nowLoginUsername);
        char *currentPassword = inputStr("请输入当前密码:");
        if (!((!stu->pwd && strcmp(currentPassword, "123456") == 0) ||
              (stu->pwd && strcmp(stu->pwd, currentPassword) == 0))) {
            printf("密码错误\n");
        } else {
            char *password = inputStr("请输入新密码:");
            if (stu->pwd) {
                free(stu->pwd);
            }
            stu->pwd = password;
            printf("修改成功\n");
        }
        system("pause");
        free(currentPassword);
        logger.info("结束修改密码");
    }
}

void start() {
    while (1) {
        if (permission == 0) {
            showWelcomeScreen();
            login();
        } else if (permission == 1) {
            int op = inputInt("【1】查询\n【2】统计分析\n【3】修改密码\n【4】注销\n");
            switch (op) {
                case 1:
                    Get4Student();
                    break;
                case 2:
                    StatAnalyze4Student();
                    break;
                case 3:
                    changePassword();
                    break;
                case 4:
                    logout();
                    break;
                default:
                    break;
            }
        } else if (permission == 2) {
            int op = inputInt("【1】新增\n【2】删除\n【3】修改\n【4】查询\n【5】统计分析\n【6】保存\n【7】注销");
            switch (op) {
                case 1:
                    Insert();
                    break;
                case 2:
                    Delete();
                    break;
                case 3:
                    Update();
                    break;
                case 4:
                    Get();
                    break;
                case 5:
                    StatAnalyze();
                    break;
                case 6:
                    saveAll();
                    break;
                case 7:
                    logout();
                    break;
                default:
                    break;
            }
        }
    }
}

void Get4Student() {
    int op = inputInt("【1】查询个人信息\n【2】查询个人成绩\n【3】查询个人奖项\n【4】查询个人论文\n【5】查询个人项目\n");
    switch (op) {
        case 1: {
            showStudent(getStudentByStuId(nowLoginUsername));
            system("pause");
            break;
        }
        case 2: {
            Student *stu = getStudentByStuId(nowLoginUsername);
            for (Node *node = stu->scoreList->head->next; node != stu->scoreList->head; node = node->next) {
                int *id = (int *) node->obj;
                Score *score = getScoreById(*id);
                showScore(score);
            }
            system("pause");
            break;
        }
        case 3: {
            Student *stu = getStudentByStuId(nowLoginUsername);
            for (Node *node = stu->prizeList->head->next; node != stu->prizeList->head; node = node->next) {
                int *id = (int *) node->obj;
                Prize *prize = getPrizeById(*id);
                showPrize(prize);
            }
            system("pause");
            break;
        }
        case 4: {
            Student *stu = getStudentByStuId(nowLoginUsername);
            for (Node *node = stu->paperList->head->next; node != stu->paperList->head; node = node->next) {
                int *id = (int *) node->obj;
                Paper *paper = getPaperById(*id);
                showPaper(paper);
            }
            system("pause");
            break;
        }
        case 5: {
            Student *stu = getStudentByStuId(nowLoginUsername);
            for (Node *node = stu->projectList->head->next; node != stu->projectList->head; node = node->next) {
                int *id = (int *) node->obj;
                Project *project = getProjectById(*id);
                showProject(project);
            }
            system("pause");
            break;
        }
        default:
            break;
    }
}

void StatAnalyze4Student() {
    int op = inputInt("【1】计算个人GPA\n");
    switch (op) {
        case 1: {
            Student *stu = getStudentByStuId(nowLoginUsername);
            float gpa = calculateTotalGPA(stu);
            printf("GPA: %.4f\n", gpa);
            system("pause");
            break;
        }
        default:
            break;
    }
}