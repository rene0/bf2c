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

#include <stdio.h>

#include "tree.h"

Tree::Tree(Token *token) {
	mytoken = token;
	myprev = NULL;
	mynext = NULL;
	myparent = NULL;
	mychild = NULL;
}

Tree::~Tree() {
	delete mytoken; // also deletes Token object itself !
	mytoken = NULL;
	if (myprev != NULL) {
		myprev->mynext = mynext;
	}
	if (mynext != NULL) {
		mynext->myprev = myprev;
	}
	if (myparent != NULL) {
		if (myparent->mychild == this) {
			if (myprev != NULL) {
				myparent->mychild = myprev;
			} else if (mynext != NULL) {
				myparent->mychild = mynext;
			}
		}
	}
	// remove children
	if (mychild != NULL) {
		delList(mychild);
		mychild = NULL;
	}
}

Token *Tree::getToken() {
	return mytoken;
}

void Tree::setToken(Token *token) {
	mytoken = token;
}

bool Tree::hasPrev() {
	return myprev != NULL;
}

bool Tree::hasNext() {
	return mynext != NULL;
}

bool Tree::hasChild() {
	return mychild != NULL;
}

bool Tree::hasParent() {
	return myparent != NULL;
}

Tree *Tree::prev() {
	return myprev;
}

Tree *Tree::next() {
	return mynext;
}

Tree *Tree::child() {
	return mychild;
}

Tree *Tree::parent() {
	return myparent;
}

void Tree::prepend(Token *token) {
	// insert new element before current
	Tree *elem = new Tree(token);

	elem->myprev = myprev;
	elem->mynext = this;
	elem->mychild = NULL;
	elem->myparent = myparent;
	if (myprev != NULL) {
		myprev->mynext = elem;
	} else if (myparent != NULL) {
		myparent->mychild = elem;
	}
	myprev = elem;
}

void Tree::append(Token *token) {
	// insert new element after current
	Tree *elem = new Tree(token);

	elem->myprev = this;
	elem->mynext = mynext;
	elem->mychild = NULL;
	elem->myparent = myparent;
	if (mynext != NULL) {
		mynext->myprev = elem;
	}
	mynext = elem;
}

void Tree::insertChild(Token *token) {
	// insert new child node and link to parent
	Tree *elem = new Tree(token);

	elem->myparent = this;
	mychild = elem;
}

void Tree::delList(Tree *t) {
	// delete a chain of nodes
	while (t->mynext != NULL) {
		t = t->mynext;
	}
	while (t != NULL) {
		Tree *temp = t;
		t = t->myprev;
		delete temp;
		temp = NULL;
	}
}

void Tree::removeChild() {
	mychild = NULL;
}
