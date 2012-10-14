# Copyright (c) 2002-2012 René Ladan. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#   notice, this list of conditions and the following disclaimer in the
#   documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
# OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
# SUCH DAMAGE.

"""Generate a random and valid Brainfuck program.

   The requested length is given as a parameter.  Note that due to padding of ]
   and/or . characters, the length might be slightly larger.
"""

from random import randint
from sys import argv

def gen_bf(reqlen):
    """Generate the program.

       @param reqlen the requested program length in bytes
    """

    token = ["-", "+", "<", ">", ".", ",", "[", "]"]
    balance = 0  # number of [ characters - number of ] characters
    code = ""
    prevval = -1
    deadcode = False
    while reqlen:
        value = randint(0, 7)
        if (value == 0 and prevval == 1) or \
           (value == 1 and prevval == 0) or \
           (value == 2 and prevval == 3) or \
           (value == 3 and prevval == 2) or \
           (value == 5 and prevval == 5):
            continue
        if value < 4 or value == 5:
            deadcode = False
        if value == 6:
            if deadcode:
                continue
            balance += 1
        if value == 7:
            if balance == 0 or prevval == 6:
                continue
            balance -= 1
            deadcode = True
        iotail = value != 4 and balance == 0
        code = "".join([code, token[value]])
        reqlen -= 1
        prevval = value
    print len(code) + balance + int(iotail)
    print "".join([code, "]" * balance, "." * int(iotail)])

if __name__ == "__main__":
    gen_bf(int(argv[1]))
