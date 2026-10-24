#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "common.h"

struct Attendance *attendanceHead = NULL;

static struct Attendance *findAttendance(int studentId, int sessionId) {
    struct Attendance *p = attendanceHead;
    while (p != NULL) {
        if (p->studentId == studentId && p->sessionId == sessionId) return p;
        p = p->next;
    }
    return NULL;
}

int hasAttendanceForStudent(int studentId) {
    struct Attendance *p = attendanceHead;
    while (p != NULL) {
        if (p->studentId == studentId) return 1;
        p = p->next;
    }
    return 0;
}

int hasAttendanceForSession(int sessionId) {
    struct Attendance *p = attendanceHead;
    while (p != NULL) {
        if (p->sessionId == sessionId) return 1;
        p = p->next;
    }
    return 0;
}

void markAttendance(void) {
    int studentId, sessionId;
    char statusLine[20];
    char status;
    struct Student *student;
    struct Session *session;
    struct Attendance *q, *p;

    if (!readInt("Enter student ID: ", &studentId)) return;
    student = findStudent(studentId);
    if (student == NULL) {
        printf("Student ID not found. Add the student first.\n");
        return;
    }

    if (!readInt("Enter session ID: ", &sessionId)) return;
    session = findSession(sessionId);
    if (session == NULL) {
        printf("Session ID not found. Create the session first.\n");
        return;
    }

    if (findAttendance(studentId, sessionId) != NULL) {
        printf("Attendance already exists for this student and session.\n");
        printf("Use Update Attendance to change Present/Absent status.\n");
        return;
    }

    readLine("Enter status (P = Present, A = Absent): ", statusLine, sizeof(statusLine));
    status = (char)toupper((unsigned char)statusLine[0]);
    if ((status != 'P' && status != 'A') || statusLine[1] != '\0') {
        printf("Invalid status. Enter only P or A.\n");
        return;
    }

    q = (struct Attendance *)malloc(sizeof(struct Attendance));
    if (q == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    q->studentId = studentId;
    q->sessionId = sessionId;
    q->status = status;
    q->next = NULL;

    if (attendanceHead == NULL) attendanceHead = q;
    else {
        p = attendanceHead;
        while (p->next != NULL) p = p->next;
        p->next = q;
    }

    printf("Attendance saved: %s — %s — %s\n",
           student->name, session->subject,
           status == 'P' ? "Present" : "Absent");
}

void displayAttendanceForSession(void) {
    int sessionId;
    struct Session *session;
    struct Attendance *p;
    int found = 0;

    if (!readInt("Enter session ID: ", &sessionId)) return;
    session = findSession(sessionId);
    if (session == NULL) {
        printf("Session not found.\n");
        return;
    }

    printf("\nAttendance for Session %d | %s | %s\n",
           session->id, session->date, session->subject);
    printf("%-10s %-25s %s\n", "Student ID", "Student Name", "Status");

    p = attendanceHead;
    while (p != NULL) {
        if (p->sessionId == sessionId) {
            struct Student *student = findStudent(p->studentId);
            printf("%-10d %-25s %s\n",
                   p->studentId,
                   student != NULL ? student->name : "(student missing)",
                   p->status == 'P' ? "Present" : "Absent");
            found = 1;
        }
        p = p->next;
    }
    if (!found) printf("No attendance has been recorded for this session yet.\n");
}

void updateAttendance(void) {
    int studentId, sessionId;
    char statusLine[20];
    char status;
    struct Attendance *record;

    if (!readInt("Enter student ID: ", &studentId)) return;
    if (findStudent(studentId) == NULL) {
        printf("Student not found.\n");
        return;
    }
    if (!readInt("Enter session ID: ", &sessionId)) return;
    if (findSession(sessionId) == NULL) {
        printf("Session not found.\n");
        return;
    }

    record = findAttendance(studentId, sessionId);
    if (record == NULL) {
        printf("No attendance record found for that student and session.\n");
        printf("Use Mark Attendance to create it first.\n");
        return;
    }

    readLine("Enter new status (P = Present, A = Absent): ",
             statusLine, sizeof(statusLine));
    status = (char)toupper((unsigned char)statusLine[0]);
    if ((status != 'P' && status != 'A') || statusLine[1] != '\0') {
        printf("Invalid status. Enter only P or A.\n");
        return;
    }

    record->status = status;
    printf("Attendance updated successfully.\n");
}

void freeAttendance(void) {
    struct Attendance *p = attendanceHead;
    while (p != NULL) {
        struct Attendance *next = p->next;
        free(p);
        p = next;
    }
    attendanceHead = NULL;
}
