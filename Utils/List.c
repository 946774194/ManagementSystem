#include <stdlib.h>
#include "List.h"

List *createList() { // 创建一个空的List
    List *list = (List *)malloc(sizeof(List));
    list->head = (Node *)malloc(sizeof(Node));
    list->head->pre = list->head->next = list->head;
    list->size = 0;
    return list;
}

void append(List *list, void *obj) { // 在List的末尾添加一个元素
    Node *node = (Node *)malloc(sizeof(Node));
    node->obj = obj;
    node->pre = list->head->pre;
    node->next = list->head;
    list->head->pre->next = node;
    list->head->pre = node;
    list->size++;
}

void delete(List *list, int index) { // 删除List中的第index个元素
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

void *get(const List *list, int index) { // 获取List中的第index个元素
    if (index < 0 || index >= list->size) {
        return NULL;
    }
    Node *node = list->head->next;
    for (int i = 0; i < index; i++) {
        node = node->next;
    }
    return node->obj;
}

void sort(const List *list, int (*cmp)(const void *, const void *)) { // 对List中的元素进行排序
    for (Node *i = list->head->next; i != list->head; i = i->next) {
        for (Node *j = i->next; j != list->head; j = j->next) {
            if (cmp(i->obj, j->obj) > 0) { // 交换
                void *temp = i->obj;
                i->obj = j->obj;
                j->obj = temp;
            }
        }
    }
}

void destroyList(List *list) { // 销毁List
    Node *node = list->head->next;
    while (node != list->head) {
        Node *temp = node;
        node = node->next;
        free(temp);
    }
    free(list->head);
}