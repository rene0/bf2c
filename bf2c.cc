#include "parsetree.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

#define VERSION "1.2.5"
#define ENDYEAR "2012"

// defined in sysexits.h :
#define EX_OK 0
#define EX_USAGE 64

void showhelp() {
	printf("parameters: [-i inputfile] (stdin)\n"
		"            [-o outputfile] (stdout)\n"
		"            [-r range] unary cell size, unsigned (256)\n"
		"            [-s size] array size in cells, unsigned (65536)\n"
		"            [-h] this help\n"
	);
}

int main(int argc, char *argv[]) {
	ParseTree *pt;
	char *infname, *outfname;
	int size, range, opt;
	char *invchar;

	size = 63356;
	range = 256;

	pt = NULL;
	infname = outfname = invchar = NULL;

	printf("bf2c.cc "VERSION" Copyright (c) 2002-"ENDYEAR" Rene Ladan <r.c.ladan@gmail.com>\n\n"
		"Optimizing BrainFuck to C compiler.\n\n");

	while ((opt = getopt(argc,argv,"i:o:hs:r:")) != -1) {
		switch (opt) {
			case 'h' :
				showhelp();
				return EX_OK;
			case 'i' :
				asprintf(&infname, "%s", optarg);
				break;
			case 'o' :
				asprintf(&outfname, "%s", optarg);
				break;
			case 's' :
				size = strtol(optarg, &invchar, 10);
				if (invchar != NULL) {
					printf("Invalid digit: %s\n", invchar);
					return 1;
				}
				break;
			case 'r' :
				range = strtol(optarg, &invchar, 10);
				if (invchar != NULL) {
					printf("Invalid digit: %s\n", invchar);
					return 1;
				}
				break;
			default:
				printf("Use -h for help.\n");
				return EX_USAGE;
		}
	}

	pt = new ParseTree(infname, outfname, size, range);
	pt->build();
	pt->reset();
	pt->cleanTokens();
	pt->reset();
	pt->convertMulzero();
	pt->reset();
	pt->cleanTokens();
	pt->reset();
	pt->removeTail();
	pt->reset();
	/* pt->convertAbsoluteHeader(); XXX broken */
	pt->reset();
	pt->cleanTokens();
	pt->cleanTokens(); // second time for VAL/GET cleaning
	pt->reset();
	pt->dump();
	delete pt;	// force cleanup
	pt = NULL;

	free(infname);
	infname = NULL;
	free(outfname);
	outfname = NULL;
	return EX_OK;
}
