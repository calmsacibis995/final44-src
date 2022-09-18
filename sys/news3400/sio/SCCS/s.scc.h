h43847
s 00002/00002/00069
d D 8.1 93/06/11 15:05:33 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00014/00070
d D 7.2 93/03/10 00:02:50 utashiro 2 1
c cleanup header and machine dependency.
e
s 00084/00000/00000
d D 7.1 92/06/04 16:07:55 mckusick 1 0
c initial port from Kazumasa Utashiro
e
u
U
t
T
I 1
/*
D 3
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * Sony Corp. and Kazumasa Utashiro of Software Research Associates, Inc.
 *
 * %sccs.include.redist.c%
 *
 * from: $Hdr: scc.h,v 4.300 91/06/09 06:44:56 root Rel41 $ SONY
 *
 *	%W% (Berkeley) %G%
 */

D 2
#ifdef news700
#define splscc		spl4
#endif

#if defined(news1200) || defined(news1700)
#define splscc		spl5
#endif

E 2
#ifdef news3400
D 2
#ifdef PMAXSPL
#define	splscc		Mach_spl1
#else
E 2
#define	splscc		spl4
D 2
#endif /* PMAXSPL */
#endif /* news3400 */
E 2
I 2
#endif
E 2

#define	SCCWAIT		DELAY(2)
D 2
#define	SCCWAIT		_delay(5)
E 2

#define SCC_REMOTE0	0
#define SCC_REMOTE1	1
#define SCC_REMOTE2	2
#define SCC_REMOTE3	3
#define SCC_REMOTE4	4
#define SCC_REMOTE5	5
#define SCC_REMOTE6	6
#define SCC_REMOTE7	7
#define SCC_REMOTE8	8
#define SCC_REMOTE9	9

#define	SCCVEC0		64
#define	SCCVEC1		(SCCVEC0+16)
#define SCCVEC2		(SCCVEC0+32)
#define SCCVEC3		(SCCVEC0+48)
#define SCCVEC4		(SCCVEC0+64)

/*
 *	SCC channel control block
 */
typedef struct scc_dma {
	char	*dma_addr;
	int	dma_count;
} Scc_dma;

typedef struct scc_channel {
	int	scc_status;		/* channel status		*/
	int	scc_param;		/* channel parameter		*/
	struct	scc_reg	*scc_port;	/* port address			*/
	char	*scc_init;		/* initialize data		*/
	int	scc_vec;		/* interrupt vector		*/
	Scc_dma	x_dma;
	Scc_dma	r_dma;
} Scc_channel;

/*
 *	SCC channel status
 */
#define	OACTIVE		0x00000001	/* transmit in progress	*/
#define	OSTOP		0x00000002	/* output stop request	*/
#define	OFLUSH		0x00000004	/* output flush request	*/
#define	OBUSY		0x00000008	/* output in use	*/
#define LINE_BREAK	0x00000010	/* line break interrupt	*/
#define	ENABLE		0x00000020	/* receiver enable	*/
#define	CHAN_ACTIVE	0x80000000	/* channel active	*/

/*
 *	SCC channel usage
 */
#define	SCC_MOUSE	0
#define	SCC_KEYBOARD	1
E 1
