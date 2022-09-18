h52962
s 00020/00014/00216
d D 8.4 95/02/14 10:39:42 cgd 34 33
c new argument passing conventions.  minor type size cleanup.
e
s 00002/00002/00228
d D 8.3 93/09/23 15:27:56 bostic 33 32
c changes for 4.4BSD-Lite requested by USL
e
s 00008/00005/00222
d D 8.2 93/09/21 07:31:39 bostic 32 31
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00225
d D 8.1 93/06/10 21:58:29 bostic 31 30
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00002/00218
d D 7.20 93/05/10 14:30:08 mckusick 30 29
c turn down clock rate when kernel is not being profiled
e
s 00003/00000/00217
d D 7.19 93/04/29 23:39:26 mckusick 29 28
c set hashfraction; enable getting gmonparam
e
s 00045/00011/00172
d D 7.18 93/04/27 15:11:12 mckusick 28 27
c move sizes into the gmonparam structure; add sysctl_doprof
e
s 00007/00006/00176
d D 7.17 92/07/10 21:04:51 torek 27 26
c ANSIfy syscall args
e
s 00000/00001/00182
d D 7.16 92/07/10 02:34:50 torek 26 25
c there is no profrate in gmonparam (only in gmonhdr)
e
s 00148/00219/00035
d D 7.15 92/07/08 00:57:56 torek 25 24
c major overhaul to profiling; new addupc_intr and addupc_task for
c interrupt and sync updates of user profiling statistics; profil system call
c moved in from sys_process.c
e
s 00001/00005/00253
d D 7.14 92/06/20 12:00:47 mckusick 24 23
c call initprofclock to start profiling clock
e
s 00004/00004/00254
d D 7.13 92/06/04 14:49:46 mckusick 23 22
c support for luna68k from Omron
e
s 00008/00000/00250
d D 7.12 92/03/18 21:59:25 mckusick 22 21
c update for new gprof header format
e
s 00000/00004/00250
d D 7.11 92/02/24 09:24:14 mckusick 21 20
c get rid of unnecessary asm's
e
s 00004/00015/00250
d D 7.10 91/05/07 09:16:30 hibler 20 19
c don't wait for initial mcount buffer,
c get rid of non-GCC hp300 code
e
s 00001/00009/00264
d D 7.9 90/06/30 19:29:19 william 19 18
c i386 support for kernel addition
e
s 00010/00001/00263
d D 7.8 90/05/25 15:07:38 mckusick 18 17
c "update from Mike Hibler at Utah"
e
s 00041/00009/00223
d D 7.7 90/05/15 14:38:07 mckusick 17 16
c new copyright; hp300 support from Utah
e
s 00001/00001/00231
d D 7.6 89/04/25 17:07:03 mckusick 16 15
c syntax error in bzero
e
s 00001/00001/00231
d D 7.5 88/01/19 15:04:42 mckusick 15 14
c must avoid asm label botch on vax too (from torek)
e
s 00003/00000/00229
d D 7.4 87/07/21 17:15:07 mckusick 14 13
c zero out malloc'ed memory before using it!
e
s 00007/00006/00222
d D 7.3 87/06/06 15:12:09 mckusick 13 12
c calloc => malloc
e
s 00080/00082/00148
d D 7.2 86/11/03 12:00:05 karels 12 11
c merge in tahoe support
e
s 00001/00001/00229
d D 7.1 86/06/05 00:06:40 mckusick 11 10
c 4.3BSD release version
e
s 00007/00001/00223
d D 6.5 85/06/08 14:41:16 mckusick 10 9
c Add copyright
e
s 00003/00003/00221
d D 6.4 84/08/29 20:21:26 bloom 9 8
c Change to includes.  no more ../h
e
s 00008/00003/00216
d D 6.3 84/08/12 12:27:57 mckusick 8 7
c use spl's rather than exclusion to single thread mcount() as this
c allows all interrupts to be accounted for.
e
s 00006/00006/00213
d D 6.2 84/07/28 12:05:44 mckusick 7 6
c allocate profiling buffers from special profiling map instead of Kernelmap
e
s 00000/00000/00219
d D 6.1 83/07/29 06:35:49 sam 6 5
c 4.2 distribution
e
s 00000/00003/00219
d D 4.5 83/07/01 02:18:59 sam 5 4
c purge #if sun's
e
s 00127/00069/00095
d D 4.4 83/01/15 16:52:22 mckusick 4 3
c new austere memory version; speed-ups for parametric calls
e
s 00007/00000/00157
d D 4.3 82/12/17 11:45:38 sam 3 2
c sun merge
e
s 00003/00003/00154
d D 4.2 82/11/13 22:51:04 sam 2 1
c merge of 4.1b and 4.1c
e
s 00157/00000/00000
d D 4.1 82/06/28 12:09:53 sam 1 0
c date and time created 82/06/28 12:09:53 by sam
e
u
U
t
T
I 1
D 10
/*	%M%	%I%	%E%	*/
E 10
I 10
D 25
/*
E 25
I 25
/*-
E 25
D 11
 * Copyright (c) 1982 Regents of the University of California.
E 11
I 11
D 31
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 11
D 17
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 17
I 17
 * All rights reserved.
E 31
I 31
 * Copyright (c) 1982, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
E 31
E 17
 *
I 17
 * %sccs.include.redist.c%
 *
E 17
 *	%W% (Berkeley) %G%
 */
E 10

I 25
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/kernel.h>
#include <sys/proc.h>
#include <sys/user.h>
I 34

#include <sys/mount.h>
#include <sys/syscallargs.h>

E 34
#include <machine/cpu.h>

E 25
I 4
D 12
/* last integrated from: gmon.c	4.10 (Berkeley) 1/14/83 */

E 12
E 4
#ifdef GPROF
D 4
#include "../h/crt0.h"
E 4
I 4
D 9
#include "../h/gprof.h"
E 4
#include "../h/param.h"
#include "../h/systm.h"
E 9
I 9
D 25
#include "gprof.h"
#include "param.h"
#include "systm.h"
I 22
#include "kernel.h"
E 22
I 13
#include "malloc.h"
E 25
I 25
#include <sys/malloc.h>
#include <sys/gmon.h>
E 25
E 13
E 9

/*
 * Froms is actually a bunch of unsigned shorts indexing tos
 */
D 4
int	profiling = 3;
u_short	*froms = 0;
struct	tostruct *tos = 0;
u_short	tolimit = 0;
E 4
I 4
D 12
int profiling = 3;
u_short *froms;
struct tostruct *tos = 0;
long tolimit = 0;
E 4
I 3
#ifdef vax
E 12
I 12
D 25
int	profiling = 3;
u_short	*froms;
struct	tostruct *tos = 0;
long	tolimit = 0;
D 19
#if defined(vax)
E 12
E 3
char	*s_lowpc = (char *)0x80000000;
I 3
#endif
D 5
#ifdef sun
char	*s_lowpc = (char *)0x4000;
#endif
E 5
E 3
D 4
extern	char etext;
char	*s_highpc = &etext;
E 4
I 4
D 12
extern char etext;
char *s_highpc = &etext;
E 12
I 12
#if defined(tahoe)
char	*s_lowpc = (char *)0xc0000000;
#endif
I 17
#if defined(hp300)
char	*s_lowpc = (char *)0x00000000;
#endif
E 19
I 19
char	*s_lowpc = (char *)KERNBASE;
E 19
E 17
extern	char etext;
char	*s_highpc = &etext;
E 12
E 4
u_long	s_textsize = 0;
D 4
int	ssiz;
E 4
I 4
D 12
int ssiz;
E 12
I 12
int	ssiz;
E 12
E 4
u_short	*sbuf;
E 25
I 25
struct gmonparam _gmonparam = { GMON_PROF_OFF };

E 25
D 28
u_short	*kcount;
E 28
I 25
extern char etext[];
E 25

I 34
void
E 34
kmstartup()
{
D 4
	u_long	limit;
E 4
I 4
D 12
	u_long	fromssize, tossize;
E 12
I 12
D 25
	u_long fromssize, tossize;
E 12
E 4

E 25
I 25
	char *cp;
D 28
	int fsize, tsize, ksize;
E 28
	struct gmonparam *p = &_gmonparam;
E 25
I 4
	/*
D 12
	 *	round lowpc and highpc to multiples of the density we're using
	 *	so the rest of the scaling (here and in gprof) stays in ints.
E 12
I 12
	 * Round lowpc and highpc to multiples of the density we're using
	 * so the rest of the scaling (here and in gprof) stays in ints.
E 12
	 */
D 25
	s_lowpc = (char *)
D 12
	    ROUNDDOWN((unsigned)s_lowpc, HISTFRACTION*sizeof(HISTCOUNTER));
E 12
I 12
	    ROUNDDOWN((unsigned)s_lowpc, HISTFRACTION*sizeof (HISTCOUNTER));
E 12
	s_highpc = (char *)
D 12
	    ROUNDUP((unsigned)s_highpc, HISTFRACTION*sizeof(HISTCOUNTER));
E 12
I 12
	    ROUNDUP((unsigned)s_highpc, HISTFRACTION*sizeof (HISTCOUNTER));
E 12
E 4
	s_textsize = s_highpc - s_lowpc;
D 4
	ssiz = s_textsize + sizeof(struct phdr);
E 4
	printf("Profiling kernel, s_textsize=%d [%x..%x]\n",
		s_textsize, s_lowpc, s_highpc);
I 4
D 12
	ssiz = (s_textsize / HISTFRACTION) + sizeof(struct phdr);
E 12
I 12
	ssiz = (s_textsize / HISTFRACTION) + sizeof (struct phdr);
E 12
E 4
D 2
	sbuf = (u_short *)wmemall(vmemall, ssiz);
E 2
I 2
D 7
	sbuf = (u_short *)wmemall(memall, ssiz);
E 7
I 7
D 13
	sbuf = (u_short *)calloc(ssiz);
E 13
I 13
	sbuf = (u_short *)malloc(ssiz, M_GPROF, M_WAITOK);
E 13
E 7
E 2
	if (sbuf == 0) {
		printf("No space for monitor buffer(s)\n");
E 25
I 25
	p->lowpc = ROUNDDOWN(KERNBASE, HISTFRACTION * sizeof(HISTCOUNTER));
	p->highpc = ROUNDUP((u_long)etext, HISTFRACTION * sizeof(HISTCOUNTER));
	p->textsize = p->highpc - p->lowpc;
D 26
	p->profrate = profhz;
E 26
	printf("Profiling kernel, textsize=%d [%x..%x]\n",
	       p->textsize, p->lowpc, p->highpc);
D 28
	ksize = p->textsize / HISTFRACTION;
	fsize = p->textsize / HASHFRACTION;
E 28
I 28
	p->kcountsize = p->textsize / HISTFRACTION;
I 29
	p->hashfraction = HASHFRACTION;
E 29
	p->fromssize = p->textsize / HASHFRACTION;
E 28
	p->tolimit = p->textsize * ARCDENSITY / 100;
	if (p->tolimit < MINARCS)
		p->tolimit = MINARCS;
	else if (p->tolimit > MAXARCS)
		p->tolimit = MAXARCS;
D 28
	tsize = p->tolimit * sizeof(struct tostruct);
	cp = (char *)malloc(ksize + fsize + tsize, M_GPROF, M_NOWAIT);
E 28
I 28
	p->tossize = p->tolimit * sizeof(struct tostruct);
	cp = (char *)malloc(p->kcountsize + p->fromssize + p->tossize,
	    M_GPROF, M_NOWAIT);
E 28
	if (cp == 0) {
		printf("No memory for profiling.\n");
E 25
		return;
	}
I 14
D 25
	bzero(sbuf, ssiz);
E 14
D 12
	blkclr((caddr_t)sbuf, ssiz);
E 12
D 2
	froms = (u_short *)wmemall(vmemall, s_textsize);
E 2
I 2
D 4
	froms = (u_short *)wmemall(memall, s_textsize);
E 4
I 4
	fromssize = s_textsize / HASHFRACTION;
D 7
	froms = (u_short *)wmemall(memall, fromssize);
E 7
I 7
D 13
	froms = (u_short *)calloc(fromssize);
E 13
I 13
D 20
	froms = (u_short *)malloc(fromssize, M_GPROF, M_WAITOK);
E 20
I 20
	froms = (u_short *)malloc(fromssize, M_GPROF, M_NOWAIT);
E 20
E 13
E 7
E 4
E 2
	if (froms == 0) {
		printf("No space for monitor buffer(s)\n");
D 7
		wmemfree(sbuf, ssiz);
E 7
I 7
D 13
		cfreemem(sbuf, ssiz);
E 13
I 13
		free(sbuf, M_GPROF);
E 13
E 7
		sbuf = 0;
		return;
	}
I 14
D 16
	bzero(froms, fromsize);
E 16
I 16
	bzero(froms, fromssize);
E 16
E 14
D 4
	blkclr((caddr_t)froms, s_textsize);
D 2
	tos = (struct tostruct *)wmemall(vmemall, s_textsize);
E 2
I 2
	tos = (struct tostruct *)wmemall(memall, s_textsize);
E 4
I 4
D 12
	blkclr((caddr_t)froms, fromssize);
E 12
	tolimit = s_textsize * ARCDENSITY / 100;
D 12
	if (tolimit < MINARCS) {
E 12
I 12
	if (tolimit < MINARCS)
E 12
		tolimit = MINARCS;
D 12
	} else if (tolimit > 65534) {
		tolimit = 65534;
	}
	tossize = tolimit * sizeof(struct tostruct);
E 12
I 12
	else if (tolimit > (0xffff - 1))
		tolimit = 0xffff - 1;
	tossize = tolimit * sizeof (struct tostruct);
E 12
D 7
	tos = (struct tostruct *)wmemall(memall, tossize);
E 7
I 7
D 13
	tos = (struct tostruct *)calloc(tossize);
E 13
I 13
	tos = (struct tostruct *)malloc(tossize, M_GPROF, M_WAITOK);
E 13
E 7
E 4
E 2
	if (tos == 0) {
		printf("No space for monitor buffer(s)\n");
D 7
		wmemfree(sbuf, ssiz);
E 7
I 7
D 12
		cfreemem(sbuf, ssiz);
E 7
		sbuf = 0;
D 4
		wmemfree(froms, s_textsize);
E 4
I 4
D 7
		wmemfree(froms, fromssize);
E 7
I 7
		cfreemem(froms, fromssize);
E 7
E 4
		froms = 0;
E 12
I 12
D 13
		cfreemem(sbuf, ssiz), sbuf = 0;
		cfreemem(froms, fromssize), froms = 0;
E 13
I 13
		free(sbuf, M_GPROF), sbuf = 0;
		free(froms, M_GPROF), froms = 0;
E 13
E 12
		return;
	}
I 14
	bzero(tos, tossize);
E 14
D 4
	blkclr((caddr_t)tos, s_textsize);
E 4
I 4
D 12
	blkclr((caddr_t)tos, tossize);
E 12
E 4
	tos[0].link = 0;
D 4
	limit = s_textsize / sizeof(struct tostruct);
	/*
	 * Tolimit is what mcount checks to see if
	 * all the data structures are ready!!!
	 * Make sure it won't overflow.
	 */
	tolimit = limit > 65534 ? 65534 : limit;
E 4
	((struct phdr *)sbuf)->lpc = s_lowpc;
	((struct phdr *)sbuf)->hpc = s_highpc;
	((struct phdr *)sbuf)->ncnt = ssiz;
I 22
	((struct phdr *)sbuf)->version = GMONVERSION;
E 25
I 25
D 28
	bzero(cp, ksize + tsize + fsize);
E 28
I 28
	bzero(cp, p->kcountsize + p->tossize + p->fromssize);
E 28
	p->tos = (struct tostruct *)cp;
D 28
	cp += tsize;
	kcount = (u_short *)cp;
	cp += ksize;
E 28
I 28
	cp += p->tossize;
	p->kcount = (u_short *)cp;
	cp += p->kcountsize;
E 28
	p->froms = (u_short *)cp;
E 25
D 24
#ifdef PROFTIMER
	initprofclock();
E 24
I 24
D 30
	startprofclock(&proc0);
E 30
E 24
D 25
	((struct phdr *)sbuf)->profrate = profhz;
D 24
#else
	((struct phdr *)sbuf)->profrate = hz;
#endif
E 24
E 22
D 12
	kcount = (u_short *)(((int)sbuf) + sizeof(struct phdr));
E 12
I 12
	kcount = (u_short *)(((int)sbuf) + sizeof (struct phdr));
E 25
E 12
D 17
#ifdef notdef
I 4
	/*
D 12
	 *	profiling is what mcount checks to see if
	 *	all the data structures are ready!!!
E 12
I 12
	 * Profiling is what mcount checks to see if
	 * all the data structures are ready!!!
E 12
	 */
E 4
	profiling = 0;		/* patch by hand when you're ready */
#endif
E 17
}
I 25
D 28
#endif
E 28
I 28

/*
 * Return kernel profiling information.
 */
I 34
int
E 34
sysctl_doprof(name, namelen, oldp, oldlenp, newp, newlen, p)
	int *name;
	u_int namelen;
	void *oldp;
	size_t *oldlenp;
	void *newp;
	size_t newlen;
{
	struct gmonparam *gp = &_gmonparam;
I 30
	int error;
E 30

	/* all sysctl names at this level are terminal */
	if (namelen != 1)
		return (ENOTDIR);		/* overloaded */

	switch (name[0]) {
	case GPROF_STATE:
D 30
		return (sysctl_int(oldp, oldlenp, newp, newlen, &gp->state));
E 30
I 30
		error = sysctl_int(oldp, oldlenp, newp, newlen, &gp->state);
		if (error)
			return (error);
		if (gp->state == GMON_PROF_OFF)
			stopprofclock(&proc0);
		else
			startprofclock(&proc0);
		return (0);
E 30
	case GPROF_COUNT:
		return (sysctl_struct(oldp, oldlenp, newp, newlen,
		    gp->kcount, gp->kcountsize));
	case GPROF_FROMS:
		return (sysctl_struct(oldp, oldlenp, newp, newlen,
		    gp->froms, gp->fromssize));
	case GPROF_TOS:
		return (sysctl_struct(oldp, oldlenp, newp, newlen,
		    gp->tos, gp->tossize));
I 29
	case GPROF_GMONPARAM:
		return (sysctl_rdstruct(oldp, oldlenp, newp, gp, sizeof *gp));
E 29
	default:
		return (EOPNOTSUPP);
	}
	/* NOTREACHED */
}
#endif /* GPROF */
E 28
E 25

I 3
D 12
#ifdef vax
E 12
E 3
/*
I 17
D 20
 * Special, non-profiled versions
 */
D 18
#if defined(hp300)
E 18
I 18
#if defined(hp300) && !defined(__GNUC__)
E 18
#define splhigh	_splhigh
#define splx	_splx
#endif

/*
E 20
E 17
D 12
 * This routine is massaged so that it may be jsb'ed to
E 12
I 12
D 25
 * This routine is massaged so that it may be jsb'ed to on vax.
E 25
I 25
 * Profiling system call.
 *
 * The scale factor is a fixed point number with 16 bits of fraction, so that
 * 1.0 is represented as 0x10000.  A scale factor of 0 turns off profiling.
E 25
E 12
 */
I 27
D 34
struct profil_args {
D 32
	caddr_t	buf;
	u_int	bufsize;
E 32
I 32
	caddr_t	samples;
	u_int	size;
E 32
	u_int	offset;
	u_int	scale;
};
E 34
E 27
D 4
asm("#define _mcount mcount");
E 4
I 4
D 21
asm(".text");
asm("#the beginning of mcount()");
asm(".data");
E 21
E 4
D 25
mcount()
E 25
I 25
/* ARGSUSED */
I 34
int
E 34
profil(p, uap, retval)
	struct proc *p;
D 27
	register struct args {
		caddr_t	buf;
		u_int	bufsize;
		u_int	offset;
		u_int	scale;
	} *uap;
E 27
I 27
D 34
	register struct profil_args *uap;
E 27
	int *retval;
E 34
I 34
	register struct profil_args /* {
		syscallarg(caddr_t) samples;
		syscallarg(u_int) size;
		syscallarg(u_int) offset;
		syscallarg(u_int) scale;
	} */ *uap;
	register_t *retval;
E 34
E 25
{
D 4
	register char *selfpc;		/* r11 */
	register u_short *frompcindex;	/* r10 */
	register struct tostruct *top;	/* r9 */
E 4
I 4
D 12
	register char			*selfpc;	/* r11 => r5 */
	register unsigned short		*frompcindex;	/* r10 => r4 */
	register struct tostruct	*top;		/* r9  => r3 */
	register struct tostruct	*prevtop;	/* r8  => r2 */
	register long			toindex;	/* r7  => r1 */
E 12
I 12
D 25
	register char *selfpc;			/* r11 => r5 */
	register u_short *frompcindex;		/* r10 => r4 */
	register struct tostruct *top;		/* r9  => r3 */
	register struct tostruct *prevtop;	/* r8  => r2 */
	register long toindex;			/* r7  => r1 */
E 12
I 8
	static int s;
E 25
I 25
	register struct uprof *upp;
	int s;
E 25
E 8
E 4

I 12
D 21
	asm("	.text");		/* make sure we're in text space */
E 21
D 25
	/*
	 * Check that we are profiling.
	 */
	if (profiling)
		goto out;
	/*
	 * Find the return address for mcount,
	 * and the return address for mcount's caller.
	 */
E 12
D 4
	asm("	forgot to run ex script on gcrt0.s");
	asm("#define r11 r5");
	asm("#define r10 r4");
	asm("#define r9 r3");
E 4
#ifdef lint
D 4
	selfpc = (char *) 0;
E 4
I 4
	selfpc = (char *)0;
E 4
	frompcindex = 0;
D 12
#else not lint
	/*
D 4
	 * Find the return address for mcount,
	 * and the return address for mcount's caller.
E 4
I 4
	 *	find the return address for mcount,
	 *	and the return address for mcount's caller.
E 4
	 */
I 4
	asm("	.text");		/* make sure we're in text space */
E 12
I 12
#else
I 15
	;				/* avoid label botch */
I 17
#ifdef __GNUC__
E 17
E 15
#if defined(vax)
I 17
	Fix Me!!
#endif
#if defined(tahoe)
	Fix Me!!
#endif
D 23
#if defined(hp300)
E 23
I 23
#if defined(hp300) || defined(luna68k)
E 23
	/*
	 * selfpc = pc pushed by mcount jsr,
	 * frompcindex = pc pushed by jsr into self.
	 * In GCC the caller's stack frame has already been built so we
	 * have to chase a6 to find caller's raddr.  This assumes that all
	 * routines we are profiling were built with GCC and that all
	 * profiled routines use link/unlk.
	 */
	asm("movl a6@(4),%0" : "=r" (selfpc));
	asm("movl a6@(0)@(4),%0" : "=r" (frompcindex));
#endif
#else
#if defined(vax)
E 17
E 12
E 4
	asm("	movl (sp), r11");	/* selfpc = ... (jsb frame) */
	asm("	movl 16(fp), r10");	/* frompcindex =     (calls frame) */
D 12
#endif not lint
E 12
I 12
#endif
#if defined(tahoe)
D 15
	;				/* avoid label botch */
E 15
	asm("	movl -8(fp),r12");	/* selfpc = callf frame */
	asm("	movl (fp),r11");
	asm("	movl -8(r11),r11");	/* frompcindex = 1 callf frame back */
#endif
I 17
D 23
#if defined(hp300)
E 23
I 23
#if defined(hp300) || defined(luna68k)
E 23
D 20
	asm("	.text");		/* make sure we're in text space */
	asm("	movl a6@(4),a5");	/* selfpc = pc pushed by mcount jsr */
	asm("	movl a6@(8),a4");	/* frompcindex = pc pushed by jsr into
					   self, stack frame not yet built */
E 20
I 20
	Fix Me!!
E 20
E 17
#endif
I 17
#endif /* not __GNUC__ */
#endif /* not lint */
E 17
E 12
	/*
D 4
	 * Check that we are profiling
	 * and that we aren't recursively invoked.
E 4
I 4
D 12
	 *	check that we are profiling
E 12
I 12
	 * Insure that we cannot be recursively invoked.
	 * this requires that splhigh() and splx() below
	 * do NOT call mcount!
E 12
D 8
	 *	and that we aren't recursively invoked.
E 8
E 4
	 */
I 18
D 20
#if defined(hp300) && defined(__GNUC__)
E 20
I 20
D 23
#if defined(hp300)
E 23
I 23
#if defined(hp300) || defined(luna68k)
E 23
E 20
	asm("movw	sr,%0" : "=g" (s));
	asm("movw	#0x2700,sr");
#else
E 18
D 4
	if (tolimit == 0)
E 4
I 4
D 12
	if (profiling) {
E 4
		goto out;
D 4
	if (profiling)
		goto out;
E 4
I 4
	}
E 4
D 8
	profiling++;
E 8
	/*
I 8
	 *	insure that we cannot be recursively invoked.
	 *	this requires that splhigh() and splx() below
	 *	do NOT call mcount!
	 */
E 12
	s = splhigh();
I 18
#endif
E 18
	/*
E 8
D 4
	 * Check that frompcindex is a reasonable pc value.
	 * For example:	signal catchers get called from the stack,
	 * 		not from text space.  too bad.
E 4
I 4
D 12
	 *	check that frompcindex is a reasonable pc value.
	 *	for example:	signal catchers get called from the stack,
	 *			not from text space.  too bad.
E 12
I 12
	 * Check that frompcindex is a reasonable pc value.
	 * For example:	signal catchers get called from the stack,
	 *	not from text space.  too bad.
E 12
E 4
	 */
D 4
	frompcindex = (u_short *)((long)frompcindex - (long)s_lowpc);
	if ((u_long)frompcindex > s_textsize)
E 4
I 4
D 12
	frompcindex = (unsigned short *)((long)frompcindex - (long)s_lowpc);
	if ((unsigned long)frompcindex > s_textsize) {
E 12
I 12
	frompcindex = (u_short *)((long)frompcindex - (long)s_lowpc);
	if ((u_long)frompcindex > s_textsize)
E 12
E 4
		goto done;
D 4
	frompcindex = &froms[((long)frompcindex) >> 1];
	if (*frompcindex != 0)
		top = &tos[*frompcindex];
	else {
		*frompcindex = ++tos[0].link;
		if (*frompcindex >= tolimit)
E 4
I 4
D 12
	}
E 12
	frompcindex =
D 12
	    &froms[((long)frompcindex) / (HASHFRACTION * sizeof(*froms))];
E 12
I 12
	    &froms[((long)frompcindex) / (HASHFRACTION * sizeof (*froms))];
E 12
	toindex = *frompcindex;
	if (toindex == 0) {
		/*
D 12
		 *	first time traversing this arc
E 12
I 12
		 * First time traversing this arc
E 12
		 */
		toindex = ++tos[0].link;
D 12
		if (toindex >= tolimit) {
E 12
I 12
		if (toindex >= tolimit)
E 12
E 4
			goto overflow;
D 4
		top = &tos[*frompcindex];
E 4
I 4
D 12
		}
E 12
		*frompcindex = toindex;
		top = &tos[toindex];
E 4
		top->selfpc = selfpc;
D 4
		top->count = 0;
E 4
I 4
		top->count = 1;
E 4
		top->link = 0;
I 4
		goto done;
E 25
I 25
D 34
	if (uap->scale > (1 << 16))
E 34
I 34
	if (SCARG(uap, scale) > (1 << 16))
E 34
		return (EINVAL);
D 34
	if (uap->scale == 0) {
E 34
I 34
	if (SCARG(uap, scale) == 0) {
E 34
		stopprofclock(p);
		return (0);
E 25
E 4
	}
D 4
	for (; /* break */; top = &tos[top->link]) {
E 4
I 4
D 25
	top = &tos[toindex];
	if (top->selfpc == selfpc) {
		/*
D 12
		 *	arc at front of chain; usual case.
E 12
I 12
		 * Arc at front of chain; usual case.
E 12
		 */
		top->count++;
		goto done;
E 25
I 25
	upp = &p->p_stats->p_prof;
D 32
	s = splstatclock(); /* block profile interrupts while changing state */
	upp->pr_base = uap->buf;
	upp->pr_size = uap->bufsize;
E 32
I 32

	/* Block profile interrupts while changing state. */
	s = splstatclock();
E 32
D 34
	upp->pr_off = uap->offset;
	upp->pr_scale = uap->scale;
I 32
	upp->pr_base = uap->samples;
	upp->pr_size = uap->size;
E 34
I 34
	upp->pr_off = SCARG(uap, offset);
	upp->pr_scale = SCARG(uap, scale);
	upp->pr_base = SCARG(uap, samples);
	upp->pr_size = SCARG(uap, size);
E 34
E 32
	startprofclock(p);
	splx(s);
I 32

E 32
	return (0);
}

/*
 * Scale is a fixed-point number with the binary point 16 bits
 * into the value, and is <= 1.0.  pc is at most 32 bits, so the
 * intermediate result is at most 48 bits.
 */
#define	PC_TO_INDEX(pc, prof) \
	((int)(((u_quad_t)((pc) - (prof)->pr_off) * \
	    (u_quad_t)((prof)->pr_scale)) >> 16) & ~1)

/*
 * Collect user-level profiling statistics; called on a profiling tick,
 * when a process is running in user-mode.  This routine may be called
 * from an interrupt context.  We try to update the user profiling buffers
 * cheaply with fuswintr() and suswintr().  If that fails, we revert to
 * an AST that will vector us to trap() with a context in which copyin
 * and copyout will work.  Trap will then call addupc_task().
 *
 * Note that we may (rarely) not get around to the AST soon enough, and
 * lose profile ticks when the next tick overwrites this one, but in this
 * case the system is overloaded and the profile is probably already
 * inaccurate.
 */
void
addupc_intr(p, pc, ticks)
	register struct proc *p;
	register u_long pc;
	u_int ticks;
{
	register struct uprof *prof;
	register caddr_t addr;
	register u_int i;
	register int v;

	if (ticks == 0)
		return;
	prof = &p->p_stats->p_prof;
	if (pc < prof->pr_off ||
	    (i = PC_TO_INDEX(pc, prof)) >= prof->pr_size)
		return;			/* out of range; ignore */

	addr = prof->pr_base + i;
	if ((v = fuswintr(addr)) == -1 || suswintr(addr, v + ticks) == -1) {
		prof->pr_addr = pc;
		prof->pr_ticks = ticks;
		need_proftick(p);
E 25
	}
D 25
	/*
D 12
	 *	have to go looking down chain for it.
	 *	top points to what we are looking at,
	 *	prevtop points to previous top.
	 *	we know it is not at the head of the chain.
E 12
I 12
	 * Have to go looking down chain for it.
	 * Top points to what we are looking at,
	 * prevtop points to previous top.
	 * We know it is not at the head of the chain.
E 12
	 */
	for (; /* goto done */; ) {
		if (top->link == 0) {
			/*
D 12
			 *	top is end of the chain and none of the chain
			 *	had top->selfpc == selfpc.
			 *	so we allocate a new tostruct
			 *	and link it to the head of the chain.
E 12
I 12
			 * Top is end of the chain and none of the chain
			 * had top->selfpc == selfpc.
			 * So we allocate a new tostruct
			 * and link it to the head of the chain.
E 12
			 */
			toindex = ++tos[0].link;
D 12
			if (toindex >= tolimit) {
E 12
I 12
			if (toindex >= tolimit)
E 12
				goto overflow;
D 12
			}
E 12
			top = &tos[toindex];
			top->selfpc = selfpc;
			top->count = 1;
			top->link = *frompcindex;
			*frompcindex = toindex;
			goto done;
		}
		/*
D 12
		 *	otherwise, check the next arc on the chain.
E 12
I 12
		 * Otherwise, check the next arc on the chain.
E 12
		 */
		prevtop = top;
		top = &tos[top->link];
E 4
		if (top->selfpc == selfpc) {
I 4
			/*
D 12
			 *	there it is.
			 *	increment its count
			 *	move it to the head of the chain.
E 12
I 12
			 * There it is, increment its count and
			 * move it to the head of the chain.
E 12
			 */
E 4
			top->count++;
D 4
			break;
E 4
I 4
			toindex = prevtop->link;
			prevtop->link = top->link;
			top->link = *frompcindex;
			*frompcindex = toindex;
			goto done;
E 4
		}
E 25
I 25
}
E 25
D 4
		if (top->link != 0)
			continue;
		top->link = ++tos[0].link;
		if (top->link >= tolimit)
			goto overflow;
		top = &tos[top->link];
		top->selfpc = selfpc;
		top->count = 1;
		top->link = 0;
		break;
E 4
I 4

I 25
/*
 * Much like before, but we can afford to take faults here.  If the
 * update fails, we simply turn off profiling.
 */
void
addupc_task(p, pc, ticks)
	register struct proc *p;
	register u_long pc;
	u_int ticks;
{
	register struct uprof *prof;
	register caddr_t addr;
	register u_int i;
	u_short v;

D 33
	/* testing SPROFIL may be unnecessary, but is certainly safe */
	if ((p->p_flag & SPROFIL) == 0 || ticks == 0)
E 33
I 33
	/* Testing P_PROFIL may be unnecessary, but is certainly safe. */
	if ((p->p_flag & P_PROFIL) == 0 || ticks == 0)
E 33
		return;

	prof = &p->p_stats->p_prof;
	if (pc < prof->pr_off ||
	    (i = PC_TO_INDEX(pc, prof)) >= prof->pr_size)
		return;

	addr = prof->pr_base + i;
	if (copyin(addr, (caddr_t)&v, sizeof(v)) == 0) {
		v += ticks;
		if (copyout((caddr_t)&v, addr, sizeof(v)) == 0)
			return;
E 25
E 4
	}
D 25
done:
I 18
D 20
#if defined(hp300) && defined(__GNUC__)
E 20
I 20
D 23
#if defined(hp300)
E 23
I 23
#if defined(hp300) || defined(luna68k)
E 23
E 20
	asm("movw	%0,sr" : : "g" (s));
#else
E 18
D 8
	profiling--;
E 8
I 8
	splx(s);
I 18
#endif
E 18
E 8
	/* and fall through */
out:
I 12
#if defined(vax)
E 12
	asm("	rsb");
D 4
	asm("#undef r11");
	asm("#undef r10");
	asm("#undef r9");
	asm("#undef _mcount");
E 4
D 12

E 12
I 12
#endif
	return;
E 12
overflow:
D 4
	tolimit = 0;
E 4
I 4
	profiling = 3;
E 4
	printf("mcount: tos overflow\n");
	goto out;
E 25
I 25
	stopprofclock(p);
E 25
}
I 3
D 4
#endif
E 4
I 4
D 25
asm(".text");
asm("#the end of mcount()");
asm(".data");
D 12
#endif vax
E 4
E 3
#endif GPROF
E 12
I 12
#endif
E 25
E 12
E 1
