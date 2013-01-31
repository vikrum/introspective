#ifndef GLOBAL_H
#define GLOBAL_H

#define DEBUG 0

#include <stdio.h>
#include "bitree.h"

char *current_identifier,
*current_datatype,
*current_function_t,
*current_function_n;

int decleration_state,
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

char** userdef;
int user_count;

char** storage;
int stor_count;

const char space[] = " ";
const char asterisk[] = "*";
const char brackets[] = "[]";

int line_count = 1;

BiTree tree;

extern char* yytext;
extern FILE* yyin;
#endif
