//
// Created by rcao on 2021/6/18.
//

#ifndef _ADLIST_H
#define _ADLIST_H

/* Node, List and Iterator are the only data structure used currently */
typedef struct ListNode {
    struct ListNode *prev;
    struct ListNode *next;
    void *value;
} ListNode;

typedef struct ListIter {
    ListNode *next;
    int direction;
} ListIter;

typedef struct List {
    ListNode *head;
    ListNode *tail;

    void *(*dup)(void *ptr);

    void (*free)(void *ptr);

    int (*match)(void *ptr, void *key);

    unsigned long len;
} List;

/* Function implemented as macros */
#define list_length(list) ((list)->len)
#define list_head(list) ((list)->head)
#define list_tail(list) ((list)->tail)
#define list_node_data(node) ((node)->data)
#define list_next_node(node) ((node)->next)
#define list_prev_node(node) ((node)->prev)
#define list_is_head(list, node) (node == (list)->head ? 1 : 0)
#define list_is_tail(node) ((node)->next == NULL ? 1 : 0)

#define list_set_dup_method(list, method) ((list)->dup = (method))
#define list_set_free_method(list, method) ((list)->free = (method))
#define list_set_match_method(list, method) ((list)->match = (method))

#define list_get_dup_method(list, method) ((list)->dup)
#define list_get_free_method(list, method) ((list)->free)
#define list_get_match_method(list, method) ((list)->match)

/* Prototypes */
List *ListCreate(void);
void ListRelease(List *list);
void ListEmpty(List *list);
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
void ListJoin(List *l, List *o);



#endif //_ADLIST_H
