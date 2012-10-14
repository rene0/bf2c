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
