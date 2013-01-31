#include <string.h>
#include "extern.h"

int
userdef_lookup(const char* str) {

	int i;

	for(i = 0; i < user_count; i++) {
		if(strcmp(str, userdef[i]) == 0) {
			return(i);
		}
	};
	return(-1);
};

int
reserved_loopup(const char* str) {
        int i = 1;
        static const char *const keywords[] = { NULL,
                "auto", "char", "const", "double", "enum", "extern",
                "float", "int", "long", "register", "short", "signed",
                "static", "struct", "typedef", "union", "unsigned",
                "void", "volatile", "wchar_t", "FILE" };
        const int n = sizeof(keywords) / sizeof(keywords[0]);

        for( ; i < n && keywords[i] != NULL; i++ ) {
                if(strcmp(str, keywords[i]) == 0) {
                        return(i);
                };
        };
        return(i + ( userdef_lookup(str)));
};
