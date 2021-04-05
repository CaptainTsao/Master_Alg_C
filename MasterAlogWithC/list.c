/*
 * =====================================================================================
 *
 *       Filename:  list.c
 *
 *    Description:  source file of list
 *
 *        Version:  1.0
 *        Created:  2021年04月04日 22时46分33秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <string.h>

#include "list.h"

/* Initialize the list */
void 
list_init(List *list, void (*destroy)(void *data)) 
{
    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;
    list->tail = NULL;
    return;
}

void list_destroy(List *list) 
{
    void *data;
    while (list_size(list) > 0) {
        if (list_rem_next(list, NULL, (void **)&data) == 0 && list->destroy != NULL) 
        {
            // Call a user-defined function to free dynamically allocated data.
            list->destroy(data);
        }
    }
    // No operations are allowed now, but clear the structure as a precaution.
    memset(list, 0, sizeof(List));
    return;
}

/* insert element into list */
int 
list_ins_next(List *list, ListElem *element, const void *data)
{
    ListElem *new_element;
    // allocate storage for the element 
    if ((new_element = (ListElem *)malloc(sizeof(ListElem))) == NULL) {
        return -1;
    }
    // Insert element into list
    new_element->data = (void *)data;
    if (element == NULL) {
        /* handle insertio at the head of list */
        if (list_size(list) == 0) {
            list->tail = new_element;
        }
        new_element->next = list->head;
        list->head = new_element;
    } else {
        /* handle insertion somewhere other than at the hand */
        if (element->next == NULL) {
            list->tail = new_element;
        }
        new_element->next = element->next;
        element->next = new_element;
    }
    /* adjust the size of list to account for the inserted element */
    list->size++;
    return 0;
}


int 
list_rem_next(List *list, ListElem *element, void **data) 
{
    ListElem *old_element;
    /* Do not allow removal from empty list */
    if (list_size(list) == 0) {
        return -1;
    }
    /* remove element from list */
    if (element == NULL) {
        /* handle removal from the head of list */
        *data = list->head->data;
        old_element = list->head;
        list->head = list->head->next;

        if (list_size(list) == 1) {
            list->tail = NULL;
        }
    } else {
        /* handle removal from somewhere other than the head */
        if (element->next == NULL) {
            return -1;
        }

        *data = element->next->data;
        old_element = element->next;
        element->next = element->next->next;

        if (element->next == NULL) {
            list->tail = element;
        }
    }
    /* free storage allocated by abstract data type */
    free(old_element);
    list->size--;

    return 0;
}




























