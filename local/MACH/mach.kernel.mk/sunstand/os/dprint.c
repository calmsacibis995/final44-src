/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	dprint.c,v $
 * Revision 2.2  89/07/12  01:11:15  jjc
 * 	Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
#ifndef lint
static        char sccsid[] = "@(#)dprint.c 1.7 88/02/08 Copyr 1983 Sun Micro";
#endif

#include <stand/saio.h>
#include <sys/reboot.h>
#include <mon/sunromvec.h>

#ifdef DUMP_DEBUG
/*
 * Utilities used by both client and server
 * Standard levels:
 * 0) no debugging
 * 1) hard failures
 * 2) soft failures
 * 3) current test software
 * 4) main procedure entry points
 * 5) main procedure exit points
 * 6) utility procedure entry points
 * 7) utility procedure exit points
 * 8) obscure procedure entry points
 * 9) obscure procedure exit points
 * 10) random stuff
 * 11) all <= 1
 * 12) all <= 2
 * 13) all <= 3
 * ...
 */

/*VARARGS2*/
dprint(var, level, str, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12)
        int var;
        int level;
        char *str;
        int a1, a2, a3, a4, a5, a6, a7, a8, a9;
{
        if (var == level || (var > 10 && (var - 10) >= level))
                printf(str, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12);
}
#endif

dump_buffer (string, from, length)
char    *string;
char    *from;
int     length;
{
        int     i;
        char    *p;

	printf ("dump buffer: ");
        printf ("%s", string);
        for (p = from, i = 0; i < length; i++, p++)     {
                if ((i & 0x3) == 0) printf (" ");
                if ((*p & 0xf0) == 0) printf ("0");
                printf ("%x", (*p & 0xff));
        }
        printf ("\n");

}

