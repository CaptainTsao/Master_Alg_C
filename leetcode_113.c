//
// Created by rcao on 2021/6/18.
//

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

#include "list.h"
#include "bitree.h"

int **ret;
int retSize;
int *retColSize;

int *path;
int pathSize;
/* 113. 路径总和 II */
/* 方法一：深度优先搜索
 * 思路及算法
 * 我们可以采用深度优先搜索的方式，
 * 枚举每一条从根节点到叶子节点的路径。
 * 当我们遍历到叶子节点，且此时路径和恰为目标和时，
 * 我们就找到了一条满足条件的路径。
 * */
void dfs(BiTreeNode *root, int targetSum) {
    if (root == NULL) {
        return;
    }
    path[pathSize++] = *(int *) root->data;
    targetSum -= *(int *) root->data;
    if (root->left == NULL && root->right == NULL && targetSum == 0) {
        int *tmp = (int *) malloc(sizeof(int) * pathSize);
        ret[retSize] = tmp;
        retColSize[retSize++] = pathSize;
        free(tmp);
    }
    dfs(root->left, targetSum);
    dfs(root->right, targetSum);
    pathSize--;
}


int **PathSum_113_bfs(BiTreeNode *root, int targetSum, int *returnSize, int **returnColumnSizes) {
    int **ret = (int *) malloc(sizeof(int *) * 2001);
    int *retColSize = (int *) malloc(sizeof(int) * 2001);
    int *path = (int *) malloc(sizeof(int) * 2001);
    int retSize = 0, pathSize = 0;
    dfs(root, targetSum);
    *returnColumnSizes = retColSize;
    *returnSize = retSize;
    return ret;
}

int main() {
//    PathSum_113_bfs();
    return 0;
}