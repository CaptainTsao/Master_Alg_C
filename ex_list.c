/*
 * =====================================================================================
 *
 *       Filename:  ex_1.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2021年04月05日 00时04分47秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  RuiCao
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>

//#include "list.h"
#include "leetcode.h"

static void print_list(const List *list) {
    ListElem *element;
    int *data, i;

    fprintf(stdout, "List size is %d\n", list_size(list));

    i = 0;
    element = list_head(list);

    while (1) {
        data = (int *) list_data(element);
        fprintf(stdout, "list[%d]=%d\n", i, *data);

        i++;

        if (list_is_tail(element))
            break;
        else
            element = list_next(element);
    }
}


int main() {
    List list;
    ListElem *element;
    int *data, i;

    list_init(&list, free);

    element = list_head(&list);

    for (i = 10; i > 0; i--) {
        if ((data = (int *) malloc(sizeof(int))) == NULL) {
            return 1;
        }
        *data = i;

        if (list_ins_next(&list, NULL, data) != 0)
            return 1;
    }

    print_list(&list);


    element = list_head(&list);

    for (i = 0; i < 7; i++) {
        element = list_next(element);
    }
    data = (int *) list_data(element);

    fprintf(stdout, "Removing an element after the one containing %03d\n", *data);

    if (list_rem_next(&list, element, (void **) &data) != 0)
        return 1;

    print_list(&list);


    fprintf(stdout, "Insert 011 at the tail of the list\n");
    *data = 11;
    if (list_ins_next(&list, list_tail(&list), data) != 0)
        return 1;
    print_list(&list);

    BiTreeNode*  res = SortedListToBST_LeetCode109(&list);

    return 0;
}
