//
// Created by CaoRui on 2021/6/8.
//
#include <stdio.h>
#include <stdlib.h>

#include "bitree.h"
#include "traverse.h"

static void print_preOrder(const BiTreeNode *node) {
    if (!bitree_is_eob(node)) {
        fprintf(stdout, "Node = %d\n", *(int *) bitree_data(node));

        if (!bitree_is_eob(bitree_left(node))) {
            print_preOrder(bitree_left(node));
        }
        if (!bitree_is_eob(bitree_right(node))) {
            print_preOrder(bitree_right(node));
        }
    }
}

static void print_inOrder(const BiTreeNode *node) {
    if (!bitree_is_eob(node)) {
        if (!bitree_is_eob(bitree_left(node))) {
            print_inOrder(bitree_left(node));
        }

        fprintf(stdout, "Node = %d\n", *(int *) bitree_data(node));

        if (!bitree_is_eob(bitree_right(node))) {
            print_inOrder(bitree_right(node));
        }
    }
}

static void print_postOrder(const BiTreeNode *node) {
    if (!bitree_is_eob(node)) {
        if (!bitree_is_eob(bitree_left(node))) {
            print_postOrder(bitree_left(node));
        }

        fprintf(stdout, "Node = %d\n", *(int *) bitree_data(node));

        if (!bitree_is_eob(bitree_right(node))) {
            print_postOrder(bitree_right(node));
        }
    }
}

static int insert_int(BiTree *tree, int i) {
    BiTreeNode *node, *prev;
    int direction, *data;

    node = tree->root;
    direction = 0;

    while (!bitree_is_eob(node)) {
        prev = node;
        if (i == *(int *) bitree_data(node)) {
            return -1;
        } else if (i < *(int *) bitree_data(node)) {
            node = bitree_left(node);
            direction = 1;
        } else {
            node = bitree_right(node);
            direction = 2;
        }
    }

    if ((data = (int *)malloc(sizeof(int))) == NULL)
        return -1;

    *data = i;

    if (direction == 0)
        return bitree_ins_left(tree, NULL, data);

    if (direction == 1)
        return bitree_ins_left(tree, prev, data);

    if (direction == 2)
        return bitree_ins_right(tree, prev, data);
    return -1;
}