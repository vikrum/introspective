#ifndef MISC_STRUCT_H
#define MISC_STRUCT_H

#include "list_struct.h"

typedef struct Loc_ {
	char *fname;
	char *ftype;
	char *type;
	int line_no;
} Loc;

typedef struct tnode_ {
	char *vname;
	List *appear;
} TNode;
#endif
