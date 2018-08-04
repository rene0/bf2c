Changelog
=========

* 1.3.1 2013-06-11
 * Clean up Makefile to not depend on GNU Make
 * Add gen\_bf.c (from gen\_bf.py) to the build

* 1.2.5 2012-02-19
 * Temporarily disable absolute header conversion which crashes in a lot of cases.
 * Code cleanups.

* 1.2.4 2012-01-02
 * Some cleanups and compiler fixes.

* 1.2.3 2004-04-21
 * [BUGFIX] If node is first in row, check for parent and make link from that parent to current node in tree.cc::prepend() This fixes the code for factor.

* 1.2.2 2003-08-21
 * [BUGFIX] Parse tree traversal didn't advance when 2 mulzero tokens were encountered after each other

* 1.2.1 (internal release)

* 1.2 2003-08-18
 * Added support for get/val token optimizations, join get/val nodes with equal offsets
 * Better standard input/output support
 " [BUGFIX] Fix bug related to absolute value nodes

* 1.1 2003-08-15
 * Added absolute-value functionality to put token, show ASCII character if code >= 32
 * Added get token handling in convertAbsoluteHeader()
 * Better command line interface, use getopt()

* 1.0 2003-07-27
 * First public release
