#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list_struct.h"
#include "list.h"
#include "bitree.h"
#include "bistree.h"
#include "traverse.h"
#include "extern.h"
#include "misc_struct.h"


void
print_nodechildren(const BiTreeNode *node) {

	printf("%s\t\t\t%s\t\t\t",
		((!bitree_is_eob(bitree_right(node))) ? 
		((char *)((TNode *)((AvlNode *)
		bitree_data(bitree_right(node)))->data)->vname) :
		"NIL"),

		((!bitree_is_eob(bitree_left(node))) ? 
		((char *)((TNode *)((AvlNode *)
		bitree_data(bitree_left(node)))->data)->vname) :
		"NIL")
	);
	return;
};

void
print_formatedlist(const List *list) {

	ListElmt *element;
	Loc *tmp_loc;
	int i = 0;

	element = list_head(list);

	for(; i < list_size(list) ; i++) {
		tmp_loc = list_data(element);
		printf("%s:%s, %s; ", 
				tmp_loc->ftype,
				tmp_loc->fname,
				tmp_loc->type);
		element = list_next(element);
	};
	printf("\n");
	return;
};

void
print_lineno(const List *list) {

	ListElmt *element;
	Loc *tmp_loc;
	int i = 0;

	element = list_head(list);

	for(; i < list_size(list) ; i++) {
		tmp_loc = list_data(element);
		if(i != 0) 
			printf(", ");
		
		printf("%d", tmp_loc->line_no);
		element = list_next(element);
	};
	printf("\n");
	return;
};

void
report1_format(const BiTreeNode *node) {

	printf("%s\t\t",
			(char *)((TNode *)((AvlNode *)
			bitree_data(node))->data)->vname);
	print_nodechildren(node);
	print_lineno((List *)((TNode *)((AvlNode *)
			bitree_data(node))->data)->appear);
	return;
};

void
report2_format(const BiTreeNode *node) {
	printf("%s		%d		",
			(char *)((TNode *)((AvlNode *)
			bitree_data(node))->data)->vname, 
			list_size((List *)((TNode *)((AvlNode *)
			bitree_data(node))->data)->appear)
			);
	print_formatedlist((List *)((TNode *)((AvlNode *)
				bitree_data(node))->data)->appear);
	return;
};

void
report1_header(void) {

	printf("1st Report: Tree structure of user defined variable names.\n"
"\t     (sorted in aph. order.  Using 'NIL' to indicate none.)\n\n"
"Variable_Name\tRight_child_name\tLeft_child_name\t\tLine_no\n"
"-------------\t----------------\t---------------\t\t-------\n");
	return;
}

void
report2_header(void) {

	printf("2nd Report:\n\n"
"		Tot number	Location of Appearance\n"
"Var_Name	declared	(Function_Type:Function_Name, data type)\n"
"--------	----------	----------------------------------------\n");
	return;
};

void
report1_data(void) {
	inorder(bitree_root(&tree), report1_format);
	return;
};

void
report2_data(void) {
	inorder(bitree_root(&tree), report2_format);
	return;
};

void
display_report(short num) {

	if(bitree_is_eob(bitree_root(&tree))) {
		printf("No variables declared.\n");
		return;
	}

	switch(num) {

		case 1:
			report1_header();
			report1_data();
			break;

		case 2:
			report2_header();
			report2_data();
			break;

		default:
			fprintf(stderr, "Invalid report type: %d\n", num);
			exit(-1);
			break;
	};
	return;
};
