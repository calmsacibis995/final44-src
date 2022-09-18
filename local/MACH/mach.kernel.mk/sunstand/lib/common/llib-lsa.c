/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	llib-lsa.c,v $
 * Revision 2.2  89/07/12  00:20:05  jjc
 * 	Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/*	@(#)llib-lsa.c 1.2 88/02/08 SMI	*/

    /* LINTLIBRARY */

#include <sys/types.h>
#include <mon/cpu.map.h>

int	poke(a, c) short *a; int c; { return 0; }
int	pokec(a, c) char *a; int c; { return 0; }
int	peek(a) caddr_t a; { return 0; }
	setsegmap(a, v) caddr_t a; int v; {}
	getidprom(a, s) unsigned char *a; unsigned s; {}
	setpgmap(a, v) caddr_t a; struct pgmapent v; {}
/* this declaration gets fixed when <mon/cpu.map.h> does */
int /*struct pgmapent*/	getpgmap(a) caddr_t a;
		{ /*struct pgmapent b; return b;*/ return 0; }
