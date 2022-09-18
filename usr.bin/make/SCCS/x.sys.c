h29052
s 00025/00007/00060
d D 5.2 90/03/11 16:50:59 bostic 2 1
c add Berkeley specific copyright notices
e
s 00067/00000/00000
d D 5.1 90/03/11 16:48:08 bostic 1 0
c release 2.1 of pmake
e
u
U
t
T
I 1
D 2
/* 
 * sys.c --
E 2
I 2
/*
 * Copyright (c) 1988, 1989, 1990 The Regents of the University of California.
 * Copyright (c) 1988, 1989 by Adam de Boor
 * Copyright (c) 1989 by Berkeley Softworks
 * All rights reserved.
E 2
 *
D 2
 *	Miscellaneous user-level run-time library routines for the Sys module.
E 2
I 2
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
E 2
 *
D 2
 * Copyright 1986 Regents of the University of California
 * All rights reserved.
E 2
I 2
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 2
 */

#ifndef lint
D 2
static char rcsid[] = "$Id: sys.c,v 1.2 89/06/13 17:25:37 adam Exp $ SPRITE (Berkeley)";
#endif not lint
E 2
I 2
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 2

I 2
/* 
 * sys.c --
 *
 *	Miscellaneous user-level run-time library routines for the Sys module.
 */
E 2

#include <stdio.h>
#include "sprite.h"
#include "sys.h"
#include "varg.h"




/*
 * ----------------------------------------------------------------------------
 *
 * Sys_Panic --
 *
 *      Print a formatted string and then,depending on the panic level,
 *	abort to the debugger or continue.
 *
 * Results:
 *      None.
 *
 * Side effects:
 *      The process may be put into the debug state.
 *
 * ----------------------------------------------------------------------------
 */

/*VARARGS2*/
void
Sys_Panic(level, format, Varg_Args)
    Sys_PanicLevel      level;	/* Severity of the error. */
    char 	*format;	/* Contains literal text and format control
                                 * sequences indicating how elements of
                                 * Varg_Alist are to be printed.  See the
                                 * Io_Print manual page for details. */
    Varg_Decl;                  /* Variable number of values to be formatted
                                 * and printed. */
{
    Varg_List args;

    Varg_Start(args);

    if (level == SYS_WARNING) {
        fprintf(stderr, "Warning: ");
    } else {
        fprintf(stderr, "Fatal Error: ");
    }

    fprintf(stderr, format, args);
    fflush(stderr);

    if (level == SYS_FATAL) {
	abort();
    }
}
E 1
