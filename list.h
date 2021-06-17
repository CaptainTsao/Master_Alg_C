/*
 * =====================================================================================
 *
 *       Filename:  list.h
 *
 *    Description:  head file of list 
 *
 *        Version:  1.0
 *        Created:  2021年04月04日 22时09分19秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

/* Define a structure for linked list elememts */
typedef struct ListElem_ {
    void *data;
    struct ListElem_* next;
} ListElem;

/* Define a structure for linked lists */
typedef struct List_ {
    int size;
    int (*match)(const void* key1, const void* key2);
    void (*destroy)(void *data);
    ListElem *head;
    ListElem *tail;
} List;


/* Public interface */
void list_init(List *list, void (*destroy)(void *data));
void list_destroy(List* list);
int list_ins_next(List *list, ListElem *element, const void *data);
int list_rem_next(List *list, ListElem *element, void **data);
int list_ins_prev(List *list, ListElem *element, const void  *data);

#define list_size(list) ((list)->size)
#define list_head(list) ((list)->head)
#define list_tail(list) ((list)->tail)
#define list_is_head(list, element) (element == (list)->head ? 1 : 0)
#define list_is_tail(element) ((element)->next == NULL ? 1 : 0)
#define list_data(element) ((element)->data)
#define list_next(element) ((element)->next)


#endif
