/*
 * =====================================================================================
 *
 *       Filename:  set.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2021年04月05日 12时16分04秒
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
#include "set.h"

void set_init(Set *set, int (*match)(const void *key1, const void *key2), void (*destroy)(void *data)) 
{
    list_init(set, destroy);
    set->match = match;
    return;
}

int set_insert(Set *set, const void *data)
{   
    // do not allow the insertion of duplicates
    if (set_is_member(set, data)) {
        return 1;
    }
    // insert data 
    return list_ins_next(set, list_tail(set), data);
}


int set_remove(Set *set, void **data)
{
    ListElem *member, *prev;
    
    // find the member to remove 
    prev = NULL;
    
    for (member = list_head(set); member != NULL; member = list_next(member))
    {
        if (set->match(*data, list_data(member)))
            break;

        prev = member;
    }

    // return if member is not found
    if (member == NULL) {
        return -1;
    }

    return list_rem_next(set, prev, data);
}


int
set_union(Set *setu, const Set *set1, const Set *set2)
{
    ListElem *member;
    void *data;

    // initialize the set for union
    set_init(setu, set1->match, NULL);

    // insert the member of the first set
    for (member = list_head(set1); member != NULL; member = list_next(member)) {
        data = list_data(member);
        if (list_ins_next(setu, list_tail(setu), data) != 0) {
            set_destroy(setu);
            return -1;
        }
    }
    
    // insert the member of second set
    for (member = list_head(set2); member != NULL; member = list_next(member)) {
        if (set_is_member(set1, list_data(member))) {
            continue;       // do not allow the insertion of duplicates
        } else {
            data = list_data(member);

            if (list_ins_next(setu, list_tail(setu), data) != 0) {
                set_destroy(setu);
                return -1;
            }
        }
    }

    return 0;
}

int
set_intersection(Set *seti, const Set *set1, const Set *set2)
{
    ListElem *member;
    void *data;

    // initializee the set for intersection 
    set_init(seti, set1->match, NULL);

    // insert the members presetn in both sets 
    for (member = list_head(set1); member != NULL; member = list_next(member)) {
        if (set_is_member(set2, list_data(member))) {
            data = list_data(member);

            if (list_ins_next(seti, list_tail(seti), data) != 0) {
                set_destroy(seti);
                return -1;
            }
        }
    }
    return 0;
}


int 
set_difference(Set *setd, const Set *set1, const Set *set2)
{
    ListElem *member;
    void *data;
    // initialize the set of the difference
    set_init(setd, set1->match, NULL);

    // insert member form set1 not in set2 
    for (member = list_head(set1); member != NULL; member = list_next(member)) {
        if (!set_is_member(set2, list_data(member))) {
            data = list_data(member);
            if (list_ins_next(setd, list_tail(setd), data) != 0) {
                set_destroy(setd);
                return -1;
            }
        }
    }
    return 0;
}


int 
set_is_member(const Set *set, const void *data)
{
    ListElem *member;

    for (member = list_head(set); member != NULL; member = list_next(member)) {
        if (set->match(data, list_data(member))) {
                    return 1;
        }
    }
    return 0;
}


int set_is_subset(const Set *set1, const Set *set2)
{
    ListElem *member;
    if (set_size(set1) > set_size(set2)) 
        return 0;
    
    for (member = list_head(set1); member != NULL; member = list_next(member)) {
        if (!set_is_member(set2, list_data(member)))
            return 0;
    }
    return 1;
}

int set_is_equal(const Set *set1, const Set *set2) {
    // Do a quick tets to rule out some cases
    if (set_size(set1) != set_size(set2)) {
        return 0;
    }

    return set_is_subset(set1, set2);
}


