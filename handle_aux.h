#ifndef HANDLE_AUX_H
#define HANDLE_AUX_H
void handle_userdef(int key);
void handle_semicolon(void);
void handle_comma(void);
void handle_paren(int token);
void handle_brace(int token);
void handle_asterisk(void);
void handle_open_bracket(void);
void handle_close_bracket(void);
void handle_misc(void);
#endif
