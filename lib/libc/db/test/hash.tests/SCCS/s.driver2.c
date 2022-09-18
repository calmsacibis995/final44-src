h59595
s 00005/00005/00083
d D 8.1 93/06/04 15:32:42 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00086
d D 5.2 91/09/11 16:02:55 bostic 2 1
c use dbopen, not hash_open
e
s 00088/00000/00000
d D 5.1 91/09/04 12:44:43 bostic 1 0
c date and time created 91/09/04 12:44:43 by bostic
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * Margo Seltzer.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
D 3
char copyright[] =
"%Z% Copyright (c) 1991 The Regents of the University of California.\n\
 All rights reserved.\n";
E 3
I 3
static char copyright[] =
"%Z% Copyright (c) 1991, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 3
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*
 * Test driver, to try to tackle the large ugly-split problem.
 */

#include <sys/file.h>
#include <stdio.h>
#include "ndbm.h"

int my_hash(key, len)
	char	*key;
	int	len;
{
	return(17);		/* So I'm cruel... */
}

main(argc, argv)
	int	argc;
{
	DB	*db;
	DBT	key, content;
	char	keybuf[2049];
	char	contentbuf[2049];
	char	buf[256];
	int	i;
	HASHINFO	info;

	info.bsize = 1024;
	info.ffactor = 5;
	info.nelem = 1;
	info.cachesize = NULL;
#ifdef HASH_ID_PROGRAM_SPECIFIED
	info.hash_id = HASH_ID_PROGRAM_SPECIFIED;
	info.hash_func = my_hash;
#else
	info.hash = my_hash;
#endif
	info.lorder = 0;
D 2
	if (!(db = hash_open("bigtest", O_RDWR | O_CREAT, 0644, &info))) {
		sprintf(buf, "hash_open failed on file bigtest");
E 2
I 2
	if (!(db = dbopen("bigtest", O_RDWR | O_CREAT, 0644, DB_HASH, &info))) {
		sprintf(buf, "dbopen: failed on file bigtest");
E 2
		perror(buf);
		exit(1);
	}
	srandom(17);
	key.data = keybuf;
	content.data = contentbuf;
	bzero(keybuf, sizeof(keybuf));
	bzero(contentbuf, sizeof(contentbuf));
	for (i=1; i <= 500; i++) {
		key.size = 128 + (random()&1023);
		content.size = 128 + (random()&1023);
/*		printf("%d: Key size %d, data size %d\n", i, key.size,
		       content.size); */
		sprintf(keybuf, "Key #%d", i);
		sprintf(contentbuf, "Contents #%d", i);
		if ((db->put)(db, &key, &content, R_NOOVERWRITE)) {
			sprintf(buf, "dbm_store #%d", i);
			perror(buf);
		}
	}
	if ((db->close)(db)) {
		perror("closing hash file");
		exit(1);
	}
	exit(0);
}

	

E 1
