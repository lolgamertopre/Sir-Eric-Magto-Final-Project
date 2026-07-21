# Enhanced Student Registry (Module 12)

## Description
A command-line student registry for Dr. Santos, extended from the
Day 10 version to add **file persistence** and **abstraction**.
Students are now saved to `students.dat` so data survives between
program runs, and the code is split into interface (`.h`) and
implementation (`.c`) files.

## How to Compile
Using the Makefile (recommended):
```
make
```
Or manually:
```
gcc -c student_registry.c -o student_registry.o
gcc -c main.c -o main.o
gcc student_registry.o main.o -o student_registry
```

## How to Run
```
./student_registry
```
Or in one step:
```
make run
```

## Data Structure Design
```c
typedef struct {
    int   id;
    char  name[100];
    char  major[50];
    float gpa;
    int   credits;
} Student;
```
Students are stored in a fixed-size array (`Student students[MAX_STUDENTS]`)
with a separate `count` variable tracking how many slots are filled.
This mirrors the Day 10 design so the core functions (add, search,
display, findByGPA, findByMajor) barely changed — only file I/O was
added on top.

## File Format Chosen: Text (Pipe-Delimited)
```
ID|NAME|MAJOR|GPA|CREDITS
```
Example:
```
1001|Alice Johnson|Computer Science|3.85|90
1002|Bob Smith|Business|3.45|85
```
Chosen over binary because it's human-readable — you can open
`students.dat` in any text editor to check or fix data, which
makes debugging much easier than a binary format.

## Test Cases Run
1. **First run, no data file** → Program printed
   "No existing data file found. Starting fresh." and started with 0 students. ✓
2. **Add & save** → Added 3 students, displayed them to confirm,
   chose "Save & Exit" — `students.dat` was created. ✓
3. **Persistence** → Ran the program again, it printed
   "Loaded 3 student(s) from students.dat" and displaying all
   showed the same 3 students. ✓
4. **Search functions** → Verified search by ID, GPA threshold,
   and major all return correct matches (and a clear message when
   nothing matches). ✓

## Design Decisions / Challenges
- Used `%99[^\n]` / `%49[^|]`-style `scanf`/`sscanf` format specifiers
  to safely read strings that may contain spaces, and to avoid
  buffer overflows by limiting how many characters are read.
- `loadStudentsFromFile` treats a missing file as a normal case
  (first run), not an error — it just returns 0 students.
- `strcasecmp` is used in `findByMajor` so "computer science" and
  "Computer Science" both match, since users won't always match
  capitalization exactly.



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

    printf("\nTotal Students: %d\n", count);   /* FIX: show count */
}