// student.h
#ifndef STUDENT_H
#define STUDENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NAME_LEN 100
#define NETID_LEN 40

struct student {
    char name[NAME_LEN + 1], netid[NETID_LEN + 1], cop2510_grade;
    double gpa;
    int attempts;
    struct student *next;
};

void help();
void read(char *name, char *netid, char *cop2510_grade, double *gpa, int *attempts);
struct student *add_student(struct student *registration, char *name, char *netid, char cop2510_grade, double gpa, int attempts);
struct student *pop_student(struct student *registration);
void list_students(struct student *registration);
void list_gpa_min(struct student *registration, double gpa);
void list_cop2510_min(struct student *registration, char cop2510_grade);
struct student *clear_queue(struct student *registration);

#endif // STUDENT_H