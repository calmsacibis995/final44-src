h25810
s 00003/00003/00167
d D 5.4 91/05/06 20:43:16 bostic 4 3
c new copyright; att/bsd/shared
e
s 00032/00032/00138
d D 5.3 91/05/03 12:28:04 donn 3 2
c Convert for GCC.  Some reformatting; needs more!
e
s 00013/00000/00157
d D 5.2 91/04/12 11:50:59 bostic 2 1
c new copyright; att/bsd/shared
e
s 00157/00000/00000
d D 5.1 91/04/12 11:46:35 bostic 1 0
c date and time created 91/04/12 11:46:35 by bostic
e
u
U
t
T
I 2
/*-
 * Copyright (c) 1984 The Regents of the University of California.
 * All rights reserved.
 *
D 4
 * %sccs.include.proprietary.c%
E 4
I 4
 * %sccs.include.redist.c%
E 4
 */

D 4
#if defined(LIBC_SCCS) && !defined(lint)
E 4
I 4
#ifndef lint
E 4
static char sccsid[] = "%W% (Berkeley) %G%";
D 4
#endif /* LIBC_SCCS and not lint */
E 4
I 4
#endif /* not lint */
E 4

D 3
/*
E 2
I 1
static	char *sccsid = "@(#)mon.c	2.0 (Tahoe) 5/7/84";
I 2
*/
E 3
I 3
#include <unistd.h>
E 3
E 2

I 3
extern mcount() asm ("mcount");
extern char *minbrk asm ("minbrk");

E 3
#define ARCDENSITY	5	/* density of routines */
#define MINARCS		50	/* minimum number of counters */
#define	HISTFRACTION	2	/* fraction of text space for histograms */

D 3

E 3
struct phdr {
	char *lpc;
	char *hpc;
	int ncnt;
};

struct cnt {
	char *pc;
	long ncall;
} *countbase;

static int cntrs = 0;
static int profiling = 3;
static char *s_sbuf;
static int s_bufsiz;
static int s_scale;
static char *s_lowpc;

int numctrs;

D 3
#define	MSG "No space for monitor buffer(s)\n"
E 3
I 3
char nospace_msg[] = "No space for monitor buffer(s)\n";
#define NOSPACE() (void) write(2, nospace_msg, sizeof nospace_msg - 1)
E 3

I 3
char overflow_msg[] = "mcount: tos overflow\n";
#define OVERFLOW() (void) write(2, overflow_msg, sizeof overflow_msg - 1)

E 3
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
D 3
		write(2, MSG, sizeof(MSG));
E 3
I 3
		NOSPACE();
E 3
		return;
	}
	minbrk = sbrk(0);
	monitor(lowpc, highpc, buffer, monsize, cntsiz);
}

mcount(cntpa)
	long **cntpa;
{
	register long **cntp;
	register char *selfpc;

	/*
D 3
	 * find the return address for mcount,
E 3
I 3
	 * Find the return address for mcount,
E 3
	 * and address of counter pointer
	 */
	selfpc = *((char **)&cntpa-3);	/* -8(fp) */
	cntp = cntpa;
I 3

E 3
	/*
D 3
	 * check that we aren't recursively invoked.
E 3
I 3
	 * Check that we aren't recursively invoked.
E 3
	 */
	if (profiling)
D 3
		goto out;
E 3
I 3
		return;
E 3
	profiling++;
I 3

E 3
	/*
D 3
	 * check that counter is allocated
E 3
I 3
	 * Check that counter is allocated
E 3
	 */
	if (*cntp == 0) {
		/*
D 3
		 * check that a counter is available
E 3
I 3
		 * Check that a counter is available
E 3
		 */
D 3
		if (cntrs++ == numctrs)
			goto overflow;
E 3
I 3
		if (cntrs++ == numctrs) {
			profiling++;
			OVERFLOW();
			return;
		}
E 3
		countbase->pc = selfpc;
		*cntp = &countbase->ncall;
		countbase++;
	}
	(**cntp)++;
	profiling--;
D 3
out:
E 3
	return;
D 3

overflow:
#   define	TOLIMIT	"mcount: counter overflow\n"
	write( 2 , TOLIMIT , sizeof( TOLIMIT ) );
	goto out;
E 3
}

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
	php->lpc = lowpc;
	php->hpc = highpc;
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
D 3
    int mode;
E 3
I 3
	int mode;
E 3
{
D 3
    if (mode) {
	/* start */
	profil(s_sbuf, s_bufsiz, s_lowpc, s_scale);
	profiling = 0;
    } else {
	/* stop */
	profil((char *)0, 0, 0, 0);
	profiling = 3;
    }
E 3
I 3
	if (mode) {
		/* start */
		profil(s_sbuf, s_bufsiz, (int)s_lowpc, s_scale);
		profiling = 0;
	} else {
		/* stop */
		profil((char *)0, 0, 0, 0);
		profiling = 3;
	}
E 3
}
E 1
