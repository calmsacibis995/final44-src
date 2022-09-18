h37518
s 00000/00001/00073
d D 8.4 94/02/21 15:07:29 bostic 11 10
c move __DBINTERFACE_PRIVATE into Makefile.inc
e
s 00002/00002/00072
d D 8.3 93/09/13 20:50:46 bostic 10 9
c O_NONBLOCK is reasonable for an open(2) flag
e
s 00019/00008/00055
d D 8.2 93/09/07 11:54:48 bostic 9 8
c add DB_ flags to calls to access method open routines
c check against acceptable open(2) flags here, not in per access method open's
e
s 00002/00002/00061
d D 8.1 93/06/04 15:20:26 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00062
d D 5.6 93/05/24 09:47:29 bostic 7 6
c add fd routine, to return a file descriptor
e
s 00010/00055/00052
d D 5.5 93/05/16 16:19:43 bostic 6 4
c was going to add a flags argument to the sync call, rewrote it
c instead to just cast the return-error routine
e
s 00002/00000/00107
d R 5.5 93/02/15 10:19:20 bostic 5 4
c abort if unknown type
e
s 00005/00004/00102
d D 5.4 93/02/11 11:39:39 bostic 4 3
c move db.h to the end of the includes, make compat.h work better
e
s 00003/00002/00103
d D 5.3 92/11/13 17:42:55 bostic 3 2
c put can now set the key, so it's not a const * anymore
e
s 00003/00009/00102
d D 5.2 91/09/11 15:58:11 bostic 2 1
c remove __hash_open stub, change dbpanic get call to take const key
e
s 00111/00000/00000
d D 5.1 91/09/04 12:52:40 bostic 1 0
c Rev #2.  Redo the btree code add recno's and checkpoint
e
u
U
t
T
I 1
/*-
D 8
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <sys/types.h>
I 4

#include <errno.h>
I 9
#include <fcntl.h>
E 9
#include <stddef.h>
#include <stdio.h>

E 4
D 11
#define	__DBINTERFACE_PRIVATE
E 11
#include <db.h>
D 4
#include <stdio.h>
#include <stddef.h>
#include <errno.h>
#include "../btree/btree.h"
E 4

DB *
dbopen(fname, flags, mode, type, openinfo)
	const char *fname;
	int flags, mode;
	DBTYPE type;
	const void *openinfo;
{
D 9
	switch (type) {
	case DB_BTREE:
		return (__bt_open(fname, flags, mode, openinfo));
	case DB_HASH:
		return (__hash_open(fname, flags, mode, openinfo));
	case DB_RECNO:
		return (__rec_open(fname, flags, mode, openinfo));
	}
E 9
I 9

#define	DB_FLAGS	(DB_LOCK | DB_SHMEM | DB_TXN)
#define	USE_OPEN_FLAGS							\
D 10
	(O_CREAT | O_EXCL | O_EXLOCK | O_RDONLY | O_RDWR |		\
	    O_SHLOCK | O_TRUNC)
E 10
I 10
	(O_CREAT | O_EXCL | O_EXLOCK | O_NONBLOCK | O_RDONLY |		\
	 O_RDWR | O_SHLOCK | O_TRUNC)
E 10

	if ((flags & ~(USE_OPEN_FLAGS | DB_FLAGS)) == 0)
		switch (type) {
		case DB_BTREE:
			return (__bt_open(fname, flags & USE_OPEN_FLAGS,
			    mode, openinfo, flags & DB_FLAGS));
		case DB_HASH:
			return (__hash_open(fname, flags & USE_OPEN_FLAGS,
			    mode, openinfo, flags & DB_FLAGS));
		case DB_RECNO:
			return (__rec_open(fname, flags & USE_OPEN_FLAGS,
			    mode, openinfo, flags & DB_FLAGS));
		}
E 9
	errno = EINVAL;
	return (NULL);
}

D 2
DB *
__hash_open(fname, flags, mode, openinfo)
	const char *fname;
	int flags, mode;
	const HASHINFO *openinfo;
{ return (NULL); }

E 2
D 6
static int __db_edel __P((const DB *, const DBT *, u_int));
D 2
static int __db_eget __P((const DB *, DBT *, DBT *, u_int));
E 2
I 2
static int __db_eget __P((const DB *, const DBT *, DBT *, u_int));
E 2
D 3
static int __db_eput __P((const DB *dbp, const DBT *, const DBT *, u_int));
E 3
I 3
static int __db_eput __P((const DB *dbp, DBT *, const DBT *, u_int));
E 3
static int __db_eseq __P((const DB *, DBT *, DBT *, u_int));
static int __db_esync __P((const DB *));
E 6
I 6
static int
__dberr()
{
	return (RET_ERROR);
}
E 6

/*
 * __DBPANIC -- Stop.
 *
 * Parameters:
 *	dbp:	pointer to the DB structure.
 */
void
__dbpanic(dbp)
	DB *dbp;
{
	/* The only thing that can succeed is a close. */
D 6
	dbp->del = __db_edel;
	dbp->get = __db_eget;
	dbp->put = __db_eput;
	dbp->seq = __db_eseq;
	dbp->sync = __db_esync;
}

static int
__db_edel(dbp, key, flags)
	const DB *dbp;
	const DBT *key;
	u_int flags;
{
	return (RET_ERROR);
}

static int
__db_eget(dbp, key, data, flag)
	const DB *dbp;
D 2
	DBT *key, *data;
E 2
I 2
	const DBT *key;
	DBT *data;
E 2
	u_int flag;
{
	return (RET_ERROR);
}

static int
__db_eput(dbp, key, data, uflags)
	const DB *dbp;
D 3
	const DBT *key, *data;
E 3
I 3
	DBT *key;
	const DBT *data;
E 3
	u_int uflags;
{
	return (RET_ERROR);
}

static int
__db_eseq(dbp, key, data, flags)
	const DB *dbp;
	DBT *key, *data;
	u_int flags;
{
	return (RET_ERROR);
}

static int
__db_esync(dbp)
	const DB *dbp;
{
	return (RET_ERROR);
E 6
I 6
	dbp->del = (int (*)())__dberr;
I 7
	dbp->fd = (int (*)())__dberr;
E 7
	dbp->get = (int (*)())__dberr;
	dbp->put = (int (*)())__dberr;
	dbp->seq = (int (*)())__dberr;
	dbp->sync = (int (*)())__dberr;
E 6
}
E 1
