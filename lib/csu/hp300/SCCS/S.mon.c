h20554
s 00001/00001/00165
d D 5.4 91/05/06 20:39:46 bostic 4 3
c new copyright; att/bsd/shared
e
s 00011/00021/00155
d D 5.3 91/04/28 14:59:45 donn 3 2
c Clean-up for GCC.
e
s 00007/00006/00169
d D 5.2 91/04/12 11:40:12 bostic 2 1
c new copyright; att/bsd/shared
e
s 00175/00000/00000
d D 5.1 90/06/25 23:10:02 bostic 1 0
c date and time created 90/06/25 23:10:02 by bostic
e
u
U
t
T
I 1
D 2
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 2
I 2
/*-
D 3
 * Copyright (c) 1990 The Regents of the University of California.
E 3
I 3
 * Copyright (c) 1991 The Regents of the University of California.
E 3
 * All rights reserved.
 *
D 4
 * %sccs.include.proprietary.c%
E 4
I 4
 * %sccs.include.redist.c%
E 4
E 2
 */

D 3
#if defined(LIBC_SCCS) && !defined(lint)
E 3
I 3
#ifndef lint
E 3
D 2
static char sccsid[] = "@(#)mon.c	5.3 (Berkeley) 3/9/86";
#endif LIBC_SCCS and not lint
E 2
I 2
static char sccsid[] = "%W% (Berkeley) %G%";
D 3
#endif /* LIBC_SCCS and not lint */
E 3
I 3
#endif /* not lint */
E 3
E 2

I 3
#include <unistd.h>

extern mcount() asm ("mcount");
extern char *minbrk asm ("minbrk");

E 3
#define ARCDENSITY	5	/* density of routines */
#define MINARCS		50	/* minimum number of counters */
#define	HISTFRACTION	2	/* fraction of text space for histograms */


struct phdr {
	int *lpc;
	int *hpc;
	int ncnt;
};

struct cnt {
	int *pc;
	long ncall;
} *countbase;

static int cntrs = 0;
static int profiling = 3;
static char *s_sbuf;
static int s_bufsiz;
static int s_scale;
static char *s_lowpc;

int numctrs;

#define	MSG "No space for monitor buffer(s)\n"

monstartup(lowpc, highpc)
	char *lowpc;
	char *highpc;
{
	int monsize;
	char *buffer;
	int cntsiz;
D 3
	extern char *sbrk();
	extern char *minbrk;
E 3

D 3

E 3
	cntsiz = (highpc - lowpc) * ARCDENSITY / 100;
	if (cntsiz < MINARCS)
		cntsiz = MINARCS;
	monsize = (highpc - lowpc + HISTFRACTION - 1) / HISTFRACTION
		+ sizeof(struct phdr) + cntsiz * sizeof(struct cnt);
	monsize = (monsize + 1) & ~1;
	buffer = sbrk(monsize);
	if (buffer == (char *)-1) {
		write(2, MSG, sizeof(MSG));
		return;
	}
	minbrk = sbrk(0);
	monitor(lowpc, highpc, buffer, monsize, cntsiz);
}

D 3
/*
 *	This routine is massaged so that it may be jsb'ed to
 */
asm(".text");
asm(".data");
E 3
mcount()
{
D 3
	register int *selfpc;	/* PCC a5 */
	register long **cntp;   /* PCC a4 */
E 3
I 3
	register int *selfpc;
	register long **cntp;
E 3

	/*
	 * find the return address for mcount,
	 * and address of counter pointer
	 */
D 3
#ifdef __GNUC__
E 3
	asm("movl a6@(4),%0" : "=r" (selfpc));	/* selfpc = ... (jsb frame) */
	asm("movl a0,%0" : "=r" (cntp));	/* address of count local */
D 3
#else
	asm("	movl	a6@(4),a5");	/* selfpc = ... (jsb frame) */
	asm("	movl	a0,a4");	/* address of count local */
#endif
E 3
	/*
	 * check that we aren't recursively invoked.
	 */
	if (profiling)
		return;
	profiling++;
	/*
	 * check that counter is allocated
	 */
	if (*cntp == 0) {
		/*
		 * check that a counter is available
		 */
		if (cntrs++ == numctrs)
			goto overflow;
		countbase->pc = selfpc;
		*cntp = &countbase->ncall;
		countbase++;
	}
	(**cntp)++;
	profiling--;
	return;

overflow:
#   define	TOLIMIT	"mcount: counter overflow\n"
	write( 2 , TOLIMIT , sizeof( TOLIMIT ) );
	profiling--;
}
D 3
asm(".text");
asm(".data");
E 3

monitor(lowpc, highpc, buf, bufsiz, cntsiz)
	char *lowpc, *highpc;
	char *buf;
	int bufsiz, cntsiz;
{
	register int o;
	struct phdr *php;
	static int ssiz;
	static char *sbuf;

	if (lowpc == 0) {
		moncontrol(0);
		o = creat("mon.out", 0666);
		write(o, sbuf, ssiz);
		close(o);
		return;
	}
	sbuf = buf;
	ssiz = bufsiz;
	php = (struct phdr *)&buf[0];
	php->lpc = (int *)lowpc;
	php->hpc = (int *)highpc;
	php->ncnt = cntsiz;
	numctrs = cntsiz;
	countbase = (struct cnt *)(buf + sizeof(struct phdr));
	o = sizeof(struct phdr) + cntsiz * sizeof(struct cnt);
	buf += o;
	bufsiz -= o;
	if (bufsiz <= 0)
		return;
	o = (highpc - lowpc);
	if(bufsiz < o)
		o = ((float) bufsiz / o) * 65536;
	else
		o = 65536;
	s_scale = o;
	s_sbuf = buf;
	s_bufsiz = bufsiz;
	s_lowpc = lowpc;
	moncontrol(1);
}

/*
 * Control profiling
 *	profiling is what mcount checks to see if
 *	all the data structures are ready.
 */
moncontrol(mode)
    int mode;
{
    if (mode) {
	/* start */
D 3
	profil(s_sbuf, s_bufsiz, s_lowpc, s_scale);
E 3
I 3
	profil(s_sbuf, s_bufsiz, (int)s_lowpc, s_scale);
E 3
	profiling = 0;
    } else {
	/* stop */
	profil((char *)0, 0, 0, 0);
	profiling = 3;
    }
}
E 1
