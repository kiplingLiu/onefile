onefile
=======

A collection of one file programs written in C


Installation
------------

Clone the repository:

	$ git clone https://github.com/kiplingLiu/onefile.git

The sources in the repository can be compiled with any C compiler
supporting C99. A POSIX-compatible C library is also required to compile
some of the sources. Other library dependencies are listed within the
individual sources as needed.

For example, to compile `bfi.c` with `gcc`, linking against `glibc`:

	$ gcc -std=c99 -D_GNU_SOURCE bfi.c -o bfi


Usage
-----

Most of the programs will work without arguments, but programs that
expect arguments will output a usage message when run without them.
