h25402
s 00002/00002/00115
d D 8.1 93/06/02 20:06:04 bostic 21 20
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00025/00003/00092
d D 5.17 93/06/02 17:07:46 karels 20 19
c add hstrerror from bind 4.9
e
s 00001/00001/00094
d D 5.16 92/03/29 08:17:34 bostic 19 18
c gethostbyname should be const char, not char
e
s 00005/00000/00090
d D 5.15 91/04/03 16:15:11 bostic 18 17
c protect all user-level include files against reinclusion
e
s 00001/00001/00089
d D 5.14 91/03/02 15:19:31 bostic 17 16
c gethostent used by mkhosts(1)
e
s 00002/00002/00088
d D 5.13 91/02/24 14:15:48 bostic 16 15
c gethostbyaddr takes a char *, not a void *
c gethostbyname modifies what its argument references
e
s 00027/00005/00063
d D 5.12 91/02/22 08:03:38 donn 15 14
c Added new prototype declarations and cleaned up.
e
s 00011/00017/00057
d D 5.11 90/05/21 17:01:06 bostic 14 12
c add network pathnames from libc/net/*
e
s 00001/00002/00072
d D 5.10.1.1 89/02/14 17:45:51 bostic 13 12
c branch for updated copyright for network release
e
s 00011/00006/00063
d D 5.10 88/06/27 16:40:45 bostic 12 11
c install approved copyright notice
e
s 00013/00005/00056
d D 5.9 88/04/05 10:44:09 karels 11 10
c change NO_ADDRESS to NO_DATA
e
s 00001/00003/00060
d D 5.8 87/11/18 09:24:01 bostic 10 9
c don't declare h_errno
e
s 00001/00001/00062
d D 5.7 86/05/12 11:38:44 kjd 9 8
c Fix comment for NO_ADDRESS
e
s 00004/00004/00059
d D 5.6 86/05/09 22:04:06 lepreau 8 7
c n_net is unsigned long, not int.
e
s 00001/00000/00062
d D 5.5 85/11/11 11:41:19 kjd 7 6
c Add fourth error return NO_ADDRESS
e
s 00010/00000/00052
d D 5.4 85/11/04 18:49:18 kjd 6 4
c Add error return codes for gethostby*() routines
e
s 00001/00002/00050
d R 5.4 85/08/26 21:12:10 mckusick 5 4
c back out -r5.2 since the code DOES NOT WORK with this change!
c Kevin what are your doing!?!?!
e
s 00001/00001/00051
d D 5.3 85/08/25 13:37:05 mckusick 4 3
c kdj, you really ought to make sure that your backwards compatibility
c is syntactically correct.
e
s 00002/00001/00050
d D 5.2 85/08/07 18:41:51 kjd 3 2
c Add h_addr_list to hostent
e
s 00008/00001/00043
d D 5.1 85/06/18 18:36:50 mckusick 2 1
c Add copyright
e
s 00044/00000/00000
d D 4.1 82/10/05 16:46:51 sam 1 0
c date and time created 82/10/05 16:46:51 by sam
e
u
U
f b 
t
T
I 1
D 2
/*	%M%	%I%	%E%	*/
E 2
I 2
D 14
/*
E 14
I 14
/*-
E 14
D 11
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 11
I 11
D 12
 * Copyright (c) 1980,1983,1988 Regents of the University of California.
E 12
I 12
D 21
 * Copyright (c) 1980, 1983, 1988 Regents of the University of California.
E 12
 * All rights reserved.
E 21
I 21
 * Copyright (c) 1980, 1983, 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 21
E 11
 *
I 11
D 14
 * Redistribution and use in source and binary forms are permitted
D 12
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 12
I 12
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
E 14
I 14
 * %sccs.include.redist.c%
E 14
E 12
 *
E 11
D 20
 *	%W% (Berkeley) %G%
E 20
I 20
 *      %W% (Berkeley) %G%
 *	$Id: netdb.h,v 4.9.1.2 1993/05/17 09:59:01 vixie Exp $
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
E 20
 */

I 18
#ifndef _NETDB_H_
#define _NETDB_H_

E 18
I 14
#define	_PATH_HEQUIV	"/etc/hosts.equiv"
#define	_PATH_HOSTS	"/etc/hosts"
#define	_PATH_NETWORKS	"/etc/networks"
#define	_PATH_PROTOCOLS	"/etc/protocols"
#define	_PATH_SERVICES	"/etc/services"

E 14
E 2
/*
D 14
 * Structures returned by network
 * data base library.  All addresses
 * are supplied in host order, and
 * returned in network order (suitable
 * for use in system calls).
E 14
I 14
 * Structures returned by network data base library.  All addresses are
 * supplied in host order, and returned in network order (suitable for
 * use in system calls).
E 14
 */
struct	hostent {
	char	*h_name;	/* official name of host */
	char	**h_aliases;	/* alias list */
	int	h_addrtype;	/* host address type */
	int	h_length;	/* length of address */
D 3
	char	*h_addr;	/* address */
E 3
I 3
D 13
	char	**h_addr_list;	/* list of addresses from name server */
D 4
#define	h_addr	h_addr_list[0]; /* address, for backward compatiblity */
E 4
I 4
#define	h_addr	h_addr_list[0]	/* address, for backward compatiblity */
E 13
I 13
	char	*h_addr;	/* address */
E 13
E 4
E 3
};

/*
 * Assumption here is that a network number
D 20
 * fits in 32 bits -- probably a poor one.
E 20
I 20
 * fits in an unsigned long -- probably a poor one.
E 20
 */
struct	netent {
D 8
	char	*n_name;	/* official name of net */
	char	**n_aliases;	/* alias list */
	int	n_addrtype;	/* net address type */
	int	n_net;		/* network # */
E 8
I 8
	char		*n_name;	/* official name of net */
	char		**n_aliases;	/* alias list */
	int		n_addrtype;	/* net address type */
	unsigned long	n_net;		/* network # */
E 8
};

struct	servent {
	char	*s_name;	/* official service name */
	char	**s_aliases;	/* alias list */
	int	s_port;		/* port # */
	char	*s_proto;	/* protocol to use */
};

struct	protoent {
	char	*p_name;	/* official protocol name */
	char	**p_aliases;	/* alias list */
	int	p_proto;	/* protocol # */
};

D 15
struct hostent	*gethostbyname(), *gethostbyaddr(), *gethostent();
struct netent	*getnetbyname(), *getnetbyaddr(), *getnetent();
struct servent	*getservbyname(), *getservbyport(), *getservent();
struct protoent	*getprotobyname(), *getprotobynumber(), *getprotoent();
I 6

E 15
/*
 * Error return codes from gethostbyname() and gethostbyaddr()
I 11
 * (left in extern int h_errno).
E 11
 */

D 10
extern  int h_errno;	

E 10
D 11
#define	HOST_NOT_FOUND	1 /* Authoritive Answer Host not found */
E 11
I 11
#define	HOST_NOT_FOUND	1 /* Authoritative Answer Host not found */
E 11
#define	TRY_AGAIN	2 /* Non-Authoritive Host not found, or SERVERFAIL */
#define	NO_RECOVERY	3 /* Non recoverable errors, FORMERR, REFUSED, NOTIMP */
I 7
D 9
#define NO_ADDRESS	4 /* Valid host name, no address, look for MF record */
E 9
I 9
D 10
#define NO_ADDRESS	4 /* Valid host name, no address, look for MX record */
E 10
I 10
D 11
#define	NO_ADDRESS	4 /* Valid host name, no address, look for MX record */
E 11
I 11
#define	NO_DATA		4 /* Valid name, no data record of requested type */
#define	NO_ADDRESS	NO_DATA		/* no address, look for MX record */
I 15

#include <sys/cdefs.h>

__BEGIN_DECLS
void		endhostent __P((void));
void		endnetent __P((void));
void		endprotoent __P((void));
void		endservent __P((void));
D 16
struct hostent	*gethostbyaddr __P((const void *, int, int));
struct hostent	*gethostbyname __P((const char *));
E 16
I 16
struct hostent	*gethostbyaddr __P((const char *, int, int));
D 19
struct hostent	*gethostbyname __P((char *));
E 19
I 19
struct hostent	*gethostbyname __P((const char *));
E 19
E 16
D 17
/* struct hostent *gethostent __P((void)); */
E 17
I 17
D 20
struct hostent *gethostent __P((void));
E 20
I 20
struct hostent	*gethostent __P((void));
E 20
E 17
struct netent	*getnetbyaddr __P((long, int)); /* u_long? */
struct netent	*getnetbyname __P((const char *));
struct netent	*getnetent __P((void));
struct protoent	*getprotobyname __P((const char *));
struct protoent	*getprotobynumber __P((int));
struct protoent	*getprotoent __P((void));
struct servent	*getservbyname __P((const char *, const char *));
struct servent	*getservbyport __P((int, const char *));
struct servent	*getservent __P((void));
void		herror __P((const char *));
I 20
char		*hstrerror __P((int));
E 20
void		sethostent __P((int));
/* void		sethostfile __P((const char *)); */
void		setnetent __P((int));
void		setprotoent __P((int));
void		setservent __P((int));
__END_DECLS
I 18

#endif /* !_NETDB_H_ */
E 18
E 15
E 11
E 10
E 9
E 7
E 6
E 1
