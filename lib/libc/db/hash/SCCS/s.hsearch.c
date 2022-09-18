h59526
s 00000/00001/00081
d D 8.3 94/02/21 15:09:12 bostic 11 10
c first pass at making DB use basic integral types (the Alpha port)
e
s 00001/00001/00081
d D 8.2 93/09/07 11:53:18 bostic 10 9
c add DB_ flags to __hash_open()
e
s 00002/00002/00080
d D 8.1 93/06/04 15:22:12 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00000/00080
d D 5.8 93/02/11 11:39:52 bostic 8 7
c move db.h to the end of the includes, make compat.h work better
e
s 00001/00000/00079
d D 5.7 91/09/08 12:18:50 bostic 7 6
c db.h needs __DBINTERFACE_PRIVATE to get prototype for hash_open
e
s 00044/00054/00035
d D 5.6 91/09/04 12:56:41 bostic 6 5
c Rev #2.  ANSI/POSIX and reformatting, a few bug fixes thrown in
e
s 00001/00001/00088
d D 5.5 91/03/12 09:34:59 bostic 5 4
c Change HASHINFO element ncached to cachesize for consistency
e
s 00004/00004/00085
d D 5.4 91/03/03 14:32:58 bostic 4 3
c DBT data changed to be unsigned, fix routines that take flags
e
s 00002/00002/00087
d D 5.3 91/02/22 17:23:39 bostic 3 2
c ANSI prototypes
e
s 00003/00001/00086
d D 5.2 91/02/19 10:31:26 bostic 2 1
c make return value static for hsearch interface
e
s 00087/00000/00000
d D 5.1 91/02/12 20:28:04 bostic 1 0
c date and time created 91/02/12 20:28:04 by bostic
e
u
U
t
T
I 1
/*-
D 9
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
 * This code is derived from software contributed to Berkeley by
 * Margo Seltzer.
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

D 3
#include <sys/file.h>
E 3
#include <sys/types.h>
I 8

E 8
D 3
#include <stdio.h>
E 3
I 3
#include <fcntl.h>
#include <string.h>
I 8

E 8
I 7
D 11
#define	__DBINTERFACE_PRIVATE
E 11
E 7
E 3
#include <db.h>
#include "search.h"

D 6
static	DB	*dbp = NULL;
static	ENTRY	retval;
E 6
I 6
static DB *dbp = NULL;
static ENTRY retval;
E 6

D 6
extern	int
hcreate ( nel )
unsigned	nel;
E 6
I 6
extern int
hcreate(nel)
	u_int nel;
E 6
{
D 6
    int	status;
    HASHINFO	info;
E 6
I 6
	HASHINFO info;
E 6

D 6
    info.nelem = nel;
    info.bsize = 256;
    info.ffactor = 8;
D 5
    info.ncached = NULL;
E 5
I 5
    info.cachesize = NULL;
E 5
    info.hash = NULL;
    info.lorder = 0;
    dbp = hash_open ( NULL, O_CREAT|O_RDWR, 0600, &info );
    return ( (int) dbp );
E 6
I 6
	info.nelem = nel;
	info.bsize = 256;
	info.ffactor = 8;
	info.cachesize = NULL;
	info.hash = NULL;
	info.lorder = 0;
D 10
	dbp = (DB *)__hash_open(NULL, O_CREAT | O_RDWR, 0600, &info);
E 10
I 10
	dbp = (DB *)__hash_open(NULL, O_CREAT | O_RDWR, 0600, &info, 0);
E 10
	return ((int)dbp);
E 6
}

D 6

extern ENTRY	*
hsearch ( item, action )
ENTRY	item;
ACTION	action;
E 6
I 6
extern ENTRY *
hsearch(item, action)
	ENTRY item;
	ACTION action;
E 6
{
D 6
    int	status;
    DBT	key, val;
E 6
I 6
	DBT key, val;
	int status;
E 6

D 6
    if ( !dbp ) {
	return(NULL);
    }
E 6
I 6
	if (!dbp)
		return (NULL);
	key.data = (u_char *)item.key;
	key.size = strlen(item.key) + 1;
E 6

D 4
    key.data = item.key;
E 4
I 4
D 6
    key.data = (u_char *)item.key;
E 4
    key.size = strlen(item.key) + 1;

    if ( action == ENTER ) {
D 4
	val.data = item.data;
E 4
I 4
	val.data = (u_char *)item.data;
E 4
	val.size = strlen(item.data) + 1;
	status = (dbp->put) ( dbp, &key, &val, R_NOOVERWRITE );
	if ( status ) {
	    return(NULL);
	} 
    } else {
	/* FIND */
D 4
	status = (dbp->get) ( dbp, &key, &val );
E 4
I 4
	status = (dbp->get) ( dbp, &key, &val, 0 );
E 4
	if ( status ) {
	    return ( NULL );
E 6
I 6
	if (action == ENTER) {
		val.data = (u_char *)item.data;
		val.size = strlen(item.data) + 1;
		status = (dbp->put)(dbp, &key, &val, R_NOOVERWRITE);
		if (status)
			return (NULL);
E 6
	} else {
D 4
	    item.data = val.data;
E 4
I 4
D 6
	    item.data = (char *)val.data;
E 6
I 6
		/* FIND */
		status = (dbp->get)(dbp, &key, &val, 0);
		if (status)
			return (NULL);
		else
			item.data = (char *)val.data;
E 6
E 4
	}
D 6
    }
D 2
    return ( &item );
E 2
I 2
    retval.key = item.key;
    retval.data = item.data;
    return ( &retval );
E 6
I 6
	retval.key = item.key;
	retval.data = item.data;
	return (&retval);
E 6
E 2
}

D 6

E 6
extern void
D 6
hdestroy ()
E 6
I 6
hdestroy()
E 6
{
D 6
    if (dbp) {
	(void)(dbp->close) (dbp);
	dbp = NULL;
    }
    return;
E 6
I 6
	if (dbp) {
		(void)(dbp->close)(dbp);
		dbp = NULL;
	}
E 6
}
D 6


E 6
E 1
