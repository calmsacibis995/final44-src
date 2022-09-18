h01120
s 00002/00002/00049
d D 8.1 93/06/06 15:35:45 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00005/00045
d D 5.3 91/04/16 15:36:56 bostic 5 4
c new copyright; att/bsd/shared
e
s 00001/00001/00049
d D 5.2 91/03/06 00:40:33 donn 4 3
c Fix mktemp() call.  Don't know why I bother...
e
s 00008/00002/00042
d D 5.1 85/06/07 19:45:13 mckusick 3 2
c Add copyright
e
s 00020/00016/00024
d D 1.2 82/03/08 18:52:40 linton 2 1
c added a call to "initstart" so that process information 
c is re-initialized
e
s 00040/00000/00000
d D 1.1 82/01/18 19:20:07 linton 1 0
c date and time created 82/01/18 19:20:07 by linton
e
u
U
t
T
I 1
D 3
/* Copyright (c) 1982 Regents of the University of California */
E 3
I 3
D 5
/*
 * Copyright (c) 1982 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 5
I 5
/*-
D 6
 * Copyright (c) 1982 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1982, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.redist.c%
E 5
 */
E 3

D 3
static char sccsid[] = "%Z%%M% %I% %G%";
E 3
I 3
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 5
#endif not lint
E 5
I 5
#endif /* not lint */
E 5
E 3

/*
 * Remake the object file from the source.
 */

#include "defs.h"
#include "command.h"
#include "object.h"

/*
 * Invoke "pi" on the dotpfile, then reread the symbol table information.
 *
 * We have to save tracing info before, and read it in after, because
 * it might contain symbol table pointers.
I 2
 *
 * We also have to restart the process so that px dependent information
 * is recomputed.
E 2
 */

remake()
{
D 2
	char *tmpfile;
E 2
I 2
    char *tmpfile;
E 2

D 2
	if (call("pi", stdin, stdout, dotpfile, NIL) == 0) {
		if (strcmp(objname, "obj") != 0) {
			call("mv", stdin, stdout, "obj", objname, NIL);
		}
		tmpfile = mktemp("/tmp/pdxXXXX");
		setout(tmpfile);
		status();
		unsetout();
		bpfree();
		objfree();
		readobj(objname);
		setinput(tmpfile);
		unlink(tmpfile);
	} else {
		puts("pi unsuccessful");
E 2
I 2
    if (call("pi", stdin, stdout, dotpfile, NIL) == 0) {
	if (strcmp(objname, "obj") != 0) {
	    call("mv", stdin, stdout, "obj", objname, NIL);
E 2
	}
I 2
D 4
	tmpfile = mktemp("/tmp/pdxXXXX");
E 4
I 4
	tmpfile = mktemp(strdup("/tmp/pdxXXXX"));
E 4
	setout(tmpfile);
	status();
	unsetout();
	bpfree();
	objfree();
	initstart();
	readobj(objname);
	setinput(tmpfile);
	unlink(tmpfile);
    } else {
	puts("pi unsuccessful");
    }
E 2
}
E 1
