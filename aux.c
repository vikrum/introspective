#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokens.h"
#include "bitree.h"
#include "bistree.h"
#include "extern.h"
#include "debug.h"
#include "misc_struct.h"
#include "clobber.h"
#define MEMINCR 1024

int
compare_str(const void *str1, const void *str2) {
	int retval;

	if ((retval = strcmp((const char *)str1, (const char *)str2)) > 0) 
		return(1);
	else if (retval < 0) 
		return(-1);
	else 
		return(0);
};

int
compare_tnode(const void *node1, const void *node2) {
	return( 
  	  compare_str( (void *)((TNode *)node1)->vname,
			(void *)((TNode *)node2)->vname));
};

void
init_globals(void) {

	current_identifier = current_datatype = current_function_t = 
		current_function_n = NULL;

	decleration_state = inside_function =  function_being_declared = 
		typedef_target = paren_state = brace_state = comma_patrol = 
		need_structclosure = need_functionclosure = 
		pointer_to_datatype = need_bracketclosure = need_semicolon = 0;

	user_count = stor_count = 0;

	bistree_init(&tree, compare_tnode, clobber_tnode);
	if( (userdef = (char **)malloc((unsigned)MEMINCR*(sizeof(char *)))) == NULL) {
		perror("init_globals/malloc()");
		exit(-1);
	};
	memset(userdef, 0, MEMINCR*sizeof(char *));

	if( (storage = (char **)malloc((unsigned)MEMINCR*(sizeof(char *)))) == NULL) {
		perror("init_globals/malloc()");
		exit(-1);
	};
	memset(storage, 0, MEMINCR*sizeof(char *));
	return;
};
		
void
add_usertype(char *str) {
#ifdef DEBUG
	printf("DEBUG: Added user type: %s\n", str);
#endif
	if( (user_count % (MEMINCR - 2)) == 0 ) {
		if ( (userdef = (char **)realloc((void *)userdef, (user_count + MEMINCR) * sizeof(char *))) == NULL) {
			perror("add_usertype/realloc()");
			exit(-1);
		}
	}
	userdef[user_count++] = str;
	return;
}

void
close_currentfunction(void) {
	inside_function = 0;
	function_being_declared = 0;
	decleration_state = 0;
	need_functionclosure = 0;
	reset_allstates();
	return;
};
 
int
make_haste(int token, char *str) {

	if(need_bracketclosure == 1) {
		if(token != BRACKET_CLOSE) {
			return(1);
		}
		else
			return(0);
	}
		
	if(need_semicolon == 1) {
		if(token != SEMICOLON) {
			return(1);
		}
		else 
			return(0);
	}

	if(need_structclosure == 1 && brace_state == 1) {
		if(token != BRACE_CLOSE) {
			return(1);
		}
		else 
			return(0);
	}
	
	if(need_functionclosure == 1 && brace_state > 0) {
		if( (token != BRACE_CLOSE) && (token != BRACE_OPEN) ) {
			return(1);
		}
		else 
			return(0);
	}
	return(0);
}
