#include "slist.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

snode * snode_create(int data, snode * next) {
    snode * p = (snode *)malloc(sizeof(snode));
    p->next = next;
    p->data = data;
    return p;
}

slist * slist_create(void) {
    slist * p = (slist *)malloc(sizeof(slist));
    p->head = NULL;
    p->tail = NULL;
    p->size = 0;
    return p;
}

bool slist_empty(slist * list) {
    return (list->size == 0);
}

size_t slist_size(slist * list) {
    return list->size;
}

void slist_popfront(slist * list) {
    if (slist_empty(list)) {
        fprintf(stderr, "Underflow error (slist_popfront()): List is empty.\n");
        return;
    }
    snode * p = list->head;
    list->head = list->head->next;
    if (list->head == NULL) list->tail = NULL;
    --list->size;
    free(p);
}

void slist_popback(slist * list) {
    if (slist_empty(list)) {
        fprintf(stderr, "Underflow error (slist_popback()): List is empty.\n");
        return;
    }
    snode * p = list->head;
    while(p->next != list->tail) p = p->next;
    p->next = NULL;
    free(list->tail);
    list->tail = p;
}

void slist_pushfront(slist * list, int data) {
    snode * node = snode_create(data, list->head);
    list->head = node;
    if (list->size == 0) list->tail = node;
    ++list->size;
}

void slist_pushback(slist * list, int data) {
    if (list->size == 0) {
        slist_pushfront(list, data);
        return;
    }
    snode * node = snode_create(data, NULL);
    list->tail->next = node;
    list->tail = node;
    ++list->size;
}

void slist_clear(slist * list) {
    while(!slist_empty(list)) slist_popfront(list);
}

void slist_print(slist * list, const char * msg) {
    if (slist_empty(list)) {
        fprintf(stderr, "Underflow error (slist_print()): List is empty.\n");
        return;
    }
    printf("%s\n", msg);
    snode * p = list->head;
    while(p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

int slist_front(slist * list) {
    return list->head->data;
}
int slist_back(slist * list) {
    return list->tail->data;
}