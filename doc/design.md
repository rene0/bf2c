The Language
============

BrainFuck is a minimalistic but Turing complete programming language devised by Urban Mueller. It is oriented around a tape, a read/write head, an input device and an output device. There are 8 instructions available:

Character	Name	Action

\+ -		val	increase/decrease the value of the tape cell pointed to by the head

\> <		ptr	move the head 1 position to the right respectively left

\[		do	loop while the contents of the tape cell is nonzero

]		od	close a loop

,		get	read a value from the input device and write the ASCII code of that value to the current tape cell

.		put	output the value from the current tape cell as an ASCII character to the output device

Any other character represents a comment.

The de facto default values for the environment are:
* cell: 8 bits wide
* tape: 10000, 30000 (original value) or 65536 cells wide

The head position and cell values are mostly wrapped. Initially, the head points to cell 0 (the leftmost one) and all cells contain the value 0. So, both [-] and [+] set the current cell value to 0 and [-] outputs a NUL character.

The Program
===========

The program uses "a" as name for the tape and "p" as the value of the head's position.

The Terminology
===============

* Mulzero: A loop dedicated to multiplying values and clearing the current cell after wards (hence its name). [-] and \[+] are the most obvious ones, they only zero out the current cell. \[>+++<-] equals a[p+1] += 3 \* a[p] ; a[p] = 0. Multiple multiplications are also possible. Note that the current cell value may only be increased or decreased by 1, since other values may cause infinite loops. Also, only ptr and val tokens are allowed within the loop.
* Non-i/o tail: All statements of the program after the last loop and after the last get and put token.

Absolute header: Because of the initial state of the program, all output code before the first loop can be made absolute. This means that all ptr tokens can be removed after recording the head position in the other statements and all val and put can be made absolute. Also, values are calculated on the fly and only the resulting value is written to the final parse tree. This includes values derived from mulzero nodes. Positions with get statement are necessarily made relative, but are made absolute again after a val token with an absolute value.

---

The Structure
=============

For each token, a separate class has been defined:
* token (a generic class, ancestor of all token classes)
* eof (end of file)
* mulzero (synthesized by the optimizer)
* the 8 tokens listed above

Each token class has methods for generating the output code, interpreting itself, setting and retrieving its various values and states and testing if it is usable in the parse tree (i.e. if it isn't redundant).

The parse tree is cleaned in the following way:
* neighbouring tokens of the same type are unified
* (resulting) redundant tokens are removed
* loops right after a loop and before a get, val or ptr token are removed since they are never executed
* the non-I/O tail is removed

The parse tree is optimized as follows:
* mulzero nodes are detected and generated
* the header is made absolute
* val and get statements are unified in a non-redundant way

Comments are never added to the parse tree.

Tokens are scanned in a cumulative way and a count is kept for the tokens, except for do and od. This results in a much smaller initial parse tree and reduces the work in the cleaning phases.
