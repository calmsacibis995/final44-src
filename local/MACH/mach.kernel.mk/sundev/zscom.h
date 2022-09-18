/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	zscom.h,v $
 * Revision 2.7  90/12/17  17:21:24  berman
 * 	Switched control of SUNS_403 macro to reg.h and included it.
 * 	[90/11/09            berman]
 * 
 * Revision 2.6  90/04/28  00:04:35  jjc
 * 	Picked up definition of ZSDELAY() from SunOS 4.0.3.
 * 	[90/04/15            jjc]
 * 
 * Revision 2.5  89/07/11  17:28:58  jjc
 * 	Picked up SunOS 3.5 version.
 * 	[89/07/05  20:51:56  jjc]
 * 
 * Revision 2.4  89/03/09  21:50:57  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  20:00:55  gm0w
 * 	Added new copyright and fixed includes as part of kernel
 * 	cleanup.
 * 	[89/02/10            jjc]
 * 
 *  1-Mar-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	Made VOLATILE
 *
 */
/*    @(#)zscom.h 1.1 87/12/21 SMI      */

/*
 * Copyright (c) 1984 by Sun Microsystems, Inc.
 */

/*
 * Support common to all users of Z8530 devices
 */

/*
 * Interrupt vectors - per protocol
 */
struct zsops {
	int	(*zsop_attach)();	/* attach protocol */
	int	(*zsop_txint)();	/* xmit buffer empty */
	int	(*zsop_xsint)();	/* external/status */
	int	(*zsop_rxint)();	/* receive char available */
	int	(*zsop_srint)();	/* special receive condition */
	int	(*zsop_softint)();	/* process software interrupt */
};

/*
 * Common data
 */
struct zscom {
	int	(*zs_vec[4])();		/* vector routines - must be first */
volatile
	struct zscc_device *zs_addr;	/* address of half of chip  - second */
	short	zs_unit;		/* which channel (0:NZSLINE) */
	caddr_t	zs_priv;		/* protocol private data */
	struct zsops *zs_ops;		/* intr op vector */
	u_char	zs_wreg[16];		/* shadow of write registers */
	char	zs_flags;		/* random flags */
};
/* flags */
#define ZS_NEEDSOFT	1

int zssoftpend;				/* level 3 interrupt pending */
#define ZSSETSOFT(zs)	{		\
	zs->zs_flags |= ZS_NEEDSOFT;	\
	if (!zssoftpend) {		\
		zssoftpend = 1;		\
		setzssoft();		\
	}				\
}

#include <machine/reg.h>

#if	SUNOS_403
#ifdef	sun4c
#define ZSDELAY(x)
#else
#define ZSDELAY(x)	DELAY(x)
#endif
#endif	SUNOS_403

/* 
 * Macros to access a port
 */
#define ZREAD(n)	zszread(zs->zs_addr, n)
#define ZWRITE(n,v)	zszwrite(zs->zs_addr, n, (int)(zs->zs_wreg[n] = v))
#define ZBIS(n,v)	zszwrite(zs->zs_addr, n, (int)(zs->zs_wreg[n] |= v))
#define ZBIC(n,v)	zszwrite(zs->zs_addr, n, (int)(zs->zs_wreg[n] &=~ v))

extern struct zsops *zs_proto[];
