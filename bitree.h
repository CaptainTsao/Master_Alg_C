/*
 * =====================================================================================
 *
 *       Filename:  bitree.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2021年04月24日 20时39分09秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef BITREE_H
#define BITREE_H

#include <stdlib.h>

typedef struct BiTreeNode_ {
    void *data;
    struct BiTreeNode_ *left;
    struct BiTreeNode_ *right;
} BiTreeNode;

/* define a structure for binary tree */
typedef struct BiTree_ {
    int size;

    int (*compare)(const void *key1, const void *key2);

    void (*destroy)(void *data);

    BiTreeNode *root;
} BiTree;

/* public interface */
void bitree_init(BiTree *biTree, void (*destroy)(void *data));

void bitree_init_with_exited_node(BiTree *biTree, void (*destroy)(void *data), BiTreeNode *node, int size);

void bitree_destroy(BiTree *biTree);

int bitree_ins_left(BiTree *biTree, BiTreeNode *node, const void *data);

int bitree_ins_right(BiTree *biTree, BiTreeNode *node, const void *data);

void bitree_rem_left(BiTree *biTree, BiTreeNode *node);

void bitree_rem_right(BiTree *biTree, BiTreeNode *node);

int bitree_merge(BiTree *merge, BiTree *left, BiTree *right, const void *data);

#define bitree_size(biTree) ((biTree)->size)
#define bitree_root(biTree) ((biTree)->root)
#define bitree_is_eob(node) ((node) == NULL)
#define bitree_is_left(node) ((node)->left == NULL && (node)->right == NULL)
#define bitree_data(node) ((node)->data)
#define bitree_left(node) ((node)->left)
#define bitree_right(node) ((node)->right)

#endif
