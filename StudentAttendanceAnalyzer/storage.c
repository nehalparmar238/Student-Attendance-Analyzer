#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

#define LINE_SIZE 200

static int validDate(const char *date) {
    int i;
    if (strlen(date) != 10 || date[4] != '-' || date[7] != '-') return 0;
    for (i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (date[i] < '0' || date[i] > '9') return 0;
    }
    return 1;
}

int saveAllData(void) {
    FILE *f;
    struct Student *s;
    struct Session *c;
    struct Attendance *a;

    f = fopen("students.txt", "w");
    if (!f) { puts("Could not save students.txt"); return 0; }
    for (s = studentHead; s; s = s->next) fprintf(f, "%d|%s\n", s->id, s->name);
    if (fclose(f) != 0) { puts("Error saving students.txt"); return 0; }

    f = fopen("sessions.txt", "w");
    if (!f) { puts("Could not save sessions.txt"); return 0; }
    for (c = sessionHead; c; c = c->next) fprintf(f, "%d|%s|%s\n", c->id, c->date, c->subject);
    if (fclose(f) != 0) { puts("Error saving sessions.txt"); return 0; }

    f = fopen("attendance.txt", "w");
    if (!f) { puts("Could not save attendance.txt"); return 0; }
    for (a = attendanceHead; a; a = a->next) fprintf(f, "%d|%d|%c\n", a->studentId, a->sessionId, a->status);
    if (fclose(f) != 0) { puts("Error saving attendance.txt"); return 0; }

    puts("All data saved successfully.");
    return 1;
}

static void appendStudent(int id, const char *name) {
    struct Student *q, *p;
    if (id <= 0 || name[0] == '\0' || findStudent(id)) return;
    q = (struct Student *)malloc(sizeof *q);
    if (!q) return;
    q->id = id; snprintf(q->name, sizeof q->name, "%s", name); q->next = NULL;
    if (!studentHead) studentHead = q;
    else { p = studentHead; while (p->next) p = p->next; p->next = q; }
}

static void appendSession(int id, const char *date, const char *subject) {
    struct Session *q, *p;
    if (id <= 0 || !validDate(date) || subject[0] == '\0' || findSession(id)) return;
    q = (struct Session *)malloc(sizeof *q);
    if (!q) return;
    q->id = id; snprintf(q->date, sizeof q->date, "%s", date);
    snprintf(q->subject, sizeof q->subject, "%s", subject); q->next = NULL;
    if (!sessionHead) sessionHead = q;
    else { p = sessionHead; while (p->next) p = p->next; p->next = q; }
}

static void appendAttendance(int studentId, int sessionId, char status) {
    struct Attendance *q, *p, *scan;
    if (!findStudent(studentId) || !findSession(sessionId) || (status != 'P' && status != 'A')) return;
    for (scan = attendanceHead; scan; scan = scan->next)
        if (scan->studentId == studentId && scan->sessionId == sessionId) return;
    q = (struct Attendance *)malloc(sizeof *q);
    if (!q) return;
    q->studentId = studentId; q->sessionId = sessionId; q->status = status; q->next = NULL;
    if (!attendanceHead) attendanceHead = q;
    else { p = attendanceHead; while (p->next) p = p->next; p->next = q; }
}

void loadAllData(void) {
    FILE *f;
    char line[LINE_SIZE], name[NAME_SIZE], date[DATE_SIZE], subject[SUBJECT_SIZE], status;
    int id, studentId, sessionId;

    f = fopen("students.txt", "r");
    if (f) {
        while (fgets(line, sizeof line, f))
            if (sscanf(line, "%d|%49[^\n]", &id, name) == 2) appendStudent(id, name);
        fclose(f);
    }
    f = fopen("sessions.txt", "r");
    if (f) {
        while (fgets(line, sizeof line, f))
            if (sscanf(line, "%d|%10[^|]|%49[^\n]", &id, date, subject) == 3)
                appendSession(id, date, subject);
        fclose(f);
    }
    f = fopen("attendance.txt", "r");
    if (f) {
        while (fgets(line, sizeof line, f))
            if (sscanf(line, "%d|%d| %c", &studentId, &sessionId, &status) == 3)
                appendAttendance(studentId, sessionId, status);
        fclose(f);
    }
}
