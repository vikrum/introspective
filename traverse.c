#include <stdio.h>
#include "list_struct.h"
#include "list.h"
#include "bitree.h"
#include "bistree.h"
#include "misc_struct.h"

int
preorder(const BiTreeNode *node) {
	if (!bitree_is_eob(node)) {

fprintf(stdout, "Node=%s (size: %d), %+2d, hidden=%d\n", 
   (char *)((TNode *)((AvlNode *)bitree_data(node))->data)->vname, 
   list_size((List *)((TNode *)((AvlNode *)bitree_data(node))->data)->appear), 
   ((AvlNode *)bitree_data(node))->factor,
   ((AvlNode *)bitree_data(node))->hidden);
	
		if (!bitree_is_eob(bitree_left(node)))
			if(preorder(bitree_left(node)) != 0)
				return(-1);
	
		if (!bitree_is_eob(bitree_right(node)))
			if(preorder(bitree_right(node)) != 0)
				return(-1);
	}
	return(0);
}


int
inorder(const BiTreeNode *node, void (*display_node)(const BiTreeNode *node)){
	if (!bitree_is_eob(node)) {
		if (!bitree_is_eob(bitree_left(node)))
			if(inorder(bitree_left(node), display_node) != 0)
				return(-1);

			display_node(node);

/*
fprintf(stdout, "Node=%s (size: %d), %+2d, hidden=%d\n", 
   (char *)((TNode *)((AvlNode *)bitree_data(node))->data)->vname, 
   list_size((List *)((TNode *)((AvlNode *)bitree_data(node))->data)->appear), 
   ((AvlNode *)bitree_data(node))->factor,
   ((AvlNode *)bitree_data(node))->hidden);
*/
	
		if (!bitree_is_eob(bitree_right(node)))
			if(inorder(bitree_right(node), display_node) != 0)
				return(-1);
	}
	return(0);
}

int
postorder(const BiTreeNode *node) {
	if (!bitree_is_eob(node)) {
		if (!bitree_is_eob(bitree_left(node)))
			if(postorder(bitree_left(node)) != 0)
				return(-1);

		if (!bitree_is_eob(bitree_right(node)))
			if(postorder(bitree_right(node)) != 0)
				return(-1);

fprintf(stdout, "Node=%s (size: %d), %+2d, hidden=%d\n", 
   (char *)((TNode *)((AvlNode *)bitree_data(node))->data)->vname, 
   list_size((List *)((TNode *)((AvlNode *)bitree_data(node))->data)->appear), 
   ((AvlNode *)bitree_data(node))->factor,
   ((AvlNode *)bitree_data(node))->hidden);
	}
	return(0);
}
