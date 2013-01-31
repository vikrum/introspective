#include <stdio.h>
#include "extern.h"
#include "tokens.h"
#include "aux.h"
#include "debug.h"
#include "process.h"
#include "lookup.h"
#include "handle.h"

extern int yylex();

void
proc_file(void) {

	int token;

	reset_allstates();
	do {
		token = yylex();
#ifdef DEBUG
		printf("%d	%s -> ", token, yytext); 
#endif
#ifdef VDEBUG
		show_state();
#endif
		if( make_haste(token, yytext) ) {
#ifdef VVDEBUG
			printf("haste!\n");
#endif
			continue;
		}
		switch(token) {
			case RESERVED:
				handle_reserved(yytext);
				break;
			case NUMBER:
			case STRING:
			case OPERATOR:
				break;
			case IDENTIFIER:
				handle_identifier(yytext);
				break;
			case BRACE_OPEN:
			case BRACE_CLOSE:
				handle_brace(token);
				break;
			case PAREN_OPEN:
			case PAREN_CLOSE:
				handle_paren(token);
				break;
			case SEMICOLON:
				handle_semicolon();
				break;
			case COMMA:
				handle_comma();
				break;
			case NEWLINE:
				line_count++;
				break;
			case ASTERISK:
				handle_asterisk();
				break;
			case BRACKET_OPEN:
				handle_open_bracket();
				break;
			case BRACKET_CLOSE:
				handle_close_bracket();
				break;
			case MISC:
				handle_misc();
				break;
			case OTHER:
			case ERROR:
				break;
			case ENDOFFILE:
				break;
			default:
				fprintf(stderr, "??? %d: %s\n", token, yytext);
				break;
		};
	} while(token > 0 && token != ERROR);
  
	if(token == ERROR) {
		fprintf(stderr, "??? %d: %s\n", token, yytext);
	}
	return;
};
