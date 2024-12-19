// project10_registration.c
#include "student.h"

int main() {
	char code;
	char name[NAME_LEN + 1], netid[NETID_LEN + 1], cop2510_grade;
	double gpa;
	int attempts;

	struct student *registration = NULL;

	help();
	printf("\n");

	for (;;) {
		printf("Enter operation code: ");
		scanf(" %c", &code);
		while (getchar() != '\n')
			;

		switch (code) {
			case 'h':
				help();
			break;
			case 'a':
				read(name, netid, &cop2510_grade, &gpa, &attempts);
			registration = add_student(registration, name, netid, cop2510_grade, gpa, attempts);
			break;
			case 'p':
				registration = pop_student(registration);
			break;
			case 'l':
				list_students(registration);
			break;
			case 'g':
				read(NULL, NULL, NULL, &gpa, NULL);
			list_gpa_min(registration, gpa);
			break;
			case 'c':
				read(NULL, NULL, &cop2510_grade, NULL, NULL);
			list_cop2510_min(registration, cop2510_grade);
			break;
			case 'q':
				registration = clear_queue(registration);
			return 0;
			default:
				printf("Illegal operation code!\n");
		}
		printf("\n");
	}
}
