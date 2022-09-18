h57877
s 00016/00006/01006
d D 8.3 94/03/25 15:41:46 bostic 18 17
c cgetent accesses free'd memory
c From: Chris Torek <torek@BSDI.COM>
e
s 00002/00002/01010
d D 8.2 94/01/02 14:40:49 bostic 17 16
c fgetline(3) renamed to be fgetln(3)
e
s 00002/00002/01010
d D 8.1 93/06/04 12:02:12 bostic 16 15
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00012/01003
d D 5.15 93/03/19 08:51:35 bostic 15 14
c return the length if the record is from a cap_mkdb database
c minor cleanups
e
s 00029/00033/00986
d D 5.14 93/03/06 10:45:41 bostic 14 13
c make shadow records really work
c make fgetline calls work (was messing up on continuation lines)
e
s 00001/00001/01018
d D 5.13 93/03/04 16:11:08 bostic 13 12
c make it compile...
e
s 00004/00002/01015
d D 5.12 93/03/04 15:44:56 elan 12 11
c Fixed to work with new fgetline(3) (need to clobber \n).
e
s 00002/00028/01015
d D 5.11 92/09/13 12:20:03 ralph 11 10
c add SCCS ids back in.
e
s 00005/00005/01038
d D 5.10 92/09/13 12:13:52 ralph 10 9
c fix cgetnum hex number conversion for 'A' - 'F' case.
e
s 00004/00002/01039
d D 5.9 92/09/09 10:57:19 elan 9 8
c If file in path not found -- don't make it an error, just continue. 
c Also fixed bug in key size from new version of cap_mkdb(1).
e
s 00025/00020/01016
d D 5.8 92/09/04 15:38:55 elan 8 7
c Eliminated redundant tc expansion upon retrieval from .db file.
c Changed cdbget to conform to changes in cap_mkdb(1) which eliminated the 
c REFERENCE\RECORD marks and added the TCERR mark to signal a failed tc 
e
s 00009/00001/01027
d D 5.7 92/09/04 11:07:28 elan 7 6
c Made return value from cgetnext be the first entry in the case of 
c duplicate entries.
e
s 00073/00016/00955
d D 5.6 92/09/03 13:04:51 elan 6 5
c Enabled cgetnext to work properly with multiple records -- passed 
c name field along with name to getent() so verification can be made. 
c Also fixed bug in name field parsing -- it wasn't parsing name fields on 
c multiple lines correctly, now it does.
e
s 00012/00005/00959
d D 5.5 92/09/02 17:59:12 elan 5 4
c Added error checking to realloc's.
e
s 00088/00015/00876
d D 5.4 92/08/17 09:37:46 elan 4 3
c Added db(3) support to routines.  Added return value to getent() 
c that specifies an unresolved tc expansion rather than it being an error.
e
s 00040/00048/00851
d D 5.3 92/08/07 17:18:02 elan 3 2
c Fixed bug in cgetset interaction with cgetent.
e
s 00069/00027/00830
d D 5.2 92/08/07 15:25:38 elan 2 1
c Made cgetset() work with sequential access.  Cleaned up cgetnext().
e
s 00857/00000/00000
d D 5.1 92/08/06 18:21:27 bostic 1 0
c date and time created 92/08/06 18:21:27 by bostic
e
u
U
t
T
I 1
/*-
D 16
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 16
I 16
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 16
 *
 * This code is derived from software contributed to Berkeley by
 * Casey Leedom of Lawrence Livermore National Laboratory.
 *
D 2
 * %sccs.include.redist.c%
E 2
I 2
D 11
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
E 11
I 11
 * %sccs.include.redist.c%
E 11
E 2
 */

#if defined(LIBC_SCCS) && !defined(lint)
D 2
static char sccsid[] = "%W% (Berkeley) %G%";
E 2
I 2
D 11
static char sccsid[] = "@(#)getcap.c	5.1 (Berkeley) 8/6/92";
E 11
I 11
static char sccsid[] = "%W% (Berkeley) %G%";
E 11
E 2
#endif /* LIBC_SCCS and not lint */

#include <sys/types.h>

#include <ctype.h>
I 4
#include <db.h>
E 4
D 9
#include <errno.h>
E 9
#include <errno.h>	
#include <fcntl.h>
I 4
#include <limits.h>
E 4
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define	BFRAG		1024
D 6
#define	BSIZE		80
E 6
I 6
#define	BSIZE		1024
E 6
#define	ESC		('[' & 037)	/* ASCII ESC */
#define	MAX_RECURSION	32		/* maximum getent recursion */
#define	SFRAG		100		/* cgetstr mallocs in SFRAG chunks */

I 4
D 8
#define REFERENCE	(char)0
#define RECORD		(char)1
E 8
I 8
#define RECOK	(char)0
#define TCERR	(char)1
I 14
#define	SHADOW	(char)2
E 14
E 8

E 4
static size_t	 topreclen;	/* toprec length */
static char	*toprec;	/* Additional record specified by cgetset() */
I 2
static int	 gottoprec;	/* Flag indicating retrieval of toprecord */
E 2

D 4
static int getent __P((char **, u_int *, char **, int, char *, int));
E 4
I 4
static int	cdbget __P((DB *, char **, char *));
D 6
static int 	getent __P((char **, u_int *, char **, int, char *, int));
E 6
I 6
static int 	getent __P((char **, u_int *, char **, int, char *, int, char *));
static int	nfcmp __P((char *, char *));
E 6
E 4

/*
 * Cgetset() allows the addition of a user specified buffer to be added
 * to the database array, in effect "pushing" the buffer on top of the
 * virtual database. 0 is returned on success, -1 on failure.
 */
int
cgetset(ent)
	char *ent;
{
	if (ent == NULL) {
		if (toprec)
			free(toprec);
                toprec = NULL;
                topreclen = 0;
                return (0);
        }
        topreclen = strlen(ent);
        if ((toprec = malloc (topreclen + 1)) == NULL) {
		errno = ENOMEM;
                return (-1);
	}
I 3
	gottoprec = 0;
E 3
        (void)strcpy(toprec, ent);
        return (0);
}

/*
 * Cgetcap searches the capability record buf for the capability cap with
 * type `type'.  A pointer to the value of cap is returned on success, NULL
 * if the requested capability couldn't be found.
 *
 * Specifying a type of ':' means that nothing should follow cap (:cap:).
 * In this case a pointer to the terminating ':' or NUL will be returned if
 * cap is found.
 *
 * If (cap, '@') or (cap, terminator, '@') is found before (cap, terminator)
 * return NULL.
 */
char *
cgetcap(buf, cap, type)
	char *buf, *cap;
	int type;
{
	register char *bp, *cp;

	bp = buf;
	for (;;) {
		/*
		 * Skip past the current capability field - it's either the
		 * name field if this is the first time through the loop, or
		 * the remainder of a field whose name failed to match cap.
		 */
		for (;;)
			if (*bp == '\0')
				return (NULL);
			else
				if (*bp++ == ':')
					break;

		/*
		 * Try to match (cap, type) in buf.
		 */
		for (cp = cap; *cp == *bp && *bp != '\0'; cp++, bp++)
			continue;
		if (*cp != '\0')
			continue;
		if (*bp == '@')
			return (NULL);
		if (type == ':') {
			if (*bp != '\0' && *bp != ':')
				continue;
			return(bp);
		}
		if (*bp != type)
			continue;
		bp++;
		return (*bp == '@' ? NULL : bp);
	}
	/* NOTREACHED */
}

/*
 * Cgetent extracts the capability record name from the NULL terminated file
 * array db_array and returns a pointer to a malloc'd copy of it in buf.
 * Buf must be retained through all subsequent calls to cgetcap, cgetnum,
 * cgetflag, and cgetstr, but may then be free'd.  0 is returned on success,
 * -1 if the requested record couldn't be found, -2 if a system error was
 * encountered (couldn't open/read a file, etc.), and -3 if a potential
 * reference loop is detected.
 */
int
cgetent(buf, db_array, name)
	char **buf, **db_array, *name;
{
	u_int dummy;

D 6
	return (getent(buf, &dummy, db_array, -1, name, 0));
E 6
I 6
	return (getent(buf, &dummy, db_array, -1, name, 0, NULL));
E 6
}

/*
 * Getent implements the functions of cgetent.  If fd is non-negative,
 * *db_array has already been opened and fd is the open file descriptor.  We
 * do this to save time and avoid using up file descriptors for tc=
 * recursions.
 *
 * Getent returns the same success/failure codes as cgetent.  On success, a
 * pointer to a malloc'ed capability record with all tc= capabilities fully
 * expanded and its length (not including trailing ASCII NUL) are left in
 * *cap and *len.
 *
 * Basic algorithm:
 *	+ Allocate memory incrementally as needed in chunks of size BFRAG
 *	  for capability buffer.
 *	+ Recurse for each tc=name and interpolate result.  Stop when all
 *	  names interpolated, a name can't be found, or depth exceeds
 *	  MAX_RECURSION.
 */
static int
D 6
getent(cap, len, db_array, fd, name, depth)
	char **cap, **db_array, *name;
E 6
I 6
getent(cap, len, db_array, fd, name, depth, nfield)
	char **cap, **db_array, *name, *nfield;
E 6
	u_int *len;
	int fd, depth;
{
I 4
	DB *capdbp;
	DBT key, data;
E 4
	register char *r_end, *rp, **db_p;
D 4
	int myfd, eof, foundit;
E 4
I 4
D 18
	int myfd, eof, foundit, retval;
E 4
	char *record;
E 18
I 18
	int myfd, eof, foundit, retval, clen;
	char *record, *cbuf;
E 18
D 4

E 4
I 4
	int tc_not_resolved;
	char pbuf[_POSIX_PATH_MAX];
	
E 4
	/*
	 * Return with ``loop detected'' error if we've recursed more than
	 * MAX_RECURSION times.
	 */
	if (depth > MAX_RECURSION)
		return (-3);

	/*
	 * Check if we have a top record from cgetset().
         */
D 2
	if (depth == 0 && toprec != NULL) {
E 2
I 2
D 3
	if (depth == 0 && toprec != NULL && !gottoprec) {
E 3
I 3
	if (depth == 0 && toprec != NULL && cgetmatch(toprec, name) == 0) {
E 3
E 2
		if ((record = malloc (topreclen + BFRAG)) == NULL) {
			errno = ENOMEM;
			return (-2);
		}
		(void)strcpy(record, toprec);
		myfd = 0;
		db_p = db_array;
		rp = record + topreclen + 1;
		r_end = rp + BFRAG;
		goto tc_exp;
	}
	/*
	 * Allocate first chunk of memory.
	 */
	if ((record = malloc(BFRAG)) == NULL) {
		errno = ENOMEM;
		return (-2);
	}
	r_end = record + BFRAG;
	foundit = 0;
D 4

E 4
	/*
	 * Loop through database array until finding the record.
	 */

	for (db_p = db_array; *db_p != NULL; db_p++) {
		eof = 0;

		/*
		 * Open database if not already open.
		 */
I 4

E 4
		if (fd >= 0) {
D 15
			(void)lseek(fd, 0L, L_SET);
E 15
I 15
			(void)lseek(fd, (off_t)0, L_SET);
E 15
			myfd = 0;
		} else {
D 4
			fd = open(*db_p, O_RDONLY, 0);
			if (fd < 0) {
E 4
I 4
D 15
			sprintf(pbuf, "%s.db", *db_p);
E 15
I 15
			(void)snprintf(pbuf, sizeof(pbuf), "%s.db", *db_p);
E 15
			if ((capdbp = dbopen(pbuf, O_RDONLY, 0, DB_HASH, 0))
			     != NULL) {
E 4
				free(record);
D 4
				return (-2);
E 4
I 4
				retval = cdbget(capdbp, &record, name);
D 18
				if (capdbp->close(capdbp) < 0)
E 18
I 18
				if (retval < 0) {
					/* no record available */
					(void)capdbp->close(capdbp);
					return (retval);
				}
				/* save the data; close frees it */
				clen = strlen(record);
				cbuf = malloc(clen + 1);
				memcpy(cbuf, record, clen + 1);
				if (capdbp->close(capdbp) < 0) {
					free(cbuf);
E 18
					return (-2);
D 8
				if (retval < 0)
					return (retval);
				rp = record + strlen(record) + 1;
				myfd = 0;
				goto tc_exp;
E 8
I 8
D 15
				*cap = malloc (strlen(record) + 1);
				strcpy(*cap, record);
E 15
I 15
D 18
				*len = strlen(record);
				*cap = malloc(*len + 1);
				memmove(*cap, record, *len + 1);
E 18
I 18
				}
				*len = clen;
				*cap = cbuf;
E 18
E 15
				return (retval);
E 8
			} else {
				fd = open(*db_p, O_RDONLY, 0);
				if (fd < 0) {
I 9
					/* No error on unfound file. */
					if (errno == ENOENT)
						continue;
E 9
					free(record);
					return (-2);
				}
				myfd = 1;
E 4
			}
D 4
			myfd = 1;
E 4
		}
D 4

E 4
		/*
		 * Find the requested capability record ...
		 */
		{
		char buf[BUFSIZ];
		register char *b_end, *bp;
		register int c;

		/*
		 * Loop invariants:
		 *	There is always room for one more character in record.
		 *	R_end always points just past end of record.
		 *	Rp always points just past last character in record.
		 *	B_end always points just past last character in buf.
		 *	Bp always points at next character in buf.
		 */
		b_end = buf;
		bp = buf;
		for (;;) {

			/*
			 * Read in a line implementing (\, newline)
			 * line continuation.
			 */
			rp = record;
			for (;;) {
				if (bp >= b_end) {
					int n;
		
					n = read(fd, buf, sizeof(buf));
					if (n <= 0) {
						if (myfd)
							(void)close(fd);
						if (n < 0) {
							free(record);
							return (-2);
						} else {
							fd = -1;
							eof = 1;
							break;
						}
					}
					b_end = buf+n;
					bp = buf;
				}
	
				c = *bp++;
				if (c == '\n') {
					if (rp > record && *(rp-1) == '\\') {
						rp--;
						continue;
					} else
						break;
				}
				*rp++ = c;

				/*
				 * Enforce loop invariant: if no room 
				 * left in record buffer, try to get
				 * some more.
				 */
				if (rp >= r_end) {
D 2
					u_int pos, newsize;
E 2
I 2
					u_int pos;
					size_t newsize;
E 2

					pos = rp - record;
					newsize = r_end - record + BFRAG;
					record = realloc(record, newsize);
					if (record == NULL) {
						errno = ENOMEM;
						if (myfd)
							(void)close(fd);
						return (-2);
					}
					r_end = record + newsize;
					rp = record + pos;
				}
			}
				/* loop invariant let's us do this */
			*rp++ = '\0';

			/*
			 * If encountered eof check next file.
			 */
			if (eof)
				break;
				
			/*
			 * Toss blank lines and comments.
			 */
			if (*record == '\0' || *record == '#')
				continue;
	
			/*
			 * See if this is the record we want ...
			 */
			if (cgetmatch(record, name) == 0) {
D 6
				foundit = 1;
				break;	/* found it! */
E 6
I 6
				if (nfield == NULL || !nfcmp(nfield, record)) {
					foundit = 1;
					break;	/* found it! */
				}
E 6
			}
		}
D 6
		}
E 6
I 6
	}
E 6
		if (foundit)
			break;
	}

	if (!foundit)
		return (-1);
D 3
	
E 3
I 3

E 3
	/*
	 * Got the capability record, but now we have to expand all tc=name
	 * references in it ...
	 */
tc_exp:	{
		register char *newicap, *s;
		register int newilen;
		u_int ilen;
		int diff, iret, tclen;
		char *icap, *scan, *tc, *tcstart, *tcend;

		/*
		 * Loop invariants:
		 *	There is room for one more character in record.
		 *	R_end points just past end of record.
		 *	Rp points just past last character in record.
		 *	Scan points at remainder of record that needs to be
		 *	scanned for tc=name constructs.
		 */
		scan = record;
I 4
		tc_not_resolved = 0;
E 4
		for (;;) {
			if ((tc = cgetcap(scan, "tc", '=')) == NULL)
				break;

			/*
			 * Find end of tc=name and stomp on the trailing `:'
			 * (if present) so we can use it to call ourselves.
			 */
			s = tc;
			for (;;)
				if (*s == '\0')
					break;
				else
					if (*s++ == ':') {
D 5
						*(s-1) = '\0';
E 5
I 5
						*(s - 1) = '\0';
E 5
						break;
					}
			tcstart = tc - 3;
			tclen = s - tcstart;
			tcend = s;

D 6
			iret = getent(&icap, &ilen, db_p, fd, tc, depth+1);
E 6
I 6
			iret = getent(&icap, &ilen, db_p, fd, tc, depth+1, 
				      NULL);
E 6
			newicap = icap;		/* Put into a register. */
			newilen = ilen;
			if (iret != 0) {
D 4
				/* an error or couldn't resolve tc= */
E 4
I 4
D 8
				/* couldn't resolve tc */
E 8
I 8
				/* an error */
				if (iret < -1) {
					if (myfd)
						(void)close(fd);
					free(record);
					return (iret);
				}
E 8
				if (iret == 1)
					tc_not_resolved = 1;
I 8
				/* couldn't resolve tc */
E 8
				if (iret == -1) {
D 5
					*(s-1) = ':';			
E 5
I 5
					*(s - 1) = ':';			
E 5
					scan = s - 1;
					tc_not_resolved = 1;
					continue;
					
				}
D 8
				/* an error */
E 4
				if (myfd)
					(void)close(fd);
				free(record);
				return (iret);
E 8
			}
D 8

E 8
			/* not interested in name field of tc'ed record */
			s = newicap;
			for (;;)
				if (*s == '\0')
					break;
				else
					if (*s++ == ':')
						break;
			newilen -= s - newicap;
			newicap = s;

			/* make sure interpolated record is `:'-terminated */
			s += newilen;
			if (*(s-1) != ':') {
				*s = ':';	/* overwrite NUL with : */
				newilen++;
			}

			/*
			 * Make sure there's enough room to insert the
			 * new record.
			 */
			diff = newilen - tclen;
			if (diff >= r_end - rp) {
D 2
				u_int pos, newsize, tcpos, tcposend;
E 2
I 2
				u_int pos, tcpos, tcposend;
				size_t newsize;
E 2

				pos = rp - record;
				newsize = r_end - record + diff + BFRAG;
				tcpos = tcstart - record;
				tcposend = tcend - record;
				record = realloc(record, newsize);
				if (record == NULL) {
					errno = ENOMEM;
					if (myfd)
						(void)close(fd);
					free(icap);
					return (-2);
				}
				r_end = record + newsize;
				rp = record + pos;
				tcstart = record + tcpos;
				tcend = record + tcposend;
			}

			/*
			 * Insert tc'ed record into our record.
			 */
			s = tcstart + newilen;
			bcopy(tcend, s, rp - tcend);
			bcopy(newicap, tcstart, newilen);
			rp += diff;
			free(icap);

			/*
			 * Start scan on `:' so next cgetcap works properly
			 * (cgetcap always skips first field).
			 */
			scan = s-1;
		}
I 6
	
E 6
	}
D 6

E 6
	/*
	 * Close file (if we opened it), give back any extra memory, and
	 * return capability, length and success.
	 */
	if (myfd)
		(void)close(fd);
	*len = rp - record - 1;	/* don't count NUL */
	if (r_end > rp)
D 2
		record = realloc(record, (u_int)(rp - record));
E 2
I 2
D 5
		record = realloc(record, (size_t)(rp - record));
E 5
I 5
		if ((record = 
		     realloc(record, (size_t)(rp - record))) == NULL) {
			errno = ENOMEM;
			return (-2);
		}
		
E 5
E 2
	*cap = record;
I 4
	if (tc_not_resolved)
		return (1);
E 4
	return (0);
D 6
}
E 6
I 6
}	
E 6

I 4
static int
cdbget(capdbp, bp, name)
	DB *capdbp;
	char **bp, *name;
{
	DBT key, data;
	char *buf;
	int st;

	key.data = name;
D 14
	key.size = strlen(name) + 1;
E 14
I 14
	key.size = strlen(name);
E 14

I 14
	for (;;) {
		/* Get the reference. */
		switch(capdbp->get(capdbp, &key, &data, 0)) {
		case -1:
			return (-2);
		case 1:
			return (-1);
		}
E 14
I 8

I 15
		/* If not an index to another record, leave. */
E 15
D 14
	/* 
	 * Get the reference.
	 */
E 8
	if ((st = capdbp->get(capdbp, &key, &data, 0)) < 0)
		return(-2);
	if (st == 1)
		return(-1);
E 14
I 14
		if (((char *)data.data)[0] != SHADOW)
			break;
E 14

D 8
	if (((char *)(data.data))[0] == RECORD) {
		*bp = &((char *)(data.data))[1];
		return(0);
	}
E 8
D 14
	if ((buf = malloc(data.size - 1)) == NULL)
		return(-2);
	
D 8
	strcpy(buf, &((char *)(data.data))[1]);
E 8
I 8
	strcpy(buf, (char *)(data.data));
E 8
	
	key.data = buf;
D 9
	key.size = data.size - 1;
E 9
I 9
	key.size = data.size;
E 9

I 8
	/*
	 * Get the record.
	 */
E 8
	if (capdbp->get(capdbp, &key, &data, 0) < 0) {
		free(buf);
		return(-2);
E 14
I 14
D 15
		key.data = data.data + 1;
E 15
I 15
		key.data = (char *)data.data + 1;
E 15
		key.size = data.size - 1;
E 14
	}
D 14
	free(buf);
E 14
I 14
	
E 14
D 15
	*bp = &((char *)(data.data))[1];
I 14

E 14
D 8
	return(0);
E 8
I 8
	if (((char *)(data.data))[0] == TCERR)
D 14
		return 1;
E 14
I 14
		return (1);
E 14
	else
D 14
		return 0;
E 14
I 14
		return (0);
E 15
I 15
	*bp = (char *)data.data + 1;
	return (((char *)(data.data))[0] == TCERR ? 1 : 0);
E 15
E 14
E 8
}
D 15

E 15

E 4
/*
 * Cgetmatch will return 0 if name is one of the names of the capability
 * record buf, -1 if not.
 */
int
cgetmatch(buf, name)
	char *buf, *name;
{
	register char *np, *bp;

	/*
	 * Start search at beginning of record.
	 */
	bp = buf;
	for (;;) {
		/*
		 * Try to match a record name.
		 */
		np = name;
		for (;;)
			if (*np == '\0')
				if (*bp == '|' || *bp == ':' || *bp == '\0')
					return (0);
				else
					break;
			else
				if (*bp++ != *np++)
					break;

		/*
		 * Match failed, skip to next name in record.
		 */
		bp--;	/* a '|' or ':' may have stopped the match */
		for (;;)
			if (*bp == '\0' || *bp == ':')
				return (-1);	/* match failed totally */
			else
				if (*bp++ == '|')
					break;	/* found next name */
	}
}

I 3




E 3
int
cgetfirst(buf, db_array)
	char **buf, **db_array;
{
I 2
D 3
	if (toprec) {
		if ((*buf = malloc(topreclen + 1)) == NULL) {
			errno = ENOMEM;
			return(-2);
		}
		strcpy(*buf, toprec);
		(void)cgetclose();
		gottoprec = 1;
		return(1);
	}
E 3
E 2
	(void)cgetclose();
	return (cgetnext(buf, db_array));
}

static FILE *pfp;
static int slash;
static char **dbp;

int
cgetclose()
{
	if (pfp != NULL) {
		(void)fclose(pfp);
		pfp = NULL;
	}
	dbp = NULL;
I 2
	gottoprec = 0;
E 2
	slash = 0;
D 2
	return (0);
E 2
I 2
	return(0);
E 2
}

/*
 * Cgetnext() gets either the first or next entry in the logical database 
 * specified by db_array.  It returns 0 upon completion of the database, 1
 * upon returning an entry with more remaining, and -1 if an error occurs.
 */
int
cgetnext(bp, db_array)
        register char **bp;
	char **db_array;
{
	size_t len;
D 6
	int status;
	char *cp, *line, *rp, buf[BSIZE];
E 6
I 6
	int status, i, done;
	char *cp, *line, *rp, *np, buf[BSIZE], nbuf[BSIZE];
E 6
I 3
	u_int dummy;
E 3

D 2
	if (dbp == NULL)
E 2
I 2
D 3
	if (dbp == NULL) {
		if (toprec && !gottoprec) {
			if ((*bp = malloc(topreclen + 1)) == NULL) {
				errno = ENOMEM;
				return(-2);
			}
			strcpy(*bp, toprec);
			gottoprec = 1;
			return(1);
		}
E 3
I 3
	if (dbp == NULL)
E 3
E 2
		dbp = db_array;
D 2

	if (pfp == NULL && (pfp = fopen(*dbp, "r")) == NULL)
E 2
I 2
D 3
	}
E 3
I 3

E 3
	if (pfp == NULL && (pfp = fopen(*dbp, "r")) == NULL) {
		(void)cgetclose();
E 2
		return (-1);
D 2

E 2
I 2
	}
E 2
	for(;;) {
D 3
		line = fgetline(pfp, &len);
		if (line == NULL) {
			(void)fclose(pfp);
			if (ferror(pfp)) {
D 2
				pfp = NULL;
				dbp = NULL;
				slash = 0;
E 2
I 2
				(void)cgetclose();
E 2
				return (-1);
			} else {
				dbp++;
				if (*dbp == NULL) {
E 3
I 3
		if (toprec && !gottoprec) {
			gottoprec = 1;
			line = toprec;
		} else {
D 17
			line = fgetline(pfp, &len);
E 17
I 17
			line = fgetln(pfp, &len);
E 17
			if (line == NULL && pfp) {
				(void)fclose(pfp);
				if (ferror(pfp)) {
E 3
D 2
					pfp = NULL;
					dbp = NULL;
					slash = 0;
E 2
I 2
					(void)cgetclose();
E 2
D 3
					return (0);
				} else if ((pfp = fopen(*dbp, "r")) == NULL) {
D 2
					pfp = NULL;
					dbp = NULL;
					slash = 0;
E 2
I 2
					(void)cgetclose();
E 3
E 2
					return (-1);
D 3
				} else
					continue;
E 3
I 3
				} else {
D 14
					dbp++;
					if (*dbp == NULL) {
E 14
I 14
					if (*++dbp == NULL) {
E 14
						(void)cgetclose();
						return (0);
D 14
					} else if ((pfp = fopen(*dbp, "r")) ==
					    NULL) {
E 14
I 14
					} else if ((pfp =
					    fopen(*dbp, "r")) == NULL) {
E 14
						(void)cgetclose();
						return (-1);
					} else
						continue;
				}
E 3
D 12
			}
E 12
I 12
			} else
				line[len - 1] = '\0';
E 12
D 3
		}
		if (isspace(*line) || *line == ':' || *line == '#' 
		    || len == 0 || slash) {
E 3
I 3
D 14
			if (isspace(*line) || *line == ':' || *line == '#' 
			    || len == 0 || slash) {
				if (len > 0 && line[len - 1] == '\\')
E 14
I 14
			if (len == 1) {
				slash = 0;
				continue;
			}
			if (isspace(*line) ||
			    *line == ':' || *line == '#' || slash) {
				if (line[len - 2] == '\\')
E 14
					slash = 1;
				else
					slash = 0;
				continue;
			}
E 3
D 14
			if (len > 0 && line[len - 1] == '\\')
E 14
I 14
			if (line[len - 2] == '\\')
E 14
				slash = 1;
			else
				slash = 0;
D 3
			continue;
		}
		if (len > 0 && line[len - 1] == '\\')
			slash = 1;
		else
			slash = 0;

E 3
I 3
		}			
E 3
D 6
		/* line points to a name line */
E 6

I 6

		/* 
		 * Line points to a name line.
		 */
		i = 0;
		done = 0;
		np = nbuf;
		for (;;) {
			for (cp = line; *cp != '\0'; cp++) {
				if (*cp == ':') {
					*np++ = ':';
					done = 1;
					break;
				}
				if (*cp == '\\')
					break;
				*np++ = *cp;
			}
			if (done) {
				*np = '\0';
				break;
			} else { /* name field extends beyond the line */
D 17
				line = fgetline(pfp, &len);
E 17
I 17
				line = fgetln(pfp, &len);
E 17
				if (line == NULL && pfp) {
					(void)fclose(pfp);
					if (ferror(pfp)) {
						(void)cgetclose();
						return (-1);
					}
D 12
				}
E 12
I 12
D 13
				} else {
E 13
I 13
				} else
E 13
					line[len - 1] = '\0';
E 12
			}
		}
E 6
		rp = buf;
D 6
		for(cp = line; *cp != NULL; cp++)
E 6
I 6
		for(cp = nbuf; *cp != NULL; cp++)
E 6
			if (*cp == '|' || *cp == ':')
				break;
			else
				*rp++ = *cp;

		*rp = '\0';
D 3
		status = cgetent(bp, db_array, &buf[0]);
E 3
I 3
D 6
		status = getent(bp, &dummy, db_array, -1, buf, 0);
E 6
I 6
D 7
		status = getent(bp, &dummy, db_array, -1, buf, 0, nbuf);
E 7
I 7
		/* 
		 * XXX 
		 * Last argument of getent here should be nbuf if we want true
		 * sequential access in the case of duplicates.  
		 * With NULL, getent will return the first entry found
		 * rather than the duplicate entry record.  This is a 
		 * matter of semantics that should be resolved.
		 */
		status = getent(bp, &dummy, db_array, -1, buf, 0, NULL);
E 7
E 6
E 3
D 4
		if (status == 0)
			return (1);
		if (status == -2 || status == -3) {
E 4
I 4
		if (status == -2 || status == -3)
E 4
D 2
			pfp = NULL;
			dbp = NULL;
			slash = 0;
E 2
I 2
			(void)cgetclose();
E 2
D 4
			return (status + 1);
		}
E 4
I 4

		return (status + 1);
E 4
	}
	/* NOTREACHED */
}

/*
 * Cgetstr retrieves the value of the string capability cap from the
 * capability record pointed to by buf.  A pointer to a decoded, NUL
 * terminated, malloc'd copy of the string is returned in the char *
 * pointed to by str.  The length of the string not including the trailing
 * NUL is returned on success, -1 if the requested string capability
 * couldn't be found, -2 if a system error was encountered (storage
 * allocation failure).
 */
int
cgetstr(buf, cap, str)
	char *buf, *cap;
	char **str;
{
	register u_int m_room;
	register char *bp, *mp;
	int len;
	char *mem;

	/*
	 * Find string capability cap
	 */
	bp = cgetcap(buf, cap, '=');
	if (bp == NULL)
		return (-1);

	/*
	 * Conversion / storage allocation loop ...  Allocate memory in
	 * chunks SFRAG in size.
	 */
	if ((mem = malloc(SFRAG)) == NULL) {
		errno = ENOMEM;
		return (-2);	/* couldn't even allocate the first fragment */
	}
	m_room = SFRAG;
	mp = mem;

	while (*bp != ':' && *bp != '\0') {
		/*
		 * Loop invariants:
		 *	There is always room for one more character in mem.
		 *	Mp always points just past last character in mem.
		 *	Bp always points at next character in buf.
		 */
		if (*bp == '^') {
			bp++;
			if (*bp == ':' || *bp == '\0')
				break;	/* drop unfinished escape */
			*mp++ = *bp++ & 037;
		} else if (*bp == '\\') {
			bp++;
			if (*bp == ':' || *bp == '\0')
				break;	/* drop unfinished escape */
			if ('0' <= *bp && *bp <= '7') {
				register int n, i;

				n = 0;
				i = 3;	/* maximum of three octal digits */
				do {
					n = n * 8 + (*bp++ - '0');
				} while (--i && '0' <= *bp && *bp <= '7');
				*mp++ = n;
			}
			else switch (*bp++) {
				case 'b': case 'B':
					*mp++ = '\b';
					break;
				case 't': case 'T':
					*mp++ = '\t';
					break;
				case 'n': case 'N':
					*mp++ = '\n';
					break;
				case 'f': case 'F':
					*mp++ = '\f';
					break;
				case 'r': case 'R':
					*mp++ = '\r';
					break;
				case 'e': case 'E':
					*mp++ = ESC;
					break;
				case 'c': case 'C':
					*mp++ = ':';
					break;
				default:
					/*
					 * Catches '\', '^', and
					 *  everything else.
					 */
					*mp++ = *(bp-1);
					break;
			}
		} else
			*mp++ = *bp++;
		m_room--;

		/*
		 * Enforce loop invariant: if no room left in current
		 * buffer, try to get some more.
		 */
		if (m_room == 0) {
D 2
			u_int size = mp - mem;
E 2
I 2
			size_t size = mp - mem;
E 2

			if ((mem = realloc(mem, size + SFRAG)) == NULL)
				return (-2);
			m_room = SFRAG;
			mp = mem + size;
		}
	}
	*mp++ = '\0';	/* loop invariant let's us do this */
	m_room--;
	len = mp - mem - 1;

	/*
	 * Give back any extra memory and return value and success.
	 */
	if (m_room != 0)
D 2
		mem = realloc(mem, (u_int)(mp - mem));
E 2
I 2
D 5
		mem = realloc(mem, (size_t)(mp - mem));
E 5
I 5
		if ((mem = realloc(mem, (size_t)(mp - mem))) == NULL)
			return (-2);
E 5
E 2
	*str = mem;
	return (len);
}

/*
 * Cgetustr retrieves the value of the string capability cap from the
 * capability record pointed to by buf.  The difference between cgetustr()
 * and cgetstr() is that cgetustr does not decode escapes but rather treats
 * all characters literally.  A pointer to a  NUL terminated malloc'd 
 * copy of the string is returned in the char pointed to by str.  The 
 * length of the string not including the trailing NUL is returned on success,
 * -1 if the requested string capability couldn't be found, -2 if a system 
 * error was encountered (storage allocation failure).
 */
int
cgetustr(buf, cap, str)
	char *buf, *cap, **str;
{
	register u_int m_room;
	register char *bp, *mp;
	int len;
	char *mem;

	/*
	 * Find string capability cap
	 */
	if ((bp = cgetcap(buf, cap, '=')) == NULL)
		return (-1);

	/*
	 * Conversion / storage allocation loop ...  Allocate memory in
	 * chunks SFRAG in size.
	 */
	if ((mem = malloc(SFRAG)) == NULL) {
		errno = ENOMEM;
		return (-2);	/* couldn't even allocate the first fragment */
	}
	m_room = SFRAG;
	mp = mem;

	while (*bp != ':' && *bp != '\0') {
		/*
		 * Loop invariants:
		 *	There is always room for one more character in mem.
		 *	Mp always points just past last character in mem.
		 *	Bp always points at next character in buf.
		 */
		*mp++ = *bp++;
		m_room--;

		/*
		 * Enforce loop invariant: if no room left in current
		 * buffer, try to get some more.
		 */
		if (m_room == 0) {
D 2
			u_int size = mp - mem;
E 2
I 2
			size_t size = mp - mem;
E 2

			if ((mem = realloc(mem, size + SFRAG)) == NULL)
				return (-2);
			m_room = SFRAG;
			mp = mem + size;
		}
	}
	*mp++ = '\0';	/* loop invariant let's us do this */
	m_room--;
	len = mp - mem - 1;

	/*
	 * Give back any extra memory and return value and success.
	 */
	if (m_room != 0)
D 2
		mem = realloc(mem, (u_int)(mp - mem));
E 2
I 2
D 5
		mem = realloc(mem, (size_t)(mp - mem));
E 5
I 5
		if ((mem = realloc(mem, (size_t)(mp - mem))) == NULL)
			return (-2);
E 5
E 2
	*str = mem;
	return (len);
}

/*
 * Cgetnum retrieves the value of the numeric capability cap from the
 * capability record pointed to by buf.  The numeric value is returned in
 * the long pointed to by num.  0 is returned on success, -1 if the requested
 * numeric capability couldn't be found.
 */
int
cgetnum(buf, cap, num)
	char *buf, *cap;
	long *num;
{
	register long n;
	register int base, digit;
	register char *bp;

	/*
	 * Find numeric capability cap
	 */
	bp = cgetcap(buf, cap, '#');
	if (bp == NULL)
		return (-1);

	/*
	 * Look at value and determine numeric base:
	 *	0x... or 0X...	hexadecimal,
	 * else	0...		octal,
	 * else			decimal.
	 */
	if (*bp == '0') {
		bp++;
		if (*bp == 'x' || *bp == 'X') {
			bp++;
			base = 16;
		} else
			base = 8;
	} else
		base = 10;

	/*
	 * Conversion loop ...
	 */
	n = 0;
	for (;;) {
		if ('0' <= *bp && *bp <= '9')
			digit = *bp - '0';
I 10
		else if ('a' <= *bp && *bp <= 'f')
			digit = 10 + *bp - 'a';
		else if ('A' <= *bp && *bp <= 'F')
			digit = 10 + *bp - 'A';
E 10
		else
D 10
			if (   ('a' <= *bp && *bp <= 'f')
			    || ('A' <= *bp && *bp <= 'F'))
				digit = 10 + *bp - 'a';
			else
				break;
E 10
I 10
			break;
E 10

		if (digit >= base)
			break;

		n = n * base + digit;
		bp++;
	}

	/*
	 * Return value and success.
	 */
	*num = n;
	return (0);
I 6
}


/*
 * Compare name field of record.
 */
static int
nfcmp(nf, rec)
	char *nf, *rec;
{
	char *cp, tmp;
	int ret;
	
	for (cp = rec; *cp != ':'; cp++)
		;
	
	tmp = *(cp + 1);
	*(cp + 1) = '\0';
	ret = strcmp(nf, rec);
	*(cp + 1) = tmp;

	return (ret);
E 6
}
E 1
