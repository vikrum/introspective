#ifndef EXTERN_H
#define EXTERN_H

#include <stdio.h>
#include "bitree.h"

extern char *current_identifier,
*current_datatype,
*current_function_t,
*current_function_n;

extern int decleration_state,
inside_function,
function_being_declared,
typedef_target,
paren_state,
brace_state,
comma_patrol,
need_structclosure,
need_functionclosure,
pointer_to_datatype,
need_bracketclosure,
need_semicolon;

extern char** userdef;
extern int user_count;

extern char** storage;
extern int stor_count;

extern const char space[];
extern const char asterisk[];
extern const char brackets[];

extern int line_count;

extern BiTree tree;

extern char* yytext;
extern FILE* yyin;
#endif
