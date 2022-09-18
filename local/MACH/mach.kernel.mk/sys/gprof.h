/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	gprof.h,v $
 * Revision 2.5  89/05/30  10:43:12  rvb
 * 	Added mods for Mips.  Included uniqtime(), for Mips only.
 * 	[89/05/30  08:35:15  rvb]
 * 
 * Revision 2.4  89/03/09  22:04:43  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  17:53:59  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.2  89/01/23  22:26:03  af
 * 	Added mods for Mips.
 * 	[89/01/07            af]
 * 
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)gprof.h	7.1 (Berkeley) 6/4/86
 */

#ifndef	_SYS_GPROF_H_
#define _SYS_GPROF_H_

#ifdef	mips
/*
 * profiling header
 * used by kgmon to determine appropriate form of mon.out file
 */
struct phdr {
    int		proftype;	/* profile type, see below */
    char	*lowpc;		/* low text pc */
    char	*highpc;	/* high text pc */
    char	*pc_buf;	/* address of pc sample buckets */
    int		pc_bytes;	/* size of pc sample buckets in bytes */
    char	*bb_buf;	/* address of bb counters */
    int		bb_bytes;	/* size of invocation/bb counters in bytes */
    char	*tos_buf;	/* address of tos array */
    int		tos_bytes;	/* size of gprof tos array in bytes */
    char	*froms_buf;	/* address of froms array */
    int		froms_bytes;	/* size of gprof froms array in bytes */
    int		sample_hz;	/* frequency of sampling */
};

#else	mips

struct phdr {
    char	*lpc;
    char	*hpc;
    int		ncnt;
};

#endif	mips

    /*
     *	histogram counters are unsigned shorts (according to the kernel).
     */
#define HISTCOUNTER	unsigned short

    /*
     *	fraction of text space to allocate for histogram counters
     *	here, 1/2
     */
#define HISTFRACTION	2

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
     *
     *	For Mips the shortest call sequence is:
     *
     *		jal	x
     *		jal	y
     *
     * which is separated by four bytes, thus HASHFRACTION is calculated as:
     *
     *		HASHFRACTION = 4 / (2 * 2 - 1) = 1
     */
#ifdef	mips
#define HASHFRACTION	1
#else	mips
#define HASHFRACTION	2
#endif	mips

    /*
     *	percent of text space to allocate for tostructs
     *	with a minimum.
     */
#define ARCDENSITY	2
#define MINARCS		50

struct tostruct {
    char		*selfpc;
    long		count;
    unsigned short	link;
};

    /*
     *	a raw arc,
     *	    with pointers to the calling site and the called site
     *	    and a count.
     */
struct rawarc {
    unsigned long	raw_frompc;
    unsigned long	raw_selfpc;
    long		raw_count;
};

    /*
     *	general rounding functions.
     */
#define ROUNDDOWN(x,y)	(((x)/(y))*(y))
#define ROUNDUP(x,y)	((((x)+(y)-1)/(y))*(y))

#ifdef	mips
/*
 * profile types
 */
#define PC_SAMPLES	0x1	/* pc samples taken */
#define INV_COUNTS	0x2	/* procedure invocations */
#define BB_COUNTS	0x4	/* basic block counts */
#define GPROF_COUNTS	0x8	/* gprof call graph info */

#if	PROFTYPE == 2 || PROFTYPE == 3
#define BB_SCALE	2	/* half of textsize for bb counts */
#endif	PROFTYPE == 2 || PROFTYPE == 3

#endif	mips

#endif	_SYS_GPROF_H_
