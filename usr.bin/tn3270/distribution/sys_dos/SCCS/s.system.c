h07935
s 00002/00002/00112
d D 8.1 93/06/06 16:46:04 bostic 12 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00013/00111
d D 4.2 91/04/26 15:46:40 bostic 11 10
c new copyright; att/bsd/shared
e
s 00000/00000/00124
d D 4.1 88/12/04 15:12:46 minshall 10 9
c Release 4.1
e
s 00010/00005/00114
d D 3.3 88/06/29 19:57:23 bostic 9 8
c install approved copyright notice
e
s 00009/00018/00110
d D 3.2 88/03/28 12:23:52 bostic 8 7
c add Berkeley specific header
e
s 00000/00000/00128
d D 3.1 87/08/11 10:20:26 minshall 7 6
c New version numbering.
e
s 00025/00000/00103
d D 1.6 87/07/17 10:05:06 minshall 6 5
c Install sccs headers and copyright notices.
e
s 00007/00000/00096
d D 1.5 87/07/16 13:43:00 minshall 5 4
c Fix to pause after command (!) invocation.
e
s 00001/00001/00095
d D 1.4 87/07/15 15:26:57 minshall 4 3
c New directory structure.
e
s 00044/00020/00052
d D 1.3 87/05/25 16:28:38 minshall 3 2
c Split up shell into shell and shell_continue (so that
c we run from the right place on the stack: from the top loop).
e
s 00001/00000/00071
d D 1.2 87/05/22 12:21:20 minshall 2 1
c New directory structure.
e
s 00071/00000/00000
d D 1.1 87/05/22 12:01:28 minshall 1 0
c date and time created 87/05/22 12:01:28 by minshall
e
u
U
t
T
I 6
D 11
/*
D 8
 *	Copyright (c) 1984-1987 by the Regents of the
 *	University of California and by Gregory Glenn Minshall.
E 8
I 8
 * Copyright (c) 1988 Regents of the University of California.
E 11
I 11
/*-
D 12
 * Copyright (c) 1988 The Regents of the University of California.
E 11
 * All rights reserved.
E 12
I 12
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 12
E 8
 *
D 8
 *	Permission to use, copy, modify, and distribute these
 *	programs and their documentation for any purpose and
 *	without fee is hereby granted, provided that this
 *	copyright and permission appear on all copies and
 *	supporting documentation, the name of the Regents of
 *	the University of California not be used in advertising
 *	or publicity pertaining to distribution of the programs
 *	without specific prior permission, and notice be given in
 *	supporting documentation that copying and distribution is
 *	by permission of the Regents of the University of California
 *	and by Gregory Glenn Minshall.  Neither the Regents of the
 *	University of California nor Gregory Glenn Minshall make
 *	representations about the suitability of this software
 *	for any purpose.  It is provided "as is" without
 *	express or implied warranty.
E 8
I 8
D 11
 * Redistribution and use in source and binary forms are permitted
D 9
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 9
I 9
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 11
I 11
 * %sccs.include.redist.c%
E 11
E 9
E 8
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 8
#endif	/* not lint */
E 8
I 8
#endif /* not lint */
E 8

E 6
I 1
#include <stdio.h>

I 2
#include "../general/general.h"
E 2
D 4
#include "../api/api.h"
E 4
I 4
#include "../ctlr/api.h"
E 4
#include "spint.h"

I 3
#include "../general/globals.h"
E 3


I 3
static Spint spinted;
static char command[256];
static int need_to_start = 0;

E 3
/*
I 3
 * shell_continue() actually runs the command, and looks for API
 * requests coming back in.
 *
 * We are called from the main loop in telnet.c.
 */

int
shell_continue()
{
    /*
     * spint_start() returns when either the command has finished, or when
     * the required interrupt comes in.  In the latter case, the appropriate
     * thing to do is to process the interrupt, and then return to
     * the interrupt issuer by calling spint_continue().
     */
    if (need_to_start) {
	need_to_start = 0;
	spint_start(command, &spinted);
    }

    if (spinted.done == 0) {
	/* Process request */
	handle_api(&spinted.regs, &spinted.sregs);
	spint_continue(&spinted);
    } else {
I 5
	char inputbuffer[100];

E 5
	if (spinted.rc != 0) {
	    fprintf(stderr, "Process generated a return code of 0x%x.\n",
								spinted.rc);
	}
I 5
	printf("[Hit return to continue]");
	fflush(stdout);
	(void) gets(inputbuffer);
E 5
	shell_active = 0;
I 5
	setconnmode();
	ConnectScreen();
E 5
    }
    return shell_active;
}


/*
E 3
 * Called from telnet.c to fork a lower command.com.  We
 * use the spint... routines so that we can pick up
 * interrupts generated by application programs.
 */


int
shell(argc,argv)
int	argc;
char	*argv[];
{
D 3
    Spint spinted;
    char command[256];
E 3

    ClearElement(spinted);
    spinted.int_no = API_INTERRUPT_NUMBER;
    if (argc == 1) {
	command[0] = 0;
    } else {
	char *cmdptr;
	int length;

	argc--;
	argv++;
	strcpy(command, " /c");
	cmdptr = command+strlen(command);
	while (argc) {
	    if ((cmdptr+strlen(*argv)) >= (command+sizeof command)) {
		fprintf(stderr, "Argument list too long at argument *%s*.\n",
			    *argv);
		return 0;
	    }
	    *cmdptr++ = ' ';		/* Blank separators */
	    strcpy(cmdptr, *argv);
	    cmdptr += strlen(cmdptr);
	    argc--;
	    argv++;
	}
	length = strlen(command)-1;
	if (length < 0) {
	    length = 0;
	}
	command[0] = length;
    }
D 3

    /*
     * spint_start() returns when either the command has finished, or when
     * the required interrupt comes in.  In the latter case, the appropriate
     * thing to do is to process the interrupt, and then return to
     * the interrupt issuer by calling spint_continue().
     */
    spint_start(command, &spinted);
    while (spinted.done == 0) {
	/* Process request */
	handle_api(&spinted.regs, &spinted.sregs);
	spint_continue(&spinted);
    }
    if (spinted.rc != 0) {
	fprintf(stderr, "Process generated a return code of 0x%x.\n",
								spinted.rc);
    }
    return 0;
E 3
I 3
    need_to_start = 1;
    shell_active = 1;
    return 1;			/* Go back to main loop */
E 3
}
E 1
