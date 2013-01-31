#ifndef TRAVERSE_H
#define TRAVERSE_H
int preorder(const BiTreeNode *node);
int inorder(const BiTreeNode *node, void (*display_node)(const BiTreeNode *node));
int postorder(const BiTreeNode *node);
#endif
