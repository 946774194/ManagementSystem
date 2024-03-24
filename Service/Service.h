#pragma once
#include "./../poco/Student.h"
#include "./../poco/Course.h"
#include "./../poco/Score.h"
#include "./../poco/Prize.h"
#include "./../poco/Paper.h"
#include "./../poco/Project.h"

void saveAll();

void insertStudent(Student *stu);

void deleteStudentById(int id);

Student *getStudentById(int id);

void updateStudent(Student *stu);

void insertCourse(Course *course);

void deleteCourseById(int id);

Course *getCourseById(int id);

void updateCourse(Course *course);

void insertScore(Score *score, int ownerId);

void deleteScoreById(int id);

Score *getScoreById(int id);

void updateScore(Score *score);

void insertPrize(Prize *prize);

void deletePrizeById(int id);

Prize *getPrizeById(int id);

void updatePrize(Prize *prize);

void insertPaper(Paper *paper);

void deletePaperById(int id);

Paper *getPaperById(int id);

void updatePaper(Paper *paper);

void insertProject(Project *project);

void deleteProjectById(int id);

Project *getProjectById(int id);

void updateProject(Project *project);

float calculateGPA(Student *stu);

float calculateTotalGPA(Student *stu);

List *calculateAllGPA();

void analyzeCourseDistribution(int id);