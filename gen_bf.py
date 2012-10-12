"""Generate a random and valid Brainfuck program.

   The requested length is given as a parameter.  Note that due to padding of ]
   and/or . characters, the length might be slightly larger.

   Licensed under the 2-claused BSD-license by Rene Ladan <r.c.ladan@gmail.com>
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
