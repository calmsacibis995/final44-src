h38916
s 00027/00027/00062
d D 7.4 90/05/03 17:47:09 sklower 4 3
c first crack at torek changes, may need bug fixes
e
s 00006/00001/00083
d D 7.3 89/09/02 12:46:05 karels 3 2
c add :k (kill kernel), with panic from trap like other traps
e
s 00011/00005/00073
d D 7.2 86/12/15 20:26:50 sam 2 1
c lint
e
s 00078/00000/00000
d D 7.1 86/11/20 12:22:05 sam 1 0
c date and time created 86/11/20 12:22:05 by sam
e
u
U
t
T
I 1
D 2
/*	%M%	%I%	%E%	*/
E 2
I 2
/*
D 3
 * Copyright (c) 1986 Regents of the University of California.
E 3
I 3
 * Copyright (c) 1986, 1989 Regents of the University of California.
E 3
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	%W% (Berkeley) %G%
 */
E 2

#include "../kdb/defs.h"

D 4
char	*NOBKPT;
char	*SZBKPT;
char	*EXBKPT;
char	*BADMOD;
E 4
I 4
char	*kdbNOBKPT;
char	*kdbSZBKPT;
char	*kdbEXBKPT;
char	*kdbBADMOD;
E 4

/* breakpoints */
D 4
BKPTR	bkpthead;
E 4
I 4
BKPTR	kdbbkpthead;
E 4

D 4
char	*lp;
char	lastc;
E 4
I 4
char	*kdblp;
char	kdblastc;
E 4
D 2

E 2
I 2
extern	char *kdbmalloc();
E 2
D 4
long	loopcnt;
E 4
I 4
long	kdbloopcnt;
E 4

/* sub process control */

D 4
subpcs(modif)
E 4
I 4
kdbsubpcs(modif)
E 4
{
	register check, runmode;
	register BKPTR bkptr;
	register char *comptr;

D 4
	loopcnt=cntval;
E 4
I 4
	kdbloopcnt=kdbcntval;
E 4
	switch (modif) {

		/* delete breakpoint */
	case 'd': case 'D':
D 2
		if (bkptr=scanbkpt(dot)) {
E 2
I 2
D 4
		if (bkptr=scanbkpt((ADDR)dot)) {
E 4
I 4
		if (bkptr=kdbscanbkpt((ADDR)kdbdot)) {
E 4
E 2
			bkptr->flag=0;
			return;
		}
D 4
		error(NOBKPT);
E 4
I 4
		kdberror(kdbNOBKPT);
E 4

		/* set breakpoint */
	case 'b': case 'B':
D 2
		if (bkptr=scanbkpt(dot))
E 2
I 2
D 4
		if (bkptr=scanbkpt((ADDR)dot))
E 4
I 4
		if (bkptr=kdbscanbkpt((ADDR)kdbdot))
E 4
E 2
			bkptr->flag=0;
D 4
		for (bkptr=bkpthead; bkptr; bkptr=bkptr->nxtbkpt)
E 4
I 4
		for (bkptr=kdbbkpthead; bkptr; bkptr=bkptr->nxtbkpt)
E 4
			if (bkptr->flag == 0)
				break;
		if (bkptr==0) {
			bkptr=(BKPTR)kdbmalloc(sizeof *bkptr);
			if (bkptr == (BKPTR)-1)
D 4
				error(SZBKPT);
			bkptr->nxtbkpt=bkpthead;
			bkpthead=bkptr;
E 4
I 4
				kdberror(kdbSZBKPT);
			bkptr->nxtbkpt=kdbbkpthead;
			kdbbkpthead=bkptr;
E 4
		}
D 4
		bkptr->loc = dot;
		bkptr->initcnt = bkptr->count = cntval;
E 4
I 4
		bkptr->loc = kdbdot;
		bkptr->initcnt = bkptr->count = kdbcntval;
E 4
		bkptr->flag = BKPTSET;
D 2
		check=MAXCOM-1; comptr=bkptr->comm; rdc(); lp--;
E 2
I 2
D 4
		check=MAXCOM-1; comptr=bkptr->comm; (void) rdc(); lp--;
E 4
I 4
		check=MAXCOM-1; comptr=bkptr->comm; (void) kdbrdc(); kdblp--;
E 4
E 2
		do
D 4
			*comptr++ = readchar();
		while (check-- && lastc!=EOR);
		*comptr=0; lp--;
E 4
I 4
			*comptr++ = kdbreadchar();
		while (check-- && kdblastc!=EOR);
		*comptr=0; kdblp--;
E 4
		if (check)
			return;
D 4
		error(EXBKPT);
E 4
I 4
		kdberror(kdbEXBKPT);
E 4

		/* single step */
	case 's': case 'S':
		runmode=SINGLE;
		break;

		/* continue */
	case 'c': case 'C':
		runmode=CONTIN;
		break;
I 3

		/* kill */
	case 'k': case 'K':
		reset(PANIC);
		/* NOTREACHED */
E 3

	default:
D 4
		error(BADMOD);
E 4
I 4
		kdberror(kdbBADMOD);
E 4
	}
D 4
	if (loopcnt>0)
		runpcs(runmode, 0);
E 4
I 4
	if (kdbloopcnt>0)
		kdbrunpcs(runmode, 0);
E 4
}
E 1
