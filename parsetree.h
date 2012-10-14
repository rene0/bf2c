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

#ifndef BF2C_PARSETREE_H
#define BF2C_PARSETREE_H 1

#include <stdio.h>

#include "tree.h"

#define CSUNUSED 0
#define CSPTRABSOLUTE 1
#define CSABSOLUTE 2
#define CSGETFOUND 4

class ParseTree {
public:
	ParseTree(char *infilename, char *outfilename, int size, int range);
	~ParseTree();

	void build(); // build initial parse tree
	void reset();
	void dump();
	void removeTail();
	void cleanTokens();
	void convertMulzero();
	void convertAbsoluteHeader();
protected:
private:
	Token *scan();
	Token *pStat(Tree **base);
	Token *pProg(Tree **base);
	int balance(int plus, int minus, int current);
	int count(int plus);
	void dumpMain(Tree **base, int numTabs);
	void putTabs(int numTabs);
	void packTokens(Tree **base);
	void mulzero(Tree **base);
	bool tryMulzero(Tree **base);
	void putAbsolute(Tree **base);

	Tree *tree;
	char *srcname;
	FILE *src;
	FILE *dst;
	unsigned need__i;
	unsigned need__stdio;
	unsigned need__range;
	int mysize; // array size
	int myrange; // cell range
} ;
#endif
