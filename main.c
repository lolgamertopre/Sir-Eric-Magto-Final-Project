#include <stdio.h>
#include <stdlib.h>
#include "student_registry.h"

void pauseAndClear(void) {
    printf("\nPress Enter to continue...");
    while (getchar() != '\n') { }
    getchar();
#ifdef _WIN32
    system("cls");   /* FIX: use Windows clear-screen command */
#else
    system("clear");
#endif
}

int main(void) {
    Student students[MAX_STUDENTS];
    int count = 0;
    int choice;

    printf("=== Dr. Santos' Student Registry (with File Storage) ===\n");

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

        /* FIX: validate the menu choice, this was the main
           source of "stacking" when non-numeric input was typed */
        while (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number 1-7: ");
            clearInputBuffer();
        }
        clearInputBuffer(); /* FIX: eat leftover newline after %d */

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