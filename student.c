// student.c
#include "student.h"

void help() {
    printf("List of operation codes:\n");
    printf("\t'h' for help;\n");
    printf("\t'a' for adding a student to the queue;\n");
    printf("\t'p' for removing a student from the queue;\n");
    printf("\t'l' for listing all students in the queue;\n");
    printf("\t'g' for searching students with a minimum GPA;\n");
    printf("\t'c' for searching students with a minimum grade in COP2510;\n");
    printf("\t'q' to quit.\n");
}

void read(char *name, char *netid, char *cop2510_grade, double *gpa, int *attempts) {
    if (name != NULL) {
        printf("Enter the name of the student: ");
        scanf("%[^\n]", name);
        getchar(); // Consume the newline character
    }
    if (netid != NULL) {
        printf("Enter the NetID of the student: ");
        scanf("%s", netid);
        getchar(); // Consume the newline character
    }
    if (cop2510_grade != NULL) {
        printf("Enter the COP2510 letter grade: ");
        scanf(" %c", cop2510_grade);
    }
    if (gpa != NULL) {
        printf("Enter the GPA: ");
        scanf("%lf", gpa);
    }
    if (attempts != NULL) {
        printf("Enter the number of previous attempts: ");
        scanf("%d", attempts);
    }
}

struct student *add_student(struct student *registration, char *name, char *netid, char cop2510_grade, double gpa, int attempts) {
    struct student *new_student = (struct student *)malloc(sizeof(struct student));
    if (new_student == NULL) {
        printf("Error: malloc failed in add_student\n");
        exit(EXIT_FAILURE);
    }

    strncpy(new_student->name, name, NAME_LEN);
    new_student->name[NAME_LEN] = '\0';

    strncpy(new_student->netid, netid, NETID_LEN);
    new_student->netid[NETID_LEN] = '\0';

    new_student->cop2510_grade = toupper(cop2510_grade);
    new_student->gpa = gpa;
    new_student->attempts = attempts;
    new_student->next = NULL;

    if (registration == NULL) {
        return new_student;
    }

    struct student *current, *previous;
    for (previous = NULL, current = registration; current != NULL && current->attempts >= attempts; previous = current, current = current->next);
    new_student->next = current;
    if (previous == NULL) {
        return new_student;
    } else {
        previous->next = new_student;
        return registration;
    }
}

struct student *pop_student(struct student *registration) {
    if (registration == NULL) {
        return NULL;
    }

    struct student *popped_student = registration;
    registration = registration->next;

    printf("|----------------------|----------------------|---------|-----|----------|\n");
    printf("| Name                 | NetID                | COP2510 | GPA | Attempts |\n");
    printf("|----------------------|----------------------|---------|-----|----------|\n");
    printf("| %-20s | %-20s |       %c | %1.1f | %8d |\n",
           popped_student->name, popped_student->netid, popped_student->cop2510_grade,
           popped_student->gpa, popped_student->attempts);
    printf("|----------------------|----------------------|---------|-----|----------|\n");

    free(popped_student);
    return registration;
}

void list_students(struct student *registration) {
    if (registration == NULL) {
        return;
    }

    printf("|----------------------|----------------------|---------|-----|----------|\n");
    printf("| Name                 | NetID                | COP2510 | GPA | Attempts |\n");
    printf("|----------------------|----------------------|---------|-----|----------|\n");

    struct student *current = registration;
    while (current != NULL) {
        printf("| %-20s | %-20s |       %c | %1.1f | %8d |\n",
               current->name, current->netid, current->cop2510_grade,
               current->gpa, current->attempts);
        printf("|----------------------|----------------------|---------|-----|----------|\n");
        current = current->next;
    }
}

void list_gpa_min(struct student *registration, double gpa) {
    if (registration == NULL) {
        return;
    }

    int found = 0;
    struct student *current = registration;
    while (current != NULL) {
        if (current->gpa >= gpa && !found) {
            printf("|----------------------|----------------------|---------|-----|----------|\n");
            printf("| Name                 | NetID                | COP2510 | GPA | Attempts |\n");
            printf("|----------------------|----------------------|---------|-----|----------|\n");
            found = 1;
        }
        if (current->gpa >= gpa) {
            printf("| %-20s | %-20s |       %c | %1.1f | %8d |\n",
                   current->name, current->netid, current->cop2510_grade,
                   current->gpa, current->attempts);
            printf("|----------------------|----------------------|---------|-----|----------|\n");
        }
        current = current->next;
    }
}

void list_cop2510_min(struct student *registration, char cop2510_grade) {
    if (registration == NULL) {
        return;
    }

    int found = 0;
    cop2510_grade = toupper(cop2510_grade);

    struct student *current = registration;
    while (current != NULL) {
        if (toupper(current->cop2510_grade) <= cop2510_grade && !found) {
            printf("|----------------------|----------------------|---------|-----|----------|\n");
            printf("| Name                 | NetID                | COP2510 | GPA | Attempts |\n");
            printf("|----------------------|----------------------|---------|-----|----------|\n");
            found = 1;
        }
        if (toupper(current->cop2510_grade) <= cop2510_grade) {
            printf("| %-20s | %-20s |       %c | %1.1f | %8d |\n",
                   current->name, current->netid, current->cop2510_grade,
                   current->gpa, current->attempts);
            printf("|----------------------|----------------------|---------|-----|----------|\n");
        }
        current = current->next;
    }
}

struct student *clear_queue(struct student *registration) {
    struct student *current = registration;
    while (current != NULL) {
        struct student *next_student = current->next;
        free(current);
        current = next_student;
    }
    return NULL;
}
