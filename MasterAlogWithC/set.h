/*
 * =====================================================================================
 *
 *       Filename:  set.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2021年04月05日 01时03分27秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef SET_H
#define SET_H

#include <stdlib.h>

#include "list.h"

/* 
 *Implement sets as linked lists 
 * */
typedef List Set;


void set_init(Set *set, int (*match)(const void *key1, const void *key2),
              void (*destroy)(void *data));

#define set_destroy list_destroy

int set_insert(Set *set, const void *data);


#endif
