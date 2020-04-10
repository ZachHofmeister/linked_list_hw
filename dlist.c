#include "dlist.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

dnode * dnode_create(int data, dnode* prev, dnode* next) {
    dnode * p = (dnode *)malloc(sizeof(dnode));
    p->prev = prev;
    p->next = next;
    p->data = data;
    return p;
}

dlist * dlist_create(void) {
    dlist * p = (dlist *)malloc(sizeof(dlist));
    p->head = NULL;
    p->tail = NULL;
    p->size = 0;
    return p;
}

bool dlist_empty(dlist * list) {
    return (list->size == 0);
}

size_t dlist_size(dlist * list) {
    return list->size;
}

//NULL <-- dnode <--> head <--> tail --> NULL
//NULL <-- head <--> tail --> NULL
void dlist_popfront(dlist * list) {
    if (dlist_empty(list)) {
        fprintf(stderr, "Underflow error (dlist_pop_front()): List is empty.\n");
        return;
    }
    dnode * p = list->head;
    list->head = list->head->next;
    if (list->head == NULL) list->tail = NULL;
    else list->head->prev = NULL;
    --list->size;
    free(p);
}

//NULL <-- head <--> tail <--> dnode --> NULL
//NULL <-- head <--> tail --> NULL
void dlist_popback(dlist * list) {
    if (dlist_empty(list)) {
        fprintf(stderr, "Underflow error (dlist_pop_back()): List is empty.\n");
        return;
    }
    dnode * p = list->tail;
    list->tail = list->tail->prev;
    if (list->tail == NULL) list->head = NULL;
    else list->tail->next = NULL;
    --list->size;
    free(p);
}

void dlist_pushfront(dlist * list, int data) {
    dnode * node = dnode_create(data, NULL, NULL);
    node->next = list->head;
    if (list->size != 0) list->head->prev = node;
    node->prev = NULL;
    list->head = node;
    if (list->size == 0) list->tail = node;
    ++list->size;
}

void dlist_pushback(dlist * list, int data) {
    if (list->size == 0) {
        dlist_pushfront(list, data);
        return;
    }
    dnode * node = dnode_create(data, NULL, NULL);
    node->next = NULL;
    node->prev = list->tail;
    list->tail->next = node;
    list->tail = node;
    ++list->size;
}

void dlist_clear(dlist * list) {
    while(!dlist_empty(list)) dlist_popfront(list);
}

void dlist_print(dlist * list, const char * msg) {
    if (dlist_empty(list)) {
        fprintf(stderr, "Underflow error (dlist_print()): List is empty.\n");
        return;
    }
    printf("%s\n", msg);
    dnode * p = list->head;
    while(p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

int dlist_front(dlist * list) {
    return list->head->data;
}
int dlist_back(dlist * list) {
    return list->tail->data;
}