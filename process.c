#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list_struct.h"
#include "list.h"
#include "bitree.h"
#include "bistree.h"
#include "extern.h"
#include "report.h"
#include "misc_struct.h"
#include "clobber.h"
#define MEMINCR 1024

void 
proc_data(int line_no, char *vtype, int ptr_to_type, 
		char *vname, char *ftype, char *fname) {

	Loc *tmp_loc;
	TNode *tmp_tnode;
	List *tmp_list;

	char *buffer;
	int i = 0;

	if((tmp_loc = (Loc *)malloc((unsigned)sizeof(Loc))) == NULL) {
		fprintf(stderr, "save_data/malloc(): tmp_loc");
		exit(-1);
	}
	if((tmp_tnode = (TNode *)malloc((unsigned)sizeof(TNode))) == NULL) {
		fprintf(stderr, "save_data/malloc(): tmp_tnode");
		exit(-1);
	}
	if((tmp_list = (List *)malloc((unsigned)sizeof(List))) == NULL) {
		fprintf(stderr, "save_data/malloc(): tmp_list");
		exit(-1);
	}

	memset(tmp_loc, 0, sizeof(Loc));
	memset(tmp_tnode, 0, sizeof(TNode));
	memset(tmp_list, 0, sizeof(List));

	list_init(tmp_list, clobber_loc);

	tmp_loc->fname = fname;
	tmp_loc->ftype = ftype;
	if(ptr_to_type > 0) {
		if( (buffer = (char *)malloc((unsigned)strlen(vtype) + 
				1 + ptr_to_type + 1 + 1)) == NULL) {
			fprintf(stderr, "save_data/malloc()");
			exit(-1);
		}
		strcat(buffer, vtype);
		for(i = 0; i < ptr_to_type; i++) {
			strcat(buffer, asterisk);
		}
		vtype = buffer;
	}
	tmp_loc->type = vtype;
	tmp_loc->line_no = line_no;

	list_ins_next(tmp_list, NULL, tmp_loc);

	tmp_tnode->vname = vname;
	tmp_tnode->appear = tmp_list;
	
	bistree_insert(&tree, tmp_tnode); 
	return;
}


void
proc_currentidentifier(void) {

	char *buffer;

	if(current_function_n == NULL) {
		if((buffer = (char *)malloc(strlen("global") + 1)) == NULL) {
			perror("handle_open_bracket/malloc()");
			exit(-1);
		}
		strcat(buffer, "global");
		current_function_n = buffer;
	}

	if(current_function_t == NULL) {
		if((buffer = (char *)malloc(strlen("extern") + 1)) == NULL) {
			perror("handle_open_bracket/malloc()");
			exit(-1);
		}
		strcat(buffer, "extern");
		current_function_t = buffer;
	}

	if(current_identifier == NULL) {
#ifdef DEBUG
		printf("DEBUG:  caught %s in %s %s()\n",
				current_datatype, current_function_t, 
				current_function_n);
#endif
		current_datatype = NULL;
	}
	else {
		proc_data(line_count, current_datatype, pointer_to_datatype,
				current_identifier, current_function_t, 
				current_function_n);
#ifdef VDEBUG
		printf("%d %s%s %s in %s %s()\n", line_count, 
				current_datatype, 
				((pointer_to_datatype) ? "*" : ""),
				current_identifier, current_function_t, 
				current_function_n);
#endif
		if( (stor_count % (MEMINCR - 2))  == 0 ) {
	                if ( (userdef = (char **)realloc((void *)userdef, 
			(user_count + MEMINCR) * sizeof(char *))) == NULL) {
				perror("proc_currenttype/realloc()");
				exit(-1);
			}
		}
		storage[stor_count++] = current_identifier;
		current_identifier = NULL;
		pointer_to_datatype = 0;
	}
	return;
};

void
proc_currenttype(void) {
#ifdef DEBUG
	printf("DEBUG: storage: %s\n", current_datatype);
#endif
	if( (stor_count % (MEMINCR - 2))  == 0 ) {
                if ( (userdef = (char **)realloc((void *)userdef, 
		(user_count + MEMINCR) * sizeof(char *))) == NULL) {
			perror("proc_currenttype/realloc()");
			exit(-1);
		}
	}
	storage[stor_count++] = current_datatype;
	current_datatype = NULL;
	return;
};

void
proc_currentfunction(void) {

	current_function_n = current_identifier;
	current_identifier = NULL;

	current_function_t = current_datatype;
	current_datatype = NULL;

	return;
};
