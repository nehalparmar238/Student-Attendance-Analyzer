STUDENT ATTENDANCE ANALYZER - C PROJECT (MULTI-FILE)
====================================================

This project intentionally keeps each part in a separate file.

FILES
-----
common.h     Shared structures and function declarations
input.c      Input helper functions
student.c    Student linked-list operations
session.c    Class session linked-list operations
attendance.c Mark, display, and update attendance
reports.c    Student history and attendance summary/shortage reports
storage.c    Save and load data using text files
main.c       Main menu

HOW TO COMPILE
--------------
Compile ALL C source files together:

gcc -std=c99 main.c input.c student.c session.c attendance.c reports.c storage.c -o attendance

Then run the generated program. Some systems use ./attendance to run it.

If using a phone, the online compiler must support MULTIPLE FILES. Look for a
Project or Add File option. Upload/extract this ZIP, open all .c files in the
same project, then compile them together. Do not compile main.c by itself.

FEATURES
--------
- Add, display, search, update, and delete students
- Create, display, and search class sessions
- Mark attendance (P = Present, A = Absent)
- Prevent duplicate attendance for the same student/session
- Correct attendance status
- View session-wise attendance
- View individual student attendance history
- Calculate attendance percentages and shortage reports
- Save/load data with file handling

DATA FILES
----------
The program creates students.txt, sessions.txt, and attendance.txt in its
current working directory. Some online compilers erase these files after a
run, so file persistence depends on the compiler's environment.

DATE FORMAT: YYYY-MM-DD (example: 2026-10-24)
