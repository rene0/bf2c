Future plans
============

* 1.3.2
 * Re-evaluate \*\_needed, use them as counters instead of flags. This eliminates unused variables in the generated code if multiple put or get tokens occur only in unreachable code.
 * Use a directed acyclic graph for parse tree storage, search for common code generating void functions in the output code
 * More (verbose) information with a -v parameter
 * New tokens main and eof, use main as root of the graph

* 1.4 ?
 * Study for more absolutification (reuse put\_head\_absolute ?)
 * Better optimization for unreferenced code and data. The following cells are referenced:
  * cells used with put> and get nodes
   * cells used in loops
   * cells used in calculations with referenced cells
   * no other cells are referenced
 * Introduction of pointer balances in loops, use it as a generalization of mulzero tokens. For a \"zeroloop\", the pointer balance is 0 and the value balance is plusminus 1. This can possibly be used for the recognition of if and for statements and for live code.

New Concepts
============
* Introduce a language parameter -l for the output language. This means all getCode() methods for all tokens should use a list.
* Introduce an interpreter mode (parameter -I) with debugging and tracing options, using the ncurses interface.
	
