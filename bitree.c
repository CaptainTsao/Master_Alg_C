#include <stdlib.h>
#include <string.h>

#include "bitree.h"

void bitree_init(BiTree *biTree, void (*destroy)(void *data)) {
    biTree->size = 0;
    biTree->destroy = destroy;
    biTree->root = NULL;
}

void bitree_init_with_exited_node(BiTree *biTree, void (*destroy)(void *data), BiTreeNode *node, int size) {
    biTree->size = size;
    biTree->destroy = destroy;
    biTree->root = node;
}

void bitree_destroy(BiTree *biTree) {
    // remove all nodes from the tree
    bitree_rem_left(biTree, NULL);
    // no operations are allowed now, but clear the structures as a precaution
    memset(biTree, 0, sizeof(BiTree));
}

int bitree_ins_left(BiTree *biTree, BiTreeNode *node, const void *data) {
    BiTreeNode *new_node, **position;
    // determine where to insert the node
    if (node == NULL) {
        // allow insertion at the root only in an empty tree
        if (bitree_size(biTree) > 0) {
            return -1;
        }
        position = &biTree->root;
    } else {
        // normally allow insertion only at the end of a branch
        if (bitree_left(node) != NULL) {
            return -1;
        }
        position = &node->left;
    }
    // allocate storage for the node
    if ((new_node = (BiTreeNode *) malloc(sizeof(BiTreeNode))) == NULL) {
        return -1;
    }
    // insert the node into the tree
    new_node->data = (void *) data;
    new_node->left = NULL;
    new_node->right = NULL;
    *position = new_node;
    // adjust the size of tree to acount for the inserted node.
    biTree->size++;
    return 0;
}

int bitree_ins_right(BiTree *biTree, BiTreeNode *node, const void *data) {
    BiTreeNode *new_node, **position;
    // determine where to insert the node
    if (node == NULL) {
        // allow insertion at the root only in an empty tree
        if (bitree_size(biTree) > 0) {
            /* code */
            return -1;
        }
        position = &biTree->root;
    } else {
        // normally allow insertion only at the end of a branch
        if (bitree_right(node) != NULL) {
            return -1;
        }
        position = &node->right;
    }
    // allocate storage for the node
    if ((new_node = (BiTreeNode *) malloc(sizeof(BiTreeNode))) == NULL) {
        return -1;
    }
    new_node->data = (void *) data;
    new_node->left = NULL;
    new_node->right = NULL;
    *position = new_node;

    biTree->size++;
    return 0;
}

void bitree_rem_left(BiTree *biTree, BiTreeNode *node) {
    BiTreeNode **position;
    // do not allow removal from an empty tree;
    if (bitree_size(biTree) == 0) {
        return;
    }
    // determine where to remove nodes
    if (node == NULL) {
        position = &biTree->root;
    } else {
        position = &node->left;
    }
    // remove the node
    if (*position != NULL) {
        bitree_rem_left(biTree, *position);
        bitree_rem_right(biTree, *position);
        if (biTree->destroy != NULL) {
            biTree->destroy((*position)->data);
        }
        free(*position);
        *position = NULL;
        biTree->size--;
    }
}

/* return:如果合并操作成功，返回0;否则返回-1
 * 描述:将left与right所指定的两棵二叉树合并为单颗二叉树。
 * 合并完成后，参数data所代表的的数据存储在merge的根节点中，
 * 而left与right则代表该根节点的左右子树。一旦合并完成，
 * left与right就好像在它们之上执行bitree_destroy操作一样。*/
int bitree_merge(BiTree *merge, BiTree *left, BiTree *right, const void *data) {
    bitree_init(merge, left->destroy);
    // Insert data for root node of merged tree
    if (bitree_ins_left(merge, NULL, data) != 0) {
        bitree_destroy(merge);
        return -1;
    }
    bitree_root(merge)->left = bitree_root(left);
    bitree_root(merge)->right = bitree_root(right);
    merge->size = merge->size + bitree_size(left) + bitree_size(right);
    // do not left the original trees access the merged nodes
    left->root = NULL;
    left->size = 0;
    right->root = NULL;
    right->size = 0;

    return 0;
}

void bitree_rem_right(BiTree *biTree, BiTreeNode *node) {
    BiTreeNode **position;
    // do not allow removal from an empty tree;          
    if (bitree_size(biTree) == 0) {
        return;
    }
    // determine where to remove nodes                   
    if (node == NULL) {
        position = &biTree->root;
    } else {
        position = &node->right;
    }
    // remove the node                                   
    if (*position != NULL) {
        bitree_rem_left(biTree, *position);
        bitree_rem_right(biTree, *position);
        if (biTree->destroy != NULL) {
            biTree->destroy((*position)->data);
        }
        free(*position);
        *position = NULL;
        biTree->size--;
    }
    return;
}


