#include "token.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Token::Token() {
	myname = strdup("TOKEN");
	mytype = ttToken;
}

Token::~Token() {
	free(myname);
	myname = NULL;
}

int Token::getValue() {
	return 0;
}

int Token::getOffset() {
	return 0;
}

int Token::getCount() {
	return 0;
}

bool Token::isAbsoluteValue() {
	return false;
}

bool Token::isAbsoluteOffset() {
	return false;
}

int Token::getOffsetDestination() {
	return 0;
}

int Token::getOffsetSource() {
	return 0;
}

int Token::getMultiplier() {
	return 0;
}

doType Token::getDoType() {
	return dtWhile;
}

bool Token::isWrapped() {
	return false;
}

bool Token::isAbsoluteOffsetDestination() {
	return false;
}

bool Token::isAbsoluteOffsetSource() {
	return false;
}

bool Token::isUsable() {
	return false;
}

tokenType Token::getType() {
	return mytype;
}

char *Token::getName() {
	return myname;
}

char *Token::getCode() {
	return strdup("/* generic Token code */"); 
}

bool Token::interpret(unsigned**, unsigned*, bool, unsigned) {
	return false;
}

void Token::setValue(int value) {
}

void Token::setOffset(int offset) {
}

void Token::setCount(int count) {
}

void Token::makeAbsoluteValue(bool absoluteValue) {
}

void Token::makeAbsoluteOffset(bool absoluteOffset) {
}

void Token::setDoType(doType dotype) {
}

void Token::setOffsetDestination(int ofsdest) {
}

void Token::setOffsetSource(int ofssrc) {
}

void Token::setMultiplier(int mult) {
}

void Token::setWrapped(bool wrapped) {
}

void Token::makeAbsoluteOffsetDestination(bool absofssrc) {
}

void Token::makeAbsoluteOffsetSource(bool absofssrc) {
}

void Token::format(char **dest, char *head, int value, bool absolutevalue) {
	if (absolutevalue) {
		asprintf(dest, "%s = %i;", head, value);
	} else {
		if (value == 1) {
			asprintf(dest, "%s++;", head);
		} else if (value == -1) {
			asprintf(dest, "%s--;", head);
		} else if (value > 1) {
			asprintf(dest, "%s += %i;", head, value);
		} else if (value < -1) {
			asprintf(dest, "%s -= %i;" ,head, -value);
		}
	}
}

Ptr::Ptr() {
	myname = strdup("PTR");
	mytype = ttPtr;
	myvalue = 0;
	myabsolutevalue = false;
}

char *Ptr::getCode() {
	char *r;
	format(&r, strdup("p"), myvalue, myabsolutevalue);
	return r;
}

bool Ptr::interpret(unsigned **array, unsigned *pointer, bool, unsigned) {
	if (myabsolutevalue) {
		*pointer = myvalue;
	} else {
		*pointer += myvalue;
	}
	return true;
}

bool Ptr::isUsable() {
	return myabsolutevalue || (myvalue != 0);
}

int Ptr::getValue() {
	return myvalue;
}

bool Ptr::isAbsoluteValue() {
	return myabsolutevalue;
}

void Ptr::setValue(int value) {
	myvalue = value;
}

void Ptr::makeAbsoluteValue(bool absoluteValue) {
	myabsolutevalue = absoluteValue;
}

Val::Val() {
	myname = strdup("VAL");
	mytype = ttVal;
	myvalue = 0;
	myoffset = 0;
	myabsolutevalue = false;
	myabsoluteoffset = false;
}

int Val::getValue() {
	return myvalue;
}

int Val::getOffset() {
	return myoffset;
}

bool Val::isAbsoluteValue() {
	return myabsolutevalue;
}

bool Val::isAbsoluteOffset() {
	return myabsoluteoffset;
}

bool Val::isUsable() {
	return myabsolutevalue || myabsoluteoffset || (myvalue != 0) ||
		(myoffset != 0);
}

char *Val::getCode() {
	char *r, *dest;
	if (myabsoluteoffset) {
		asprintf(&dest, "a[%i]", myoffset);
		format(&r, dest, myvalue, myabsolutevalue);
	} else {
		if (myoffset != 0) {
			asprintf(&dest, "a[p%s%i]", myoffset > 0 ? "+" : "",
				myoffset);
		} else {
			dest = strdup("a[p]");
		}
		format(&r, dest, myvalue, myabsolutevalue);
	}
	return r;
}

bool Val::interpret(unsigned **array, unsigned *pointer, bool, unsigned) {
	if (myabsoluteoffset) {
		if (myabsolutevalue) {
			(*array)[myoffset] = myvalue;
		} else {
			(*array)[myoffset] += myvalue;
		}
	} else {
		if (myabsolutevalue) {
			(*array)[*pointer + myoffset] = myvalue;
		} else {
			(*array)[*pointer + myoffset] += myvalue;
		}
	}
	return true;
}

void Val::setValue(int value) {
	myvalue = value;
}

void Val::setOffset(int offset) {
	myoffset = offset;
}

void Val::makeAbsoluteValue(bool absoluteValue) {
	myabsolutevalue = absoluteValue;
}

void Val::makeAbsoluteOffset(bool absoluteOffset) {
	myabsoluteoffset = absoluteOffset;
}

Put::Put() {
	myname = strdup("PUT");
	mytype = ttPut;
	mycount = 1;
	myoffset = 0;
	myabsoluteoffset = false;
	myvalue = 0;
	myabsolutevalue = false;
}

bool Put::isUsable() {
	return true;
}

int Put::getCount() {
	return mycount;
}

int Put::getOffset() {
	return myoffset;
}

int Put::getValue() {
	return myvalue;
}

bool Put::isAbsoluteOffset() {
	return myabsoluteoffset;
}

bool Put::isAbsoluteValue() {
	return myabsolutevalue;
}

char* Put::getCode() {
	char *r, *r0;
	asprintf(&r0, "putchar(");
	if (!myabsolutevalue) {
		asprintf(&r0, "%sa[", r0);
		if (myabsoluteoffset) {
			asprintf(&r0, "%s%i]);", r0, myoffset);
		} else {
			if (myoffset == 0) {
				asprintf(&r0, "%sp]);", r0);
			} else {
				asprintf(&r0, "p%s%i]);",
					myoffset < 0 ? "" : "+", myoffset);
			}
		}
	} else {
		asprintf(&r0, "%s%i);", r0, myvalue);
		// output ASCII comment
		if (myvalue >= 32) {
			asprintf(&r0, "%s /* %c */", r0, myvalue);
		}
	}
	if (mycount > 1) {
		asprintf(&r, "for (i = 0; i < %i; i++) { %s }",
			mycount, r0);
		return r;
	} else {
		return r0;
	}
}

bool Put::interpret(unsigned **array, unsigned *pointer, bool running, unsigned) {
	for (int i = 0; running && (i < mycount); i++) {
		if (myabsolutevalue) {
			putchar(myvalue);
		} else {
			if (myabsoluteoffset) {
				putchar((*array)[myoffset]);
			} else {
				putchar((*array)[myoffset + *pointer]);
			}
		}
	}
	return true;
}

void Put::setCount(int count) {
	mycount = count;
}

void Put::setOffset(int offset) {
	myoffset = offset;
}

void Put::makeAbsoluteOffset(bool absoluteoffset) {
	myabsoluteoffset = absoluteoffset;
}

void Put::setValue(int value) {
	myvalue = value;
}

void Put::makeAbsoluteValue(bool absolutevalue) {
	myabsolutevalue = absolutevalue;
}

Get::Get() {
	myname = strdup("GET");
	mytype = ttGet;
	mycount = 1;
	myoffset = 0;
	myabsoluteoffset = false;
}

bool Get::isUsable() {
	return true;
}

int Get::getCount() {
	return mycount;
}

int Get::getOffset() {
	return myoffset;
}

bool Get::isAbsoluteOffset() {
	return myabsoluteoffset;
}

char *Get::getCode() {
	char *r, *r0;
	if (myabsoluteoffset) {
		asprintf(&r0, "a[%i", myoffset);
	} else {
		if (myoffset == 0) {
			r0 = strdup("a[p");
		} else {
			asprintf(&r0, "a[p%s%i",
				myoffset < 0 ? "" : "+", myoffset);
		}
	}
	asprintf(&r0, "%s] = getchar();", r0);
	if (mycount > 1) {
		asprintf(&r, "for (i = 0; i < %i; i++) { %s }",
			mycount, r0);
		return r;
	} else {
		return r0;
	}
}

bool Get::interpret(unsigned **array, unsigned *pointer, bool running, unsigned) {
	for (int i = 0; running && (i < mycount); i++) {
		if (myabsoluteoffset) {
			(*array)[myoffset] = getchar();
		} else {
			(*array)[myoffset + *pointer] = getchar();
		}
	}
	return true;
}

void Get::setCount(int count) {
	mycount = count;
}

void Get::setOffset(int offset) {
	myoffset = offset;
}

void Get::makeAbsoluteOffset(bool absoluteoffset) {
	myabsoluteoffset = absoluteoffset;
}

Do::Do() {
	myname = strdup("DO");
	mytype = ttDo;
	mydotype = dtWhile;
}

bool Do::isUsable() {
	return false; // requires special handling anyway
}

doType Do::getDoType() {
	return mydotype;
}

char *Do::getCode() {
	char *r;
	switch (mydotype) {
		case dtWhile:
			asprintf(&r,"while (a[p]) {");
			break;
		case dtIf:
			asprintf(&r,"if (a[p]) {");
			break;
		case dtFor:
			// TODO research this case -- temp code
			asprintf(&r,"for (i = 0; i < 1; i++) {");
			break;
	}
	return r;
}

void Do::setDoType(doType dotype) {
	// TODO research this method in case of dtFor
	mydotype = dotype;
}

bool Do::interpret(unsigned **array, unsigned *pointer, bool, unsigned) {
	return (*array)[*pointer] != 0;
}

Od::Od() {
	myname = strdup("OD");
	mytype = ttOd;
}

bool Od::isUsable() {
	return false; // this token is never used in the parse tree
}

char* Od::getCode() {
	return strdup("}");
}

bool Od::interpret(unsigned **, unsigned *, bool, unsigned) {
	return false;
}

Eof::Eof() {
	myname = strdup("EOF");
	mytype = ttEof;
}

bool Eof::isUsable() {
	return false; // not in the tree
}

char* Eof::getCode() {
	return strdup("/* EOF code */");
}

bool Eof::interpret(unsigned **, unsigned *, bool, unsigned) {
	return false;
}

Mulzero::Mulzero() {
	myname = strdup("MULZERO");
	mytype = ttMulzero;
	myofsdest = 0;
	myofssrc = 0;
	mymult = 0;
	mywrapped = false;
	myabsofsdest = false;
	myabsofssrc = false;
}

bool Mulzero::isUsable() {
	return true; // generated token
}

int Mulzero::getOffsetDestination() {
	return myofsdest;
}

int Mulzero::getOffsetSource() {
	return myofssrc;
}

int Mulzero::getMultiplier() {
	return mymult;
}

bool Mulzero::isWrapped() {
	return mywrapped;
}

bool Mulzero::isAbsoluteOffsetDestination() {
	return myabsofsdest;
}
bool Mulzero::isAbsoluteOffsetSource() {
	return myabsofssrc;
}

char *Mulzero::getCode() {
	char *r, *r1, *r2, *r3o, *r3c, *r3;
	if (myabsofsdest) {
		asprintf(&r1, "a[%i]", myofsdest);
	} else {
		if (myofsdest == 0) {
			r1 = strdup("a[p]");
		} else {
			asprintf(&r1, "a[p%s%i]", myofsdest > 0 ? "+" : "",
				myofsdest);
		}
	}

	if (mymult < 0) {
		r2 = strdup("-=");
	} else {
		r2 = strdup("+=");
	}

	if (mywrapped) {
		asprintf(&r3o, "(RANGE-a[");
		asprintf(&r3c, "])");
	} else {
		asprintf(&r3o, "a[");
		asprintf(&r3c, "]");
	}

	if (myabsofssrc) {
		asprintf(&r3, "%s%i%s", r3o, myofssrc, r3c);
	} else {
		if (myofssrc == 0) {
			asprintf(&r3, "%sp%s", r3o, r3c);
		} else {
			asprintf(&r3, "%sp%s%i%s", r3o,
				myofssrc < 0 ? "" : "+",
				myofssrc, r3c);
		}
	}

	if (abs(mymult) != 1) {
		asprintf(&r, "%s %s %i * %s;", r1, r2, abs(mymult), r3);
	} else {
		asprintf(&r, "%s %s %s;", r1, r2, r3);
	}

	return r;
}

bool Mulzero::interpret(unsigned **array, unsigned *pointer, bool, unsigned range) {
	unsigned dest = myofsdest;
	unsigned src = myofssrc;

	src += myabsofssrc ? 0 : *pointer;
	dest += myabsofsdest ? 0 : *pointer;

	if (mywrapped) {
		(*array)[src] = range - (*array)[src];
	}
	(*array)[dest] += mymult * (*array)[src];

	return true;
}

void Mulzero::setOffsetDestination(int ofsdest) {
	myofsdest = ofsdest;
}

void Mulzero::setOffsetSource(int ofssrc) {
	myofssrc = ofssrc;
}

void Mulzero::setMultiplier(int mult) {
	mymult = mult;
}

void Mulzero::setWrapped(bool wrapped) {
	mywrapped = wrapped;
}

void Mulzero::makeAbsoluteOffsetDestination(bool absofsdest) {
	myabsofsdest = absofsdest;
}

void Mulzero::makeAbsoluteOffsetSource(bool absofssrc) {
	myabsofssrc = absofssrc;
}
