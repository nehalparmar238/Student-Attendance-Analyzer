#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

struct Student *studentHead = NULL;

struct Student *findStudent(int id) {
    struct Student *p = studentHead;
    while (p != NULL) {
        if (p->id == id) return p;
        p = p->next;
    }
    return NULL;
}

void addStudent(void) {
    int id;
    struct Student *q, *p;

    if (!readInt("Enter student ID: ", &id)) return;
    if (id <= 0) {
        printf("Student ID must be positive.\n");
        return;
    }
    if (findStudent(id) != NULL) {
        printf("A student with this ID already exists.\n");
        return;
    }

    q = (struct Student *)malloc(sizeof(struct Student));
    if (q == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    q->id = id;
    readLine("Enter student name: ", q->name, sizeof(q->name));
    if (q->name[0] == '\0') {
        printf("Name cannot be empty. Student was not added.\n");
        free(q);
        return;
    }

    q->next = NULL;
    if (studentHead == NULL) studentHead = q;
    else {
        p = studentHead;
        while (p->next != NULL) p = p->next;
        p->next = q;
    }
    printf("Student added successfully.\n");
}

void displayStudents(void) {
    struct Student *p = studentHead;
    if (p == NULL) {
        printf("No students added yet.\n");
        return;
    }
    printf("\n--- Student List ---\n");
    printf("%-10s %s\n", "ID", "Name");
    while (p != NULL) {
        printf("%-10d %s\n", p->id, p->name);
        p = p->next;
    }
}

void searchStudent(void) {
    int id;
    struct Student *p;
    if (!readInt("Enter student ID to search: ", &id)) return;
    p = findStudent(id);
    if (p == NULL) printf("Student not found.\n");
    else printf("Found: ID: %d | Name: %s\n", p->id, p->name);
}

void updateStudent(void) {
    int id;
    struct Student *p;
    char newName[NAME_SIZE];

    if (!readInt("Enter student ID to update: ", &id)) return;
    p = findStudent(id);
    if (p == NULL) {
        printf("Student not found.\n");
        return;
    }
    readLine("Enter new student name: ", newName, sizeof(newName));
    if (newName[0] == '\0') {
        printf("Name cannot be empty. No changes made.\n");
        return;
    }
    strcpy(p->name, newName);
    printf("Student updated successfully.\n");
}

void deleteStudent(void) {
    int id;
    struct Student *p = studentHead, *previous = NULL;

    if (!readInt("Enter student ID to delete: ", &id)) return;
    if (hasAttendanceForStudent(id)) {
        printf("Cannot delete this student because attendance records exist.\n");
        printf("Keep the student record so attendance history remains valid.\n");
        return;
    }

    while (p != NULL && p->id != id) {
        previous = p;
        p = p->next;
    }
    if (p == NULL) {
        printf("Student not found.\n");
        return;
    }
    if (previous == NULL) studentHead = p->next;
    else previous->next = p->next;
    free(p);
    printf("Student deleted successfully.\n");
}

void freeStudents(void) {
    struct Student *p = studentHead;
    while (p != NULL) {
        struct Student *next = p->next;
        free(p);
        p = next;
    }
    studentHead = NULL;
}
