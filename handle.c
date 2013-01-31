#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "extern.h"
#include "lookup.h"
#include "process.h"
#include "handle.h"
#include "aux.h"

void
handle_reserved(const char *str) {

	int i = strlen(str);
	int id;
	char *buffer;

	id = reserved_loopup(str);

	decleration_state = 1;

	if(id == 15 ) { /* if typedef, keep an eye out */
		typedef_target = 1;
		return;
	};
	
	if(current_datatype == NULL) {
		if((buffer = (char *)malloc((unsigned)i+1)) == NULL) {
			perror("handle_reserved/malloc()");
			exit(-1);
		}
		strcpy(buffer, str);
	}
	else {
		buffer = current_datatype;
		if((buffer = (char *)realloc(buffer, strlen(buffer) + i + 3)) 
				== NULL) {
			perror("handle_reserved/realloc()");
			exit(-1);
		}
		strcat(buffer, space);
		strcat(buffer, str);
	}

	if( (id == 14) || (id == 5) ) { /* 14 == struct; 5 == enum */
		need_structclosure = 1;
	}
	current_datatype = buffer;
};

void
handle_identifier(const char *str) {

	int i = strlen(str);
	int lookup = userdef_lookup(str);
	char *buffer;

	if(lookup != -1) {
		handle_userdef(lookup);
		return;
	}

	if(need_structclosure == 1)  {
		buffer = current_datatype;
		if((buffer = (char *)realloc(buffer, strlen(buffer) + i + 3)) 
				== NULL) {
			perror("handle_reserved/realloc()");
			exit(-1);
		}
		strcat(buffer, space);
		strcat(buffer, str);
		current_datatype = buffer;
		return;
	}

	if( (decleration_state == 0) && (inside_function == 2)) {
		need_functionclosure = 1;
		return;
	};
		

	if((buffer = (char *)malloc((unsigned)i+1)) == NULL) {
		perror("handle_reserved/malloc()");
		exit(-1);
	}
	strcpy(buffer, str);

	current_identifier = buffer;
	return;
}
