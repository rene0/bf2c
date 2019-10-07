/*
Copyright (c) 2002-2012 René Ladan. All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
SUCH DAMAGE.
*/

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

	printf("bf2c.cc " VERSION " Copyright (c) 2002-" ENDYEAR " Rene Ladan <r.c.ladan@gmail.com>\n\n"
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
