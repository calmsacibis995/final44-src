h38847
s 00002/00002/00069
d D 8.1 93/06/11 15:16:16 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00069
d D 7.3 93/04/20 21:31:58 torek 3 2
c spelling
e
s 00005/00000/00066
d D 7.2 92/07/21 16:54:22 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00066/00000/00000
d D 7.1 92/07/13 00:44:30 torek 1 0
c date and time created 92/07/13 00:44:30 by torek
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
I 2
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
D 3
 *	California, Lawrence Berkeley Laboratories.
E 3
I 3
 *	California, Lawrence Berkeley Laboratory.
E 3
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 3
 * from: $Header: clockreg.h,v 1.5 92/06/17 05:21:59 torek Exp $ (LBL)
E 3
I 3
 * from: $Header: clockreg.h,v 1.6 92/11/26 03:04:48 torek Exp $ (LBL)
E 3
 */

/*
 * Sun-4c clock Mostek TOD clock.  This includes the ``id prom''.
 */

/*
 * ID prom format.  The ``host id'' is set up by taking the machine
 * ID as the top byte and the hostid field as the remaining three.
 * The id_xxx0 field appears to contain some other number.  The id_xxx1
 * contains a bunch of 00's and a5's on my machines, suggesting it is
 * not actually used.  The checksum seems to include them, however.
 */
struct sun4c_idprom {
	u_char	id_format;		/* format identifier (= 1) */
	u_char	id_machine;		/* machine type (see cpu.h) */
	u_char	id_ether[6];		/* ethernet address */
	long	id_xxx0;		/* ??? */
	u_char	id_hostid[3];		/* ``host id'' bytes */
	u_char	id_checksum;		/* xor of everything else */
	char	id_xxx1[16];		/* ??? */
};

/*
 * Mostek MK48T02 clock.
 *
 * The clock includes 2040 bytes of RAM, the last 32 of which serve to
 * identify the kind of Sun 4c this is.
 */
struct clockreg {
	char	cl_nvram[2008];		/* `free' nonvolatile memory */
	struct	sun4c_idprom cl_idprom;	/* `id prom' */
	volatile u_char	cl_csr;		/* control register */
	volatile u_char	cl_sec;		/* seconds (0..59; BCD) */
	volatile u_char	cl_min;		/* minutes (0..59; BCD) */
	volatile u_char	cl_hour;	/* hour (0..23; BCD) */
	volatile u_char	cl_wday;	/* weekday (1..7) */
	volatile u_char	cl_mday;	/* day in month (1..31; BCD) */
	volatile u_char	cl_month;	/* month (1..12; BCD) */
	volatile u_char	cl_year;	/* year (0..99; BCD) */
};

/* bits in cl_csr */
#define	CLK_WRITE	0x80		/* want to write */
#define	CLK_READ	0x40		/* want to read (freeze clock) */

struct clockreg *clockreg;

/*
 * Sun chose the year `68' as their base count, so that
 * cl_year==0 means 1968.
 */
#define	YEAR0	68
E 1
