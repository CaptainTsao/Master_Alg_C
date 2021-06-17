/*
 * =====================================================================================
 *
 *       Filename:  bistree.h
 *
 *    Description:  Binary search tree
 *
 *        Version:  1.0
 *        Created:  2021年05月05日 18时53分10秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef BISTREE_H
#define BISTREE_H

#include "bitree.h"

/* Define balance factors for AVL trees. */
#define AVL_LEFT_HEAVY  1
#define AVL_BALANCED    0
#define AVL_RGT_HEAVY   -1


/* Define a structure for nodes in AVL trees */
typedef struct AvlNode_ {
    void *data;
    int hidden;
    int factor;
} AvlNode;


/* Implement binary search trees as binary trees */
typedef BiTree BisTree;


/* Public Interface */
void bistree_init(BisTree *bisTree, 
                  int(*compare)(const void *key1, const void *key2), 
                  void(*destroy)(void *data));

void bistree_destroy(BisTree *bisTree);

int bistree_insert(BisTree *bisTree, const void *data);

int bistree_remove(BisTree *bisTree, const void *data);

int bistree_lookup(BisTree *bisTree, void **data);

#define bistree_size(bisTree) ((bisTree)->size)
#endif
