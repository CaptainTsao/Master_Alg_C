/*
 * =====================================================================================
 *
 *       Filename:  bistree.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2021年05月05日 19时01分20秒
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

#include "bistree.h"

static void destroy_right(BisTree *bisTree, BiTreeNode *node);

static void rotate_left(BiTreeNode **node) {
    BiTreeNode *left, *grandchild;
    left = bitree_left(*node);

    if (((AvlNode *) bitree_data(left))->factor == AVL_LEFT_HEAVY) {
        // Perform an LL rotation
        bitree_left(*node) = bitree_right(left);
        bitree_right(left) = *node;
        ((AvlNode *) bitree_data(*node))->factor = AVL_BALANCED;
        ((AvlNode *) bitree_data(left))->factor = AVL_BALANCED;
        *node = left;
    } else {
        /* Perform an LR rotation */
        grandchild = bitree_right(left);
        bitree_right(left) = bitree_left(grandchild);
    }
}
