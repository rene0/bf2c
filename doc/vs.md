BF2C Versioning Scheme
======================

The Structure
=============

A version number is built from 3 parts, x, y and z and given as x.y.z. x denotes the major version number, y denotes the minor version number and z denotes the fix number. x starts from 1, y and z start from 0. If z = 0, it isn't included in the version number.

The Counting
============

The major version number is increased when a new concept is added. The minor version number is increased when an existing concept is improved. The fix number increases with every bug- or security fix.

The fix number is reset to 0 when a concept is changed which inherently corrects all fixes. The minor version number reset to 0 when a new concept inherently includes all improvements. This thus means that a x.0 version is quite unlikely, at the time of writing, version 1.3.2, not version 1.3, is in development.
