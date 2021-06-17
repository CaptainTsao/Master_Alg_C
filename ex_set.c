/*
 * =====================================================================================
 *
 *       Filename:  ex_set.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2021年04月11日 15时52分34秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "set.h"

static void print_set(const Set *set)
{
    ListElem *member;
    int *data, size, i;

    fprintf(stdout, "Set size is %d\n", size = set_size(set));

    i = 0;
    member = list_head(set);
    
    while (i < size) {
        data = (int *)list_data(member);
        fprintf(stdout, "set[%03d]=%03d\n", i, *data);
        member = list_next(member);
        i++;
    }
    return;
}

static int match_int(const void *key1, const void *key2)
{
    return !memcmp(key1, key2, sizeof(int));
}

int main(int argc, char *argv[])
{
    Set set, set1, set2;
    int *data, retVal, i;
    
    /* Initialize the set */
    set_init(&set, match_int, free);
   
    /* perform some set operation */
    fprintf(stdout, "Inserting 10 members\n");
    for (i = 9; i >= 0; i--) {
        if ((data = (int *)malloc(sizeof(int))) == NULL) {
            return 1;
        }
        *data = i + 1;

        if ((retVal = set_insert(&set, data)) < 0) {
            return 1;
        } else if (retVal == 1) {
            free(data);
        }
    }
    print_set(&set);
    
    fprintf(stdout, "Inserting the same members again\n");
    for (i = 9; i >= 0; i--) {
        if ((data = (int *)malloc(sizeof(int))) == NULL) {
            return 1;
        }
        *data = i + 1;
        if ((retVal = set_insert(&set, data)) < 0) {
            return 1;
        } else if (retVal == 1) {
            free(data);
        }
    }
    print_set(&set);
}
