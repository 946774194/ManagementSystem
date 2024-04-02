#include "Project.h"
#include <stdlib.h>
#include <string.h>
#include "./../include/inc.h"
#include "./../Utils/Pairif.h"
#include "./../poco/Student.h"
#include "../Mapper/Mapper.h"

Project *createProject() {
    Project *project = (Project *)malloc(sizeof(Project));
    project->id = 0;
    project->teacher = NULL;
    project->name = NULL;
    project->code = NULL;
    project->startDate = NULL;
    project->endDate = NULL;
    project->authors = createList();
    project->awards = createList();
    return project;
}

char *projectToString(const Project *project) { // 与prizeToString类似
    char *str = (char *)malloc(512);
    char *authorsAndAwards = (char *)malloc(DEFAULT_BUFFER_SIZE);
    *authorsAndAwards = '\0';
    char *p = authorsAndAwards;
    for (int i = 0; i < project->authors->size; i++) {
        Student *stu = (Student *)get(project->authors, i);
        sprintf(p, "%d %s", i + 1, stu->name);
        p += strlen(p);

        if (getObjById(project->awards, stu->id) != NULL) {
            sprintf(p, " +%.2f", getF((Pairif *)getObjById(project->awards, stu->id)));
            p += strlen(p);
        }
        if (i != project->authors->size - 1) {
            sprintf(p, ", ");
            p += strlen(p);
        }
    }
    sprintf(str, "id: %d\t指导教师: %s\t项目名称: %s\t项目编号: %s\t立项日期: %s\t结项日期: %s\n作者: %s\n",
            project->id, project->teacher, project->name, project->code,
            project->startDate,project->endDate, authorsAndAwards);
    free(authorsAndAwards);
    return str;
}

void showProject(const Project *project) {
    char *str = projectToString(project);
    printf("%s", projectToString(project));
    free(str);
}

void destroyProjectMembers(Project *project) {
    free(project->teacher);
    free(project->name);
    free(project->code);
    free(project->startDate);
    free(project->endDate);
    for (Node *node = project->authors->head->next; node != project->authors->head; node = node->next) {
        Student *stu = (Student *) node->obj;
        free(stu->name);
        free(stu->scoreList);
        free(stu->paperList);
        free(stu->prizeList);
        free(stu->projectList);
        free(stu);
    }
    destroyList(project->awards);
}

Project *readProject(FILE *fp) {
    Project *project = createProject();
    fscanf(fp, "%d\n", &project->id);
    project->teacher = inputStringFromFile(fp);
    project->name = inputStringFromFile(fp);
    project->code = inputStringFromFile(fp);
    project->startDate = inputStringFromFile(fp);
    project->endDate = inputStringFromFile(fp);
    int size;
    fscanf(fp, "%d\n", &size);
    for (int i = 0; i < size; i++) {
        Student *stu = createStudent();
        fscanf(fp, "%d\n", &stu->id);
        stu->name = inputStringFromFile(fp);
        insertObj(project->authors, stu);
    }
    fscanf(fp, "%d\n", &size);
    for (int i = 0; i < size; i++) {
        Pairif *pairif = newPairif(0,0);
        fscanf(fp, "%d\n", &pairif->i);
        fscanf(fp, "%f\n", &pairif->f);
        insertObj(project->awards, pairif);
    }
    return project;
}

void writeProject(FILE *fp, const Project *project) {
    fprintf(fp, "%d\n", project->id);
    fprintf(fp, "%s\n", project->teacher);
    fprintf(fp, "%s\n", project->name);
    fprintf(fp, "%s\n", project->code);
    fprintf(fp, "%s\n", project->startDate);
    fprintf(fp, "%s\n", project->endDate);
    fprintf(fp, "%d\n", project->authors->size);
    for (Node *node = project->authors->head->next; node != project->authors->head; node = node->next) {
        Student *stu = (Student *) node->obj;
        fprintf(fp, "%d\n", stu->id);
        fprintf(fp, "%s\n", stu->name);
    }
    fprintf(fp, "%d\n", project->awards->size);
    for (Node *node = project->awards->head->next; node != project->awards->head; node = node->next) {
        Pairif *pairif = (Pairif *) node->obj;
        fprintf(fp, "%d\n", pairif->i);
        fprintf(fp, "%.2f\n", pairif->f);
    }
}
