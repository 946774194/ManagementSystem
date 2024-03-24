#include <stdlib.h>
#include "List.h"

List *createList() {
    List *list = (List *)malloc(sizeof(List));
    list->head = (Node *)malloc(sizeof(Node));
    list->head->pre = list->head->next = list->head;
    list->size = 0;
    return list;
}

void append(List *list, void *obj) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->obj = obj;
    node->pre = list->head->pre;
    node->next = list->head;
    list->head->pre->next = node;
    list->head->pre = node;
    list->size++;
}

void delete(List *list, int index) {
    if (index < 0 || index >= list->size) {
        return;
    }
    Node *node = list->head->next;
    for (int i = 0; i < index; i++) {
        node = node->next;
    }
    node->pre->next = node->next;
    node->next->pre = node->pre;
    free(node->obj);
    free(node);
    list->size--;
}

void *get(const List *list, int index) {
    if (index < 0 || index >= list->size) {
        return NULL;
    }
    Node *node = list->head->next;
    for (int i = 0; i < index; i++) {
        node = node->next;
    }
    return node->obj;
}

void sort(const List *list, int (*cmp)(const void *, const void *)) {
    for (Node *i = list->head->next; i != list->head; i = i->next) {
        for (Node *j = i->next; j != list->head; j = j->next) {
            if (cmp(i->obj, j->obj) > 0) {
                void *temp = i->obj;
                i->obj = j->obj;
                j->obj = temp;
            }
        }
    }
}

void destroyList(List *list) { // TODO: 追究obj的释放
    Node *node = list->head->next;
    while (node != list->head) {
        Node *temp = node;
        node = node->next;
        free(temp);
    }
    free(list->head);
}