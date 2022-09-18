h60007
s 00002/00002/00202
d D 8.1 93/06/04 12:51:24 bostic 29 28
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00047/00024/00157
d D 6.17 93/06/02 17:04:57 karels 28 27
c integrate changes from bind 4.9 (most of them); continue to use address
c INADDR_ANY rather than 127.1; convert u_short to u_int16_t as appropriate
e
s 00010/00010/00171
d D 6.16 91/03/06 16:02:44 bostic 27 26
c resolver interface with named and friends defined in resolve.h
e
s 00009/00007/00172
d D 6.15 91/02/24 12:40:27 bostic 26 25
c Add include files to get prototype declarations, and fix bugs found.
e
s 00018/00018/00161
d D 6.14 91/02/21 16:23:38 bostic 25 24
c make dn_skipname, fp_query, hostalias, p_cdname, p_class, p_query,
c p_rr, p_time, p_type, putlong and putshort hidden
e
s 00001/00001/00178
d D 6.13 90/12/28 16:00:56 william 24 23
c use param.h instead of types.h to pick up BYTE_ORDER transparently
e
s 00001/00011/00178
d D 6.12 90/06/01 14:16:58 bostic 23 22
c new copyright notice
e
s 00000/00001/00189
d D 6.11 89/12/27 14:45:09 bloom 22 21
c dnbuf is no longer used
e
s 00004/00001/00186
d D 6.10 89/12/27 12:56:22 bloom 21 20
c add more error checking
e
s 00001/00005/00186
d D 6.9 88/12/08 10:20:54 karels 20 19
c clear the whole header
e
s 00010/00019/00181
d D 6.8 88/09/20 12:15:26 karels 19 18
c remove DEFNAME processing in res_mkquery (do only in res_search)
e
s 00009/00003/00191
d D 6.7 88/03/07 21:17:23 bostic 18 17
c added Berkeley specific header
e
s 00004/00004/00190
d D 6.6 87/10/22 17:43:26 bostic 17 16
c ANSI C; sprintf now returns an int.
e
s 00000/00002/00194
d D 6.5 87/08/03 17:40:48 bostic 16 15
c karels; completion queries deleted
e
s 00036/00041/00160
d D 6.4 86/11/10 15:36:14 kjd 15 14
c fixes for dynamic updates from Mike Schwartz@washington
e
s 00001/00001/00200
d D 6.3 86/03/17 09:07:02 kjd 14 13
c move resolv.h to /usr/include
e
s 00002/00002/00199
d D 6.2 86/03/09 20:36:12 donn 13 12
c added LIBC_SCCS condition for sccs ids
e
s 00000/00000/00201
d D 6.1 85/10/31 15:29:49 kjd 12 11
c Freeze for November 1 network distribution
e
s 00002/00000/00199
d D 5.6 85/10/25 16:20:26 kjd 11 10
c declare sprintf as extern for SUNs
e
s 00002/00002/00197
d D 5.5 85/10/10 11:39:53 kjd 10 9
c Fix to get this to run on a SUN from smoot@ut-sally
e
s 00004/00001/00195
d D 5.4 85/09/14 11:21:05 bloom 9 8
c add ifdef DEBUG around debugging code, res_init() now returns a value
e
s 00002/00002/00194
d D 5.3 85/07/29 18:02:53 kjd 8 7
c Move /usr/include/nameser.h & resolv.h to /usr/include/arpa
e
s 00003/00003/00193
d D 5.2 85/07/16 11:03:14 kjd 7 6
c Change HTONS to standard htons()
e
s 00007/00004/00189
d D 5.1 85/05/30 12:06:42 dist 6 5
c Add copyright
e
s 00005/00000/00188
d D 4.5 85/04/01 15:11:19 ralph 5 4
c add copyright notice
e
s 00002/00002/00186
d D 4.4 85/03/28 09:26:07 ralph 4 3
c name changes and fix return value in res_init().
e
s 00015/00013/00173
d D 4.3 85/03/27 14:58:32 ralph 3 2
c make more machine independent.
e
s 00004/00005/00182
d D 4.2 85/03/15 16:11:07 ralph 2 1
c changed single label to names not ending in '.' as local.
e
s 00187/00000/00000
d D 4.1 85/03/01 10:42:18 ralph 1 0
c date and time created 85/03/01 10:42:18 by ralph
e
u
U
t
T
I 1
D 6
/*	%M%	%I%	%E%	*/

E 6
I 5
D 28
/*
E 28
I 28
/*-
E 28
D 6
 * Copyright (c) 1985 Regents of the University of California
 *	All Rights Reserved
E 6
I 6
D 29
 * Copyright (c) 1985 Regents of the University of California.
D 18
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 18
I 18
 * All rights reserved.
E 29
I 29
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
E 29
 *
D 23
 * Redistribution and use in source and binary forms are permitted
D 19
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 19
I 19
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
E 23
I 23
 * %sccs.include.redist.c%
I 28
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
E 28
E 23
E 19
E 18
E 6
 */
I 6

D 13
#ifndef lint
E 13
I 13
#if defined(LIBC_SCCS) && !defined(lint)
E 13
static char sccsid[] = "%W% (Berkeley) %G%";
I 28
static char rcsid[] = "$Id: res_mkquery.c,v 4.9.1.2 1993/05/17 10:00:01 vixie Exp $";
E 28
D 13
#endif not lint
E 13
I 13
D 18
#endif LIBC_SCCS and not lint
E 18
I 18
#endif /* LIBC_SCCS and not lint */
E 18
E 13
E 6

E 5
D 26
#include <stdio.h>
E 26
D 24
#include <sys/types.h>
E 24
I 24
#include <sys/param.h>
E 24
#include <netinet/in.h>
D 8
#include <nameser.h>
#include <resolv.h>
E 8
I 8
#include <arpa/nameser.h>
D 14
#include <arpa/resolv.h>
E 14
I 14
#include <resolv.h>
I 26
#include <stdio.h>
#include <string.h>
E 26
E 14
E 8

I 11
D 17
extern	char *sprintf();

E 17
E 11
/*
 * Form all types of queries.
 * Returns the size of the result or -1.
 */
D 4
mkquery(op, dname, class, type, data, datalen, newrr, buf, buflen)
E 4
I 4
D 28
res_mkquery(op, dname, class, type, data, datalen, newrr, buf, buflen)
E 28
I 28
res_mkquery(op, dname, class, type, data, datalen, newrr_in, buf, buflen)
E 28
E 4
	int op;			/* opcode of query */
D 26
	char *dname;		/* domain name */
E 26
I 26
	const char *dname;		/* domain name */
E 26
	int class, type;	/* class and type of query */
D 26
	char *data;		/* resource record data */
E 26
I 26
	const char *data;		/* resource record data */
E 26
	int datalen;		/* length of data */
D 26
	struct rrec *newrr;	/* new rr for modify or append */
E 26
I 26
D 28
	const struct rrec *newrr;	/* new rr for modify or append */
E 28
I 28
	const char *newrr_in;	/* new rr for modify or append */
E 28
E 26
	char *buf;		/* buffer to put query */
	int buflen;		/* size of buffer */
{
	register HEADER *hp;
	register char *cp;
	register int n;
I 28
	struct rrec *newrr = (struct rrec *) newrr_in;
E 28
D 22
	char dnbuf[MAXDNAME];
E 22
	char *dnptrs[10], **dpp, **lastdnptr;
I 3
D 26
	extern char *index();
E 26
E 3
D 2
	extern char *index();
E 2

I 9
#ifdef DEBUG
E 9
	if (_res.options & RES_DEBUG)
D 4
		printf("mkquery(%d, %s, %d, %d)\n", op, dname, class, type);
E 4
I 4
D 28
		printf("res_mkquery(%d, %s, %d, %d)\n", op, dname, class, type);
I 9
D 10
#endif
E 10
I 10
#endif DEBUG
E 28
I 28
		printf(";; res_mkquery(%d, %s, %d, %d)\n",
		       op, dname, class, type);
#endif
E 28
E 10
E 9
E 4
	/*
	 * Initialize header fields.
	 */
I 21
	if ((buf == NULL) || (buflen < sizeof(HEADER)))
		return(-1);
E 21
I 20
	bzero(buf, sizeof(HEADER));
E 20
	hp = (HEADER *) buf;
	hp->id = htons(++_res.id);
	hp->opcode = op;
D 20
	hp->qr = hp->aa = hp->tc = hp->ra = 0;
E 20
	hp->pr = (_res.options & RES_PRIMARY) != 0;
	hp->rd = (_res.options & RES_RECURSE) != 0;
	hp->rcode = NOERROR;
D 20
	hp->qdcount = 0;
	hp->ancount = 0;
	hp->nscount = 0;
	hp->arcount = 0;
E 20
	cp = buf + sizeof(HEADER);
	buflen -= sizeof(HEADER);
	dpp = dnptrs;
	*dpp++ = buf;
	*dpp++ = NULL;
D 2
	lastdnptr = dnptrs + sizeof(dnptrs);
E 2
I 2
	lastdnptr = dnptrs + sizeof(dnptrs)/sizeof(dnptrs[0]);
E 2
D 19
	/*
D 2
	 * If the domain name consists of a single label, then
E 2
I 2
D 3
	 * If the domain name does not end in '.', then
E 3
I 3
	 * If the domain name contains no dots (single label), then
E 3
E 2
	 * append the default domain name to the one given.
	 */
D 2
	if ((_res.options & RES_DEFNAMES) && dname[0] != '\0' &&
	    index(dname, '.') == NULL) {
E 2
I 2
D 3
	if ((_res.options & RES_DEFNAMES) && (n = strlen(dname)) > 0 &&
	    dname[n - 1] != '.') {
E 3
I 3
D 10
	if ((_res.options & RES_DEFNAMES) && dname[0] != '\0' &&
E 10
I 10
	if ((_res.options & RES_DEFNAMES) && dname != 0 && dname[0] != '\0' &&
E 10
	    index(dname, '.') == NULL) {
E 3
E 2
		if (!(_res.options & RES_INIT))
D 9
			res_init();
E 9
I 9
			if (res_init() == -1)
				return(-1);
E 9
D 17
		if (_res.defdname[0] != '\0')
			dname = sprintf(dnbuf, "%s.%s", dname, _res.defdname);
E 17
I 17
		if (_res.defdname[0] != '\0') {
			(void)sprintf(dnbuf, "%s.%s", dname, _res.defdname);
			dname = dnbuf;
		}
E 17
	}
E 19
	/*
	 * perform opcode specific processing
	 */
	switch (op) {
	case QUERY:
D 16
	case CQUERYM:
	case CQUERYU:
E 16
D 21
		buflen -= QFIXEDSZ;
E 21
I 21
		if ((buflen -= QFIXEDSZ) < 0)
			return(-1);
E 21
D 26
		if ((n = dn_comp(dname, cp, buflen, dnptrs, lastdnptr)) < 0)
E 26
I 26
		if ((n = dn_comp((u_char *)dname, (u_char *)cp, buflen,
		    (u_char **)dnptrs, (u_char **)lastdnptr)) < 0)
E 26
			return (-1);
		cp += n;
		buflen -= n;
D 3
		*((u_short *)cp) = htons(type);
E 3
I 3
D 25
		putshort(type, cp);
E 25
I 25
D 27
		__putshort(type, cp);
E 27
I 27
		__putshort(type, (u_char *)cp);
E 27
E 25
E 3
D 28
		cp += sizeof(u_short);
E 28
I 28
		cp += sizeof(u_int16_t);
E 28
D 3
		*((u_short *)cp) = htons(class);
E 3
I 3
D 25
		putshort(class, cp);
E 25
I 25
D 27
		__putshort(class, cp);
E 27
I 27
		__putshort(class, (u_char *)cp);
E 27
E 25
E 3
D 28
		cp += sizeof(u_short);
E 28
I 28
		cp += sizeof(u_int16_t);
E 28
D 7
		hp->qdcount = HTONS(1);
E 7
I 7
		hp->qdcount = htons(1);
E 7
		if (op == QUERY || data == NULL)
			break;
		/*
		 * Make an additional record for completion domain.
		 */
I 3
		buflen -= RRFIXEDSZ;
E 3
D 26
		if ((n = dn_comp(data, cp, buflen, dnptrs, lastdnptr)) < 0)
E 26
I 26
		if ((n = dn_comp((u_char *)data, (u_char *)cp, buflen,
		    (u_char **)dnptrs, (u_char **)lastdnptr)) < 0)
E 26
			return (-1);
		cp += n;
		buflen -= n;
D 3
		*((u_short *)cp) = htons(T_NULL);
E 3
I 3
D 25
		putshort(T_NULL, cp);
E 25
I 25
D 27
		__putshort(T_NULL, cp);
E 27
I 27
		__putshort(T_NULL, (u_char *)cp);
E 27
E 25
E 3
D 28
		cp += sizeof(u_short);
E 28
I 28
		cp += sizeof(u_int16_t);
E 28
D 3
		*((u_short *)cp) = htons(class);
E 3
I 3
D 25
		putshort(class, cp);
E 25
I 25
D 27
		__putshort(class, cp);
E 27
I 27
		__putshort(class, (u_char *)cp);
E 27
E 25
E 3
D 28
		cp += sizeof(u_short);
E 28
I 28
		cp += sizeof(u_int16_t);
E 28
D 3
		*((u_long *)cp) = 0;
E 3
I 3
D 25
		putlong(0, cp);
E 25
I 25
D 27
		__putlong(0, cp);
E 27
I 27
		__putlong(0, (u_char *)cp);
E 27
E 25
E 3
D 28
		cp += sizeof(u_long);
E 28
I 28
		cp += sizeof(u_int32_t);
E 28
D 3
		*((u_short *)cp) = 0;
E 3
I 3
D 25
		putshort(0, cp);
E 25
I 25
D 27
		__putshort(0, cp);
E 27
I 27
		__putshort(0, (u_char *)cp);
E 27
E 25
E 3
D 28
		cp += sizeof(u_short);
E 28
I 28
		cp += sizeof(u_int16_t);
E 28
D 7
		hp->arcount = HTONS(1);
E 7
I 7
		hp->arcount = htons(1);
E 7
		break;

	case IQUERY:
		/*
		 * Initialize answer section
		 */
		if (buflen < 1 + RRFIXEDSZ + datalen)
			return (-1);
		*cp++ = '\0';	/* no domain name */
D 3
		*((u_short *)cp) = htons(type);
E 3
I 3
D 25
		putshort(type, cp);
E 25
I 25
D 27
		__putshort(type, cp);
E 27
I 27
		__putshort(type, (u_char *)cp);
E 27
E 25
E 3
D 28
		cp += sizeof(u_short);
E 28
I 28
		cp += sizeof(u_int16_t);
E 28
D 3
		*((u_short *)cp) = htons(class);
E 3
I 3
D 25
		putshort(class, cp);
E 25
I 25
D 27
		__putshort(class, cp);
E 27
I 27
		__putshort(class, (u_char *)cp);
E 27
E 25
E 3
D 28
		cp += sizeof(u_short);
E 28
I 28
		cp += sizeof(u_int16_t);
E 28
D 3
		*((u_long *)cp) = 0;
E 3
I 3
D 25
		putlong(0, cp);
E 25
I 25
D 27
		__putlong(0, cp);
E 27
I 27
		__putlong(0, (u_char *)cp);
E 27
E 25
E 3
D 28
		cp += sizeof(u_long);
E 28
I 28
		cp += sizeof(u_int32_t);
E 28
D 3
		*((u_short *)cp) = htons(datalen);
E 3
I 3
D 25
		putshort(datalen, cp);
E 25
I 25
D 27
		__putshort(datalen, cp);
E 27
I 27
		__putshort(datalen, (u_char *)cp);
E 27
E 25
E 3
D 28
		cp += sizeof(u_short);
E 28
I 28
		cp += sizeof(u_int16_t);
E 28
		if (datalen) {
			bcopy(data, cp, datalen);
			cp += datalen;
		}
D 7
		hp->ancount = HTONS(1);
E 7
I 7
		hp->ancount = htons(1);
E 7
		break;

D 15
#ifdef notdef
E 15
I 15
#ifdef ALLOW_UPDATES
	/*
	 * For UPDATEM/UPDATEMA, do UPDATED/UPDATEDA followed by UPDATEA
	 * (Record to be modified is followed by its replacement in msg.)
	 */
	case UPDATEM:
	case UPDATEMA:

E 15
	case UPDATED:
		/*
D 15
		 * Put record to be added or deleted in additional section
E 15
I 15
		 * The res code for UPDATED and UPDATEDA is the same; user
		 * calls them differently: specifies data for UPDATED; server
		 * ignores data if specified for UPDATEDA.
E 15
		 */
I 15
	case UPDATEDA:
E 15
		buflen -= RRFIXEDSZ + datalen;
D 15
		if ((n = dn_comp(dname, cp, buflen, NULL, NULL)) < 0)
E 15
I 15
		if ((n = dn_comp(dname, cp, buflen, dnptrs, lastdnptr)) < 0)
E 15
			return (-1);
		cp += n;
D 15
		*((u_short *)cp) = htons(type);
		cp += sizeof(u_short);
		*((u_short *)cp) = htons(class);
		cp += sizeof(u_short);
		*((u_long *)cp) = 0;
E 15
I 15
D 25
		putshort(type, cp);
E 25
I 25
		__putshort(type, cp);
E 25
D 28
                cp += sizeof(u_short);
E 28
I 28
                cp += sizeof(u_int16_t);
E 28
D 25
                putshort(class, cp);
E 25
I 25
                __putshort(class, cp);
E 25
D 28
                cp += sizeof(u_short);
E 28
I 28
                cp += sizeof(u_int16_t);
E 28
D 25
		putlong(0, cp);
E 25
I 25
		__putlong(0, cp);
E 25
E 15
D 28
		cp += sizeof(u_long);
E 28
I 28
		cp += sizeof(u_int32_t);
E 28
D 15
		*((u_short *)cp) = htons(datalen);
		cp += sizeof(u_short);
E 15
I 15
D 25
		putshort(datalen, cp);
E 25
I 25
		__putshort(datalen, cp);
E 25
D 28
                cp += sizeof(u_short);
E 28
I 28
                cp += sizeof(u_int16_t);
E 28
E 15
		if (datalen) {
			bcopy(data, cp, datalen);
			cp += datalen;
		}
D 15
		break;
E 15
I 15
		if ( (op == UPDATED) || (op == UPDATEDA) ) {
			hp->ancount = htons(0);
			break;
		}
		/* Else UPDATEM/UPDATEMA, so drop into code for UPDATEA */
E 15

D 15
	case UPDATEM:
		/*
		 * Record to be modified followed by its replacement
		 */
E 15
I 15
	case UPDATEA:	/* Add new resource record */
E 15
		buflen -= RRFIXEDSZ + datalen;
		if ((n = dn_comp(dname, cp, buflen, dnptrs, lastdnptr)) < 0)
			return (-1);
		cp += n;
D 15
		*((u_short *)cp) = htons(type);
		cp += sizeof(u_short);
		*((u_short *)cp) = htons(class);
		cp += sizeof(u_short);
		*((u_long *)cp) = 0;
E 15
I 15
D 25
		putshort(newrr->r_type, cp);
E 25
I 25
		__putshort(newrr->r_type, cp);
E 25
D 28
                cp += sizeof(u_short);
E 28
I 28
                cp += sizeof(u_int16_t);
E 28
D 25
                putshort(newrr->r_class, cp);
E 25
I 25
                __putshort(newrr->r_class, cp);
E 25
D 28
                cp += sizeof(u_short);
E 28
I 28
                cp += sizeof(u_int16_t);
E 28
D 25
		putlong(0, cp);
E 25
I 25
		__putlong(0, cp);
E 25
E 15
D 28
		cp += sizeof(u_long);
E 28
I 28
		cp += sizeof(u_int32_t);
E 28
D 15
		*((u_short *)cp) = htons(datalen);
		cp += sizeof(u_short);
		if (datalen) {
			bcopy(data, cp, datalen);
			cp += datalen;
		}

	case UPDATEA:
		buflen -= RRFIXEDSZ + newrr->r_size;
		if ((n = dn_comp(dname, cp, buflen, dnptrs, lastdnptr)) < 0)
			return (-1);
		cp += n;
		*((u_short *)cp) = htons(newrr->r_type);
		cp += sizeof(u_short);
		*((u_short *)cp) = htons(newrr->r_type);
		cp += sizeof(u_short);
		*((u_long *)cp) = htonl(newrr->r_ttl);
		cp += sizeof(u_long);
		*((u_short *)cp) = htons(newrr->r_size);
		cp += sizeof(u_short);
E 15
I 15
D 25
		putshort(newrr->r_size, cp);
E 25
I 25
		__putshort(newrr->r_size, cp);
E 25
D 28
                cp += sizeof(u_short);
E 28
I 28
                cp += sizeof(u_int16_t);
E 28
E 15
		if (newrr->r_size) {
			bcopy(newrr->r_data, cp, newrr->r_size);
			cp += newrr->r_size;
		}
I 15
		hp->ancount = htons(0);
E 15
		break;
D 15
#endif
E 15
I 15

D 28
#endif ALLOW_UPDATES
E 28
I 28
#endif /* ALLOW_UPDATES */
E 28
E 15
	}
	return (cp - buf);
}
E 1
