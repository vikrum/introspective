#include <stdio.h>
#include "extern.h"

void
show_state(void) {
	printf("C; i: %s d: %s ft: %s fn: %s S; td: %d ds: %d if: %d fbn: %d P: %d " 
			"B: %d C: %d ncls: %d nfnc: %d *: %d []: %d\n",
			current_identifier,
			current_datatype,
			current_function_t,
			current_function_n,
			typedef_target,
			decleration_state,
			inside_function,
			function_being_declared,
			paren_state,
			brace_state,
			comma_patrol,
			need_structclosure,
			need_functionclosure,
			pointer_to_datatype,
			need_bracketclosure);
	return;
};

void
reset_allstates(void) {
	need_structclosure = need_functionclosure = typedef_target = 
		paren_state = brace_state = comma_patrol = 
		function_being_declared = inside_function = 
		decleration_state = pointer_to_datatype = 
		need_bracketclosure = need_semicolon = 0;

	current_datatype = current_identifier = current_function_n = 
		current_function_t = NULL;

	line_count = 1;
	return;
};
