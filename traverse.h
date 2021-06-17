/*
 * =====================================================================================
 *
 *       Filename:  traverse.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2021年05月06日 23时36分01秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef TRAVERSE_H
#define TRAVERSE_H

#include "bitree.h"
#include "list.h"

/* public interface */
int preorder(const BiTreeNode *node, List *list);

int inorder(const BiTreeNode *node, List *list);

int postorder(const BiTreeNode *node, List *list);

#endif
