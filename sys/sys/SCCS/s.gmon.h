h20037
s 00003/00003/00130
d D 8.2 94/01/04 16:16:29 bostic 14 13
c A foolish consistency is the hobgoblin of little minds. -- Emerson
e
s 00002/00002/00131
d D 8.1 93/06/02 19:53:38 bostic 13 12
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00004/00127
d D 7.7 93/04/29 23:38:47 mckusick 12 10
c add hashfraction to gmonparam; enable getting of gmonparam
e
s 00007/00004/00127
d R 7.7 93/04/29 23:25:27 mckusick 11 10
c add ability to get lowpc and hashfraction
e
s 00011/00000/00120
d D 7.6 93/04/20 17:22:24 mckusick 10 9
c add kcount and structure sizes to gmon structure; add sysctl definitions
e
s 00001/00001/00119
d D 7.5 92/07/10 15:44:43 mckusick 9 8
c fix up comment
e
s 00090/00065/00030
d D 7.4 92/06/17 16:00:51 mckusick 8 7
c update for new profiling structure
e
s 00007/00000/00088
d D 7.3 92/03/25 15:51:40 mckusick 7 6
c extended gprof header
e
s 00005/00004/00083
d D 7.2 91/02/15 14:30:22 bostic 6 5
c add Berkeley specific copyright notice
e
s 00001/00001/00086
d D 7.1 86/06/04 23:23:25 mckusick 5 4
c 4.3BSD release version
e
s 00007/00001/00080
d D 6.2 85/06/08 14:58:43 mckusick 4 3
c Add copyright
e
s 00000/00000/00081
d D 6.1 83/07/29 06:12:36 sam 3 2
c 4.2 distribution
e
s 00071/00014/00010
d D 4.2 83/01/15 16:50:07 mckusick 2 1
c new austere memory version
e
s 00024/00000/00000
d D 4.1 82/06/27 14:56:56 sam 1 0
c date and time created 82/06/27 14:56:56 by sam
e
u
U
t
T
I 1
D 4
/*	%M%	%I%	%E%	*/
E 4
I 4
D 6
/*
D 5
 * Copyright (c) 1982 Regents of the University of California.
E 5
I 5
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 5
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 6
I 6
/*-
D 8
 * Copyright (c) 1982, 1986 The Regents of the University of California.
E 8
I 8
D 13
 * Copyright (c) 1982, 1986, 1992 The Regents of the University of California.
E 8
 * All rights reserved.
E 13
I 13
 * Copyright (c) 1982, 1986, 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 13
 *
 * %sccs.include.redist.c%
E 6
 *
 *	%W% (Berkeley) %G%
 */
E 4

I 8
D 14
#ifndef _GMON_H_
#define _GMON_H_
E 14
I 14
#ifndef _SYS_GMON_H_
#define _SYS_GMON_H_
E 14

#include <machine/profile.h>

E 8
I 7
/*
D 8
 * This structure must agree with that defined in lib/csu.gmon/gmon.h
E 8
I 8
 * Structure prepended to gmon.out profiling data file.
E 8
 */
E 7
D 8
struct phdr {
D 2
	char	*lpc;
	char	*hpc;
	int	ncnt;
E 2
I 2
    char	*lpc;
    char	*hpc;
    int		ncnt;
I 7
    int		version;
    int		profrate;
    int		spare[3];
E 8
I 8
struct gmonhdr {
	u_long	lpc;		/* base pc address of sample buffer */
	u_long	hpc;		/* max pc address of sampled buffer */
D 9
	int	ncnt;		/* size of sample buffer (not including hdr) */
E 9
I 9
	int	ncnt;		/* size of sample buffer (plus this header) */
E 9
	int	version;	/* version number */
	int	profrate;	/* profiling clock rate */
	int	spare[3];	/* reserved */
E 8
E 7
E 2
};
I 7
#define GMONVERSION	0x00051879
E 7

I 2
D 8
    /*
     *	histogram counters are unsigned shorts (according to the kernel).
     */
E 8
I 8
/*
 * histogram counters are unsigned shorts (according to the kernel).
 */
E 8
#define	HISTCOUNTER	unsigned short

D 8
    /*
     *	fraction of text space to allocate for histogram counters
     *	here, 1/2
     */
E 8
I 8
/*
 * fraction of text space to allocate for histogram counters here, 1/2
 */
E 8
#define	HISTFRACTION	2

D 8
    /*
     *	Fraction of text space to allocate for from hash buckets.
     *	The value of HASHFRACTION is based on the minimum number of bytes
     *	of separation between two subroutine call points in the object code.
     *	Given MIN_SUBR_SEPARATION bytes of separation the value of
     *	HASHFRACTION is calculated as:
     *
     *		HASHFRACTION = MIN_SUBR_SEPARATION / (2 * sizeof(short) - 1);
     *
     *	For the VAX, the shortest two call sequence is:
     *
     *		calls	$0,(r0)
     *		calls	$0,(r0)
     *
     *	which is separated by only three bytes, thus HASHFRACTION is 
     *	calculated as:
     *
     *		HASHFRACTION = 3 / (2 * 2 - 1) = 1
     *
     *	Note that the division above rounds down, thus if MIN_SUBR_FRACTION
     *	is less than three, this algorithm will not work!
     *
     *	NB: for the kernel we assert that the shortest two call sequence is:
     *
     *		calls	$0,_name
     *		calls	$0,_name
     *
     *	which is separated by seven bytes, thus HASHFRACTION is calculated as:
     *
     *		HASHFRACTION = 7 / (2 * 2 - 1) = 2
     */
E 8
I 8
/*
 * Fraction of text space to allocate for from hash buckets.
 * The value of HASHFRACTION is based on the minimum number of bytes
 * of separation between two subroutine call points in the object code.
 * Given MIN_SUBR_SEPARATION bytes of separation the value of
 * HASHFRACTION is calculated as:
 *
 *	HASHFRACTION = MIN_SUBR_SEPARATION / (2 * sizeof(short) - 1);
 *
 * For example, on the VAX, the shortest two call sequence is:
 *
 *	calls	$0,(r0)
 *	calls	$0,(r0)
 *
 * which is separated by only three bytes, thus HASHFRACTION is 
 * calculated as:
 *
 *	HASHFRACTION = 3 / (2 * 2 - 1) = 1
 *
 * Note that the division above rounds down, thus if MIN_SUBR_FRACTION
 * is less than three, this algorithm will not work!
 *
 * In practice, however, call instructions are rarely at a minimal 
 * distance.  Hence, we will define HASHFRACTION to be 2 across all
 * architectures.  This saves a reasonable amount of space for 
 * profiling data structures without (in practice) sacrificing
 * any granularity.
 */
E 8
#define	HASHFRACTION	2

D 8
    /*
     *	percent of text space to allocate for tostructs
     *	with a minimum.
     */
E 8
I 8
/*
 * percent of text space to allocate for tostructs with a minimum.
 */
E 8
#define ARCDENSITY	2
#define MINARCS		50
I 8
#define MAXARCS		((1 << (8 * sizeof(HISTCOUNTER))) - 2)
E 8

E 2
struct tostruct {
D 2
	char	*selfpc;
	long	count;
	u_short	link;
E 2
I 2
D 8
    char		*selfpc;
    long		count;
    unsigned short	link;
E 8
I 8
	u_long	selfpc;
	long	count;
	u_short	link;
	u_short pad;
E 8
E 2
};

D 2
/*
 * a raw arc,
 *	with pointers to the calling site and the called site
 *	and a count.
 */
E 2
I 2
D 8
    /*
     *	a raw arc,
     *	    with pointers to the calling site and the called site
     *	    and a count.
     */
E 8
I 8
/*
 * a raw arc, with pointers to the calling site and 
 * the called site and a count.
 */
E 8
E 2
struct rawarc {
D 2
	u_long	raw_frompc;
	u_long	raw_selfpc;
	long	raw_count;
E 2
I 2
D 8
    unsigned long	raw_frompc;
    unsigned long	raw_selfpc;
    long		raw_count;
E 8
I 8
	u_long	raw_frompc;
	u_long	raw_selfpc;
	long	raw_count;
E 8
E 2
};
I 2

D 8
    /*
     *	general rounding functions.
     */
E 8
I 8
/*
 * general rounding functions.
 */
E 8
#define ROUNDDOWN(x,y)	(((x)/(y))*(y))
#define ROUNDUP(x,y)	((((x)+(y)-1)/(y))*(y))
I 8

/*
 * The profiling data structures are housed in this structure.
 */
struct gmonparam {
	int		state;
I 10
	u_short		*kcount;
	u_long		kcountsize;
E 10
	u_short		*froms;
I 10
	u_long		fromssize;
E 10
	struct tostruct	*tos;
I 10
	u_long		tossize;
E 10
	long		tolimit;
	u_long		lowpc;
	u_long		highpc;
	u_long		textsize;
I 12
	u_long		hashfraction;
E 12
};
extern struct gmonparam _gmonparam;

/*
 * Possible states of profiling.
 */
#define	GMON_PROF_ON	0
#define	GMON_PROF_BUSY	1
#define	GMON_PROF_ERROR	2
#define	GMON_PROF_OFF	3

I 10
/*
 * Sysctl definitions for extracting profiling information from the kernel.
 */
D 12
#define	GPROF_STATE	0	/* profiling enabling variable */
#define	GPROF_COUNT	1	/* profile tick count buffer */
#define	GPROF_FROMS	2	/* from location hash bucket */
#define	GPROF_TOS	3	/* destination/count structure */
E 12
I 12
#define	GPROF_STATE	0	/* int: profiling enabling variable */
#define	GPROF_COUNT	1	/* struct: profile tick count buffer */
#define	GPROF_FROMS	2	/* struct: from location hash bucket */
#define	GPROF_TOS	3	/* struct: destination/count structure */
#define	GPROF_GMONPARAM	4	/* struct: profiling parameters (see above) */
E 12
E 10
D 14
#endif
E 14
I 14
#endif /* !_SYS_GMON_H_ */
E 14
E 8
E 2
E 1
