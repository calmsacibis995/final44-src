h47890
s 00001/00001/00175
d D 8.2 93/09/11 17:58:40 bostic 17 16
c ndbm will pass none of the (future) DB flags
e
s 00002/00002/00174
d D 8.1 93/06/04 15:22:15 bostic 16 15
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00174
d D 5.14 93/05/23 13:04:00 bostic 15 14
c Change default page size to 4K and fill factor to 40.
e
s 00002/00001/00174
d D 5.13 93/02/11 11:39:53 bostic 14 13
c move db.h to the end of the includes, make compat.h work better
e
s 00001/00000/00174
d D 5.12 92/07/17 09:47:41 bostic 13 12
c lint
e
s 00000/00009/00174
d D 5.11 91/09/11 16:02:28 bostic 12 11
c make dbm_pagfno fail on compile, not at run-time
e
s 00015/00000/00168
d D 5.10 91/09/08 12:24:52 bostic 11 10
c add dbm_dirfno, dbm_pagfno functions
e
s 00001/00001/00167
d D 5.9 91/09/08 12:20:05 bostic 10 9
c needs __DBINTERFACE_PRIVATE to get prototype for hash_open
c ndbm.h includes db.h
e
s 00099/00099/00069
d D 5.8 91/09/04 12:56:44 bostic 9 8
c Rev #2.  ANSI/POSIX and reformatting, a few bug fixes thrown in
e
s 00002/00001/00166
d D 5.7 91/06/17 11:48:17 bostic 8 7
c don't use sprintf(3) so we don't drag in stdio
e
s 00002/00001/00165
d D 5.6 91/03/12 09:33:35 bostic 7 6
c make dbm_fetch set dsize to 0 when elements aren't found for backward
c compatibility; change HASHINFO element ncached to cachesize
e
s 00002/00002/00164
d D 5.5 91/03/03 14:32:59 bostic 6 5
c DBT data changed to be unsigned, fix routines that take flags
e
s 00002/00001/00164
d D 5.4 91/02/22 17:23:39 bostic 5 4
c ANSI prototypes
e
s 00002/00002/00163
d D 5.3 91/02/22 10:21:47 bostic 4 2
c ANSI and c++ stuff
e
s 00001/00000/00165
d R 5.3 91/02/18 23:31:55 mao 3 2
c need to include db.h -- we use HASHINFO here
e
s 00003/00001/00162
d D 5.2 91/02/14 12:07:23 bostic 2 1
c append ".db" to the file name
e
s 00163/00000/00000
d D 5.1 91/02/12 20:28:07 bostic 1 0
c date and time created 91/02/12 20:28:07 by bostic
e
u
U
t
T
I 1
/*-
D 16
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 16
I 16
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 16
 *
 * This code is derived from software contributed to Berkeley by
 * Margo Seltzer.
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

/*
D 9
    This package provides a dbm compatible interface to the new hashing
    package described in db(3)
*/
E 9
I 9
 * This package provides a dbm compatible interface to the new hashing
 * package described in db(3).
 */
E 9

#include <sys/param.h>
I 10
D 14
#define __DBINTERFACE_PRIVATE
E 14
I 14

E 14
E 10
#include <ndbm.h>
I 11
D 12
#include <unistd.h>
E 12
E 11
D 5
#include <stddef.h>
E 5
I 5
D 10
#include <db.h>
E 10
#include <stdio.h>
I 9
#include <string.h>
I 14

E 14
E 9
E 5
#include "hash.h"

/*
D 9
    return 	*DBM on success
		NULL on failure
*/
E 9
I 9
 * Returns:
 * 	*DBM on success
 *	 NULL on failure
 */
E 9
extern DBM *
D 9
dbm_open( file, flags, mode )
D 4
char 	*file;
E 4
I 4
const char 	*file;
E 4
int	flags;
int	mode;
E 9
I 9
dbm_open(file, flags, mode)
	const char *file;
	int flags, mode;
E 9
{
D 9
    HASHINFO	info;
I 2
    char path[MAXPATHLEN];
E 9
I 9
	HASHINFO info;
	char path[MAXPATHLEN];
E 9
E 2

D 9
    info.bsize = 1024;
    info.ffactor = 5;
    info.nelem = 1;
D 7
    info.ncached = NULL;
E 7
I 7
    info.cachesize = NULL;
E 7
    info.hash = NULL;
    info.lorder = 0;
D 2
    return( hash_open ( file, flags, mode, &info ) );
E 2
I 2
D 8
    (void)sprintf(path, "%s%s", file, DBM_SUFFIX);
E 8
I 8
    (void)strcpy(path, file);
    (void)strcat(path, DBM_SUFFIX);
E 8
    return( hash_open ( path, flags, mode, &info ) );
E 9
I 9
D 15
	info.bsize = 1024;
	info.ffactor = 5;
E 15
I 15
	info.bsize = 4096;
	info.ffactor = 40;
E 15
	info.nelem = 1;
	info.cachesize = NULL;
	info.hash = NULL;
	info.lorder = 0;
	(void)strcpy(path, file);
	(void)strcat(path, DBM_SUFFIX);
D 17
	return ((DBM *)__hash_open(path, flags, mode, &info));
E 17
I 17
	return ((DBM *)__hash_open(path, flags, mode, &info, 0));
E 17
E 9
E 2
}

D 9
extern void 
E 9
I 9
extern void
E 9
dbm_close(db)
D 9
DBM	*db;
E 9
I 9
	DBM *db;
E 9
{
D 9
    (void)(db->close) (db);
E 9
I 9
	(void)(db->close)(db);
E 9
}

/*
D 9
    Returns 	DATUM on success
		NULL on failure
*/
extern datum 
dbm_fetch( db, key )
DBM 	*db;
datum	key;
E 9
I 9
 * Returns:
 *	DATUM on success
 *	NULL on failure
 */
extern datum
dbm_fetch(db, key)
	DBM *db;
	datum key;
E 9
{
D 9
    int	status;
    datum	retval;
E 9
I 9
	datum retval;
	int status;
E 9

D 6
    status = (db->get) ( db, (DBT *)&key, (DBT *)&retval );
E 6
I 6
D 9
    status = (db->get) ( db, (DBT *)&key, (DBT *)&retval, 0 );
E 6
    if ( status ) {
	retval.dptr = NULL;
I 7
	retval.dsize = 0;
E 7
    }
    return(retval);
E 9
I 9
	status = (db->get)(db, (DBT *)&key, (DBT *)&retval, 0);
	if (status) {
		retval.dptr = NULL;
		retval.dsize = 0;
	}
	return (retval);
E 9
}

/*
D 9
    Returns 	DATUM on success
		NULL on failure
*/
extern datum 
E 9
I 9
 * Returns:
 *	DATUM on success
 *	NULL on failure
 */
extern datum
E 9
dbm_firstkey(db)
D 9
DBM 	*db;
E 9
I 9
	DBM *db;
E 9
{
D 9
    int	status;
    datum	retkey;
    datum	retdata;
E 9
I 9
	int status;
	datum retdata, retkey;
E 9

D 9
    status = (db->seq) ( db, (DBT *)&retkey, (DBT *)&retdata, R_FIRST );
    if ( status ) {
	retkey.dptr = NULL;
    }
    return(retkey);
E 9
I 9
	status = (db->seq)(db, (DBT *)&retkey, (DBT *)&retdata, R_FIRST);
	if (status)
		retkey.dptr = NULL;
	return (retkey);
E 9
}
I 9

E 9
/*
D 9
    Returns 	DATUM on success
		NULL on failure
*/
extern datum 
E 9
I 9
 * Returns:
 *	DATUM on success
 *	NULL on failure
 */
extern datum
E 9
dbm_nextkey(db)
D 9
DBM 	*db;
E 9
I 9
	DBM *db;
E 9
{
D 9
    int	status;
    datum	retkey;
    datum	retdata;
E 9
I 9
	int status;
	datum retdata, retkey;
E 9

D 9
    status = (db->seq) ( db, (DBT *)&retkey, (DBT *)&retdata, R_NEXT );
    if ( status ) {
	retkey.dptr = NULL;
    }
    return(retkey);
E 9
I 9
	status = (db->seq)(db, (DBT *)&retkey, (DBT *)&retdata, R_NEXT);
	if (status)
		retkey.dptr = NULL;
	return (retkey);
E 9
}
D 9

E 9
/*
D 9
    0 on success
    <0 failure
*/
extern int 
E 9
I 9
 * Returns:
 *	 0 on success
 *	<0 failure
 */
extern int
E 9
dbm_delete(db, key)
D 9
DBM 	*db;
datum	key;
E 9
I 9
	DBM *db;
	datum key;
E 9
{
D 9
    int	status;
E 9
I 9
	int status;
E 9

D 4
    status = (db->delete)( db, (DBT *)&key );
E 4
I 4
D 6
    status = (db->del)( db, (DBT *)&key );
E 6
I 6
D 9
    status = (db->del)( db, (DBT *)&key, 0 );
E 6
E 4
    if ( status ) {
	return(-1);
    } else {
	return(0);
    }
E 9
I 9
	status = (db->del)(db, (DBT *)&key, 0);
	if (status)
		return (-1);
	else
		return (0);
E 9
}

/*
D 9
    0 on success
    <0 failure
    1 if DBM_INSERT and entry exists
*/
extern int 
E 9
I 9
 * Returns:
 *	 0 on success
 *	<0 failure
 *	 1 if DBM_INSERT and entry exists
 */
extern int
E 9
dbm_store(db, key, content, flags)
D 9
DBM 	*db;
datum	key;
datum	content;
int	flags;
E 9
I 9
	DBM *db;
	datum key, content;
	int flags;
E 9
{
D 9
    return ((db->put)( db, (DBT *)&key, (DBT *)&content, 
			(flags == DBM_INSERT) ? R_NOOVERWRITE : 0 ));
E 9
I 9
	return ((db->put)(db, (DBT *)&key, (DBT *)&content,
	    (flags == DBM_INSERT) ? R_NOOVERWRITE : 0));
E 9
}

extern int
dbm_error(db)
D 9
DBM	*db;
E 9
I 9
	DBM *db;
E 9
{
D 9
    HTAB	*hp;
E 9
I 9
	HTAB *hp;
E 9

D 9
    hp = (HTAB *)db->internal;
    return ( hp->errno );
E 9
I 9
	hp = (HTAB *)db->internal;
	return (hp->errno);
E 9
}

extern int
dbm_clearerr(db)
D 9
DBM	*db;
E 9
I 9
	DBM *db;
E 9
{
D 9
    HTAB	*hp;
E 9
I 9
	HTAB *hp;
E 9

D 9
    hp = (HTAB *)db->internal;
    hp->errno = 0;
    return ( 0 );
E 9
I 9
	hp = (HTAB *)db->internal;
	hp->errno = 0;
	return (0);
I 11
}

I 13
extern int
E 13
dbm_dirfno(db)
	DBM *db;
{
	return(((HTAB *)db->internal)->fp);
D 12
}

dbm_pagfno(db)
	DBM *db;
{
#define	PAGFNOERR	"ndbm: hash: dbm_pagfno not available\n"
	(void)write(STDERR_FILENO, PAGFNOERR, sizeof(PAGFNOERR) - 1);
	abort();
E 12
E 11
E 9
}
E 1
