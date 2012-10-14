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

#ifndef BF2C_TOKEN_H
#define BF2C_TOKEN_H 1

typedef enum { ttToken, ttPtr, ttVal, ttPut, ttGet, ttDo, ttOd, ttEof,
	ttMulzero } tokenType;

typedef enum { dtWhile, dtIf, dtFor } doType;

/* generic token */
class Token {
public:
	Token();
	virtual ~Token();

	virtual int getValue();
	virtual int getOffset();
	virtual int getCount();
	virtual bool isAbsoluteValue();
	virtual bool isAbsoluteOffset();
	virtual int getOffsetDestination();
	virtual int getOffsetSource();
	virtual int getMultiplier();
	virtual doType getDoType();
	virtual bool isWrapped();
	virtual bool isAbsoluteOffsetDestination();
	virtual bool isAbsoluteOffsetSource();

	virtual tokenType getType();
	virtual char *getName();
	virtual char *getCode();
	virtual bool interpret(unsigned **array, unsigned *pointer,
		bool running, unsigned range);
	virtual bool isUsable();

	virtual void setValue(int value);
	virtual void setOffset(int offset);
	virtual void setCount(int count);
	virtual void makeAbsoluteValue(bool absoluteValue);
	virtual void makeAbsoluteOffset(bool absoluteOffset);
	virtual void setDoType(doType dotype);
	virtual void setOffsetDestination(int ofsdest);
	virtual void setOffsetSource(int ofssrc);
	virtual void setMultiplier(int mult);
	virtual void setWrapped(bool wrapped);
	virtual void makeAbsoluteOffsetDestination(bool absofsdest);
	virtual void makeAbsoluteOffsetSource(bool absofssrc);
protected:
	virtual void format(char **dest, char *head, int value,
			bool absolutevalue);
	char *myname;
	tokenType mytype;
};

class Ptr : public Token {
/* tokens  : < >
 * relative: p++, p--, p += N, p -= N
 * absolute: p = N
 */
public:
	Ptr();
	bool isUsable();
	int getValue();
	bool isAbsoluteValue();

	char *getCode();
	bool interpret(unsigned **array, unsigned *pointer, bool running, unsigned range);

	void setValue(int value);
	void makeAbsoluteValue(bool absoluteValue);
private:
	int myvalue;
	bool myabsolutevalue;
};

class Val : public Token {
/* tokens  : - + */
/* relative,relative: a[p+M]++, a[p-M]++, a[p+M]--, a[p-M]--, a[p+M] += N, a[p+M] -= N, a[p] += N, a[p] -= N
 * relative,absolute: a[p+M] = N, a[p-M] = N, a[p] = N
 * absolute,relative: a[M]++, a[M]--, a[M] += N, a[M] -= N
 * absolute,absolute: a[M] = N
 */
public:
	Val();
	bool isUsable();

	int getValue();
	int getOffset();
	bool isAbsoluteValue();
	bool isAbsoluteOffset();

	char *getCode();
	bool interpret(unsigned **array, unsigned *pointer, bool running, unsigned range);

	void setValue(int value);
	void setOffset(int offset);
	void makeAbsoluteValue(bool absoluteValue);
	void makeAbsoluteOffset(bool absoluteOffset);
private:
	int myvalue;
	int myoffset;
	bool myabsolutevalue;
	bool myabsoluteoffset;
};

class Put : public Token {
/* . */
public:
	Put();
	bool isUsable();

	int getCount();
	int getOffset();
	int getValue();
	bool isAbsoluteOffset();
	bool isAbsoluteValue();

	char *getCode();
	bool interpret(unsigned **array, unsigned *pointer, bool running, unsigned range);

	void setCount(int count);
	void setOffset(int offset);
	void setValue(int value);
	void makeAbsoluteOffset(bool absoluteoffset);
	void makeAbsoluteValue(bool absolutevalue);
private:
	int mycount;
	int myoffset;
	bool myabsoluteoffset;
	int myvalue;
	bool myabsolutevalue;
};

class Get : public Token {
/* , */
public:
	Get();
	bool isUsable();

	int getCount();
	int getOffset();
	bool isAbsoluteOffset();

	char *getCode();
	bool interpret(unsigned **array, unsigned *pointer, bool running, unsigned range);

	void setCount(int count);
	void setOffset(int offset);
	void makeAbsoluteOffset(bool absoluteoffset);
private:
	int mycount;
	int myoffset;
	bool myabsoluteoffset;
};

class Do : public Token {
/* [ */
public:
	Do();
	bool isUsable();

	doType getDoType();

	char *getCode();
	bool interpret(unsigned **array, unsigned *pointer, bool running, unsigned range);

	void setDoType(doType dotype);
private:
	doType mydotype;
};

class Od : public Token {
/* ] */
public:
	Od();
	bool isUsable();
	char *getCode();
	bool interpret(unsigned **array, unsigned *pointer, bool running, unsigned range);

};

class Eof : public Token {
/* EOF */
public:
	Eof();
	bool isUsable();
	char *getCode();
	bool interpret(unsigned **array, unsigned *pointer, bool running, unsigned range);
};

class Mulzero : public Token {
/* (optimized) */
public:
	Mulzero();
	bool isUsable();

	int getOffsetDestination();
	int getOffsetSource();
	int getMultiplier();
	bool isWrapped();
	bool isAbsoluteOffsetDestination();
	bool isAbsoluteOffsetSource();

	char *getCode();
	bool interpret(unsigned **array, unsigned *pointer, bool running, unsigned range);

	void setOffsetDestination(int ofsdest);
	void setOffsetSource(int ofssrc);
	void setMultiplier(int mult);
	void setWrapped(bool wrapped);
	void makeAbsoluteOffsetDestination(bool absofsdest);
	void makeAbsoluteOffsetSource(bool absofssrc);
private:
	int myofsdest;
	int myofssrc;
	int mymult;
	bool mywrapped;
	bool myabsofsdest;
	bool myabsofssrc;
};
#endif
