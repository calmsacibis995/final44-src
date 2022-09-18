h49783
s 00004/00167/00135
d D 5.6 92/03/03 00:05:59 mckusick 6 5
c break out machine independent part to csu.gmon/gmon.c
e
s 00032/00048/00270
d D 5.5 91/05/21 18:43:51 mckusick 5 4
c delete support for prof style profiling
e
s 00003/00003/00315
d D 5.4 91/05/06 20:39:45 bostic 4 3
c new copyright; att/bsd/shared
e
s 00009/00017/00309
d D 5.3 91/04/28 15:00:17 donn 3 2
c Clean-up for GCC.
e
s 00008/00007/00318
d D 5.2 91/04/12 11:40:09 bostic 2 1
c new copyright; att/bsd/shared
e
s 00325/00000/00000
d D 5.1 90/06/25 23:09:57 bostic 1 0
c date and time created 90/06/25 23:09:57 by bostic
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
D 6
 * Copyright (c) 1990 The Regents of the University of California.
E 6
I 6
 * Copyright (c) 1983 The Regents of the University of California.
E 6
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
D 2
static char sccsid[] = "@(#)gmon.c	5.3 (Berkeley) 3/9/86";
#endif LIBC_SCCS and not lint
E 2
I 2
D 6
static char sccsid[] = "%W% (Berkeley) %G%";
E 6
I 6
static char mcount_sccsid[] = "%W% (Berkeley) %G%";
E 6
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
#ifdef DEBUG
#include <stdio.h>
D 2
#endif DEBUG
E 2
I 2
#endif
E 2

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

D 5
#define	MSG "No space for monitor buffer(s)\n"
E 5
I 5
#define	MSG "No space for profiling buffer(s)\n"
E 5

monstartup(lowpc, highpc)
    char	*lowpc;
    char	*highpc;
{
    int			monsize;
    char		*buffer;
I 5
    register int	o;
E 5
D 3
    char		*sbrk();
    extern char		*minbrk;
E 3

	/*
	 *	round lowpc and highpc to multiples of the density we're using
	 *	so the rest of the scaling (here and in gprof) stays in ints.
	 */
    lowpc = (char *)
	    ROUNDDOWN((unsigned)lowpc, HISTFRACTION*sizeof(HISTCOUNTER));
    s_lowpc = lowpc;
    highpc = (char *)
	    ROUNDUP((unsigned)highpc, HISTFRACTION*sizeof(HISTCOUNTER));
    s_highpc = highpc;
    s_textsize = highpc - lowpc;
    monsize = (s_textsize / HISTFRACTION) + sizeof(struct phdr);
    buffer = sbrk( monsize );
    if ( buffer == (char *) -1 ) {
	write( 2 , MSG , sizeof(MSG) );
	return;
    }
    froms = (unsigned short *) sbrk( s_textsize / HASHFRACTION );
    if ( froms == (unsigned short *) -1 ) {
	write( 2 , MSG , sizeof(MSG) );
	froms = 0;
	return;
    }
    tolimit = s_textsize * ARCDENSITY / 100;
    if ( tolimit < MINARCS ) {
	tolimit = MINARCS;
    } else if ( tolimit > 65534 ) {
	tolimit = 65534;
    }
    tos = (struct tostruct *) sbrk( tolimit * sizeof( struct tostruct ) );
    if ( tos == (struct tostruct *) -1 ) {
	write( 2 , MSG , sizeof(MSG) );
	froms = 0;
	tos = 0;
	return;
    }
    minbrk = sbrk(0);
    tos[0].link = 0;
D 5
    monitor( lowpc , highpc , buffer , monsize , tolimit );
E 5
I 5
    sbuf = buffer;
    ssiz = monsize;
    ( (struct phdr *) buffer ) -> lpc = lowpc;
    ( (struct phdr *) buffer ) -> hpc = highpc;
    ( (struct phdr *) buffer ) -> ncnt = ssiz;
    monsize -= sizeof(struct phdr);
    if ( monsize <= 0 )
	return;
    o = highpc - lowpc;
    if( monsize < o )
#ifndef hp300
	s_scale = ( (float) monsize / o ) * SCALE_1_TO_1;
#else /* avoid floating point */
    {
	int quot = o / monsize;

	if (quot >= 0x10000)
		s_scale = 1;
	else if (quot >= 0x100)
		s_scale = 0x10000 / quot;
	else if (o >= 0x800000)
		s_scale = 0x1000000 / (o / (monsize >> 8));
	else
		s_scale = 0x1000000 / ((o << 8) / monsize);
    }
#endif
    else
	s_scale = SCALE_1_TO_1;
    moncontrol(1);
E 5
}

_mcleanup()
{
    int			fd;
    int			fromindex;
    int			endfrom;
    char		*frompc;
    int			toindex;
    struct rawarc	rawarc;

I 5
    moncontrol(0);
E 5
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
	}
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
	}
    }
    close( fd );
}

E 6
D 3
asm(".text");
asm(".even");
asm(".data");
E 3
mcount()
{
D 3
	register char			*selfpc;	/* PCC a5 */
	register unsigned short		*frompcindex;	/* PCC a4 */
E 3
I 3
	register char			*selfpc;
	register unsigned short		*frompcindex;
E 3
	register struct tostruct	*top;
	register struct tostruct	*prevtop;
	register long			toindex;

	/*
	 *	find the return address for mcount,
	 *	and the return address for mcount's caller.
	 */
D 3
	asm("	.text");		/* make sure we're in text space */
#ifdef __GNUC__
E 3
I 3
	asm(".text");		/* make sure we're in text space */
E 3
	/*
	 * selfpc = pc pushed by mcount jsr
	 */
	asm("movl a6@(4),%0" : "=r" (selfpc));
	/*
	 * frompcindex = pc pushed by jsr into self.
	 * In GCC the caller's stack frame has already been built so we
	 * have to chase a6 to find caller's raddr.
	 * NOTE: this assumes that all profiled routines use link/unlk.
	 */
	asm("movl a6@(0)@(4),%0" : "=r" (frompcindex));
D 3
#else
	asm("	movl a6@(4),a5");	/* selfpc = pc pushed by mcount jsr */
	asm("	movl a6@(8),a4");	/* frompcindex = pc pushed by jsr into
					   self, stack frame not yet built */
#endif
E 3
	/*
	 *	check that we are profiling
	 *	and that we aren't recursively invoked.
	 */
	if (profiling) {
		goto out;
	}
	profiling++;
	/*
	 *	check that frompcindex is a reasonable pc value.
	 *	for example:	signal catchers get called from the stack,
	 *			not from text space.  too bad.
	 */
	frompcindex = (unsigned short *)((long)frompcindex - (long)s_lowpc);
	if ((unsigned long)frompcindex > s_textsize) {
		goto done;
	}
	frompcindex =
	    &froms[((long)frompcindex) / (HASHFRACTION * sizeof(*froms))];
	toindex = *frompcindex;
	if (toindex == 0) {
		/*
		 *	first time traversing this arc
		 */
		toindex = ++tos[0].link;
		if (toindex >= tolimit) {
			goto overflow;
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
		 *	arc at front of chain; usual case.
		 */
		top->count++;
		goto done;
	}
	/*
	 *	have to go looking down chain for it.
	 *	top points to what we are looking at,
	 *	prevtop points to previous top.
	 *	we know it is not at the head of the chain.
	 */
	for (; /* goto done */; ) {
		if (top->link == 0) {
			/*
			 *	top is end of the chain and none of the chain
			 *	had top->selfpc == selfpc.
			 *	so we allocate a new tostruct
			 *	and link it to the head of the chain.
			 */
			toindex = ++tos[0].link;
			if (toindex >= tolimit) {
				goto overflow;
			}
			top = &tos[toindex];
			top->selfpc = selfpc;
			top->count = 1;
			top->link = *frompcindex;
			*frompcindex = toindex;
			goto done;
		}
		/*
		 *	otherwise, check the next arc on the chain.
		 */
		prevtop = top;
		top = &tos[top->link];
		if (top->selfpc == selfpc) {
			/*
			 *	there it is.
			 *	increment its count
			 *	move it to the head of the chain.
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
	/* and fall through */
out:
	return;		/* normal return restores saved registers */

overflow:
	profiling++; /* halt further profiling */
#   define	TOLIMIT	"mcount: tos overflow\n"
	write(2, TOLIMIT, sizeof(TOLIMIT));
	goto out;
D 5
}
D 3
asm(".text");
asm(".data");
E 3

/*VARARGS1*/
monitor( lowpc , highpc , buf , bufsiz , nfunc )
    char	*lowpc;
    char	*highpc;
    char	*buf;	/* declared ``short buffer[]'' in monitor(3) */
    int		bufsiz;
    int		nfunc;	/* not used, available for compatability only */
{
    register o;

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
#ifndef hp300
	s_scale = ( (float) bufsiz / o ) * SCALE_1_TO_1;
#else /* avoid floating point */
    {
	int quot = o / bufsiz;

	if (quot >= 0x10000)
		s_scale = 1;
	else if (quot >= 0x100)
		s_scale = 0x10000 / quot;
	else if (o >= 0x800000)
		s_scale = 0x1000000 / (o / (bufsiz >> 8));
	else
		s_scale = 0x1000000 / ((o << 8) / bufsiz);
    }
#endif
    else
	s_scale = SCALE_1_TO_1;
    moncontrol(1);
E 5
D 6
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
	profil(sbuf + sizeof(struct phdr), ssiz - sizeof(struct phdr),
D 3
		s_lowpc, s_scale);
E 3
I 3
		(int)s_lowpc, s_scale);
E 3
	profiling = 0;
    } else {
	/* stop */
	profil((char *)0, 0, 0, 0);
	profiling = 3;
    }
E 6
}
E 1
