#pragma once
#include "./../poco/Score.h"
#include "./../poco/Prize.h"
#include "./../poco/Student.h"
#include "./../poco/Paper.h"
#include "./../poco/Project.h"

char *inputStr(char *prompt);

char *inputStrn(char *prompt, int maxSize);

char *inputOptionalStrn(char *prompt, int maxSize);

int inputInt(char *prompt);

float inputFloat(char *prompt);

Student *inputStudent();

void InsertStudent();

void InsertStudentFromFile();

void DeleteStudent();

void UpdateStudent();

void GetStudent();

void InsertCourse();

void InsertCourseFromFile();

void DeleteCourse();

void UpdateCourse();

Score *inputScore();

void GetCourse();

void InsertScore();

void DeleteScore();

void UpdateScore();

void GetScore();

Prize *inputPrize();

void InsertPrize();

void DeletePrize();

void UpdatePrize();

void GetPrize();

void InsertPaper();

void DeletePaper();

void UpdatePaper();

void GetPaper();

void InsertProject();

void DeleteProject();

void UpdateProject();

void GetProject();

void Insert();

void Delete();

void Update();

void Get();

void StatAnalyze();

void login();

void logout();

void changePassword();

void start();

void Get4Student();

void StatAnalyze4Student();