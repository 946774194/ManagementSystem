#pragma once

typedef struct node{
    struct node *pre, *next;
    void *obj;
}Node;

typedef struct list {
    Node *head;
    int size;
}List;

List *createList();

void append(List *list, void *obj);

void delete(List *list, int index);

void *get(const List *list, int index);

void sort(const List *list, int (*cmp)(const void *, const void *));

void destroyList(List *list);
