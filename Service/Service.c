#include <stdlib.h>
#include "./../include/inc.h"
#include "Service.h"
#include "./../poco/Score.h"
#include "./../file/file.h"
#include "./../Mapper/Mapper.h"
#include "./../Utils/Pairif.h"
#include "./../Utils/Logger.h"

void saveAll() {
    writeCnt();
    writeStudentList();
    writeCourseList();
    writeScoreList();
    writePrizeList();
    writePaperList();
    writeProjectList();
    logger.info("保存成功");
}

void insertStudent(Student *stu) {
    stu->id = studentCnt++;
    insertObj(StudentList, stu);
    logger.info("成功增加学生, id: %d, name: %s", stu->id, stu->name);
}

void deleteStudentById(int id) {
    Student *stu = getStudentById(id);
    for (Node *node = stu->scoreList->head->next; node != stu->scoreList->head; node = node->next) {
        deleteScoreById(*(int *)node->obj);
    }
    for (Node *node = stu->prizeList->head->next; node != stu->prizeList->head; node = node->next) {
        Prize *prize = getPrizeById(*(int *)node->obj);
        Student *s = (Student *) getObjById(prize->authors, id);
        if (s != NULL) {
            s->id = -1;
        }
    }
    for (Node *node = stu->paperList->head->next; node != stu->paperList->head; node = node->next) {
        Paper *paper = getPaperById(*(int *)node->obj);
        Student *s = (Student *) getObjById(paper->authors, id);
        if (s != NULL) {
            s->id = -1;
        }

        s = (Student *) getObjById(paper->corrAuthors, id);
        if (s != NULL) {
            s->id = -1;
        }
    }
    for (Node *node = stu->projectList->head->next; node != stu->projectList->head; node = node->next) {
        Project *project = getProjectById(*(int *)node->obj);
        Student *s = (Student *) getObjById(project->authors, id);
        if (s != NULL) {
            s->id = -1;
        }
    }


    destroyStudentMembers(stu);
    deleteObjById(StudentList, id);
    logger.info("成功删除学生, id: %d", id);
}

Student *getStudentById(int id) {
    Student *stu = (Student *)getObjById(StudentList, id);
    logger.info("成功获取学生，id: %d%s", id, stu ? "" : ", 不存在");
    return stu;
}

void updateStudent(Student *stu) { // 为了保持id不变
    Student *old = getStudentById(stu->id);
    old->stuId = stu->stuId;
    free(old->name);
    old->name = stu->name;
    free(old->subject);
    old->subject = stu->subject;
    destroyList(stu->prizeList);
    free(stu->prizeList);
    destroyList(stu->paperList);
    free(stu->paperList);
    destroyList(stu->scoreList);
    free(stu->scoreList);
    destroyList(stu->projectList);
    free(stu->projectList);
    free(stu);
    logger.info("成功更新学生, id: %d", old->id);
}

void insertCourse(Course *course) {
    course->id = courseCnt++;
    insertObj(CourseList, course);
    logger.info("成功增加课程, id: %d", course->id);
}

void deleteCourseById(int id) {
    for (Node *node = ScoreList->head->next; node != ScoreList->head;) { // 删除该课程的所有成绩
        Score *score = (Score *)node->obj;
        if (score->courseId == id) {
            deleteScoreById(score->id);
            node = ScoreList->head->next; // 低效，但简单
        }else {
            node = node->next;
        }
    }

    destroyCourseMembers((Course *)getObjById(CourseList, id));
    deleteObjById(CourseList, id);
    logger.info("成功删除课程, id: %d", id);
}

Course *getCourseById(int id) {
    Course *course = (Course *)getObjById(CourseList, id);
    logger.info("成功获取课程, id: %d%s", id, course ? "" : ", 不存在");
    return course;
}

void updateCourse(Course *course) {
    deleteObjById(CourseList, course->id);
    insertObj(CourseList, course); // 保持id不变
    logger.info("成功更新课程, id: %d", course->id);
}

void insertScore(Score *score, int ownerId) {
    score->id = scoreCnt++;
    int *p = (int *)malloc(sizeof(int));
    *p = score->id;
    insertObj(getStudentById(ownerId)->scoreList, p); // 把Score的id插入到学生的scoreList里
    insertObj(ScoreList, score);
    logger.info("成功增加成绩, id: %d", score->id);
}

void deleteScoreById(int id) {
    List *list = getStudentByStuId(getScoreById(id)->stuId)->scoreList;
    deleteObjById(list, id);// 删除学生的scoreList里的id
    deleteObjById(ScoreList, id);
    logger.info("成功删除成绩, id: %d", id);
}

Score *getScoreById(int id) {
    Score *score = (Score *)getObjById(ScoreList, id);
    logger.info("成功获取成绩, id: %d%s", id, score ? "" : ", 不存在");
    return score;
}

void updateScore(Score *score) {
    deleteScoreById(score->id);
    insertScore(score, getStudentByStuId(score->stuId)->id);
    logger.info("成功更新成绩, id: %d", score->id);
}

void insertPrize(Prize *prize) {
    prize->id = prizeCnt++;
    List *authors = prize->authors;
    for (Node *node = authors->head->next; node != authors->head; node = node->next) { // 把Prize的id插入到学生的prizeList里
        Student *stu = (Student *)node->obj;
        if (stu->id != -1) {// 在系统里的学生
            int *p = (int *)malloc(sizeof(int));
            *p = prize->id;
            Student *owner = getStudentById(stu->id);
            insertObj(owner->prizeList, p);
        }
    }
    insertObj(PrizeList, prize);
    logger.info("成功增加奖项, id: %d", prize->id);
}

void deletePrizeById(int id) {
    List *authors = getPrizeById(id)->authors;
    for (Node *node = authors->head->next; node != authors->head; node = node->next) {
        Student *stu = (Student *)node->obj;
        if (stu->id != -1) {// 在list里的学生
            Student *student = getStudentById(stu->id);
            deleteObjById(student->prizeList, id);// 删除学生的prizeList里的id
        }
    }
    destroyPrizeMembers((Prize *)getObjById(PrizeList, id));
    deleteObjById(PrizeList, id);
    logger.info("成功删除奖项, id: %d", id);
}

Prize *getPrizeById(int id) {
    Prize *prize = (Prize *)getObjById(PrizeList, id);
    logger.info("成功获取奖项, id: %d%s", id, prize ? "" : ", 不存在");
    return prize;
}

void updatePrize(Prize *prize) {
    deletePrizeById(prize->id);
    insertPrize(prize);
    logger.info("成功更新奖项, id: %d", prize->id);
}

void insertPaper(Paper *paper) {
    paper->id = paperCnt++;
    List *authors = paper->authors;
    for (Node *node = authors->head->next; node != authors->head; node = node->next) { // 把Prize的id插入到学生的prizeList里
        Student *stu = (Student *)node->obj;
        if (stu->id != -1) {// 在list里的学生
            int *p = (int *)malloc(sizeof(int));
            *p = paper->id;
            Student *owner = getStudentById(stu->id);
            insertObj(owner->paperList, p);
        }
    }
    List *corrAuthors = paper->corrAuthors;
    for (Node *node = corrAuthors->head->next; node != corrAuthors->head; node = node->next) {
        Student *stu = (Student *)node->obj;
        if (stu->id != -1) {// 在list里的学生
            int *p = (int *)malloc(sizeof(int));
            *p = paper->id;
            Student *owner = getStudentById(stu->id);
            insertObj(owner->paperList, p);
        }
    }
    insertObj(PaperList, paper);
    logger.info("成功增加论文, id: %d", paper->id);
}

void deletePaperById(int id) {
    List *authors = getPaperById(id)->authors;
    for (Node *node = authors->head->next; node != authors->head; node = node->next) {
        Student *stu = (Student *)node->obj;
        if (stu->id != -1) {// 在list里的学生
            Student *student = getStudentById(stu->id);
            deleteObjById(student->paperList, id);// 删除学生的paperList里的id
        }
    }
    List *corrAuthors = getPaperById(id)->corrAuthors;
    for (Node *node = corrAuthors->head->next; node != corrAuthors->head; node = node->next) {
        Student *stu = (Student *)node->obj;
        if (stu->id != -1) {// 在list里的学生
            Student *student = getStudentById(stu->id);
            deleteObjById(student->paperList, id);// 删除学生的paperList里的id
        }
    }
    destroyPaperMembers((Paper *)getObjById(PaperList, id));
    deleteObjById(PaperList, id);
    logger.info("成功删除论文, id: %d", id);
}

Paper *getPaperById(int id) {
    Paper *paper = (Paper *)getObjById(PaperList, id);
    logger.info("成功获取论文, id: %d%s", id, paper ? "" : ", 不存在");
    return paper;
}

void updatePaper(Paper *paper) {
    deletePaperById(paper->id);
    insertPaper(paper);
    logger.info("成功更新论文, id: %d", paper->id);
}

void insertProject(Project *project) {
    project->id = projectCnt++;
    List *authors = project->authors;
    for (Node *node = authors->head->next; node != authors->head; node = node->next) {
        Student *stu = (Student *)node->obj;
        if (stu->id != -1) {// 在list里的学生
            int *p = (int *)malloc(sizeof(int));
            *p = project->id;
            Student *owner = getStudentById(stu->id);
            insertObj(owner->projectList, p);
        }
    }
    insertObj(ProjectList, project);
    logger.info("成功增加项目, id: %d", project->id);
}

void deleteProjectById(int id) {
    List *authors = getProjectById(id)->authors;
    for (Node *node = authors->head->next; node != authors->head; node = node->next) {
        Student *stu = (Student *)node->obj;
        if (stu->id != -1) {// 在list里的学生
            Student *student = getStudentById(stu->id);
            deleteObjById(student->projectList, id);// 删除学生的projectList里的id
        }
    }
    destroyProjectMembers((Project *)getObjById(ProjectList, id));
    deleteObjById(ProjectList, id);
    logger.info("成功删除项目, id: %d", id);
}

Project *getProjectById(int id) {
    Project *project = (Project *)getObjById(ProjectList, id);
    logger.info("成功获取项目, id: %d%s", id, project ? "" : ", 不存在");
    return project;
}

void updateProject(Project *project) {
    deleteProjectById(project->id);
    insertProject(project);
    logger.info("成功更新项目, id: %d", project->id);
}

float calculateGPA(Student *stu) { // 计算学生的GPA，只计算必修，不包括加分
    float numerator = 0, denominator = 0; // 分子 分母
    for (Node *node = stu->scoreList->head->next; node != stu->scoreList->head; node = node->next) {
        Score *score = getScoreById(*(int *)node->obj);
        Course *course = getCourseById(score->courseId);
        if(course->isReq != 1){ // 不是必修
            continue;
        }
        numerator +=  score->point * course->credit; // 绩点 * 学分
        denominator += course->credit; // 学分
    }
    if(denominator < 1e-6f){
        return 0.0f;
    }
    return numerator / denominator;
}

float calculateTotalGPA(Student *stu) {
    float prizeMax = 0, paperMax = 0, projectMax = 0;
    for (Node *node = stu->prizeList->head->next; node != stu->prizeList->head; node = node->next) { // 计算最高奖项
        Prize *prize = getPrizeById(*(int *)node->obj);
        Pairif *pairif = (Pairif *)getObjById(prize->awards, stu->id);
        if(pairif != NULL){ // 有加分
            prizeMax = getF(pairif) > prizeMax ? getF(pairif) : prizeMax;
        }
    }
    for (Node *node = stu->paperList->head->next; node != stu->paperList->head; node = node->next) {
        Paper *paper = getPaperById(*(int *)node->obj);
        Pairif *pairif = (Pairif *)getObjById(paper->awards, stu->id);
        if(pairif != NULL){
            paperMax = getF(pairif) > paperMax ? getF(pairif) : paperMax;
        }
    }
    for (Node *node = stu->projectList->head->next; node != stu->projectList->head; node = node->next) {
        Project *project = getProjectById(*(int *)node->obj);
        Pairif *pairif = (Pairif *)getObjById(project->awards, stu->id);
        if(pairif != NULL){
            projectMax = getF(pairif) > projectMax ? getF(pairif) : projectMax;
        }
    }
    float totalAwards = prizeMax + paperMax > projectMax ? paperMax : projectMax; // 论文和项目取最高，再加上奖项
    totalAwards = totalAwards > 0.4f ? 0.4f : totalAwards; // 加分最高0.4
    float total = calculateGPA(stu) + totalAwards;
    return total > 4.0f ? 4.0f : total; // GPA最高4.0
}

List *calculateAllGPA() {
    List *list = createList();
    for (Node *node = StudentList->head->next; node != StudentList->head; node = node->next) {
        Student *stu = (Student *)node->obj;
        stu->gpa = calculateTotalGPA(stu);
        insertObj(list, stu);
    }
    logger.info("成功计算所有学生GPA, 共%d人", list->size);
    return list;
}

void analyzeCourseDistribution(int id) { // 分析课程成绩分布
    int *cnt = (int *)malloc(sizeof(int) * 12);
    int line[] = {0, 60, 64, 67, 70, 74, 77, 80, 84, 87, 90, 95, 101};
    for (int i = 0; i < 12; i++) {
        cnt[i] = 0;
    }
    for (Node *node = ScoreList->head->next; node != ScoreList->head; node = node->next) {
        Score *score = (Score *) node->obj;
        if (score->courseId == id) {
            for (int i = 0; i <= 11; i++) {
                if (score->score >= line[i] && score->score < line[i + 1]) {
                    cnt[i]++;
                    break;
                }
            }
        }
    }
    printf("A+ [95, 100]: %d\n", cnt[11]);
    printf("A [90, 95): %d\n", cnt[10]);
    printf("A- [87, 90): %d\n", cnt[9]);
    printf("B+ [84, 87): %d\n", cnt[8]);
    printf("B [80, 84): %d\n", cnt[7]);
    printf("B- [77, 80): %d\n", cnt[6]);
    printf("C+ [74, 77): %d\n", cnt[5]);
    printf("C [70, 74): %d\n", cnt[4]);
    printf("C- [67, 70): %d\n", cnt[3]);
    printf("D+ [64, 67): %d\n", cnt[2]);
    printf("D [60, 64): %d\n", cnt[1]);
    printf("F [0, 60): %d\n", cnt[0]);
    system("pause");
    free(cnt);
    logger.info("成功分析课程分布, id: %d", id);
}