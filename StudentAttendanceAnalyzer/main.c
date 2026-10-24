#include <stdio.h>
#include "common.h"

static void saveAfterChange(void) {
    (void)saveAllData();
}

int main(void) {
    int choice = 0;
    loadAllData();
    puts("Student Attendance Analyzer");
    puts("Saved data loaded if files were available.");

    do {
        printf("\n========================================\n");
        printf("     STUDENT ATTENDANCE ANALYZER\n");
        printf("========================================\n");
        printf("1. Add student\n");
        printf("2. Display all students\n");
        printf("3. Search student\n");
        printf("4. Update student\n");
        printf("5. Delete student\n");
        printf("6. Create class session\n");
        printf("7. Display all sessions\n");
        printf("8. Search session\n");
        printf("9. Mark attendance\n");
        printf("10. View attendance for a session\n");
        printf("11. Update attendance\n");
        printf("12. Student attendance history\n");
        printf("13. Attendance summary and shortage report\n");
        printf("14. Save all data\n");
        printf("15. Exit\n");

        if (!readInt("Enter your choice: ", &choice)) continue;

        switch (choice) {
            case 1: addStudent(); saveAfterChange(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); saveAfterChange(); break;
            case 5: deleteStudent(); saveAfterChange(); break;
            case 6: createSession(); saveAfterChange(); break;
            case 7: displaySessions(); break;
            case 8: searchSession(); break;
            case 9: markAttendance(); saveAfterChange(); break;
            case 10: displayAttendanceForSession(); break;
            case 11: updateAttendance(); saveAfterChange(); break;
            case 12: studentAttendanceReport(); break;
            case 13: attendanceSummaryReport(); break;
            case 14: saveAllData(); break;
            case 15:
                saveAllData();
                puts("Exiting program. Goodbye!");
                break;
            default: puts("Invalid choice. Please choose 1 to 15.");
        }
    } while (choice != 15);

    freeAttendance();
    freeStudents();
    freeSessions();
    return 0;
}
