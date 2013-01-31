#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokens.h"
#include "extern.h"
#include "debug.h"
#include "process.h"
#include "aux.h"

void
handle_userdef(int key) {

	decleration_state = 1;
	current_datatype = userdef[key];	
	return;
};

void
handle_semicolon(void) {
	

	if(need_semicolon == 1)
		need_semicolon = 0;


	if(decleration_state == 1) {
		if(inside_function == 2) {
			proc_currentidentifier();
			proc_currenttype();
		}
		else if (inside_function == 0) {
			if(typedef_target ==1) {
				add_usertype(current_identifier);
				current_identifier = NULL;
			}
			else {
				proc_currentidentifier();
				proc_currenttype();
			}
		}
	}
	else if(decleration_state == 0) {
		if(inside_function == 0) {
			if((paren_state == 0) &&  (brace_state == 0) &&
					(function_being_declared == 1) ) {
#ifdef DEBUG
				printf("DEBUG: %s %s() prototype\n", 
						current_function_t, 
						current_function_n);
#endif
				close_currentfunction();
			}
			else {
			/* this is for the situation when a bracket from an
			 * array decleration has already closed stuff off and
			 * there is residual identifiers/types
			 */
			current_datatype = current_identifier = NULL;
			/* we do not want to reset all states as to 
			 * preserve the scope, if any
			 */
			}
		}
		else {
			if((paren_state == 0) &&  (brace_state == 0) &&
					(function_being_declared == 0) ) {
#ifdef DEBUG
				printf("DEBUG: %s %s() prototype\n", 
						current_function_t, 
						current_function_n);
#endif
				close_currentfunction();
			}
			else {
				/* unreached */
			}
		}
	}
	typedef_target = 0;
	decleration_state = 0;
	comma_patrol = 0;
	pointer_to_datatype = 0;
	return;
};

void
handle_comma(void) {

	if(function_being_declared == 1) {
		decleration_state = 0;
		proc_currentidentifier();
		proc_currenttype();
		comma_patrol = 0;
	}
	else {
		comma_patrol = 1;
		if(decleration_state == 1) {
			if(inside_function == 2 ) {
				proc_currentidentifier();
			}
			else if (inside_function == 0) {
				if(typedef_target ==1) {
					add_usertype(current_identifier);
					return;
				}
				proc_currentidentifier();
			}
		}
	}
	return;
};

	
void
handle_paren(int token) {

	if(token == PAREN_OPEN) {
		paren_state = 1;
		if(decleration_state == 1) {
			decleration_state = 0;
			function_being_declared = 1;
			proc_currentfunction();
		}
	}
	else {
		paren_state = 0;
		if(decleration_state == 1) {
			decleration_state = 0;
			proc_currentidentifier();
			if(function_being_declared == 1) {
				inside_function = 1;
			}
			function_being_declared = 0;
		};
	};
	return;
};

void
handle_brace(int token) {

	if(token == BRACE_OPEN) {
		brace_state++;
		if(inside_function == 1 || function_being_declared == 1) {
			function_being_declared = 0;
			inside_function = 2;
			current_datatype = current_identifier = NULL;
		}
		else if(inside_function == 2) {
			/* unreached */
		}
	}
	else {
		brace_state--;
		if(need_structclosure == 1) {
			need_structclosure = 0;
			proc_currenttype();
		};
		if(need_functionclosure == 1 && brace_state == 0) 
			close_currentfunction();
	};
	return;
}

void
handle_asterisk(void) {

	if(decleration_state == 1)
		pointer_to_datatype++;

	return;
}

void
handle_open_bracket(void) {

	char *buffer;
	
	if(decleration_state == 1) {
		decleration_state = 0;
		buffer = current_datatype;
		if((buffer = (char *)realloc(buffer, 
				strlen(buffer) + 1 + 2 )) == NULL) {
			perror("handle_open_bracket/realloc()");
			exit(-1);
		}
		strcat(buffer, brackets);
		current_datatype = buffer;
		if(inside_function == 2 ) {
			proc_currentidentifier();
		}
		else if (inside_function == 0) {
			proc_currentidentifier();
		}
	}
	need_bracketclosure = 1;
		
	return;
};

void
handle_close_bracket(void) {

	if(need_bracketclosure == 1) {
		need_bracketclosure = 0;
	}
	else {
#ifdef DEBUG
		printf("DEBUG: Bracket closure w/o open\n");
#endif
	}
	return;
}

void
handle_misc(void) {
	if(current_identifier != NULL) {
		proc_currentidentifier();
		need_semicolon = 1;
	}
	return;
}
