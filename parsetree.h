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
