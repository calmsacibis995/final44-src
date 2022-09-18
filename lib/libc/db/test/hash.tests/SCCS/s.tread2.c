h50616
s 00005/00005/00074
d D 8.1 93/06/04 15:34:41 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00078
d D 5.5 91/09/11 16:05:56 bostic 5 4
c use dbopen, not hash_open
e
s 00005/00031/00074
d D 5.4 91/09/04 12:43:42 bostic 4 3
c clean up SCCS headers, include files
e
s 00034/00008/00071
d D 5.3 91/09/04 12:39:45 bostic 3 2
c Rev #2 (after ANSI/POSIX changes to hash)
e
s 00001/00001/00078
d D 5.2 91/03/12 09:36:52 bostic 2 1
c Change HASHINFO element ncached to cachesize for consistency
e
s 00079/00000/00000
d D 5.1 91/01/31 17:16:29 bostic 1 0
c date and time created 91/01/31 17:16:29 by bostic
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1990 The Regents of the University of California.
E 4
I 4
D 6
 * Copyright (c) 1991 The Regents of the University of California.
E 4
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * This code is derived from software contributed to Berkeley by
 * Margo Seltzer.
 *
D 3
 * %sccs.include.redist.c%
E 3
I 3
D 4
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
E 4
I 4
 * %sccs.include.redist.c%
E 4
E 3
 */

#ifndef lint
D 6
char copyright[] =
D 3
"%Z% Copyright (c) 1990 The Regents of the University of California.\n\
E 3
I 3
D 4
"@(#) Copyright (c) 1990 The Regents of the University of California.\n\
E 4
I 4
"%Z% Copyright (c) 1991 The Regents of the University of California.\n\
E 4
E 3
 All rights reserved.\n";
E 6
I 6
static char copyright[] =
"%Z% Copyright (c) 1991, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 6
#endif /* not lint */

#ifndef lint
D 3
static char sccsid[] = "%W% (Berkeley) %G%";
E 3
I 3
D 4
static char sccsid[] = "@(#)tread2.c	5.2 (Berkeley) 3/12/91";
E 4
I 4
static char sccsid[] = "%W% (Berkeley) %G%";
E 4
E 3
#endif /* not lint */

#include <sys/types.h>
D 4
#include <stdio.h>
E 4
#include <sys/file.h>
I 4
#include <stdio.h>
E 4
#include <db.h>

#define INITIAL	25000
#define MAXWORDS    25000	       /* # of elements in search table */

typedef struct {		       /* info to be stored */
	int num, siz;
} info;

D 3
char	wp1[256];
char	wp2[256];
E 3
I 3
char	wp1[8192];
char	wp2[8192];
E 3
main(argc, argv)
char **argv;
{
	DBT item, key, res;
	DB	*dbp;
	HASHINFO ctl;
	int	stat;

	int i = 0;

	ctl.nelem = INITIAL;
	ctl.hash = NULL;
	ctl.bsize = 64;
	ctl.ffactor = 1;
D 2
	ctl.ncached = atoi(*argv++);
E 2
I 2
	ctl.cachesize = atoi(*argv++);
E 2
	ctl.lorder = 0;
D 5
	if (!(dbp = hash_open( "hashtest", O_RDONLY, 0400, &ctl))) {
E 5
I 5
	if (!(dbp = dbopen( "hashtest", O_RDONLY, 0400, DB_HASH, &ctl))) {
E 5
		/* create table */
		fprintf(stderr, "cannot open: hash table\n" );
		exit(1);
	}

	key.data = wp1;
	item.data = wp2;
D 3
	while ( fgets(wp1, 256, stdin) &&
		fgets(wp2, 256, stdin) &&
E 3
I 3
	while ( fgets(wp1, 8192, stdin) &&
		fgets(wp2, 8192, stdin) &&
E 3
		i++ < MAXWORDS) {
/*
* put info in structure, and structure in the item
*/
		key.size = strlen(wp1);
		item.size = strlen(wp2);

D 3
		stat = (dbp->get)(dbp, &key, &res);
E 3
I 3
		stat = (dbp->get)(dbp, &key, &res,0);
E 3
		if (stat < 0) {
		    fprintf ( stderr, "Error retrieving %s\n", key.data );
		    exit(1);
		} else if ( stat > 0 ) {
		    fprintf ( stderr, "%s not found\n", key.data );
		    exit(1);
		}
	}
	(dbp->close)(dbp);
	exit(0);
}
E 1
