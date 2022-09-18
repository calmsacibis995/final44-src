/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 *
 */

/*
 **********************************************************************
 *	File:	cons.c
 *
 *	Define stubs for procedures we may not want loaded with
 *	the boot binary.
 *
 * HISTORY
 * $Log:	cons.c,v $
 * Revision 2.3  89/02/26  14:19:59  gm0w
 * 	Changes for cleanup.
 * 
 * 16-Apr-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Extracted from print module to here so that the  simple console
 *	I/O routines may be more readily used alone.
 *	[ V5.1(F8) ]
 *
 * 17-May-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Upgraded previous changes to 4.3.
 *
 * 01-Jul-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	Hooked character input/output through optional virtual console.
 *
 **********************************************************************
 */

#include <machine/cons.h>
#include <machine/mtpr.h>


extern int cn_getchar(), cn_putchar();
int   	 (*vgetc)() = cn_getchar;
int	 (*vputc)() = cn_putchar;



putchar(c)
    register int c;
{
    (*vputc)(c);
    if (c == '\n')
	putchar('\r');
}



getchar()
{
    register int c;

    c = (*vgetc)();
    if (c == '\r')
	c = '\n';
    putchar(c);
    return(c);
}


cn_putchar(c)
    register c;
{
    register int txcs, tout;

    tout = 32767;
    while((mfpr(TXCS)&TXCS_RDY) == 0)
	if(--tout == 0)
	    break;
    if(c == 0)
	return;
    txcs = mfpr(TXCS);
    mtpr(TXCS, 0);
    mtpr(TXDB, c&0xff);
    mtpr(TXCS, txcs);
    cn_putchar(0);
}

cn_getchar()
{
    register int c;

    while ((mfpr(RXCS)&RXCS_DONE) == 0 || (c=mfpr(RXDB)&0177) < 0)
	    ;
    return(c);
}
