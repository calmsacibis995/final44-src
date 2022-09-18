h05903
s 00002/00002/00042
d D 8.1 93/06/10 22:54:19 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00014/00000/00030
d D 7.2 90/05/11 15:22:26 sklower 2 1
c install combined copyright headers using sccs include for terms
e
s 00030/00000/00000
d D 7.1 90/05/11 11:19:44 sklower 1 0
c date and time created 90/05/11 11:19:44 by sklower
e
u
U
t
T
I 1
/*
I 2
 * Copyright (c) University of British Columbia, 1984
D 3
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * the Laboratory for Computation Vision and the Computer Science Department
 * of the University of British Columbia.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
E 2
 * Format of X.25 accounting record written
 * to X25ACCTF whenever a circuit is closed.
 */

#ifdef waterloo
#define X25ACCTF	"/usr/adm/logs/x25acct"
#else
#define X25ACCTF	"/usr/adm/x25acct"
#endif

struct	x25acct {
	time_t	x25acct_stime;		/* start time */
#ifdef waterloo
	u_long	x25acct_etime;		/* elapsed time (seconds) */
#else
	u_short	x25acct_etime;		/* elapsed time (seconds) */
#endif
	short	x25acct_uid;		/* user id */
	short	x25acct_net;		/* network id */
	u_short	x25acct_psize:4,	/* packet size */
		x25acct_addrlen:4,	/* x25acct_addr length */
		x25acct_revcharge:1,	/* reverse charging */
		x25acct_callin:1,	/* incoming call */
		x25acct_unused:6;
	char	x25acct_addr[8];	/* remote DTE address (in bcd) */
	char	x25acct_udata[4];	/* protocol id */
	long	x25acct_txcnt;		/* packets transmitted */
	long	x25acct_rxcnt;		/* packets received */
};
E 1
