//
// Created by CaoRui on 2021/6/7.
//
#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "bitree.h"

ListElem *GetMedian(ListElem *left, ListElem *right) {
    ListElem *fast = left;
    ListElem *slow = left;
    while (fast != right && fast->next != right) {
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow;
}

BiTreeNode *BuildTree(ListElem *left, ListElem *right) {
    if (left == right) {
        return NULL;
    }

    ListElem *mid = GetMedian(left, right);
    BiTreeNode *root = (BiTreeNode *) malloc(sizeof(BiTreeNode));
    root->data = mid->data;
    root->left = root->right = NULL;
    root->left = BuildTree(left, mid);
    root->right = BuildTree(mid->next, right);
    return root;
}

BiTreeNode *SortedListToBST_LeetCode109(List *list) {
    return BuildTree(list->head, NULL);
}
