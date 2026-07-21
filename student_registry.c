#include <stdio.h>
#include <string.h>
#include "student_registry.h"

/* FIX: flushes anything left in stdin up to and including the
   next newline (or EOF). Call this after any scanf() that reads
   a number, so leftover bad characters never leak into the next
   prompt and cause a chain reaction of failed reads. */
void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

void addStudent(Student students[], int *count) {
    if (*count >= MAX_STUDENTS) {
        printf("Registry is full! Cannot add more students.\n");
        return;
    }

    Student s;

    printf("Enter Student ID: ");
    /* FIX: loop until scanf successfully reads an int */
    while (scanf("%d", &s.id) != 1) {
        printf("Invalid input. Please enter a whole number: ");
        clearInputBuffer();
    }
    clearInputBuffer(); /* FIX: eat the leftover newline after %d */

    printf("Enter Name: ");
    scanf(" %99[^\n]", s.name);

    printf("Enter Major: ");
    scanf(" %49[^\n]", s.major);

    printf("Enter GPA: ");
    while (scanf("%f", &s.gpa) != 1) {
        printf("Invalid input. Please enter a number (e.g. 3.5): ");
        clearInputBuffer();
    }
    clearInputBuffer();

    printf("Enter Credits: ");
    while (scanf("%d", &s.credits) != 1) {
        printf("Invalid input. Please enter a whole number: ");
        clearInputBuffer();
    }
    clearInputBuffer();

    students[*count] = s;
    (*count)++;

    printf("Student added successfully!\n");
}

void deleteStudent(Student students[], int *count) {
    int id;
    printf("Enter Student ID to delete: ");
    while (scanf("%d", &id) != 1) {
        printf("Invalid input. Please enter a whole number: ");
        clearInputBuffer();
    }
    clearInputBuffer();

    for (int i = 0; i < *count; i++) {
        if (students[i].id == id) {
            for (int j = i; j < *count - 1; j++) {
                students[j] = students[j + 1];
            }
            (*count)--;
            printf("Student %d deleted.\n", id);
            return;
        }
    }
    printf("No student found with ID %d.\n", id);
}

void displayAllStudents(const Student students[], int count) {
    if (count == 0) {
        printf("No students to display.\n");
        return;
    }

    printf("\n%-6s %-20s %-15s %-6s %-8s\n",
           "ID", "Name", "Major", "GPA", "Credits");
    printf("--------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%-6d %-20s %-15s %-6.2f %-8d\n",
               students[i].id,
               students[i].name,
               students[i].major,
               students[i].gpa,
               students[i].credits);
    }
}

void searchByID(const Student students[], int count) {
    int id;
    printf("Enter Student ID to search: ");
    while (scanf("%d", &id) != 1) {
        printf("Invalid input. Please enter a whole number: ");
        clearInputBuffer();
    }
    clearInputBuffer();

    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            printf("Found: %d | %s | %s | GPA: %.2f | Credits: %d\n",
                   students[i].id, students[i].name, students[i].major,
                   students[i].gpa, students[i].credits);
            return;
        }
    }
    printf("No student found with ID %d.\n", id);
}

void findByGPA(const Student students[], int count) {
    float threshold;
    int found = 0;

    printf("Enter minimum GPA: ");
    while (scanf("%f", &threshold) != 1) {
        printf("Invalid input. Please enter a number (e.g. 3.0): ");
        clearInputBuffer();
    }
    clearInputBuffer();

    for (int i = 0; i < count; i++) {
        if (students[i].gpa >= threshold) {
            printf("%d | %s | GPA: %.2f\n",
                   students[i].id, students[i].name, students[i].gpa);
            found = 1;
        }
    }
    if (!found) {
        printf("No students found with GPA >= %.2f\n", threshold);
    }
}

void findByMajor(const Student students[], int count) {
    char major[50];
    int found = 0;

    printf("Enter major to search: ");
    scanf(" %49[^\n]", major);

    for (int i = 0; i < count; i++) {
        if (strcasecmp(students[i].major, major) == 0) {
            printf("%d | %s | %s\n",
                   students[i].id, students[i].name, students[i].major);
            found = 1;
        }
    }
    if (!found) {
        printf("No students found in major: %s\n", major);
    }
}

void saveStudentsToFile(const Student students[], int count) {
    FILE *file = fopen(DATA_FILE, "w");

    if (file == NULL) {
        printf("Error: Could not open %s for writing.\n", DATA_FILE);
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d|%s|%s|%.2f|%d\n",
                students[i].id,
                students[i].name,
                students[i].major,
                students[i].gpa,
                students[i].credits);
    }

    fclose(file);
    printf("Saved %d student(s) to %s\n", count, DATA_FILE);
}

int loadStudentsFromFile(Student students[]) {
    FILE *file = fopen(DATA_FILE, "r");
    int count = 0;

    if (file == NULL) {
        printf("No existing data file found. Starting fresh.\n");
        return 0;
    }

    char line[300];
    while (fgets(line, sizeof(line), file) != NULL && count < MAX_STUDENTS) {
        Student s;

        int fields = sscanf(line, "%d|%99[^|]|%49[^|]|%f|%d",
                             &s.id, s.name, s.major, &s.gpa, &s.credits);

        if (fields == 5) {
            students[count] = s;
            count++;
        }
    }

    fclose(file);
    printf("Loaded %d student(s) from %s\n", count, DATA_FILE);
    return count;
}