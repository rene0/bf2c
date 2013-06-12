/*
Copyright (c) 2008-2013 René Ladan. All rights reserved.

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

/*
 * Generate a random and valid Brainfuck program.
 *
 * The requested length is given as a parameter.  Note that due to padding of ]
 * and/or . characters, the length might be slightly larger.
*/

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * Generate the program.
 *
 * @param reqlen the requested program length in bytes
 */

/* from http://eternallyconfuzzled.com/arts/jsw_art_rand.aspx */
double
uniform_deviate(int seed)
{
	return seed * (1.0 / (RAND_MAX + 1.0));
}

void
gen_bf(int reqlen)
{
	char token[8] = {'-', '+', '<', '>', '.', ',' ,'[', ']'};
	int balance; /* number of '[' characters - number of ']' characters */
	int value, prevval;
	int deadcode, iotail;
	
	balance = 0;
	prevval = -1;
	deadcode = 0;
	while (reqlen > 0) {
		value = uniform_deviate(rand()) * 8;
		if ((value == 0 && prevval == 1) ||
		   (value == 1 && prevval == 0) ||
		   (value == 2 && prevval == 3) ||
		   (value == 3 && prevval == 2))
			continue;
		if (value < 4 || value == 5)
			deadcode = 0;
		if (value == 6) {
			if (deadcode)
				continue;
			balance++;
		}
		if (value == 7) {
			if (balance == 0 || prevval == 6)
				continue;
			balance--;
			deadcode = 1;
		}
		iotail = (value != 4 && balance == 0);
		printf("%c", token[value]);
		reqlen--;
		prevval = value;
	}
	while (balance-- > 0)
		printf("]");
	if (iotail)
		printf(".");
	printf("\n");
}

/* also from http://eternallyconfuzzled.com/arts/jsw_art_random.aspx */
unsigned
time_seed()
{
	time_t now = time(0);
	unsigned char *p = (unsigned char *)&now;
	unsigned seed = 0;
	size_t i;

	for (i = 0; i < sizeof now; i++)
		seed = seed * (UCHAR_MAX + 2U) + p[i];

	return seed;	
}

int
main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("Usage: %s <length of program>\n", argv[0]);
		return 1;
	}
	srand(time_seed());
	gen_bf(atoi(argv[1]));
}
