h02002
s 00003/00144/00125
d D 5.6 92/03/03 00:23:49 mckusick 6 5
c break out machine independent part to ../csu.gmon/gmon.c
e
s 00019/00034/00250
d D 5.5 91/05/22 11:21:44 mckusick 5 4
c delete support for prof style profiling
e
s 00003/00003/00281
d D 5.4 91/05/06 20:43:14 bostic 4 3
c new copyright; att/bsd/shared
e
s 00148/00150/00136
d D 5.3 91/05/03 12:27:31 donn 3 2
c Convert for GCC.  Massive reformatting; needs more!
e
s 00006/00005/00280
d D 5.2 91/04/12 11:50:57 bostic 2 1
c new copyright; att/bsd/shared
e
s 00285/00000/00000
d D 5.1 87/08/27 09:19:06 mckusick 1 0
c from CCI
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
 * Copyright (c) 1987 The Regents of the University of California.
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

I 6
#include "../csu.gmon/gmon.c"

E 6
D 4
#if defined(LIBC_SCCS) && !defined(lint)
E 4
I 4
#ifndef lint
E 4
D 6
static char sccsid[] = "%W% (Berkeley) %G%";
E 6
I 6
static char mcount_sccsid[] = "%W% (Berkeley) %G%";
E 6
D 2
#endif LIBC_SCCS and not lint
E 2
I 2
D 4
#endif /* LIBC_SCCS and not lint */
E 4
I 4
#endif /* not lint */
E 4
E 2

I 3
D 6
#include <unistd.h>
E 3
#include "gmon.h"

E 6
I 3
extern mcount() asm ("mcount");
D 6
extern char *minbrk asm ("minbrk");
E 6

E 3
D 6
    /*
     *	froms is actually a bunch of unsigned shorts indexing tos
     */
static int		profiling = 3;
static unsigned short	*froms;
static struct tostruct	*tos = 0;
static long		tolimit = 0;
static char		*s_lowpc = 0;
static char		*s_highpc = 0;
static unsigned long	s_textsize = 0;

static int	ssiz;
static char	*sbuf;
static int	s_scale;
    /* see profil(2) where this is describe (incorrectly) */
#define		SCALE_1_TO_1	0x10000L

D 3
#define	MSG "No space for monitor buffer(s)\n"
E 3
I 3
D 5
char nospace_msg[] = "No space for monitor buffer(s)\n";
E 5
I 5
char nospace_msg[] = "No space for profiling buffer(s)\n";
E 5
#define NOSPACE() (void) write(2, nospace_msg, sizeof nospace_msg - 1)
E 3

I 3
char overflow_msg[] = "mcount: tos overflow\n";
#define OVERFLOW() (void) write(2, overflow_msg, sizeof overflow_msg - 1)

E 3
monstartup(lowpc, highpc)
D 3
    char	*lowpc;
    char	*highpc;
E 3
I 3
	char	*lowpc;
	char	*highpc;
E 3
{
D 3
    int			monsize;
    char		*buffer;
    char		*sbrk();
    extern char		*minbrk;
E 3
I 3
	int	monsize;
	char	*buffer;
I 5
	int	o;
	struct	phdr *p;
E 5
E 3

	/*
D 3
	 *	round lowpc and highpc to multiples of the density we're using
	 *	so the rest of the scaling (here and in gprof) stays in ints.
E 3
I 3
	 * Round lowpc and highpc to multiples of the density we're using
	 * so the rest of the scaling (here and in gprof) stays in ints.
E 3
	 */
D 3
    lowpc = (char *)
E 3
I 3
	lowpc = (char *)
E 3
	    ROUNDDOWN((unsigned)lowpc, HISTFRACTION*sizeof(HISTCOUNTER));
D 3
    s_lowpc = lowpc;
    highpc = (char *)
E 3
I 3
	s_lowpc = lowpc;
	highpc = (char *)
E 3
	    ROUNDUP((unsigned)highpc, HISTFRACTION*sizeof(HISTCOUNTER));
D 3
    s_highpc = highpc;
    s_textsize = highpc - lowpc;
    monsize = (s_textsize / HISTFRACTION) + sizeof(struct phdr);
    monsize = (monsize + 3) & ~3;
    buffer = sbrk( monsize );
    if ( buffer == (char *) -1 ) {
	write( 2 , MSG , sizeof(MSG) - 1 );
	return;
    }
    froms = (unsigned short *) sbrk( s_textsize / HASHFRACTION );
    if ( froms == (unsigned short *) -1 ) {
	write( 2 , MSG , sizeof(MSG) - 1 );
	froms = 0;
	return;
    }
    tolimit = s_textsize * ARCDENSITY / 100;
    if ( tolimit < MINARCS ) {
	tolimit = MINARCS;
    } else if ( tolimit > 65534 ) {
	tolimit = 65534;
    }
    tos = (struct tostruct *) sbrk( (tolimit*sizeof(struct tostruct)+3)&~3 );
    if ( tos == (struct tostruct *) -1 ) {
	write( 2 , MSG , sizeof(MSG) - 1 );
	froms = 0;
	tos = 0;
	return;
    }
    minbrk = sbrk(0);
    tos[0].link = 0;
    monitor( lowpc , highpc , buffer , monsize , tolimit );
E 3
I 3
	s_highpc = highpc;
	s_textsize = highpc - lowpc;
	monsize = (s_textsize / HISTFRACTION) + sizeof(struct phdr);
	monsize = (monsize + 3) & ~3;
	buffer = sbrk(monsize);
	if (buffer == (char *) -1) {
		NOSPACE();
		return;
	}
	froms = (unsigned short *) sbrk(s_textsize / HASHFRACTION);
	if (froms == (unsigned short *) -1) {
		NOSPACE();
		froms = 0;
		return;
	}
	tolimit = s_textsize * ARCDENSITY / 100;
	if (tolimit < MINARCS)
		tolimit = MINARCS;
	else if (tolimit > 65534)
		tolimit = 65534;
	tos = (struct tostruct *) sbrk((tolimit*sizeof(struct tostruct)+3)&~3);
	if (tos == (struct tostruct *) -1) {
		NOSPACE();
		froms = 0;
		tos = 0;
		return;
	}
	minbrk = sbrk(0);
	tos[0].link = 0;
D 5
	monitor(lowpc, highpc, buffer, monsize, tolimit);
E 5
I 5
	sbuf = buffer;
	ssiz = monsize;
	p = (struct phdr *) buffer;
	p->lpc = lowpc;
	p->hpc = highpc;
	p->ncnt = ssiz;
	monsize -= sizeof(struct phdr);
	if (monsize <= 0)
		return;
	o = highpc - lowpc;
	if(monsize < o)
		s_scale = ((float) monsize / o) * SCALE_1_TO_1;
	else
		s_scale = SCALE_1_TO_1;
	moncontrol(1);
E 5
E 3
}

_mcleanup()
{
D 3
    int			fd;
    int			fromindex;
    int			endfrom;
    char		*frompc;
    int			toindex;
    struct rawarc	rawarc;
E 3
I 3
	int		fd;
	int		fromindex;
	int		endfrom;
	char		*frompc;
	int		toindex;
	struct rawarc	rawarc;
E 3

I 5
	moncontrol(0);
E 5
D 3
    fd = creat( "gmon.out" , 0666 );
    if ( fd < 0 ) {
	perror( "mcount: gmon.out" );
	return;
    }
#   ifdef DEBUG
	fprintf( stderr , "[mcleanup] sbuf 0x%x ssiz %d\n" , sbuf , ssiz );
#   endif DEBUG
    write( fd , sbuf , ssiz );
    endfrom = s_textsize / (HASHFRACTION * sizeof(*froms));
    for ( fromindex = 0 ; fromindex < endfrom ; fromindex++ ) {
	if ( froms[fromindex] == 0 ) {
	    continue;
E 3
I 3
	fd = creat("gmon.out", 0666);
	if (fd < 0) {
		perror("mcount: gmon.out");
		return;
E 3
	}
D 3
	frompc = s_lowpc + (fromindex * HASHFRACTION * sizeof(*froms));
	for (toindex=froms[fromindex]; toindex!=0; toindex=tos[toindex].link) {
#	    ifdef DEBUG
		fprintf( stderr ,
			"[mcleanup] frompc 0x%x selfpc 0x%x count %d\n" ,
			frompc , tos[toindex].selfpc , tos[toindex].count );
#	    endif DEBUG
	    rawarc.raw_frompc = (unsigned long) frompc;
	    rawarc.raw_selfpc = (unsigned long) tos[toindex].selfpc;
	    rawarc.raw_count = tos[toindex].count;
	    write( fd , &rawarc , sizeof rawarc );
E 3
I 3
	(void) write(fd, sbuf, ssiz);
	endfrom = s_textsize / (HASHFRACTION * sizeof(*froms));
	for (fromindex = 0; fromindex < endfrom; fromindex++) {
		if (froms[fromindex] == 0)
			continue;
		frompc = s_lowpc + (fromindex * HASHFRACTION * sizeof(*froms));
		for (toindex = froms[fromindex];
		     toindex != 0;
		     toindex = tos[toindex].link) {
			rawarc.raw_frompc = (unsigned long) frompc;
			rawarc.raw_selfpc = (unsigned long) tos[toindex].selfpc;
			rawarc.raw_count = tos[toindex].count;
			(void) write(fd, &rawarc, sizeof rawarc);
		}
E 3
	}
D 3
    }
    close( fd );
E 3
I 3
	close(fd);
E 3
}

E 6
mcount(cntpa)
	long **cntpa;
{
	register char			*selfpc;
	register unsigned short		*frompcindex;
	register struct tostruct	*top;
	register struct tostruct	*prevtop;
	register long			toindex;

	/*
D 3
	 *	find the return address for mcount,
	 *	and address of counter pointer
E 3
I 3
	 * Find the return address for mcount,
	 * and address of counter pointer.
E 3
	 */
	selfpc = *((char **)&cntpa-3);	/* -8(fp) */
	frompcindex = (unsigned short *)(*((((long *)*((char **)&cntpa-1)))-2));
I 3

E 3
	/*
D 3
	 *	check that we are profiling
	 *	and that we aren't recursively invoked.
E 3
I 3
	 * Check that we are profiling
	 * and that we aren't recursively invoked.
E 3
	 */
D 3
	if (profiling) {
		goto out;
	}
E 3
I 3
	if (profiling)
		return;
E 3
	profiling++;
I 3

E 3
	/*
D 3
	 *	check that frompcindex is a reasonable pc value.
	 *	for example:	signal catchers get called from the stack,
	 *			not from text space.  too bad.
E 3
I 3
	 * Check that frompcindex is a reasonable pc value.
	 * for example:	signal catchers get called from the stack,
	 *		not from text space.  too bad.
E 3
	 */
	frompcindex = (unsigned short *)((long)frompcindex - (long)s_lowpc);
D 3
	if ((unsigned long)frompcindex > s_textsize) {
E 3
I 3
	if ((unsigned long)frompcindex > s_textsize)
E 3
		goto done;
D 3
	}
E 3
	frompcindex =
	    &froms[((long)frompcindex) / (HASHFRACTION * sizeof(*froms))];
I 3

E 3
	toindex = *frompcindex;
	if (toindex == 0) {
		/*
D 3
		 *	first time traversing this arc
E 3
I 3
		 * First time traversing this arc
E 3
		 */
		toindex = ++tos[0].link;
		if (toindex >= tolimit) {
D 3
			goto overflow;
E 3
I 3
			profiling++;	/* stop profiling */
			OVERFLOW();
			return;
E 3
		}
		*frompcindex = toindex;
		top = &tos[toindex];
		top->selfpc = selfpc;
		top->count = 1;
		top->link = 0;
		goto done;
	}
	top = &tos[toindex];
	if (top->selfpc == selfpc) {
		/*
D 3
		 *	arc at front of chain; usual case.
E 3
I 3
		 * Arc at front of chain; usual case.
E 3
		 */
		top->count++;
		goto done;
	}
I 3

E 3
	/*
D 3
	 *	have to go looking down chain for it.
	 *	top points to what we are looking at,
	 *	prevtop points to previous top.
	 *	we know it is not at the head of the chain.
E 3
I 3
	 * Have to go looking down chain for it.
	 * top points to what we are looking at,
	 * prevtop points to previous top.
	 * We know it is not at the head of the chain.
E 3
	 */
D 3
	for (; /* goto done */; ) {
E 3
I 3
	for (;;) {
E 3
		if (top->link == 0) {
			/*
D 3
			 *	top is end of the chain and none of the chain
			 *	had top->selfpc == selfpc.
			 *	so we allocate a new tostruct
			 *	and link it to the head of the chain.
E 3
I 3
			 * top is end of the chain and none of the chain
			 * had top->selfpc == selfpc,
			 * so we allocate a new tostruct
			 * and link it to the head of the chain.
E 3
			 */
			toindex = ++tos[0].link;
			if (toindex >= tolimit) {
D 3
				goto overflow;
E 3
I 3
				profiling++;	/* stop profiling */
				OVERFLOW();
				return;
E 3
			}
			top = &tos[toindex];
			top->selfpc = selfpc;
			top->count = 1;
			top->link = *frompcindex;
			*frompcindex = toindex;
			goto done;
		}
		/*
D 3
		 *	otherwise, check the next arc on the chain.
E 3
I 3
		 * Otherwise, check the next arc on the chain.
E 3
		 */
		prevtop = top;
		top = &tos[top->link];
		if (top->selfpc == selfpc) {
			/*
D 3
			 *	there it is.
			 *	increment its count
			 *	move it to the head of the chain.
E 3
I 3
			 * There it is.
			 * Increment its count and
			 * move it to the head of the chain.
E 3
			 */
			top->count++;
			toindex = prevtop->link;
			prevtop->link = top->link;
			top->link = *frompcindex;
			*frompcindex = toindex;
			goto done;
		}

	}
done:
	profiling--;
D 3
out:
E 3
	return;
D 3

overflow:
#   define	TOLIMIT	"mcount: tos overflow\n"
	write(2, TOLIMIT, sizeof(TOLIMIT) - 1);
	goto out;
E 3
D 5
}

/*VARARGS1*/
D 3
monitor( lowpc , highpc , buf , bufsiz , nfunc )
    char	*lowpc;
    char	*highpc;
    char	*buf;	/* declared ``short buffer[]'' in monitor(3) */
    int		bufsiz;
    int		nfunc;	/* not used, available for compatability only */
E 3
I 3
monitor(lowpc, highpc, buf, bufsiz, nfunc)
	char	*lowpc;
	char	*highpc;
	char	*buf;	/* declared ``short buffer[]'' in monitor(3) */
	int	bufsiz;
	int	nfunc;	/* not used, available for compatability only */
E 3
{
D 3
    register o;
E 3
I 3
	register int	o;
	struct phdr	*p = (struct phdr *) buf;
E 3

D 3
    if ( lowpc == 0 ) {
	moncontrol(0);
	_mcleanup();
	return;
    }
    sbuf = buf;
    ssiz = bufsiz;
    ( (struct phdr *) buf ) -> lpc = lowpc;
    ( (struct phdr *) buf ) -> hpc = highpc;
    ( (struct phdr *) buf ) -> ncnt = ssiz;
    bufsiz -= sizeof(struct phdr);
    if ( bufsiz <= 0 )
	return;
    o = highpc - lowpc;
    if( bufsiz < o )
	s_scale = ( (float) bufsiz / o ) * SCALE_1_TO_1;
    else
	s_scale = SCALE_1_TO_1;
    moncontrol(1);
E 3
I 3
	if ( lowpc == 0 ) {
		moncontrol(0);
		_mcleanup();
		return;
	}
	sbuf = buf;
	ssiz = bufsiz;
	p->lpc = lowpc;
	p->hpc = highpc;
	p->ncnt = ssiz;
	bufsiz -= sizeof(struct phdr);
	if (bufsiz <= 0)
		return;
	o = highpc - lowpc;
	if(bufsiz < o)
		s_scale = ((float) bufsiz / o) * SCALE_1_TO_1;
	else
		s_scale = SCALE_1_TO_1;
	moncontrol(1);
E 5
E 3
D 6
}

/*
D 3
 * Control profiling
 *	profiling is what mcount checks to see if
 *	all the data structures are ready.
E 3
I 3
 * While profiling is enabled, we set the variable 'profiling' to indicate
 * that all the data structures are ready.
E 3
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
	profil(sbuf + sizeof(struct phdr), ssiz - sizeof(struct phdr),
		s_lowpc, s_scale);
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
		profil(sbuf + sizeof(struct phdr), ssiz - sizeof(struct phdr),
			(int)s_lowpc, s_scale);
		profiling = 0;
	} else {
		/* stop */
		profil((char *)0, 0, 0, 0);
		profiling = 3;
	}
E 6
E 3
}
E 1
