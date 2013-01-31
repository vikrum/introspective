#ifndef AUX_H
#define AUX_H
int compare_str(const void *str1, const void *str2);
int compare_tnode(const void *node1, const void *node2);
void init_globals(void);
void add_usertype(char *str);
void close_currentfunction(void);
int make_haste(int token, char *str);
#endif
