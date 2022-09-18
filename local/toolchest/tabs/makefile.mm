.PF "'Copyright (c) 1984, 1985, 1986, 1987''AT&T All Rights Reserved'"
.H 1 "Compiling C Based Forms"
Compiling C programs using the Tab libraries is a fairly straightforward
process.  The sample programs in appendices D, E, and F are a good place
to start.  Notice that all of the programs include the same five header
files.
.ne 7
.CW
#include <stdio.h>
#include <setjmp.h>
#include "vt.h"
#include "windows.h"
#include "fields.h"
.CN
The header files must be included in the order listed above.
.P
The following is a sample makefile that can be used to compile the first
sample program, ``x1.c''.
.ne 20
.CW
#
# FORMS must point to the forms.d directory for the inclusion
#	of the libraries and the header files
#

FORMS=/u1/blewett/forms.d
TAB=${FORMS}/Tab.d/libform.a
WIN=${FORMS}/windows.d/libwindows.a
VT=${FORMS}/vt.d/libvt.a


F_LIBS=${TAB} ${WIN} ${VT}

CFLAGS=-O -I${FORMS}/Tab.d -I${FORMS}/vt.d -I${FORMS}/windows.d

x1:	x1.o ${F_LIBS}
	cc -o x1 x1.o ${F_LIBS} -lcurses

.CN
The library files should be included in the order listed above.
.P
This example assumes that the library and header files are being
maintained privately by the user.  Installing the files in
``/usr/include'' and in ``/usr/lib'' will of course simplify
the makefile.
