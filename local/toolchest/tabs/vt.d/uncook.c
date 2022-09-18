/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
#include <stdio.h>
#include <termio.h>
#include "vt.h"

char    charms[NBAUD] =
{					/* ms per char in various rates */
	100,
	100,				/* 50 */
	100,				/* 75 */
	100,				/* 110 */
	70,				/* 134 */
	66,				/* 150 */
	50,				/* 200 */
	33,				/* 300 */
	16,				/* 600 */
	8,				/* 1200 */
	5,				/* 1800 */
	4,				/* 2400 */
	2,				/* 4800 */
	1,				/* 9600 */
	1,				/* EXTA */
	1,				/* EXTB */
};

uncook ()
{
	extern struct termio    nttybuf;

	ttywarp = charms[nttybuf.c_cflag & CBAUD];
	ttyintr = nttybuf.c_cc[VINTR];
	ttyerase = nttybuf.c_cc[VERASE];
	ttykill = nttybuf.c_cc[VKILL];

	cp_stty (STTYRAW);

	if (SCINIT)
	{
#ifdef VT_TERMINFO
		extern int e_putch ();

		tputs (VEXIT, 1, e_putch);
#else	
		eprintf (SCINIT);	/* RE-init terminal */
#endif
	}
}
