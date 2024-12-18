
// mark halim
// 5827 4708
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Customers 200   // Maximum number of customers
#define NameAndEmail 100 // Maximum length for name and email

struct Customer {
    char name[NameAndEmail + 1];
    char email[NameAndEmail + 1];
    int number;
};

// Comparison function for qsort
int compare(const void *p, const void *p2) {
    const struct Customer *c1 = (const struct Customer *)p;
    const struct Customer *c2 = (const struct Customer *)p2;

    if (c1->number > c2->number)
        return -1;
    else if (c1->number < c2->number)
        return 1;
    else
        return 0;
}

// Search function
int search(struct Customer list[], int n, int num_lessons, struct Customer result[]) {
    FILE *pFile = fopen("customers.csv", "r");
    if (!pFile) {
        perror("Error opening input file");
        return -1;
    }

    char name[NameAndEmail + 1];
    char email[NameAndEmail + 1];
    int number;
    int i = 0;

    // Read customers from input file
    while (i < n && fscanf(pFile, "%[^,],%d,%[^\n]\n", email, &number, name) == 3) {
        strcpy(list[i].name, name);
        strcpy(list[i].email, email);
        list[i].number = number;
        i++;
    }
    fclose(pFile);

    int count = 0; // Counter for matching customers
    for (int j = 0; j < i; j++) {
        if (list[j].number > num_lessons) {
            // Store matching customers in result array
            result[count] = list[j];
            count++;
        }
    }

    return count; // Return the number of matching customers
}

int main() {
    struct Customer list[Customers];
    struct Customer result[Customers];
    int number_of_lessons;

    // Get the minimum number of lessons from the user

    // Call the search function
    int count = search(list, Customers, number_of_lessons, result);
    if (count < 0) {
        return 1; // Exit if there was an error reading the file
    }

    // Sort the filtered results
    qsort(result, count, sizeof(struct Customer), compare);

    // Write sorted results to output file
    FILE *OutPutfile = fopen("result.csv", "w");
    if (!OutPutfile) {
        perror("Error opening output file");
        return 1;
    }

    for (int i = 0; i < count; i++) {
        fprintf(OutPutfile, "%s,%d,%s\n", result[i].email, result[i].number, result[i].name);
    }
    fclose(OutPutfile);
    return 0;
}
