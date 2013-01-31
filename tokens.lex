/* tokens.lex */

%option noyywrap

%{
#include "tokens.h"
%}

id	[A-Za-z$_][A-Za-z0-9$_]*
sp	[ \t]
ws	[ \t]+
num	\.?[0-9][.0-9a-fA-FlLuUxX]*
com	"/*"([^*]*("*"+[^/])?)*"*/"
str	\"(\\.|[^\\"])*\"

%%

^#.*\n?			return(NEWLINE); 
"//".*\n?		return(NEWLINE);
{com}			{ ; }
{ws}			{ ; }
{num}			return(NUMBER);
{str}			return(STRING);

"auto"			|
"char"			|
"const"			|
"double"		|
"enum"			|
"extern"		|
"float"			|
"int"			|
"long"			|
"register"		|
"short"			|
"signed"		|
"static"		|
"struct"		|
"typedef"		|
"union"			|
"unsigned"		|
"void"			|
"volatile"		|
"wchar_t" 		return(RESERVED);

{id}			return(IDENTIFIER);	

":"|"="|"."|"&"|"!"|"<"|">"|"^"|"|" |
		"?"	return(MISC);
"{"			return(BRACE_OPEN);
"}"			return(BRACE_CLOSE);
"("			return(PAREN_OPEN);
")"			return(PAREN_CLOSE);
"+"|"-"|"/"|"%"		return(OPERATOR);
";"			return(SEMICOLON);
","			return(COMMA);
"\n"			return(NEWLINE);
"*"			return(ASTERISK);
"["			return(BRACKET_OPEN);
"]"			return(BRACKET_CLOSE);
.			return(OTHER);
%%
