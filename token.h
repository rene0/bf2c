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
