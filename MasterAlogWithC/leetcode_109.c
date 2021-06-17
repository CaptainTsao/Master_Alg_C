//
// Created by rcao on 2021/6/14.
//
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

#include "uthash.h"
#include "list.h"
#include "bitree.h"

void print_list(const List *list) {
    ListElem *element;
    int *data, i;

    fprintf(stdout, "List size is %d\n", list_size(list));

    i = 0;
    element = list_head(list);

    while (1) {
        data = (int *) list_data(element);
        fprintf(stdout, "list[%d]=%d\n", i, *data);

        i++;

        if (list_is_tail(element))
            break;
        else
            element = list_next(element);
    }
}

static void print_inorder(const BiTreeNode *node) {
    if (!bitree_is_eob(node)) {
        if (!bitree_is_eob(bitree_left(node))) {
            print_inorder(bitree_left(node));
        }

        fprintf(stdout, "Node=%d\n", *(int *) bitree_data(node));

        if (!bitree_is_eob(bitree_right(node))) {
            print_inorder(bitree_right(node));
        }
    }
}

int get_length_109_2(ListElem *head) {
    int ret = 0;
    while (head != NULL) {
        ++ret;
        head = head->next;
    }
    return ret;
}

BiTreeNode *build_tree_109_2(ListElem **head, int left, int right) {
    if (left > right) {
        return NULL;
    }
    int mid = (left + right + 1) / 2;
    BiTreeNode *root = (BiTreeNode *) malloc(sizeof(BiTreeNode));
    root->left = build_tree_109_2(head, left, mid - 1);
    root->data = (*head)->data;
    (*head) = (*head)->next;
    root->right = build_tree_109_2(head, mid + 1, right);
    return root;
}

BiTreeNode *sorted_list_to_BST_109_2(List *list) {
    int len = get_length_109_2(list->head);
    BiTreeNode *res = build_tree_109_2(&list->head, 0, len - 1);
    return res;
}

/* 107. 二叉树的层序遍历 II
 * 树的层次遍历可以使用广度优先搜索实现。从根节点开始
 * 搜索，每次遍历同一层的全部节点，使用一个列表存储该
 * 层的节点值。
 *
 * 如果要求从上到下输出每一层的节点值，做法是很直观的，
 * 在遍历完一层节点之后，将存储该层节点值的列表添加到
 * 结果列表的尾部。这道题要求从下到上输出每一层的节点
 * 值，只要对上述操作稍作修改即可：在遍历完一层节点之
 * 后，将存储该层节点值的列表添加到结果列表的头部。
 *
 * 为了降低在结果列表的头部添加一层节点值的列表的时间
 * 复杂度，结果列表可以使用链表的结构，在链表头部添加
 * 一层节点值的列表的时间复杂度是 O(1)。
 * */
int **level_order_bottom_107(BiTreeNode *root, int *returnSize, int **returnColumnSize) {
    int **levelOrder = malloc(sizeof(int *) * 2001);
    *returnColumnSize = malloc(sizeof(int *) * 2001);
    *returnSize = 0;
    if (!root) {
        return levelOrder;
    }
    BiTreeNode **queue = malloc(sizeof(BiTreeNode *) * 2001);
    int left = 0, right = 0;
    queue[right++] = root;
    while (left < right) {
        int len = right - left;
        int *level = malloc(sizeof(int) * len);
        (*returnColumnSize)[*returnSize] = len;
        for (int i = 0; i < len; ++i) {
            BiTreeNode *node = queue[left++];
            //*((int*) node->data)
            // first convert type of `node->data`from `void *` into `int *`,the reference the value of `node->data`
            level[i] = *(int *) node->data;
            if (node->left != NULL) {
                queue[right++] = node->left;
            }
            if (node->right != NULL) {
                queue[right++] = node->right;
            }
        }
        levelOrder[(*returnSize)++] = level;
    }
    for (int i = 0; 2 * i < *returnSize; ++i) {
        int *tmp1 = levelOrder[i];
        levelOrder[i] = levelOrder[(*returnSize) - i - 1];
        levelOrder[(*returnSize) - i - 1] = tmp1;
        int tmp2 = (*returnColumnSize)[i];
        (*returnColumnSize)[i] = (*returnColumnSize)[(*returnSize) - i - 1];
        (*returnColumnSize)[(*returnSize) - i - 1] = tmp2;
    }
    for (int i = 0; i < *returnSize; ++i) {
        printf("[");
        for (int j = 0; j < (*returnColumnSize)[i]; ++j) {
            printf("%d, ", levelOrder[i][j]);
        }
        printf("],\n");
    }
    return levelOrder;
}

/*实现了循环队列。父子队轮替，不用反转*/
typedef struct Queue_ {
    int front;
    int rear;
    int len;
    BiTreeNode *elems[];
} Queue;

Queue *create_queue(int len) {
    Queue *que = (Queue *) malloc(sizeof(Queue) + len * sizeof(BiTreeNode));
    que->len = len;
    que->front = 0;
    que->rear = 0;
    return que;
}

void en_queue(Queue *queue, BiTreeNode *node) {
    if (node == NULL)
        return;
    if ((queue->rear + 1) % (queue->len) == queue->front)
        return;
    queue->elems[queue->rear] = node;
    queue->rear = (queue->rear + 1) % (queue->len);
}

BiTreeNode *out_queue(Queue *queue) {
    if (queue->rear == queue->front)
        return NULL;
    BiTreeNode *node = queue->elems[queue->front];
    queue->front = (queue->front + 1) % (queue->len);
    return node;
}

int max_depth(BiTreeNode *root) {
    if (root == NULL)
        return 0;
    int left = max_depth(root->left), right = max_depth(root->right);
    return 1 + (left >= right ? left : right);
}

int **level_order_bottom_107_2(BiTreeNode *root, int *returnSize, int **returnColumnSize) {
    /* calculate max depth of binary tree */
    *returnSize = max_depth(root);
    /* initialize the columns number of result by max depth */
    int **arrays = (int **) malloc(*returnSize * sizeof(int *));
    if (root == NULL) {
        return arrays;
    }
    /**/
    *returnColumnSize = (int *) malloc(sizeof(int) * (*returnSize));
    /**/
    const int queue_max_len = (1 << (*returnSize - 1) % (CHAR_BIT * sizeof(int))) + 1;
    /* create parent queue and child queue, and add root into parent queue */
    Queue *parent_queue = create_queue(queue_max_len), *child_queue = create_queue(queue_max_len);
    en_queue(parent_queue, root);
    /* */
    for (int level = *returnSize - 1, i = 1; level > -1; --level) {
        (*returnColumnSize)[level] = i;
        arrays[level] = (int *) malloc(i * sizeof(int));
        /* put parent into result, and */
        for (i = 0; parent_queue->rear != parent_queue->front; ++i) {
            BiTreeNode *node = out_queue(parent_queue);
            arrays[level] = node->data;
            if (node->left) {
                en_queue(child_queue, node->left);
            }
            if (node->right) {
                en_queue(child_queue, node->right);
            }
        }
        for (i = 0; child_queue->rear != child_queue->front; ++i) {
            en_queue(parent_queue, out_queue(child_queue));
        }
    }
    return arrays;
}

/* Leetcode 94 二叉树的中序遍历 */
int *inorder_traversal_2(BiTreeNode *root, int *return_size) {
    *return_size = 0;
    int *res = (int *) malloc(sizeof(int) * 501);
    BiTreeNode **stack = (BiTreeNode **) malloc(sizeof(BiTreeNode *) * 501);
    int top = 0;
    while (root != NULL || top > 0) {
        while (root != NULL) {
            stack[top++] = root;
            root = root->left;
        }
        root = stack[--top];
        res[(*return_size)++] = *(int *) bitree_data(root);
        root = root->right;
    }
    return res;
}

/* 方法3: Morris中序遍历
 * 具体步骤如下：
 * 1. 如果x无左孩子，先将x的值加入答案组，再访问x的右孩子，即x=x->right
 * 2. 如果x有左孩子，则找到x左子树上最右的节点（即左子树中序遍历的最后一个节点，
 * x在中序遍历中的前驱节点），我们记为 predecessor。根据 predecessor的右孩子是否为空，进行如下操作。
 *  - 如果predecessor的右孩子为空，则将其右孩子指向x，然后访问x的左孩子，即x=x->left
 *  - 如果predecessor的右孩子不为空，则此时其右孩子指向x，说明我们已经遍历完x的左子树，
 *      我们将predecessor的右孩子置空，将x的值加入答案数组，然后访问 的右孩子，x=x->right
 * 3.重复上述操作，直至访问完整棵树。
 * 时间复杂度：O(n)，其中n为二叉搜索树的节点个数。Morris遍历中每个节点会被访问两次，因此总时间复杂度为O(2n)=O(n)
 * 空间复杂度：O(1)
 * */
int *inorder_traverse_morris(BiTreeNode *root, int *return_size) {
    int *res = (int *) malloc(501 * sizeof(int));
    *return_size = 0;
    BiTreeNode *predecessor = NULL;

    while (root != NULL) {
        if (root->left != NULL) {
            /* predecessor结点就是当前root结点向左走一步，然后一直向右走至无法走为止 */
            predecessor = root->left;
            while (predecessor->right != NULL && predecessor->right != root) {
                predecessor = predecessor->right;
            }
            /*让predecessor的右指针指向root，继续遍历左子树*/
            if (predecessor->right == NULL) {
                predecessor->right = root;
                root = root->left;
            } else {    /*说明左子树已经访问完，我们需要断开连接*/
                res[(*return_size)++] = *(int *) bitree_data(root);
                predecessor->right = NULL;
                root = root->right;
            }
        } else {
            res[(*return_size)++] = *(int *) bitree_data(root);
            root = root->right;
        }
    }
    return res;
}


/* 106. 从中序与后序遍历序列构造二叉树 */
/*
 * 方法一：递归
 * 思路
 * 首先解决这道题我们需要明确给定一棵二叉树，我们是如何对其进行中序遍历与后序遍历的：
 * 中序遍历的顺序是每次遍历左孩子，再遍历根节点，最后遍历右孩子。
 * 后序遍历的顺序是每次遍历左孩子，再遍历右孩子，最后遍历根节点。
 * 复杂度分析
 *  - 时间复杂度:$O(n)$，其中$n$是树中的节点个数。
 *  - 空间复杂度:$O(n)$。我们需要使用$O(n)$的空间存储哈希表，以及$O(h)$(其中$h$是树的高度)的空间表示递归时栈空间。这里$h<n$,所以总空间复杂度为$O(n)$。
*/
int post_idx;

typedef struct {
    int key;
    int val;
    UT_hash_handle hh;
} hashTable;

hashTable *idx_map;

void insert_hash_table_106(int x, int y) {
    hashTable *rec = (hashTable *) malloc(sizeof(hashTable));
    rec->key = x;
    rec->val = y;
    HASH_ADD_INT(idx_map, key, rec);
}

int query_hash_table(int x) {
    hashTable *rec;
    HASH_FIND_INT(idx_map, &x, rec);
    return rec->val;
}

BiTreeNode *helper(int in_left, int in_right, int *inOrder, int *postOrder) {
    /* 如果这里没有结点构造二叉树，就结束了 */
    if (in_left > in_right) {
        return NULL;
    }

    /* 选择post_idx位置的元素作为当前子树根结点 */
    int root_val = postOrder[post_idx];
    BiTreeNode *root = (BiTreeNode *) malloc(sizeof(BiTreeNode));
    *(int *) root->data = root_val;
    // 根据 root 所在位置分成左右两棵子树
    int index = query_hash_table(root_val);

    // 下标减一
    post_idx--;
    // 构造右子树
    root->right = helper(index + 1, in_right, inOrder, postOrder);
    // 构造左子树
    root->left = helper(in_left, index - 1, inOrder, postOrder);
    return root;
}

BiTreeNode *build_tree_106(int *inOrder, int inOrderSize, int *postOrder, int postOrderSize) {
    /* 从后序遍历的最后一个元素开始 */
    post_idx = postOrderSize - 1;
    /* 建立(元素，下标)键值对的哈希表 */
    idx_map = NULL;
    int idx = 0;
    for (int i = 0; i < inOrderSize; ++i) {
        insert_hash_table_106(inOrder[i], idx++);
    }
    return helper(0, inOrderSize - 1, inOrder, postOrder);
}

BiTreeNode *create_tree_node_106(int val);

/* 方法二：迭代
 * 思路
 * 迭代法是一种非常巧妙的实现方法。迭代法的实现基于以下两点发现。
 * 如果将中序遍历反序，则得到反向的中序遍历，即每次遍历右孩子，再遍历根节点，最后遍历左孩子。
 * 如果将后序遍历反序，则得到反向的前序遍历，即每次遍历根节点，再遍历右孩子，最后遍历左孩子。
 * 「反向」的意思是交换遍历左孩子和右孩子的顺序，即反向的遍历中，右孩子在左孩子之前被遍历。
 * 时间复杂度：$O(n)$，其中$n$是树中的节点个数。
 * 空间复杂度：$O(n)$，我们需要使用$O(h)$(其中h是树的高度)的空间存储栈。这里$h<n$，所以(在最坏情况下)总空间复杂度为$O(n)$。
 * */
BiTreeNode *build_tree(int *inOrder, int inOrderSize, int *postOrder, int postOrderSize) {
    if (postOrderSize == 0) {
        return NULL;
    }
    BiTreeNode *root = create_tree_node_106(postOrder[postOrderSize - 1]);
    BiTreeNode **s = (BiTreeNode **) malloc(sizeof(BiTreeNode *) * 10001);
    int top = 0;
    s[top++] = root;
    int inOrderIndex = inOrderSize - 1;
    for (int i = postOrderSize - 2; i >= 0; i--) {
        int postOrderVal = inOrderSize - 1;
        BiTreeNode *node = s[top - 1];
        if (*(int *) node->data != inOrder[inOrderIndex]) {
            node->right = create_tree_node_106(postOrderVal);
            s[top++] = node->right;
        } else {
            while (top > 0 && *(int *) s[top - 1]->data == inOrder[inOrderIndex]) {
                node = s[--top];
                inOrderIndex--;
            }
            node->left = create_tree_node_106(postOrderVal);
            s[top++] = node->left;
        }
    }
    return root;
}

BiTreeNode *create_tree_node_106(int val) {
    BiTreeNode *ret = (BiTreeNode *) malloc(sizeof(BiTreeNode));
    *(int *)(ret->data) = val;
    ret->left = ret->right = NULL;
    return ret;
}

int main() {
    const int arrSize = 5;
    int arr[arrSize] = {-10, -3, 0, 5, 9};

    List list;
    ListElem *element;
    int *data, i;

    list_init(&list, free);

    element = list_head(&list);

    for (i = 0; i < arrSize; i++) {
        if ((data = (int *) malloc(sizeof(int))) == NULL) {
            return 1;
        }
        *data = arr[i];

        if (list_ins_next(&list, list.tail, data) != 0)
            return 1;
    }

    print_list(&list);

    BiTreeNode *res = sorted_list_to_BST_109_2(&list);

    print_inorder(res);

//    int returnSize[10] = {};
    int *returnSize = (int *) malloc(sizeof(int) * 10);
    int **returnColumnSize = (int **) malloc(sizeof(int *) * 10);
//    int **res_107 = level_order_bottom_107(res, returnSize, returnColumnSize);
//    int **res_107_2 = level_order_bottom_107_2(res, returnSize, returnColumnSize);
    memset(returnSize, 0, 10);
    int *res_94_morris = inorder_traverse_morris(res, returnSize);
//    int *res_94_2 = inorder_traversal_2(res, returnSize);
    for (int j = 0; j < *returnSize; ++j) {
        printf("%d, ", res_94_morris[j]);
    }
    /*106*/
    int inorder[5] = {9, 3, 15, 20, 7};
    int postOrder[5] = {9, 15, 7, 20, 3};
    build_tree_106(inorder, 5, postOrder, 5);

    return 0;
}