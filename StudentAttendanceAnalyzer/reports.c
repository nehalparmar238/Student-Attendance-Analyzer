#include <stdio.h>
#include "common.h"

void studentAttendanceReport(void) {
    int id, present = 0, absent = 0, total = 0;
    struct Student *student;
    struct Attendance *a;

    if (!readInt("Enter student ID for report: ", &id)) return;
    student = findStudent(id);
    if (student == NULL) { puts("Student not found."); return; }

    printf("\nAttendance history for %s (ID %d)\n", student->name, student->id);
    printf("%-12s %-12s %-25s %s\n", "Session ID", "Date", "Subject", "Status");
    for (a = attendanceHead; a != NULL; a = a->next) {
        if (a->studentId == id) {
            struct Session *session = findSession(a->sessionId);
            if (session != NULL)
                printf("%-12d %-12s %-25s %s\n", session->id, session->date,
                       session->subject, a->status == 'P' ? "Present" : "Absent");
            total++;
            if (a->status == 'P') present++; else absent++;
        }
    }
    if (total == 0) { puts("No attendance records for this student."); return; }
    printf("Present: %d | Absent: %d | Total recorded sessions: %d\n", present, absent, total);
    printf("Attendance percentage: %.2f%%\n", (double)present * 100.0 / total);
}

void attendanceSummaryReport(void) {
    struct Student *student = studentHead;
    int threshold;
    if (student == NULL) { puts("No students registered."); return; }
    if (!readInt("Enter shortage threshold percentage (0-100): ", &threshold)) return;
    if (threshold < 0 || threshold > 100) { puts("Threshold must be between 0 and 100."); return; }

    printf("\n--- Attendance Summary (threshold: %d%%) ---\n", threshold);
    printf("%-8s %-22s %-8s %-8s %-8s %s\n", "ID", "Name", "Present", "Absent", "Total", "Rate");
    while (student != NULL) {
        struct Attendance *a;
        int present = 0, absent = 0, total = 0;
        double percentage = 0.0;
        for (a = attendanceHead; a != NULL; a = a->next) {
            if (a->studentId == student->id) {
                total++;
                if (a->status == 'P') present++; else absent++;
            }
        }
        if (total > 0) percentage = (double)present * 100.0 / total;
        printf("%-8d %-22.22s %-8d %-8d %-8d %6.2f%%", student->id,
               student->name, present, absent, total, percentage);
        if (total == 0) printf("  No records");
        else if (percentage < threshold) printf("  SHORTAGE");
        putchar('\n');
        student = student->next;
    }
    puts("Note: Percentages use sessions with recorded attendance.");
}
