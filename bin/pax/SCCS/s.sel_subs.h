h18473
s 00002/00002/00045
d D 8.1 93/05/31 14:53:26 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00004/00040
d D 1.2 93/01/12 03:00:50 muller 2 1
c added support for -T changes in sel_subs.c
e
s 00044/00000/00000
d D 1.1 92/12/13 22:51:38 muller 1 0
c date and time created 92/12/13 22:51:38 by muller
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1992 Keith Muller.
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
 * Keith Muller of the University of California, San Diego.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * data structure for storing uid/grp selects (-U, -G non standard options)
 */

#define USR_TB_SZ	317		/* user selection table size */
#define GRP_TB_SZ	317		/* user selection table size */

typedef struct usrt {
	uid_t uid;
	struct usrt *fow;		/* next uid */
} USRT;

typedef struct grpt {
	gid_t gid;
	struct grpt *fow;		/* next gid */
} GRPT;

/*
 * data structure for storing user supplied time ranges (-T option)
 */

D 2
#define ATOI2(s)       ((((s)[0] - '0') * 10) + ((s)[1] - '0'))
E 2
I 2
#define ATOI2(s)	((((s)[0] - '0') * 10) + ((s)[1] - '0'))
E 2

typedef struct time_rng {
	time_t		low_time;	/* lower inclusive time limit */
	time_t		high_time;	/* higher inclusive time limit */
D 2
	int		flags;		/* option flags */
#define	HASLOW		0x1		/* has lower time limit */
#define HASHIGH		0x2		/* has higher time limit */
E 2
I 2
	int		flgs;		/* option flags */
#define	HASLOW		0x01		/* has lower time limit */
#define HASHIGH		0x02		/* has higher time limit */
#define CMPMTME		0x04		/* compare file modification time */
#define CMPCTME		0x08		/* compare inode change time */
#define CMPBOTH	(CMPMTME|CMPCTME)	/* compare inode and mod time */
E 2
	struct time_rng	*fow;		/* next pattern */
} TIME_RNG;
E 1
