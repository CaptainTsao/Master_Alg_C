//
// Created by rcao on 2021/6/18.
//

#include <stdlib.h>
#include "adlist.h"

List *ListCreate(void) {
    List *list;

    if ((list = (List *) malloc(sizeof(*list))) == NULL) {
        return NULL;
    }
    list->head = list->tail = NULL;
    list->len = 0;
    list->dup = NULL;
    list->free = NULL;
    list->match = NULL;
    return list;
}

void ListRelease(List *list);

/* Remove all elements from the list without destroying the list itself */
void ListEmpty(List *list) {
    unsigned long len;
    ListNode *current, *next;

    current = list->head;
    len = list->len;
    while (len--) {
        next = current->next;
        if (list->free) {
            list->free(current->value);
        }
        free(current);
        current = next;
    }
    list->head = list->tail = NULL;
    list->len = 0;
}

List *ListAddNodeHead(List *list, void *value);

List *ListAddNodeTail(List *list, void *value);

List *ListInsertNode(List *list, ListNode *old_node, void *value, int after);

void ListDelNode(List *list, ListNode *node);

ListIter *ListGetIterator(List *list, int direction);

ListNode *ListNext(ListIter *iter);

void ListReleaseIterator(ListIter *iter);

List *ListDup(List *orig);

ListNode *ListSearchKey(List *list, void *key);

ListNode *ListIndex(List *list, long index);

void ListRewind(List *list, ListIter *iter);

void ListRewindTail(List *list, ListIter *iter);

void ListRotateTailToHead(List *list);

void ListRotateHeadToTail(List *list);

/* Add all elements of list 'o' at the end of the
 * list 'l'. The list 'other' remains empty but
 * otherwise valid. */

void ListJoin(List *list, List *other) {
    if (other->len == 0) {
        return;
    }

    other->head->prev = list->tail;
    if (list->tail) {
        list->tail->next = other->head;
    } else {
        list->head = other->head;
    }

    list->tail = other->tail;
    list->len += other->len;

    /* Setup other as an empty list. */
    other->head = other->tail = NULL;
    other->len = 0;
}