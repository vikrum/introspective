#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "global.h"
#include "bistree.h"
#include "aux.h"
#include "process_aux.h"
#include "report.h"

int
main(int argc, char **argv) {

	++argv, --argc;

	init_globals();

	if(argc <= 0) {
		yyin = stdin;
		proc_file();
	}
	else {
		for( ; argc > 0; ++argv, --argc ) {
			if( (yyin = fopen( argv[0], "r")) == NULL) {
				perror(argv[0]);
				continue;
			}
			proc_file();
			fclose(yyin);
		}
	}
		
	display_report(1);
	display_report(2);
	
	bistree_destroy(&tree);	

	return(0);
};
