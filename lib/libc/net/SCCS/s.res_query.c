h48611
s 00002/00002/00275
d D 8.1 93/06/04 12:51:28 bostic 13 12
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00029/00007/00248
d D 5.12 93/06/02 17:04:59 karels 12 11
c integrate changes from bind 4.9 (most of them); continue to use address
c INADDR_ANY rather than 127.1; convert u_short to u_int16_t as appropriate
e
s 00005/00005/00250
d D 5.11 91/03/06 16:02:45 bostic 11 10
c resolver interface with named and friends defined in resolve.h
e
s 00001/00000/00254
d D 5.10 91/02/24 13:14:38 bostic 10 9
c need ctype.h, shouldn't have deleted it
e
s 00005/00007/00249
d D 5.9 91/02/24 12:40:28 bostic 9 8
c Add include files to get prototype declarations, and fix bugs found.
e
s 00002/00002/00254
d D 5.8 91/02/21 16:23:39 bostic 8 7
c make dn_skipname, fp_query, hostalias, p_cdname, p_class, p_query,
c p_rr, p_time, p_type, putlong and putshort hidden
e
s 00001/00011/00255
d D 5.7 90/06/01 14:17:13 bostic 7 6
c new copyright notice
e
s 00001/00001/00265
d D 5.6 90/05/15 19:46:26 bostic 6 5
c string.h is ANSI C include file
e
s 00027/00012/00239
d D 5.5 88/09/21 09:18:22 karels 5 4
c minor corrections to search procedure, always report any NO_DATA error,
c clarify comments
e
s 00000/00001/00251
d D 5.4 88/04/21 09:53:36 karels 4 3
c finish the fix
e
s 00014/00005/00238
d D 5.3 88/04/05 14:18:25 karels 3 2
c return NO_DATA instead of HOST_NOT_FOUND from res_search
c if we ever get a NO_DATA response; add res_querydomain debug line
e
s 00005/00009/00238
d D 5.2 88/03/29 11:13:22 karels 2 1
c don't check auth. bit on NXDOMAIN/noanswer (ready for neg. caching);
c add default error case
e
s 00247/00000/00000
d D 5.1 88/03/14 13:04:59 bostic 1 0
c date and time created 88/03/14 13:04:59 by bostic
e
u
U
f b 
t
T
I 1
D 12
/*
E 12
I 12
/*-
E 12
D 13
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 13
I 13
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 13
 *
D 7
 * Redistribution and use in source and binary forms are permitted
D 5
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 5
I 5
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 7
I 7
 * %sccs.include.redist.c%
I 12
 * -
 * Portions Copyright (c) 1993 by Digital Equipment Corporation.
 * 
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies, and that
 * the name of Digital Equipment Corporation not be used in advertising or
 * publicity pertaining to distribution of the document or software without
 * specific, written prior permission.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS" AND DIGITAL EQUIPMENT CORP. DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS.   IN NO EVENT SHALL DIGITAL EQUIPMENT
 * CORPORATION BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS
 * ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
 * SOFTWARE.
 * -
 * --Copyright--
E 12
E 7
E 5
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
I 12
static char rcsid[] = "$Id: res_query.c,v 1.1 1993/06/01 09:42:14 vixie Exp vixie $";
E 12
#endif /* LIBC_SCCS and not lint */

#include <sys/param.h>
D 9
#include <sys/socket.h>
E 9
#include <netinet/in.h>
D 9
#include <ctype.h>
E 9
I 9
#include <arpa/inet.h>
#include <arpa/nameser.h>
E 9
#include <netdb.h>
I 9
#include <resolv.h>
E 9
#include <stdio.h>
I 10
#include <ctype.h>
E 10
#include <errno.h>
I 9
#include <stdlib.h>
E 9
D 6
#include <strings.h>
E 6
I 6
#include <string.h>
E 6
D 9
#include <arpa/inet.h>
#include <arpa/nameser.h>
#include <resolv.h>
E 9

#if PACKETSZ > 1024
#define MAXPACKET	PACKETSZ
#else
#define MAXPACKET	1024
#endif

D 9
extern int errno;
E 9
int h_errno;

/*
 * Formulate a normal query, send, and await answer.
 * Returned answer is placed in supplied buffer "answer".
 * Perform preliminary check of answer, returning success only
 * if no error is indicated and the answer count is nonzero.
 * Return the size of the response on success, -1 on error.
 * Error number is left in h_errno.
I 2
 * Caller must parse answer and determine whether it answers the question.
E 2
 */
res_query(name, class, type, answer, anslen)
	char *name;		/* domain name */
	int class, type;	/* class and type of query */
	u_char *answer;		/* buffer to put answer */
	int anslen;		/* size of answer buffer */
{
	char buf[MAXPACKET];
	HEADER *hp;
	int n;

	if ((_res.options & RES_INIT) == 0 && res_init() == -1)
		return (-1);
#ifdef DEBUG
	if (_res.options & RES_DEBUG)
D 12
		printf("res_query(%s, %d, %d)\n", name, class, type);
E 12
I 12
		printf(";; res_query(%s, %d, %d)\n", name, class, type);
E 12
#endif
	n = res_mkquery(QUERY, name, class, type, (char *)NULL, 0, NULL,
	    buf, sizeof(buf));

	if (n <= 0) {
#ifdef DEBUG
		if (_res.options & RES_DEBUG)
D 12
			printf("res_query: mkquery failed\n");
E 12
I 12
			printf(";; res_query: mkquery failed\n");
E 12
#endif
		h_errno = NO_RECOVERY;
		return (n);
	}
D 9
	n = res_send(buf, n, answer, anslen);
E 9
I 9
	n = res_send(buf, n, (char *)answer, anslen);
E 9
	if (n < 0) {
#ifdef DEBUG
		if (_res.options & RES_DEBUG)
D 12
			printf("res_query: send error\n");
E 12
I 12
			printf(";; res_query: send error\n");
E 12
#endif
		h_errno = TRY_AGAIN;
		return(n);
	}

	hp = (HEADER *) answer;
	if (hp->rcode != NOERROR || ntohs(hp->ancount) == 0) {
#ifdef DEBUG
		if (_res.options & RES_DEBUG)
D 12
			printf("rcode = %d, ancount=%d\n", hp->rcode,
E 12
I 12
			printf(";; rcode = %d, ancount=%d\n", hp->rcode,
E 12
			    ntohs(hp->ancount));
#endif
		switch (hp->rcode) {
			case NXDOMAIN:
D 2
				/* Check if it's an authoritive answer */
				if (hp->aa)
					h_errno = HOST_NOT_FOUND;
				else
					h_errno = TRY_AGAIN;
E 2
I 2
				h_errno = HOST_NOT_FOUND;
E 2
				break;
			case SERVFAIL:
				h_errno = TRY_AGAIN;
				break;
			case NOERROR:
D 2
				if (hp->aa)
					h_errno = NO_ADDRESS;
				else
					h_errno = TRY_AGAIN;
E 2
I 2
D 3
				h_errno = NO_ADDRESS;
E 3
I 3
				h_errno = NO_DATA;
E 3
E 2
				break;
			case FORMERR:
			case NOTIMP:
			case REFUSED:
I 2
			default:
E 2
				h_errno = NO_RECOVERY;
I 2
				break;
E 2
		}
		return (-1);
	}
	return(n);
}

/*
 * Formulate a normal query, send, and retrieve answer in supplied buffer.
 * Return the size of the response on success, -1 on error.
 * If enabled, implement search rules until answer or unrecoverable failure
 * is detected.  Error number is left in h_errno.
 * Only useful for queries in the same name hierarchy as the local host
 * (not, for example, for host address-to-name lookups in domain in-addr.arpa).
 */
I 12
int
E 12
res_search(name, class, type, answer, anslen)
	char *name;		/* domain name */
	int class, type;	/* class and type of query */
	u_char *answer;		/* buffer to put answer */
	int anslen;		/* size of answer */
{
	register char *cp, **domain;
D 3
	int n, ret;
E 3
I 3
	int n, ret, got_nodata = 0;
E 3
D 8
	char *hostalias();
E 8
I 8
D 11
	static char *hostalias();
E 11
I 11
	char *__hostalias();
E 11
E 8

	if ((_res.options & RES_INIT) == 0 && res_init() == -1)
		return (-1);

	errno = 0;
I 3
D 12
	h_errno = HOST_NOT_FOUND;		/* default, if we never query */
E 12
I 12
	h_errno = HOST_NOT_FOUND;	/* default, if we never query */
E 12
E 3
	for (cp = name, n = 0; *cp; cp++)
		if (*cp == '.')
			n++;
D 11
	if (n == 0 && (cp = hostalias(name)))
E 11
I 11
	if (n == 0 && (cp = __hostalias(name)))
E 11
		return (res_query(cp, class, type, answer, anslen));

D 5
	if ((n == 0 || *--cp != '.') && (_res.options & RES_DEFNAMES))
	    for (domain = _res.dnsrch; *domain; domain++) {
E 5
I 5
	/*
	 * We do at least one level of search if
	 *	- there is no dot and RES_DEFNAME is set, or
	 *	- there is at least one dot, there is no trailing dot,
	 *	  and RES_DNSRCH is set.
	 */
	if ((n == 0 && _res.options & RES_DEFNAMES) ||
	   (n != 0 && *--cp != '.' && _res.options & RES_DNSRCH))
	     for (domain = _res.dnsrch; *domain; domain++) {
E 5
		ret = res_querydomain(name, *domain, class, type,
		    answer, anslen);
		if (ret > 0)
			return (ret);
		/*
		 * If no server present, give up.
		 * If name isn't found in this domain,
		 * keep trying higher domains in the search list
		 * (if that's enabled).
D 3
		 * On a NO_ADDRESS error, keep trying, otherwise
E 3
I 3
		 * On a NO_DATA error, keep trying, otherwise
E 3
		 * a wildcard entry of another type could keep us
		 * from finding this entry higher in the domain.
D 5
		 * If we get some other error (non-authoritative negative
		 * answer or server failure), then stop searching up,
E 5
I 5
		 * If we get some other error (negative answer or
		 * server failure), then stop searching up,
E 5
		 * but try the input name below in case it's fully-qualified.
		 */
		if (errno == ECONNREFUSED) {
			h_errno = TRY_AGAIN;
			return (-1);
		}
D 3
		if ((h_errno != HOST_NOT_FOUND && h_errno != NO_ADDRESS) ||
E 3
I 3
		if (h_errno == NO_DATA)
			got_nodata++;
		if ((h_errno != HOST_NOT_FOUND && h_errno != NO_DATA) ||
E 3
		    (_res.options & RES_DNSRCH) == 0)
			break;
D 4
		h_errno = 0;
E 4
	}
	/*
	 * If the search/default failed, try the name as fully-qualified,
	 * but only if it contained at least one dot (even trailing).
I 5
	 * This is purely a heuristic; we assume that any reasonable query
	 * about a top-level domain (for servers, SOA, etc) will not use
	 * res_search.
E 5
	 */
D 5
	if (n)
		return (res_querydomain(name, (char *)NULL, class, type,
		    answer, anslen));
E 5
I 5
	if (n && (ret = res_querydomain(name, (char *)NULL, class, type,
	    answer, anslen)) > 0)
		return (ret);
E 5
D 3
	h_errno = HOST_NOT_FOUND;
E 3
I 3
	if (got_nodata)
		h_errno = NO_DATA;
E 3
	return (-1);
}

/*
 * Perform a call on res_query on the concatenation of name and domain,
 * removing a trailing dot from name if domain is NULL.
 */
res_querydomain(name, domain, class, type, answer, anslen)
	char *name, *domain;
	int class, type;	/* class and type of query */
	u_char *answer;		/* buffer to put answer */
	int anslen;		/* size of answer */
{
	char nbuf[2*MAXDNAME+2];
	char *longname = nbuf;
	int n;

I 3
#ifdef DEBUG
	if (_res.options & RES_DEBUG)
D 12
		printf("res_querydomain(%s, %s, %d, %d)\n",
E 12
I 12
		printf(";; res_querydomain(%s, %s, %d, %d)\n",
E 12
		    name, domain, class, type);
#endif
E 3
	if (domain == NULL) {
		/*
		 * Check for trailing '.';
		 * copy without '.' if present.
		 */
		n = strlen(name) - 1;
		if (name[n] == '.' && n < sizeof(nbuf) - 1) {
			bcopy(name, nbuf, n);
			nbuf[n] = '\0';
		} else
			longname = name;
	} else
		(void)sprintf(nbuf, "%.*s.%.*s",
		    MAXDNAME, name, MAXDNAME, domain);

	return (res_query(longname, class, type, answer, anslen));
}

D 8
char *
E 8
I 8
D 11
static char *
E 8
hostalias(name)
	register char *name;
E 11
I 11
char *
__hostalias(name)
	register const char *name;
E 11
{
	register char *C1, *C2;
	FILE *fp;
	char *file, *getenv(), *strcpy(), *strncpy();
	char buf[BUFSIZ];
	static char abuf[MAXDNAME];

	file = getenv("HOSTALIASES");
	if (file == NULL || (fp = fopen(file, "r")) == NULL)
		return (NULL);
	buf[sizeof(buf) - 1] = '\0';
	while (fgets(buf, sizeof(buf), fp)) {
		for (C1 = buf; *C1 && !isspace(*C1); ++C1);
		if (!*C1)
			break;
		*C1 = '\0';
		if (!strcasecmp(buf, name)) {
			while (isspace(*++C1));
			if (!*C1)
				break;
			for (C2 = C1 + 1; *C2 && !isspace(*C2); ++C2);
			abuf[sizeof(abuf) - 1] = *C2 = '\0';
			(void)strncpy(abuf, C1, sizeof(abuf) - 1);
			fclose(fp);
			return (abuf);
		}
	}
	fclose(fp);
	return (NULL);
}
E 1
