/* ============================================================
   student_registry.c
   ------------------------------------------------------------
   This is the IMPLEMENTATION file. It contains the real code
   behind every function declared in student_registry.h.
   main.c never needs to read this file to use these functions
   — that's the "how" hidden behind the "what".
   ============================================================ */

#include <stdio.h>
#include <string.h>
#include "student_registry.h"

/* ------------------------------------------------------------
   addStudent
   Asks the user for details and adds one new student to the
   array, as long as there is still room.
   ------------------------------------------------------------ */
void addStudent(Student students[], int *count) {
    if (*count >= MAX_STUDENTS) {
        printf("Registry is full! Cannot add more students.\n");
        return;
    }

    Student s;  /* build the new student here first */

    printf("Enter Student ID: ");
    scanf("%d", &s.id);

    printf("Enter Name: ");
    scanf(" %99[^\n]", s.name);   /* reads a full line, up to 99 chars */

    printf("Enter Major: ");
    scanf(" %49[^\n]", s.major);

    printf("Enter GPA: ");
    scanf("%f", &s.gpa);

    printf("Enter Credits: ");
    scanf("%d", &s.credits);

    students[*count] = s;   /* store it in the array */
    (*count)++;             /* one more student now exists */

    printf("Student added successfully!\n");
}

/* ------------------------------------------------------------
   displayAllStudents
   Prints every student in a simple table.
   ------------------------------------------------------------ */
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

/* ------------------------------------------------------------
   searchByID
   Asks for an ID and prints that student if found.
   ------------------------------------------------------------ */
void searchByID(const Student students[], int count) {
    int id;
    printf("Enter Student ID to search: ");
    scanf("%d", &id);

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

/* ------------------------------------------------------------
   findByGPA
   Asks for a minimum GPA and lists everyone at or above it.
   ------------------------------------------------------------ */
void findByGPA(const Student students[], int count) {
    float threshold;
    int found = 0;

    printf("Enter minimum GPA: ");
    scanf("%f", &threshold);

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

/* ------------------------------------------------------------
   findByMajor
   Asks for a major (case-insensitive) and lists matches.
   ------------------------------------------------------------ */
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

/* ------------------------------------------------------------
   saveStudentsToFile
   Writes every student to DATA_FILE, one line per student,
   using '|' to separate fields (pipe-delimited text format).
   Format:  ID|NAME|MAJOR|GPA|CREDITS
   ------------------------------------------------------------ */
void saveStudentsToFile(const Student students[], int count) {
    FILE *file = fopen(DATA_FILE, "w");   /* "w" = write (overwrite) */

    if (file == NULL) {
        printf("Error: Could not open %s for writing.\n", DATA_FILE);
        return;   /* fail gracefully instead of crashing */
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d|%s|%s|%.2f|%d\n",
                students[i].id,
                students[i].name,
                students[i].major,
                students[i].gpa,
                students[i].credits);
    }

    fclose(file);   /* MUST close, or data may not actually be saved */
    printf("Saved %d student(s) to %s\n", count, DATA_FILE);
}

/* ------------------------------------------------------------
   loadStudentsFromFile
   Reads DATA_FILE line by line and rebuilds the student array.
   Returns the number of students loaded (0 if the file does
   not exist yet — that's normal on first run).
   ------------------------------------------------------------ */
int loadStudentsFromFile(Student students[]) {
    FILE *file = fopen(DATA_FILE, "r");   /* "r" = read */
    int count = 0;

    if (file == NULL) {
        /* Not an error — just means no data has been saved yet. */
        printf("No existing data file found. Starting fresh.\n");
        return 0;
    }

    char line[300];
    while (fgets(line, sizeof(line), file) != NULL && count < MAX_STUDENTS) {
        Student s;

        /* sscanf parses the pipe-delimited line back into fields.
           %d[^|] etc. means "read characters until you hit a '|'" */
        int fields = sscanf(line, "%d|%99[^|]|%49[^|]|%f|%d",
                             &s.id, s.name, s.major, &s.gpa, &s.credits);

        if (fields == 5) {   /* only keep the line if all 5 fields parsed */
            students[count] = s;
            count++;
        }
    }

    fclose(file);
    printf("Loaded %d student(s) from %s\n", count, DATA_FILE);
    return count;
}