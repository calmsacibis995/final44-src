h23941
s 00002/00002/00136
d D 8.1 93/06/02 20:06:27 bostic 19 18
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00053/00009/00085
d D 5.16 93/06/02 18:04:11 karels 18 17
c changes from bind 4.9
e
s 00005/00000/00089
d D 5.15 91/04/03 16:22:27 bostic 17 16
c protect all user-level include files against reinclusion
e
s 00024/00005/00065
d D 5.14 91/03/03 16:59:00 bostic 16 15
c put in prototypes for private libc/net routines
e
s 00003/00002/00067
d D 5.13 91/02/24 14:17:50 bostic 15 14
c dn_comp and dn_expand all expect u_char's, not chars
e
s 00005/00009/00064
d D 5.12 91/02/22 09:30:46 bostic 14 13
c all the p_ routines are static to the library
e
s 00014/00000/00059
d D 5.11 91/02/22 08:06:42 donn 13 12
c Added prototype declarations for documented interfaces.
e
s 00001/00011/00058
d D 5.10 90/06/01 14:01:26 bostic 12 11
c new copyright notice
e
s 00001/00001/00068
d D 5.9 89/12/18 10:29:06 karels 11 10
c add p_time()
e
s 00003/00002/00066
d D 5.8 89/12/14 11:22:36 karels 10 9
c increase size of search list array, but limit default to 3 anyway
e
s 00011/00001/00057
d D 5.7 89/12/13 20:59:41 karels 9 8
c move pathname defn. here; up timeout for host-req rfc
e
s 00014/00006/00044
d D 5.6 88/09/20 16:38:06 bostic 8 7
c add Berkeley specific copyright
e
s 00008/00001/00042
d D 5.5 87/05/12 22:13:25 karels 7 6
c add list of local domains
e
s 00010/00009/00033
d D 5.4 86/02/22 09:09:06 bloom 6 5
c add stayopen flag to options
e
s 00008/00002/00034
d D 5.3 85/10/09 19:46:45 kjd 5 3
c Add support for resolver to query multiple name servers
e
s 00007/00002/00034
d R 5.3 85/10/09 19:31:33 kjd 4 3
c Add support for resolver to query multiple name servers
e
s 00000/00006/00036
d D 5.2 85/07/31 14:22:24 kjd 3 2
c Move definition of CONFFILE to res_init.c
e
s 00008/00001/00034
d D 5.1 85/05/30 09:39:54 dist 2 1
c Add copyright
e
s 00034/00000/00000
d D 4.1 85/03/01 10:19:53 ralph 1 0
c date and time created 85/03/01 10:19:53 by ralph
e
u
U
t
T
I 5
D 8

E 8
E 5
I 1
D 2
/*	%M%	%I%	%E%	*/
E 2
I 2
D 18
/*
E 18
I 18
/*-
E 18
D 7
 * Copyright (c) 1983 Regents of the University of California.
E 7
I 7
D 8
 * Copyright (c) 1983, 1987 Regents of the University of California.
E 7
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 8
I 8
D 10
 * Copyright (c) 1983, 1987 The Regents of the University of California.
E 10
I 10
D 19
 * Copyright (c) 1983, 1987, 1989 The Regents of the University of California.
E 10
 * All rights reserved.
E 19
I 19
 * Copyright (c) 1983, 1987, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 19
E 8
 *
I 8
D 12
 * Redistribution and use in source and binary forms are permitted
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
E 12
I 12
 * %sccs.include.redist.c%
E 12
 *
E 8
 *	%W% (Berkeley) %G%
I 18
 *	$Id: resolv.h,v 4.9.1.2 1993/05/17 09:59:01 vixie Exp $
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
E 18
 */

I 17
#ifndef _RESOLV_H_
#define	_RESOLV_H_

I 18
#include <sys/types.h>
E 18
E 17
E 2
/*
I 9
 * Resolver configuration file.
 * Normally not present, but may contain the address of the
 * inital name server(s) to query and the domain search list.
 */

#ifndef _PATH_RESCONF
#define _PATH_RESCONF        "/etc/resolv.conf"
#endif

/*
E 9
 * Global defines and variables for resolver stub.
 */
D 8

D 3
/*
 * Resolver configuration file. Contains the address of the
 * inital name server to query and the default domain for
 * non fully qualified domain names.
 */
#define CONFFILE "/usr/local/lib/resolv.conf"
E 3

E 8
I 5
D 14
#define	MAXNS		3		/* max # name servers we'll track */
I 7
D 10
#define	MAXDNSRCH	3		/* max # default domain levels to try */
E 10
I 10
#define	MAXDFLSRCH	3		/* # default domain levels to try */
#define	MAXDNSRCH	6		/* max # domains in search path */
E 10
#define	LOCALDOMAINPARTS 2		/* min levels in name that is "local" */
E 14
I 14
#define	MAXNS			3	/* max # name servers we'll track */
#define	MAXDFLSRCH		3	/* # default domain levels to try */
#define	MAXDNSRCH		6	/* max # domains in search path */
#define	LOCALDOMAINPARTS	2	/* min levels in name that is "local" */
E 14
E 7

I 7
D 9
#define	RES_TIMEOUT	4		/* seconds between retries */
E 9
I 9
D 14
#define	RES_TIMEOUT	5		/* min. seconds between retries */
E 14
I 14
#define	RES_TIMEOUT		5	/* min. seconds between retries */
E 14
E 9
E 7

E 5
D 18
struct state {
E 18
I 18
struct __res_state {
E 18
D 5
	int	retrans;		/* retransmition time interval */
E 5
I 5
	int	retrans;	 	/* retransmition time interval */
E 5
	int	retry;			/* number of times to retransmit */
D 6
	int	options;		/* option flags - see below. */
E 6
I 6
	long	options;		/* option flags - see below. */
E 6
D 5
	struct	sockaddr_in nsaddr;	/* address of name server */
E 5
I 5
	int	nscount;		/* number of name servers */
	struct	sockaddr_in nsaddr_list[MAXNS];	/* address of name server */
#define	nsaddr	nsaddr_list[0]		/* for backward compatibility */
E 5
	u_short	id;			/* current packet id */
D 18
	char	defdname[MAXDNAME];	/* default domain */
E 18
I 7
	char	*dnsrch[MAXDNSRCH+1];	/* components of domain to search */
I 18
	char	defdname[MAXDNAME];	/* default domain */
	long	pfcode;			/* RES_PRF_ flags - see below. */
E 18
E 7
};

/*
D 18
 * Resolver options
E 18
I 18
 * Resolver options (keep these in synch with res_debug.c, please)
E 18
 */
D 6
#define RES_INIT	0x001		/* address initialized */
#define RES_DEBUG	0x002		/* print debug messages */
#define RES_AAONLY	0x004		/* authoritative answers only */
#define RES_USEVC	0x008		/* use virtual circuit */
#define RES_PRIMARY	0x010		/* query primary server only */
#define RES_IGNTC	0x020		/* ignore trucation errors */
#define RES_RECURSE	0x040		/* recursion desired */
#define RES_DEFNAMES	0x080		/* use default domain name */
E 6
I 6
#define RES_INIT	0x0001		/* address initialized */
#define RES_DEBUG	0x0002		/* print debug messages */
#define RES_AAONLY	0x0004		/* authoritative answers only */
#define RES_USEVC	0x0008		/* use virtual circuit */
#define RES_PRIMARY	0x0010		/* query primary server only */
#define RES_IGNTC	0x0020		/* ignore trucation errors */
#define RES_RECURSE	0x0040		/* recursion desired */
#define RES_DEFNAMES	0x0080		/* use default domain name */
#define RES_STAYOPEN	0x0100		/* Keep TCP socket open */
I 7
#define RES_DNSRCH	0x0200		/* search up local domain tree */

#define RES_DEFAULT	(RES_RECURSE | RES_DEFNAMES | RES_DNSRCH)
E 7
E 6

D 18
extern struct state _res;
E 18
I 18
/*
 * Resolver "pfcode" values.  Used by dig.
 */
#define RES_PRF_STATS	0x0001
/*			0x0002	*/
#define RES_PRF_CLASS   0x0004
#define RES_PRF_CMD	0x0008
#define RES_PRF_QUES	0x0010
#define RES_PRF_ANS	0x0020
#define RES_PRF_AUTH	0x0040
#define RES_PRF_ADD	0x0080
#define RES_PRF_HEAD1	0x0100
#define RES_PRF_HEAD2	0x0200
#define RES_PRF_TTLID	0x0400
#define RES_PRF_HEADX	0x0800
#define RES_PRF_QUERY	0x1000
#define RES_PRF_REPLY	0x2000
#define RES_PRF_INIT    0x4000
/*			0x8000	*/
E 18
I 13

#include <sys/cdefs.h>
I 16
#include <stdio.h>
E 16

I 18
extern struct __res_state _res;

E 18
I 16
/* Private routines shared between libc/net, named, nslookup and others. */
#define	dn_skipname	__dn_skipname
#define	fp_query	__fp_query
#define	hostalias	__hostalias
#define	putlong		__putlong
#define	putshort	__putshort
#define p_class		__p_class
#define p_time		__p_time
#define p_type		__p_type
E 16
__BEGIN_DECLS
D 14

/* THESE SHOULD ALL BE PREFIXED WITH UNDERSCORES */
E 13
D 11
extern char *p_cdname(), *p_rr(), *p_type(), *p_class();
E 11
I 11
extern char *p_cdname(), *p_rr(), *p_type(), *p_class(), *p_time();
I 13

E 14
D 15
int	dn_comp __P((const char *, char *, int, char **, char **));
int	dn_expand __P((const char *, const char *, const char *, char *, int));
E 15
I 15
D 16
int	dn_comp __P((const u_char *, u_char *, int, u_char **, u_char **));
int	dn_expand __P((const u_char *, const u_char *, const u_char *,
E 16
I 16
int	 __dn_skipname __P((const u_char *, const u_char *));
I 18
void	 __fp_resstat __P((struct __res_state *, FILE *));
E 18
void	 __fp_query __P((char *, FILE *));
char	*__hostalias __P((const char *));
D 18
void	 __putlong __P((u_long, u_char *));
E 18
I 18
void	 __putlong __P((u_int32_t, u_char *));
E 18
void	 __putshort __P((u_short, u_char *));
char	*__p_class __P((int));
D 18
char	*__p_time __P((u_long));
E 18
I 18
char	*__p_time __P((u_int32_t));
E 18
char	*__p_type __P((int));

int	 dn_comp __P((const u_char *, u_char *, int, u_char **, u_char **));
int	 dn_expand __P((const u_char *, const u_char *, const u_char *,
E 16
D 18
		u_char *, int));
E 18
I 18
			u_char *, int));
E 18
E 15
D 16
int	res_init __P((void));
int	res_mkquery __P((int, const char *, int, int, const char *, int,
E 16
I 16
int	 res_init __P((void));
int	 res_mkquery __P((int, const char *, int, int, const char *, int,
E 16
D 18
		const struct rrec *, char *, int));
E 18
I 18
			  const char *, char *, int));
E 18
D 16
int	res_send __P((const char *, int, char *, int));
E 16
I 16
int	 res_send __P((const char *, int, char *, int));
E 16
__END_DECLS
I 17

#endif /* !_RESOLV_H_ */
E 17
E 13
E 11
E 1
