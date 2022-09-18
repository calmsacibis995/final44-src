h00842
s 00010/00003/00070
d D 5.2 91/04/22 14:48:54 bostic 2 1
c new copyright; att/bsd/shared
e
s 00073/00000/00000
d D 5.1 91/04/22 14:48:12 bostic 1 0
c date and time created 91/04/22 14:48:12 by bostic
e
u
U
t
T
I 2
/*-
 * Copyright (c) 1983 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.proprietary.c%
 *
 *	%W% (Berkeley) %G%
 */

E 2
I 1
/*
D 2
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 2
I 2
 * Derived from:
E 2
 *
 *	@(#)ndbm.h	5.3 (Berkeley) 5/29/90
 */

/*
 * Hashed key data base library.
 */
#define PBLKSIZ 1024
#define DBLKSIZ 4096

typedef struct {
	int	dbm_dirf;		/* open directory file */
	int	dbm_pagf;		/* open page file */
	int	dbm_flags;		/* flags, see below */
	long	dbm_maxbno;		/* last ``bit'' in dir file */
	long	dbm_bitno;		/* current bit number */
	long	dbm_hmask;		/* hash mask */
	long	dbm_blkptr;		/* current block for dbm_nextkey */
	int	dbm_keyptr;		/* current key for dbm_nextkey */
	long	dbm_blkno;		/* current page to read/write */
	long	dbm_pagbno;		/* current page in pagbuf */
	char	dbm_pagbuf[PBLKSIZ];	/* page file block buffer */
	long	dbm_dirbno;		/* current block in dirbuf */
	char	dbm_dirbuf[DBLKSIZ];	/* directory file block buffer */
} DBM;

#define _DBM_RDONLY	0x1	/* data base open read-only */
#define _DBM_IOERR	0x2	/* data base I/O error */

#define dbm_rdonly(db)	((db)->dbm_flags & _DBM_RDONLY)

#define dbm_error(db)	((db)->dbm_flags & _DBM_IOERR)
	/* use this one at your own risk! */
#define dbm_clearerr(db)	((db)->dbm_flags &= ~_DBM_IOERR)

/* for flock(2) and fstat(2) */
#define dbm_dirfno(db)	((db)->dbm_dirf)
#define dbm_pagfno(db)	((db)->dbm_pagf)

typedef struct {
	char	*dptr;
	int	dsize;
} datum;

/*
 * flags to dbm_store()
 */
#define DBM_INSERT	0
#define DBM_REPLACE	1

#if __STDC__ || c_plusplus
extern DBM *dbm_open(const char *, int, int);
extern void dbm_close(DBM *);
extern datum dbm_fetch(DBM *, datum);
extern datum dbm_firstkey(DBM *);
extern datum dbm_nextkey(DBM *);
extern long dbm_forder(DBM *, datum);
extern int dbm_delete(DBM *, datum);
extern int dbm_store(DBM *, datum, datum, int);
#else
extern DBM *dbm_open();
extern void dbm_close();
extern datum dbm_fetch();
extern datum dbm_firstkey();
extern datum dbm_nextkey();
extern long dbm_forder();
extern int dbm_delete();
extern int dbm_store();
#endif
E 1
