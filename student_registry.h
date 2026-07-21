

#ifndef STUDENT_REGISTRY_H   
#define STUDENT_REGISTRY_H  


#define MAX_STUDENTS 100          
#define DATA_FILE    "students.dat"  


typedef struct {
    int   id;
    char  name[100];
    char  major[50];
    float gpa;
    int   credits;
} Student;


void addStudent(Student students[], int *count);
void deleteStudent(Student students[], int *count);
void displayAllStudents(const Student students[], int count);
void searchByID(const Student students[], int count);
void findByGPA(const Student students[], int count);
void findByMajor(const Student students[], int count);


void saveStudentsToFile(const Student students[], int count);
int  loadStudentsFromFile(Student students[]);   

#endif 