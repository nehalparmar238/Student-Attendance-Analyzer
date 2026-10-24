#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "common.h"

struct Session *sessionHead = NULL;

struct Session *findSession(int id) {
    struct Session *p = sessionHead;
    while (p != NULL) {
        if (p->id == id) return p;
        p = p->next;
    }
    return NULL;
}

static int validDateFormat(const char *date) {
    int i;
    if (strlen(date) != 10 || date[4] != '-' || date[7] != '-') return 0;
    for (i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (!isdigit((unsigned char)date[i])) return 0;
    }
    return 1;
}

void createSession(void) {
    int id;
    struct Session *q, *p;

    if (!readInt("Enter session ID: ", &id)) return;
    if (id <= 0) {
        printf("Session ID must be positive.\n");
        return;
    }
    if (findSession(id) != NULL) {
        printf("A session with this ID already exists.\n");
        return;
    }

    q = (struct Session *)malloc(sizeof(struct Session));
    if (q == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    q->id = id;
    readLine("Enter date (YYYY-MM-DD): ", q->date, sizeof(q->date));
    if (!validDateFormat(q->date)) {
        printf("Invalid date format. Use YYYY-MM-DD, e.g. 2026-10-23.\n");
        free(q);
        return;
    }
    readLine("Enter subject name: ", q->subject, sizeof(q->subject));
    if (q->subject[0] == '\0') {
        printf("Subject cannot be empty. Session was not created.\n");
        free(q);
        return;
    }

    q->next = NULL;
    if (sessionHead == NULL) sessionHead = q;
    else {
        p = sessionHead;
        while (p->next != NULL) p = p->next;
        p->next = q;
    }
    printf("Class session created successfully.\n");
}

void displaySessions(void) {
    struct Session *p = sessionHead;
    if (p == NULL) {
        printf("No class sessions created yet.\n");
        return;
    }
    printf("\n--- Class Sessions ---\n");
    printf("%-12s %-12s %s\n", "Session ID", "Date", "Subject");
    while (p != NULL) {
        printf("%-12d %-12s %s\n", p->id, p->date, p->subject);
        p = p->next;
    }
}

void searchSession(void) {
    int id;
    struct Session *p;
    if (!readInt("Enter session ID to search: ", &id)) return;
    p = findSession(id);
    if (p == NULL) printf("Session not found.\n");
    else printf("Found: Session %d | Date: %s | Subject: %s\n",
                p->id, p->date, p->subject);
}

void freeSessions(void) {
    struct Session *p = sessionHead;
    while (p != NULL) {
        struct Session *next = p->next;
        free(p);
        p = next;
    }
    sessionHead = NULL;
}
