[README_StudentAttendanceAnalyzer.md](https://github.com/user-attachments/files/33912960/README_StudentAttendanceAnalyzer.md)
# Student Attendance Analyzer (C)

A menu-driven console application written in **C** to manage student records, class sessions, and attendance using structures, pointers, and singly linked lists.

## Features

### Student management
- Add a student with a unique positive ID
- Display all students
- Search for a student by ID
- Update a student's name
- Delete a student when no attendance record refers to them

### Class session management
- Create a class session with a unique ID, date, and subject
- Display all class sessions
- Search for a session by ID
- Check the date's `YYYY-MM-DD` format

### Attendance management
- Mark a student as Present (`P`) or Absent (`A`) for a session
- Check that the student and session exist before recording attendance
- Prevent duplicate attendance records for the same student and session
- Display attendance recorded for a selected session
- Update an existing attendance status

## Concepts used

- C structures (`struct`)
- Singly linked lists
- Pointers and pointer traversal
- Dynamic memory allocation with `malloc()`
- Memory deallocation with `free()`
- Functions and modular programming
- Input validation
- Header files and function declarations

## Project structure

```text
StudentAttendanceAnalyzer/
├── main.c        # Main menu and program flow
├── common.h      # Shared structures, constants, and declarations
├── input.c       # Input helpers and basic validation
├── student.c     # Student record operations
├── session.c     # Class session operations
├── attendance.c  # Attendance operations
├── reports.c     # Report-related source module
├── storage.c     # File-storage-related source module
└── README.md
```

## Requirements

- A C compiler such as GCC
- A terminal or online C environment that supports compiling multiple source files

## Compile

Run this command from the project directory:

```bash
gcc -std=c99 main.c input.c student.c session.c attendance.c reports.c storage.c -o attendance
```

## Run

On Linux, macOS, or a Linux-based online environment:

```bash
./attendance
```

On Windows, run the generated executable, for example:

```text
attendance.exe
```

## How to use

1. Run the program.
2. Choose an option from the menu.
3. Add students before recording their attendance.
4. Create a class session before marking attendance for it.
5. Enter the student's ID, session ID, and attendance status when prompted.
6. Use **Update Attendance** to change a record that already exists.

## Notes and limitations

- The current interactive menu exposes student management, class session management, and attendance operations.
- `reports.c` and `storage.c` are included as separate source modules, but report and save/load functions are not currently exposed through the menu in `main.c`.
- Student, session, and attendance linked lists are stored in memory while the program runs. Do not assume records persist after the program exits unless file saving and loading are connected and tested.
- The session date validation checks the `YYYY-MM-DD` format, but it does not fully verify whether the date is a valid calendar date.

## Learning purpose

This project was created as a learning project to practise core C programming, linked-list operations, memory management, and splitting a program into multiple source files.

