/* ============================================================
   student_registry.h
   ------------------------------------------------------------
   This is the INTERFACE file. It tells other .c files what
   functions and data types exist, WITHOUT showing how they
   are implemented. That is the whole idea of "abstraction":
   main.c only needs to #include this file — it never needs to
   look inside student_registry.c to use these functions.
   ============================================================ */

#ifndef STUDENT_REGISTRY_H   /* include guard: stops this file  */
#define STUDENT_REGISTRY_H   /* from being pasted in twice       */

/* ---- Constants ------------------------------------------- */
#define MAX_STUDENTS 100          /* max students we can hold in memory */
#define DATA_FILE    "students.dat"  /* name of the file we save/load  */

/* ---- Data structure ---------------------------------------
   One Student = one row of data. Kept simple: just an array
   of these, plus a counter for how many are currently used.
   ------------------------------------------------------------ */
typedef struct {
    int   id;
    char  name[100];
    char  major[50];
    float gpa;
    int   credits;
} Student;

/* ---- Core functions (same idea as Day 10) ------------------ */
void addStudent(Student students[], int *count);
void displayAllStudents(const Student students[], int count);
void searchByID(const Student students[], int count);
void findByGPA(const Student students[], int count);
void findByMajor(const Student students[], int count);

/* ---- File handling functions (new for Day 12) -------------- */
void saveStudentsToFile(const Student students[], int count);
int  loadStudentsFromFile(Student students[]);   /* returns how many loaded */

#endif /* STUDENT_REGISTRY_H */