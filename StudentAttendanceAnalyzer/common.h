#ifndef COMMON_H
#define COMMON_H

#define NAME_SIZE 50
#define DATE_SIZE 11
#define SUBJECT_SIZE 50

struct Student {
    int id;
    char name[NAME_SIZE];
    struct Student *next;
};

struct Session {
    int id;
    char date[DATE_SIZE];
    char subject[SUBJECT_SIZE];
    struct Session *next;
};

struct Attendance {
    int studentId;
    int sessionId;
    char status; /* P = Present, A = Absent */
    struct Attendance *next;
};

extern struct Student *studentHead;
extern struct Session *sessionHead;
extern struct Attendance *attendanceHead;

int readInt(const char *prompt, int *value);
void readLine(const char *prompt, char *destination, unsigned long size);

struct Student *findStudent(int id);
void addStudent(void);
void displayStudents(void);
void searchStudent(void);
void updateStudent(void);
void deleteStudent(void);
void freeStudents(void);

struct Session *findSession(int id);
void createSession(void);
void displaySessions(void);
void searchSession(void);
void freeSessions(void);

int hasAttendanceForStudent(int studentId);
int hasAttendanceForSession(int sessionId);
void markAttendance(void);
void displayAttendanceForSession(void);
void updateAttendance(void);
void freeAttendance(void);

void studentAttendanceReport(void);
void attendanceSummaryReport(void);
int saveAllData(void);
void loadAllData(void);

#endif
