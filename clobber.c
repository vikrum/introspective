#include <stdio.h>
#include <stdlib.h>
#include "list_struct.h"
#include "list.h"
#include "misc_struct.h"
#include "clobber.h"

void
clobber_loc(void *tmp_loc) {
	if(tmp_loc != NULL) {
		free(((Loc *)tmp_loc)->fname);
		free(((Loc *)tmp_loc)->ftype);
		free(((Loc *)tmp_loc)->type);
	}
	else {
		printf("null?\n");
	}
};

void
clobber_tnode(void *tmp_tnode) {
	free((List *)(((TNode *)tmp_tnode)->appear));
	free(((TNode *)tmp_tnode)->vname);
	free(tmp_tnode);
};
