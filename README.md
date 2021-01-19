onefile
=======

A collection of one file programs written in C

Installation
------------

Clone the repository:

	$ git clone https://github.com/kiplingLiu/onefile.git

To build the programs, a compiler supporting C99 (e.g. GCC) and a
POSIX-compatible C library (e.g. Glibc) are required. Other dependencies
are listed within the individual source files as needed.

A POSIX-compatible make implementation (e.g. GNU Make) is required to
use the provided makefile. As an example of its usage, to build `bfi`
from `bfi.c` with `clang`:

	$ make CC=clang bfi
