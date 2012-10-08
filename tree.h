#ifndef BF2C_TREE_H
#define BF2C_TREE_H 1

#include "token.h"

class Tree {
public:
	Tree(Token *token);
	~Tree();

	Token *getToken();
	Tree *prev();
	Tree *next();
	Tree *child();
	Tree *parent();

	bool hasPrev();
	bool hasNext();
	bool hasChild();
	bool hasParent(); /* false for upper row */

	void setToken(Token *token);
	void prepend(Token *token);
	void append(Token *token);
	void insertChild(Token *token);
	void delList(Tree *t);
	void removeChild();
private:
	Token *mytoken;
	Tree *myprev;
	Tree *mynext;
	Tree *myparent;
	Tree *mychild;

} ;
#endif
