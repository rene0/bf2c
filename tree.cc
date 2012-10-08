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
