h08308
s 00002/00002/00049
d D 8.1 93/06/02 20:06:00 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00001/00051
d D 5.8 92/04/25 20:22:54 ralph 13 12
c deleted sys/cdefs.h since its included by db.h
e
s 00002/00000/00050
d D 5.7 91/09/11 16:14:59 bostic 12 11
c add prototype for dbm_dirfno; make dbm_pagfno fail on compile
e
s 00005/00000/00045
d D 5.6 91/04/03 16:14:33 bostic 11 10
c protect all user-level include files against reinclusion
e
s 00007/00001/00038
d D 5.5 91/02/14 12:10:42 bostic 10 9
c add DBM_SUFFIX
e
s 00028/00062/00011
d D 5.4 91/02/12 20:11:10 bostic 9 8
c new version from Margo Seltzer with the db(3) hash package
c add C function prototypes
e
s 00001/00001/00072
d D 5.3 90/05/29 19:26:48 bostic 8 7
c C++ wants the prototypes, too
e
s 00019/00008/00054
d D 5.2 90/03/06 15:49:49 bostic 7 6
c add ANSI C prototypes
e
s 00007/00001/00055
d D 5.1 85/05/30 09:37:51 dist 6 5
c Add copyright
e
s 00004/00000/00052
d D 4.5 85/01/09 12:09:50 serge 5 4
c added dbm_dirfno() and dbm_pagfno() macros for flock(2) and fstat(2)
e
s 00024/00022/00028
d D 4.4 84/09/05 14:48:40 ralph 4 3
c added dbm_blkptr, dbm_keyptr fields for dbm_nextkey() changes.
e
s 00033/00026/00017
d D 4.3 84/08/28 14:11:44 ralph 3 2
c unify subroutine names, added error macros.
e
s 00004/00000/00039
d D 4.2 83/12/20 11:02:26 ralph 2 1
c added #defines for options to dbmstore().
e
s 00039/00000/00000
d D 4.1 83/12/02 17:05:58 ralph 1 0
c date and time created 83/12/02 17:05:58 by ralph
e
u
U
t
T
I 1
D 4
/*      %M%     %I%     %E%     */
E 4
I 4
D 6
/*	%M%	%I%	%E%	*/
E 6
I 6
D 9
/*
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 9
I 9
/*-
D 14
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 14
I 14
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 14
E 9
 *
I 9
 * This code is derived from software contributed to Berkeley by
 * Margo Seltzer.
 *
 * %sccs.include.redist.c%
 *
E 9
 *	%W% (Berkeley) %G%
 */
E 6
E 4

I 11
#ifndef _NDBM_H_
#define	_NDBM_H_

E 11
D 9
/*
D 3
 * (New) Hashed key data base library (-lndbm).
E 3
I 3
 * Hashed key data base library.
E 3
 */
#define PBLKSIZ 1024
#define DBLKSIZ 4096
E 9
I 9
D 13
#include <sys/cdefs.h>
E 13
#include <db.h>
E 9

D 9
typedef struct {
D 3
	int     db_dirf;                /* open directory file */
	int     db_pagf;                /* open page file */
	int     db_flags;
#define _DB_RDONLY      0x1     /* data base open read-only */
	long    db_maxbno;              /* last ``block'' in page file */
	long    db_bitno;
	long    db_hmask;
	long    db_blkno;               /* current page to read/write */
	long    db_pagbno;              /* current page in pagbuf */
	char    db_pagbuf[PBLKSIZ];     /* page file block buffer */
	long    db_dirbno;              /* current block in dirbuf */
	char    db_dirbuf[DBLKSIZ];     /* directory file block buffer */
E 3
I 3
D 4
	int     dbm_dirf;                /* open directory file */
	int     dbm_pagf;                /* open page file */
	int     dbm_flags;		/* flags, see below */
	long    dbm_maxbno;              /* last ``block'' in page file */
	long    dbm_bitno;
	long    dbm_hmask;
	long    dbm_blkno;               /* current page to read/write */
	long    dbm_pagbno;              /* current page in pagbuf */
	char    dbm_pagbuf[PBLKSIZ];     /* page file block buffer */
	long    dbm_dirbno;              /* current block in dirbuf */
	char    dbm_dirbuf[DBLKSIZ];     /* directory file block buffer */
E 4
I 4
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
E 4
E 3
} DBM;
E 9
I 9
D 10
/* Map dbm interface onto hash(3). */
E 10
I 10
/* Map dbm interface onto db(3). */
E 10
#define DBM_RDONLY	O_RDONLY
E 9

D 3
#define dbrdonly(db)    ((db)->db_flags&_DB_RDONLY) != 0
E 3
I 3
D 9
#define _DBM_RDONLY	0x1	/* data base open read-only */
#define _DBM_IOERR	0x2	/* data base I/O error */
E 9
I 9
/* Flags to dbm_store(). */
#define DBM_INSERT      0
#define DBM_REPLACE     1
I 10

/*
 * The db(3) support for ndbm(3) always appends this suffix to the
 * file name to avoid overwriting the user's original database.
 */
#define	DBM_SUFFIX	".db"
E 10
E 9
E 3

I 3
D 9
#define dbm_rdonly(db)	((db)->dbm_flags & _DBM_RDONLY)

#define dbm_error(db)	((db)->dbm_flags & _DBM_IOERR)
	/* use this one at your own risk! */
#define dbm_clearerr(db)	((db)->dbm_flags &= ~_DBM_IOERR)

I 5
/* for flock(2) and fstat(2) */
#define dbm_dirfno(db)	((db)->dbm_dirf)
#define dbm_pagfno(db)	((db)->dbm_pagf)

E 9
E 5
E 3
typedef struct {
D 4
	char    *dptr;
	int     dsize;
E 4
I 4
D 9
	char	*dptr;
	int	dsize;
E 9
I 9
	char *dptr;
	int dsize;
E 9
E 4
} datum;

I 2
D 3
	/* flags to dbmstore() */
#define DB_INSERT	0
#define DB_REPLACE	1
E 3
I 3
D 9
/*
 * flags to dbm_store()
 */
#define DBM_INSERT	0
#define DBM_REPLACE	1
E 9
I 9
typedef DB DBM;
I 12
#define	dbm_pagfno(a)	DBM_PAGFNO_NOT_AVAILABLE
E 12
E 9
E 3

E 2
D 3
datum   dbmfetch();
datum   dbmfirstkey();
datum   dbmnextkey();
long    dbmforder();
int     dbmdelete();
int     dbmstore();

DBM     *ndbmopen();
void    ndbmclose();
E 3
I 3
D 4
DBM     *dbm_open();
void    dbm_close();
datum   dbm_fetch();
datum   dbm_firstkey();
datum   dbm_nextkey();
long    dbm_forder();
int     dbm_delete();
int     dbm_store();
E 4
I 4
D 7
DBM	*dbm_open();
void	dbm_close();
datum	dbm_fetch();
datum	dbm_firstkey();
datum	dbm_nextkey();
long	dbm_forder();
int	dbm_delete();
int	dbm_store();
E 7
I 7
D 8
#ifdef __STDC__
E 8
I 8
D 9
#if __STDC__ || c_plusplus
E 8
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
E 9
I 9
__BEGIN_DECLS
void	 dbm_close __P((DBM *));
int	 dbm_delete __P((DBM *, datum));
datum	 dbm_fetch __P((DBM *, datum));
datum	 dbm_firstkey __P((DBM *));
long	 dbm_forder __P((DBM *, datum));
datum	 dbm_nextkey __P((DBM *));
DBM	*dbm_open __P((const char *, int, int));
int	 dbm_store __P((DBM *, datum, datum, int));
I 12
int	 dbm_dirfno __P((DBM *));
E 12
__END_DECLS
I 11

#endif /* !_NDBM_H_ */
E 11
E 9
E 7
E 4
E 3
E 1
