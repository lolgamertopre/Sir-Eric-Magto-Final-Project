/* ============================================================
   main.c
   ------------------------------------------------------------
   This file is only responsible for the MENU and user
   interaction. It does not know HOW addStudent or
   saveStudentsToFile work — it just calls them. That's the
   benefit of abstraction: this file stays short and readable.
   ============================================================ */

#include <stdio.h>
#include <stdlib.h>
#include "student_registry.h"

/* Clears the terminal screen (Linux/Mac). Waits for the user
   to press Enter first, so they get to actually read the
   result of their last action before it disappears. */
void pauseAndClear(void) {
    printf("\nPress Enter to continue...");
    while (getchar() != '\n') { }   /* eat leftover Enter from scanf */
    getchar();                      /* wait for the real Enter press */
    system("clear");
}

int main(void) {
    Student students[MAX_STUDENTS];
    int count = 0;
    int choice;

    printf("=== Dr. Santos' Student Registry (with File Storage) ===\n");

    /* Load whatever was saved last time, if anything */
    count = loadStudentsFromFile(students);

    do {
        printf("\n----- MENU -----\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search by Student ID\n");
        printf("4. Find by GPA Threshold\n");
        printf("5. Find by Major\n");
        printf("6. Delete Student\n");
        printf("7. Save & Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent(students, &count);
                break;
            case 2:
                displayAllStudents(students, count);
                break;
            case 3:
                searchByID(students, count);
                break;
            case 4:
                findByGPA(students, count);
                break;
            case 5:
                findByMajor(students, count);
                break;
            case 6:
                deleteStudent(students, &count);
                break;
            case 7:
                saveStudentsToFile(students, count);
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please enter 1-7.\n");
        }

        if (choice != 7) {
            pauseAndClear();
        }

    } while (choice != 7);

    return 0;
}